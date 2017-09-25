# -*- coding: utf-8 -*-
''''
title: get photo exif information
author: ysoftman
python version : 2.x


prerequisite:
(sudo) pip install exifread

doc:
https://pypi.python.org/pypi/ExifRead
'''
import glob
import exifread


def get_exif():
    for fn in glob.glob("*.jpg"):
        f = open(fn, 'rb')
        tags = exifread.process_file(f)
        exifdata = {}
        for tag in tags.keys():
            if tag == 'Image DateTime':
                temp = str(tags[tag])
                temp = temp.replace(' ', '-')
                exifdata['DateTime'] = temp
            elif tag == 'GPS GPSLatitude':
                temp = str(tags[tag])
                exifdata['Latitude'] = temp
            elif tag == 'GPS GPSLongitude':
                temp = str(tags[tag])
                exifdata['Longitude'] = temp

        print fn, exifdata['DateTime'], exifdata['Latitude'], exifdata['Longitude']


if __name__ == '__main__':
    get_exif()
