# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : tqdm progress bar test


# tqdm
# https://github.com/tqdm/tqdm
# pip install tqdm

from tqdm import tqdm
import requests, time, os, shutil


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
        desc=url,
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


if __name__ == "__main__":
    sample()
    download_test("https://www.youtube.com")
