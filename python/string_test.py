# -*- coding: utf-8 -*-
# author : ysoftman
# title : string test
# python version : 2.x 3.x


def modify_data(str):
    str = "kkk"
    print("modified")
    return str


if __name__ == "__main__":

    # 큰 따옴표 "  를 포함 시키고 싶을때
    str1 = '"ysoftman"'
    print(str1)

    # 작은 따옴표 ' 를 포함시키고 싶은 경우
    str1 = "'ysoftman'"
    print(str1)

    # 여러줄로 표현하고 싶은 경우
    str1 = "yoon\nbyoung\nhoon"
    print(str1)

    # 이스케이프 문자 없이 여러줄료 표현하고 싶은 경우
    str1 = """yoon
byoung
hoon"""
    print(str1)

    str1 = """yoon
byoung
hoon"""
    print(str1)

    # 스트링 포맷팅
    data = {"first": "bill", "second": "yoon"}
    print("{first} {second}".format(**data))
    print("{first} {second}".format(**data))

    # 스트링 복사
    str1 = "abc"
    str2 = str1
    print("str =", str1)
    print("str2 =", str2)

    str1 = "zzz"
    print("str =", str1)
    print("str2 =", str2)

    str1 = modify_data(str1)
    print("str =", str1)
    print("str2 =", str2)

    str1 = "yOOn Byoung hooN"
    print(str1)
    # 모두 소문자로
    str1 = str1.lower()
    print(str1)
    # 모두 대문자로
    str1 = str1.upper()
    print(str1)
    # 첫문자만 대문자로
    str1 = str1.capitalize()
    print(str1)
    # 시작문자 존재 체크
    # false
    print("str.startswith", str1.startswith("aaaaaaaaaaaaaaaaaaa"))
    # 0번째 위치 이후에서 체크
    print("str.startswith", str1.startswith("Yoon b"))
    # 5번째 위치 이후에서 체크
    print("str.startswith", str1.startswith("byoung", 5))
    str2 = "lemon"
    # l 로 시작하는지 체크
    print("str2.startswith", str2.startswith("l"))
    # a 또는 1 또는 l 로 시작하는지 체크
    print("str2.startswith", str2.startswith(("a", "1", "l")))
    str2 = 321
    # int -> str 로 변경해서 시작문자 체크
    print("str2.startswith", str(str2).startswith(("1", "2", "3")))
    print("str2.startswith", str(str2).startswith(("5", "9")))

    # 끝문자 존재 체크
    print(str1)
    print("str.endswith", str1.lower().endswith("hoon"))
    # 20번째 이후에서 체크
    print("str.endswith", str1.lower().endswith("hoon", 20))
    # apple,lemon,hoon 중 하나로 끝나는지 체크
    print("str.endswith", str1.endswith(("apple", "lemon", "hoon")))

    str1 = "윤\n병\n훈"
    print("str = {}".format(str1))
    # raw 문자: escape 문자의 기능이 적용되지 않고 문자 그대로 출력
    str1 = r"윤\n병\n훈"
    print("str = {}".format(str1))

    # 멀티라인에서 포맷팅
    str1 = """
        "number:{},
        "name":{}
    """.format(
        123, "ysoftman"
    )
    print("str =", str1)

    # 멀티라인에서 {} 자체를 출력하기 위해선 {{ }} 사용
    # .3f 소수점3째자리로 표현
    # , 천단위 ,로 구
    # ,.3ㄹ 천단위 ,로 구분하고 .3f 소수점3째자리로 표현
    str1 = """
    {{
        "number:{0:.3f},
        "number:{0:,},
        "number:{0:,.3f},
        "name":{1}
    }}
    """.format(
        123456789, "ysoftman"
    )
    print("str =", str1)

    # 문자열 앞,뒤 공백 제거
    str1 = "   ysoftman     "
    print("str =", str1, "okay")
    print("str =", str1.strip(), "okay")
