import sub1.module1 as mo1


def module2_bbb():
    print("module2_bbb()")


if __name__ == "__main__":
    mo1.module1_aaa()
    module2_bbb()
    print(__file__)
    print(__name__)
