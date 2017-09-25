# -*- coding: utf-8 -*-
''''
title: get photo exif information
author: ysoftman
python version : 2.x

prerequisite:
sudo pip install exifread

doc:
https://pypi.python.org/pypi/ExifRead
'''
import glob
import exifread


def get_exif():
    for fn in glob.glob("*.jpg"):
        f = open(fn, 'rb')
        tags = exifread.process_file(f)
        # print fn, tags
        exifdata = {}
        for tag in tags.keys():
            if tag == 'Image DateTime':
                temp = str(tags[tag])
                temp = temp.replace(' ', '-')
                exifdata['DateTime'] = temp
            elif tag == 'GPS GPSLatitudeRef':
                temp = str(tags[tag])
                exifdata['LatitudeRef'] = temp
            elif tag == 'GPS GPSLatitude':
                temp = str(tags[tag])
                temp = temp[1:]
                temp = temp[:-1]
                temp = temp.replace(', ', '-')
                exifdata['Latitude'] = temp
            elif tag == 'GPS GPSLongitude':
                temp = str(tags[tag])
                temp = temp[1:]
                temp = temp[:-1]
                temp = temp.replace(', ', '-')
                exifdata['Longitude'] = temp
            elif tag == 'GPS GPSLongitudeRef':
                temp = str(tags[tag])
                exifdata['LongitudeRef'] = temp

        # print fn, exifdata['DateTime'], exifdata['LatitudeRef'],
        # exifdata['Latitude'], exifdata['LongitudeRef'], exifdata['Longitude']

        # convert to decimal degrees for googling
        temp = exifdata['Latitude'].split('-')
        LatitudeDec = int(temp[0])
        LatitudeDec += float(temp[1]) / 60
        LatitudeDec += float(temp[2]) / (60 * 60)
        if exifdata['LatitudeRef'] == 'S':
            LatitudeDec *= -1

        temp = exifdata['Longitude'].split('-')
        LongitudeDec = int(temp[0])
        LongitudeDec += float(temp[1]) / 60
        LongitudeDec += float(temp[2]) / (60 * 60)
        if exifdata['LongitudeRef'] == 'W':
            LongitudeDec *= -1

        print fn, exifdata['DateTime'], "{0},{1}".format(LatitudeDec, LongitudeDec)


if __name__ == '__main__':
    get_exif()
