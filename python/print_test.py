dic1 = {"apple": 1000, "lemon": 2000, "banana": 0}
print(dic1)

for k, v in dic1.items():
    # 왼쪽10칸 차지, 오늘쪽 8칸차지, 구분자 "="사용
    print(k.ljust(10), str(v).rjust(8), sep="=")

for i in range(1, 11):
    # 0으로 패딩해서 7자리 맞추기
    print(str(i).zfill(7))

for i in range(1, 11):
    # 오른쪽기준으로 10자리 _ 로 채우기
    print("{0:_>10}".format(i))

for i in range(1, 11):
    # 왼쪽기준으로 10자리 * 로 채우기
    print("{0:*<10}".format(i))

for i in range(1, 11):
    # 오른쪽기준으로 10자리 공백으로 채우고, 양수+ 음수- 표시
    print("{0:>+10}".format(i))
    print("{0: >+10}".format(i * -1))

for i in range(1, 11):
    # 10자리 기준으로 가운데 정렬
    print("{0:^10}".format(i))

# , 로 3자리수마다 표현, 양수+ 음수- 표시
print("{0:>+,}".format(10000000000))
print("{0:>+,}".format(-10000000000))


sample_title = "number"
sample_number = 123
# % 포맷(C style, 가독성 나쁘고 타입 제한으로 비추)
print("%s %d" % (sample_title, sample_number))
# python 2.7+ (이전 버전과 호환을 위해 사용, 비추천)
print("{0} {max_len}".format(sample_title, max_len=sample_number))
# 3.6 부터 https://peps.python.org/pep-0498/ f-string (추천)
print(f"{sample_title} {sample_number}")
