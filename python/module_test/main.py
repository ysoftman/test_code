import sub1.module1 as mo1
import sub2.module2 as mo2

if __name__ == "__main__":
    mo1.module1_aaa()
    mo2.module2_bbb()
    print(__file__)
    print(__name__)

# main.py 경로에서 실행
# main test
# python main.py
#
# module test
# python -m sub1.module1
# python -m sub2.module2
