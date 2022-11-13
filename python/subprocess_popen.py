import subprocess

# subprocess.Popen 으로 실행하기
# 참고로 os.popen 은 python 2.6 부터 deprecated 되었다.
# https://docs.python.org/2/library/os.html
args = ["ls", "-1"]
output = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
stdout, stderr = output.communicate()
print("[stdout]\n", stdout)
print("[stderr]\n", stderr)
# 라인 구분하여 리스트화 시키기
lines = str(stdout).split("\n")
for i in lines:
    print("line=" + i)
