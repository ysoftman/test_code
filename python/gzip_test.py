# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : gzip test

import gzip

if __name__ == "__main__":
    # gz 압축 파일 생성
    content = "my name is byoung hoon, yoon."
    fp = gzip.open("gzip_file.gz", "wb")
    # python 2.x
    fp.write(bytes(content))
    # python 3.x
    # fp.write(bytes(content, 'utf-8'))
    fp.close()

    # gz 압축 파일 읽기
    fp2 = gzip.open("gzip_file.gz", "rb")
    data = fp2.read()
    print(data)
    fp2.close()
