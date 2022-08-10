# ysoftman
# locals() test
def print_locals():
    # 이 위치에서는 __name__ 키가 없음
    print(locals())
    # 로컬 변수 추가
    a = 123
    b = "lemon"
    print(locals())
    # **으로 a, b 키값만 가져올 수 있다.
    print("{a} {b}".format(**locals()))


# 현재 로컬 symbol 테이블(dictionary)을 담고 있다.
# 이 위치에서는 __name__ 키가 있음
print("{__name__}".format(**locals()))
print_locals()
