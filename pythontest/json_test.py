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

if __name__ == '__main__':
    parse_json()

