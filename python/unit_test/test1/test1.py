# -*- coding: utf-8 -*-
# author : ysoftman
# title : unit test
# import sys
import unittest


# unittest.Test 를 상속받아 클래스 생성
class test1(unittest.TestCase):
    def test1_case1(self):
        a = 100
        self.assertEqual(a, 100)


if __name__ == "__main__":
    # 유닛테스트 시작
    # verbosity=2 테스트 처리 내용 자세히 출력
    unittest.main(verbosity=2)
