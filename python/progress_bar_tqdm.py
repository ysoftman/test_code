# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : tqdm progress bar test


# tqdm
# https://github.com/tqdm/tqdm
# pip install tqdm aiofiles aiohttp
from tqdm import tqdm
import requests, time, os
import asyncio, aiofiles, aiohttp


def sample():
    for x in tqdm(["a", "b", "c", "d"]):
        time.sleep(0.2)

    for x in tqdm(range(10)):
        time.sleep(0.1)

    pbar = tqdm(["a", "b", "c", "d"])
    for x in pbar:
        time.sleep(0.2)
        # 현재 진행중인 x 왼쪽에 설명 표시
        pbar.set_description(f"Processing {x}")


def download_test(url):
    # 받을 전체 크기 파악
    response = requests.head(url)
    # print(response.headers)
    if response.headers.get("Content-Length") == None:
        print(f"[HEAD] can't find Content-Length header")
    else:
        content_length = int(response.headers.get("Content-Length"))
        print(f"[HEAD] Content-Length:{content_length}")

    response = requests.get(url, stream=True)
    if response.headers.get("Content-Length") == None:
        print(f"[GET] can't find Content-Length header")
    else:
        content_length = int(response.headers.get("Content-Length"))
        print(f"[GET] Content-Length:{content_length}")

    # unit : byte (디폴트: 아이템(it))
    # unit_scale : 단위가 커지면 자동으로 단위 변경
    # total : 전체 크기
    # desc : 왼쪽에 설명 표시
    # mininterval: 최소 갱신 주기
    pbar = tqdm(
        unit="B",
        unit_scale=True,
        total=content_length,
        desc="[download]" + url,
        mininterval=0.1,
    )
    # iter_content() 는 요청 응답을 chunk 단위로 반복한다.
    # 응답 받은 만큼 pbar 업데이트하여 진행(request 시 stream=True 필요)
    received = 0
    for chunk in response.iter_content(chunk_size=1024 * 100):
        # content_length 넘어가도록 업데이트되면 progressbar가 지워지는것을 방지
        if received + len(chunk) <= content_length:
            pbar.update(len(chunk))
            received += len(chunk)
    pbar.update(content_length - received)


async def read_file(filename):
    file_size = os.path.getsize(filename)
    # unit : byte (디폴트: 아이템(it))
    # unit_scale : 단위가 커지면 자동으로 단위 변경
    # total : 전체 크기
    # desc : 왼쪽에 설명 표시
    # mininterval: 최소 갱신 주기
    pbar = tqdm(
        unit="B",
        unit_scale=True,
        total=file_size,
        desc="[upload]" + filename,
        mininterval=0.1,
    )
    chunk_size = int(file_size / 100)
    read_chunk_size = 0
    async with aiofiles.open(filename, "rb") as f:
        while read_chunk_size < file_size:
            chunk = await f.read(chunk_size)
            # 현재 읽은 데이터 리턴
            yield chunk
            read_chunk_size += len(chunk)
            pbar.update(len(chunk))


# aiohttp.ClientSession
# <https://docs.aiohttp.org/en/stable/client_quickstart.html>
# <https://docs.aiohttp.org/en/stable/client_quickstart.html#streaming-uploads>
async def upload_test(aiohttpSession, url, filename):
    try:
        basic_auth = aiohttp.BasicAuth(login="ysoftman", password="test123")
        # default timeout is 300 seconds(5min), None 이나 0으로 하면 타임아웃 없음
        # https://github.com/aio-libs/aiohttp/pull/5529/files
        timeout = aiohttp.ClientTimeout(total=None)
        # set header below to hang problem with wsgidav server(https://github.com/mar10/wsgidav)
        # https://yoonbh2714.blogspot.com/2022/07/webdav-chunked-size.html
        # headers = {}
        # headers["X_EXPECTED_ENTITY_LENGTH"] = repr(os.fstat(fileobj.fileno()).st_size) # fileobject case
        # headers["X_EXPECTED_ENTITY_LENGTH"] = repr(os.path.getsize(filename))
        # headers["User-Agent"] = "Darwin"
        # async for d in read_file(filename):
        #     print(d)
        # read_file 로 읽은 데이터만큼 전송
        async with aiohttpSession.put(
            url=url, auth=basic_auth, timeout=timeout, data=read_file(filename)
        ) as res:
            return res
    except Exception as e:
        print(e)


async def upload_main():
    aiohttpSession = aiohttp.ClientSession()
    # 세션은 한번 생성하고 upload_main() 가 종료될때까지 재사용한다.
    async with aiohttp.ClientSession() as aiohttpSession:
        # 비동기로 chunk 만큼 파일 데이터를 읽어가며 업로드한다.
        for i in range(3):
            await upload_test(
                aiohttpSession, "https://httpbin.org/put", "ysoftman_10MB"
            )


if __name__ == "__main__":
    sample()
    download_test("https://www.youtube.com")
    # 업로드 테스트용 더미 파일 생성
    os.system("dd if=/dev/urandom of=ysoftman_10MB bs=1024*1024 count=10")
    # 다음 구문은 asyncio.run() 로 대체가능
    # loop = asyncio.get_event_loop()
    # loop.run_until_complete(upload_main())
    asyncio.run(upload_main())
    os.remove("ysoftman_10MB")
