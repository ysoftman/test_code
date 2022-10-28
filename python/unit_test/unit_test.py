# -*- coding: utf-8 -*-
# author : ysoftman
# title : unit test
# import sys
import unittest

# unittest.Test 를 상속받아 클래스 생성
class mytest(unittest.TestCase):
    # test 로 시작하는 함수 생성
    def test_case1(self):
        a = 10
        b = 10
        c = a + b
        # c = 20이면 테스트 성공, 아니면 테스트 실패
        self.assertEqual(c, 20)

    def test_case2(self):
        a = 1
        b = 2
        c = a + b
        self.assertEqual(c, 3)

    def test_case3(self):
        str = "ysoftman"
        # str 에 a 가 있어야 한다.
        self.assertIn("a", str)


if __name__ == "__main__":
    # 유닛테스트 시작
    # verbosity=2 테스트 처리 내용 자세히 출력
    unittest.main(verbosity=2)
