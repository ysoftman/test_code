# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : tqdm progress bar test


# tqdm
# https://github.com/tqdm/tqdm
# pip install tqdm aiofiles aiohttp
import chunk
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
    chunk_size = 1024 * 1024
    read_data_size = 0
    async with aiofiles.open(filename, "rb") as f:
        data = await f.read(chunk_size)
        while data:
            # 현재 읽은 데이터 리턴
            yield data
            if read_data_size + len(data) <= file_size:
                pbar.update(len(data))
                read_data_size += len(data)
            data = await f.read(chunk_size)
            # await asyncio.sleep(0.5)
    pbar.update(file_size - read_data_size)


async def upload_test(url, filename):
    try:
        basic_auth = aiohttp.BasicAuth(login="ysoftman", password="test123")
        async with aiohttp.ClientSession(auth=basic_auth) as session:
            # read_file 로 읽은 데이터만큼 전송
            async with session.put(url=url, data=read_file(filename)) as res:
                return res
    except Exception as e:
        print(e)


if __name__ == "__main__":
    sample()
    download_test("https://www.youtube.com")
    # 업로드 테스트용 더미 파일 생성
    os.system("dd if=/dev/urandom of=ysoftman_10MB bs=1024 count=10000")
    # 비동기로 chunk 만큼 파일 데이터를 읽어가며 업로드한다.
    asyncio.run(upload_test("https://httpbin.org/put", "ysoftman_10MB"))
    os.remove("ysoftman_10MB")
