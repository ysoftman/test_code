# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.6
# desc : asyncio test
import time
import asyncio


# native 코루틴
async def task(param1):
    if param1 == "lemon":
        await asyncio.sleep(0.5)
    if param1 == "apple":
        await asyncio.sleep(1)
    print(param1)
    return param1


async def start():
    # 비동기로 실행할 task 리스트 생성
    futures = []
    for fruit in ["lemon", "apple", "orange"]:
        mytask = asyncio.ensure_future(task(fruit))
        futures.append(mytask)

    # print(futures)

    # futures 가 모두 끝날때까지 기다려서 결과를 취합해 출력
    result = await asyncio.gather(*futures)
    print(result)


begin = time.time()
# 이벤트 루프를 생성해서 실행
# loop = asyncio.get_event_loop()
# loop.run_until_complete(start())
# loop.close()
# 위 과정을 간단하게 run 으로 대신할 수 있다.
asyncio.run(start())
end = time.time()
print(f"elapsed: {end - begin}s")


# 비동기 함수라도 순차적으로 실행하면 동기처럼 오래걸린다.
# begin = time.time()
# for fruit in ["lemon", "apple", "orange"]:
#     asyncio.run(task(fruit))
# end = time.time()
# print(f"elapsed: {end-begin}s")
