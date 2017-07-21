# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : gzip test 

import gzip

if __name__ == '__main__':
    # gz 압축 파일 생성
    content = "my name is byoung hoon, yoon."
    fp = gzip.open('gzip_file.gz','wb')
    fp.write(content)
    fp.close()

    # gz 압축 파일 읽기
    fp2 = gzip.open('gzip_file.gz','rb')
    data = fp2.read()
    print data 
    fp2.close()
