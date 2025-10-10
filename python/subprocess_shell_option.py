import os
import subprocess


# subprcoess shell=True 로 명령을 실행할때
# 경로 인자로 single quote(')등이 있을때 \'와 같이 별도 이스케이프 하지 않아야 한다.
# 하지만 ' " 동시에 있는경우 이스케이스 \ 자체도 이스케이프 필요
def exec_Command(command, shellopt):
    # https://docs.python.org/ko/3/library/subprocess.html#popen-constructor
    # shell 인자(기본값은 False)는 셸을 실행할 프로그램으로 사용할지를 지정합니다. shell이 True이면, args를 시퀀스가 아닌 문자열로 전달하는 것이 좋습니다.
    # POSIX에서 shell=True일 때, 셸의 기본값은 /bin/sh입니다. args가 문자열이면, 문자열은 셸을 통해 실행할 명령을 지정합니다. 이것은 문자열이 프롬프트에서 입력할 때와 똑같이 포맷되어야 한다는 것을 의미합니다. 예를 들어, 스페이스가 포함된 파일명을 인용하거나 역 슬래시 이스케이핑 하는 것을 포함합니다. args가 시퀀스이면, 첫 번째 항목이 명령 문자열을 지정하고, 추가 항목은 셸 자체에 대한 추가 인자로 처리됩니다. 즉, Popen은 다음과 동등한 것을 수행합니다:
    output = subprocess.Popen(
        command, shell=shellopt, stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )
    stdout, stderr = output.communicate()
    print("[stdout]\n", stdout)
    print("[stderr]\n", stderr)


filename1 = "zzz aaa's bbb.txt"
filename2 = 'zzz aaa"s bbb.txt'
escaped_filename1 = filename1.replace("'", "\\'")
escaped_filename2 = filename2.replace('"', '\\"')
print(f"filename1:{filename1}")
print(f"filename2:{filename2}")
print(f"secaped_filename1:{escaped_filename1}")
print(f"secaped_filename2:{escaped_filename2}")

try:
    os.remove(f"{filename1}")
    os.remove(f"{filename2}")
    os.remove(f"{escaped_filename1}")
except FileNotFoundError as err:
    print("err:", err)
    pass

# shell=True 로 쉘로 실행할때는
# 이스케이프되면 이스케이프 자체가 문자열로 취급되어
# zzz aaa\'s bbb.txt 이름으로 생성된다.
exec_Command(f'touch "{escaped_filename1}"', True)

# zzz aaa\"s bbb.txt 이름으로 생성된다.
exec_Command(f"touch '{escaped_filename2}'", True)

# 이스케이스 없이 문자열을 그대로 arg 로 전달하면
# zzz aaa's bbb.txt 이름으로 생성된다.
exec_Command(f'touch "{filename1}"', True)

# 이스케이스 없이 문자열을 그대로 arg 로 전달하면
# zzz aaa's bbb.txt 이름으로 생성된다.
exec_Command(f"touch '{filename2}'", True)

# ' " 동시에 있는경우 이스케이스 \ 자체도 이스케이프 필요
# bash -c "touch zzz\'s\ \\\"a.txt"
exec_Command("touch zzz\\'s\ \\\"a.txt", True)

"""
# 실행 결과 확인
python subprocess_shell_option.py && ll zzz*
# 결과 파일 삭제
rm -f zzz*
"""
