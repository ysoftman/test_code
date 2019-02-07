# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : 파일 다운로드
import urllib2


def downloadfile(url, outfile):
    r = urllib2.urlopen(url)
    fp = open(outfile, "wb")
    fp.write(r.read())
    fp.close()


if __name__ == "__main__":
    downloadfile("http://www.google.com", "url_download_file.out")
