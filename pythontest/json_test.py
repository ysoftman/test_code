# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : json 파싱해가

import json

strJson = '''
{
    "obj1" : {
        "key1": "aaa",
        "key2": 123
    },
    "obj2" : {
        "key1": "bbb",
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
    fp = file('data.json', 'wb')
    json.dump(data, fp, indent=2)
    fp.close()


if __name__ == '__main__':
    parse_json()
