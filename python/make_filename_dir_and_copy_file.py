# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : 현재 경로에 각 파일명의 디렉토리 만들고 파일 복사하기


import os
import shutil


def show_current_files():
    # 현재 경로
    print("os.getcwd() = ", os.getcwd())

    filelist = os.listdir(os.getcwd())
    # 현재 경로 파일 리스트
    print("os.listdir(os.getcwd()) = ", filelist)

    # 파일명과 확장자 구분
    for i in filelist:
        file = i.split(".")
        n = len(file)
        # print("len(file) = ", n)
        if n >= 2:
            # print("file = ", file[1])
            # .txt 파일만 찾기
            if file[1] == "txt":
                print("file = ", file[0])
                # 해당 파일명의 디렉토리 없으면 생성
                if not os.path.exists(file[0]):
                    os.makedirs(file[0])

                src = i
                dst = file[0]

                print("copy ", src, " to ", dst, "")
                # 파일 복사
                shutil.copy(src, dst)

                presskey = input("생성한 디렉토리를 삭제하려면 'd' 키를 누르세요.")
                print("presskey = ", presskey)
                if presskey == "d":
                    shutil.rmtree(file[0])
                    print(file[0], "디렉토리 삭제")
                else:
                    print(file[0], "디렉토리 유지")


show_current_files()
