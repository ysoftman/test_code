dic1 = {"apple":1000, "lemon":2000, "banana":0}
print(dic1)

for k, v in dic1.items():
    # 왼쪽10칸 차지, 오늘쪽 8칸차지, 구분자 "="사용
    print(k.ljust(10), str(v).rjust(8), sep="=")

for i in range(1,11):
    # 0으로 패딩해서 7자리 맞추기
    print(str(i).zfill(7))

for i in range(1,11):
    # 오른쪽기준으로 10자리 _ 로 채우기
    print("{0:_>10}".format(i))

for i in range(1,11):
    # 왼쪽기준으로 10자리 * 로 채우기
    print("{0:*<10}".format(i))

for i in range(1,11):
    # 오른쪽기준으로 10자리 공백으로 채우고, 양수+ 음수- 표시
    print("{0: >+10}".format(i))
    print("{0: >+10}".format(i*-1))

# , 로 3자리수마다 표현, 양수+ 음수- 표시
print("{0:>+,}".format(10000000000))
print("{0:>+,}".format(-10000000000))
