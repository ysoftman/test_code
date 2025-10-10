# CLICK(Command Line Interface Creation Kit)
# pip install click
import click

"""
# test
python click_test.py
python click_test.py aaa
python click_test.py bbb
python click_test.py aaa func1 --help
python click_test.py aaa func1
python click_test.py aaa func1 --count 2
python click_test.py aaa func1 --count 2 --fruit lemon
python click_test.py aaa func2
python click_test.py bbb func2
"""


# click 명령어어 등록, argument, option 이 빠지면 기본 help 표시
@click.command()
# argument 등록
@click.argument("name", default="default")
# option 등록
@click.option("--count", type=int, help="iterate count", default=1)
@click.option("--fruit", type=click.Choice(["lemon", "apple", "orange"]))
def func1(name, count, fruit):
    print("name:", name)
    for i in range(count):
        print(f"count:{i}, fruit:{fruit}")


@click.command()
def func2():
    print("func2")


# main 이라는 그룹생성
@click.group()
def main():
    pass


# main 그룹에 포함할 커맨드
@main.group()
def aaa():
    pass


# main 그룹에 포함할 커맨드
@main.group()
def bbb():
    pass


# aaa 커멘드에 추가할 커맨드(함수)
aaa.add_command(func1)
aaa.add_command(func2)

# bbb 커멘드에 추가할 커맨드(함수)
bbb.add_command(func2)

if __name__ == "__main__":
    main()
