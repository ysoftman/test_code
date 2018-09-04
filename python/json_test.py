# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : json 파싱해가
import os
import json


import sys

# 한글 파일 저장을 위해 필요
reload(sys)
sys.setdefaultencoding('utf-8')


strJson = '''
{
    "obj1" : {
        "key1": "aaa",
        "key2": 123
    },
    "obj2" : {
        "key1": "bbb-한글이 들어있습니다.",
        "key2": 9999
    }
}
'''


def parse_json():
    # json 스트링 로드(파싱)
    data = json.loads(strJson)

    # 해당 키 출력
    print (data['obj1']['key1'])
    print (data['obj1']['key2'])
    print (data['obj2']['key1'])
    print (data['obj2']['key2'])

    # 키 인덱싱으로 값 변경
    data['obj1']['key1'] = 'ysoftman'

    # 탐색
    for obj in data:
        print obj
        for key, value in data[obj].items():
            print key, value

    # file 로 쓰기
    outfile = os.path.basename(__file__)
    outfile = outfile.split('.')[0]
    outfile = outfile + "_out.json"
    print "outfile :", outfile
    fp = file(outfile, 'wb')
    # 참고 https://docs.python.org/2/library/json.html
    # json.dump(data, fp, indent=2) # json 파일에 한글 \uXXX 로 escape 되어 기록된다.
    json.dump(data, fp, indent=2, ensure_ascii=False)
    fp.close()


if __name__ == '__main__':
    parse_json()
