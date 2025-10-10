# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : raise 테스트


# 사용자 예외 정의F
class MyError(Exception):
    def __init__(self, msg):
        self.msg = msg

    # str()연산 정의 메소드
    def __str__(self):
        return self.msg


def check_something(string):
    try:
        if string == "ysoftman":
            return "success"
        else:
            # 강제로 예외 발생
            # raise NotImplementedError("NotImplementedError")
            # raise Exception('raise test')
            # 사용자 정의 예외 발생F
            raise MyError("my error")
    except MyError as err:
        print("MyError exception!!!", err)
    except NotImplementedError as err:
        print("exception!!!", err)
    except Exception as err:
        print(err)
        # pass 아무것도 하지 않고 그냥 넘어간다.
        # 아무것도 없다면 에러가 발생하기 때문에 pass 로 존재만 유지
        pass
    # 무조건 수행
    finally:
        print("finally")


if __name__ == "__main__":
    print(check_something("ysoftman"))
    print(check_something("yoon"))
