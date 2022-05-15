# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.6
# desc : collection(컨테이너) 중 deque 테스트

from collections import deque
import operator

# queue 를 list 로 구현할 수 있지만 pop(0) 할때 원소들이 이동해야 하기때문에 O(N) 시간복잡도가 된다.
list = [1, 2, "lemon", 10.1]
print(f"list={list}")

list.append("apple")
print(f"list={list}")

list.pop(0)
print(f"list={list}")

# 특정 위치에 삽입할 수 있지만 원소들 이동이 필요해 O(N) 시간복잡도가 된다.
list.insert(1, "ysoftman")
print(f"list={list}")


# deque(double ended queue) 를 사용하면 popleft(), insert(), appendleft 등의 추가,삭제가 O(1) 시간복잡도에 처리된다.
dq = deque([1, 2, "lemon", 10.1])
print(f"deque={dq}")

dq.append("apple")
print(f"deque={dq}")

dq.popleft()
print(f"deque={dq}")

# 앞쪽에 추가할 수 있다.
dq.appendleft("mango")
print(f"deque={dq}")

# 특정위치에 삽입
dq.insert(3, "ysoftman")
print(f"deque={dq}")
