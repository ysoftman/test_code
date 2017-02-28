# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : ssh 접속 체크
import sys
import argparse
import subprocess
import time

def check_connection_via_ssh(user, host):
    cmd = "hostname"
    ssh = subprocess.Popen(["ssh", "%s@%s" % (user, host), cmd],
            shell=False, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    result = ssh.stdout.readlines()
    if result == []:
        error = ssh.stderr.readlines()
        print >> sys.stderr, "ERROR: %s" % error
        return False
    else:
        print "OK:", result
        return True
    

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    # 사용할 수 있는 아큐먼트 키 추가(자동으로 usage, -h help 포맷 생성)
    # help : -h 시 표시할 문구
    parser.add_argument("-host", required=True, help = "host name")
    parser.add_argument("-user", required=True, help = "user")

    args = parser.parse_args()
    
    # 주기적으로 접속 반복 
    # for i in range(10):
    i = 1
    while True:
        print "%3d " % i,
        if check_connection_via_ssh(args.user, args.host) == False:
            break
        time.sleep(0.1)
        i = i + 1
