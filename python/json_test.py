# -*- coding: utf-8 -*-
# python version : 3.x
# author: ysoftman
# desc : json 파싱
import os
import json
import sys

# python 2.x 한글 파일 저장을 위해 필요
# python 3.x 에서는 필요 없음
# reload(sys)
# sys.setdefaultencoding('utf-8')

# 인코딩 상태 확인
print(("sys.stdin.encoding:", sys.stdin.encoding))
print(("sys.stdout.encoding:", sys.stdout.encoding))


strJson = '''
{
    "obj1" : {
        "key1": "aaa",
        "key2": 123
    },
    "obj2" : {
        "key1": "bbb-한글이 들어있습니다.",
        "key2": 9999,
        "arr" : [ "apple","lemon","banana" ]
    }
}
'''

outfile = os.path.basename(__file__)
outfile = outfile.split('.')[0]
outfile = outfile + "_out.json"
print("outfile:",outfile)

def parse_json():
    # json 스트링 로드(파싱)
    # python 2.x
    # utf-8 외 euc-kr 등 2개 이상의 인코딩값들이 들어 있을 경우 무시한다.
    # unicodedstrJson = unicode(strJson, errors='ignore')
    # python 3.x
    unicodedstrJson = strJson
    jsonData = json.loads(unicodedstrJson)

    # 해당 키 출력
    print("jsonData['obj1']['key1']:", jsonData['obj1']['key1'])
    print("jsonData['obj1']['key2']:", jsonData['obj1']['key2'])
    print("jsonData['obj2']['key1']:", jsonData['obj2']['key1'])
    print("jsonData['obj2']['key2']:", jsonData['obj2']['key2'])

    # 키 인덱싱으로 값 변경
    jsonData['obj1']['key1'] = 'ysoftman'

    # 탐색
    for obj in jsonData:
        print("obj:", obj)
        # json object -> python dict 타입
        print(type(jsonData[obj]))
        for key, value in jsonData[obj].items():
            print("key: {}  value: {}".format(key, value))
            # json array -> python list 타입
            # if type(value) == 'list':
            # 또는
            if isinstance(value, list):
                print("array{} value:{}".format(type(value), value))
                for l in value:
                    print(l)

    # file 로 쓰기
    print("outfile :", outfile)
    # python 2.x
    # 참고 https://docs.python.org/2/library/json.html
    # fp = open(outfile, mode='wb')
    # json 파일에 한글 \uXXX 로 escape 되어 기록되면 ensure_ascii=Flase로 설정
    fp = open(outfile, mode='w')
    jsonDumps = json.dumps(jsonData, indent=2, ensure_ascii=False)
    print("jsonDumps--->", jsonDumps)
    fp.write(jsonDumps)
    fp.close()

    # 출력된 json 파일 읽기
    print("\n\nload from json file.")
    fp = open(outfile, 'rb')
    # fromJSONFile = json.load(fp, encoding='utf-8')
    fromJSONFile = json.load(fp)
    print("fromJSONFile['obj1']['key1']:", fromJSONFile['obj1']['key1'])
    print("fromJSONFile['obj1']['key2']:", fromJSONFile['obj1']['key2'])
    print("fromJSONFile['obj2']['key1']:", fromJSONFile['obj2']['key1'])
    print("fromJSONFile['obj2']['key2']:", fromJSONFile['obj2']['key2'])

    # key3 필드가 없으면
    if fromJSONFile['obj2'].get('key3') == None:
        print("fromJSONFile['obj2']['key3'] is null")
    # key3 필드가 없으면 0 값으로 대체
    print("set 0 if null field, fromJSONFile['obj2'].get('key3', 0)", fromJSONFile['obj2'].get(
        'key3', 0))

    # json.load 로 읽은 데이터는 u(유니코드 한글이 깨져 출력된다.)
    print("fromJSONFile:\n", fromJSONFile)
    # json.load 로 fp 는 fflush/file pointer 가 EOF 로 간것으로 추측, 따라서 다시 오픈해야한다.
    fp = open(outfile, 'rb')
    # 그냥 파일을 읽으면 한글이 깨지 않고 그대로 나온다.
    print("fp.read():\n", fp.read())
    fp.close()

    # obj1 만 가져오고
    newjson = {}
    newjson['obj1'] = fromJSONFile['obj1']
    newjson['version'] = "v1.0"
    # object array 만들기
    newjson['objarr'] = []
    newjson['objarr'].append({"name":"lemon", "num":123})
    newjson['objarr'].append({"name":"apple", "cost":123, "desc":"good!"})
    print("newjson:", newjson)
    fp = open(outfile, 'w')
    jsonDumps = json.dumps(newjson, indent=2, ensure_ascii=False)
    print("jsonDumps--->", jsonDumps)
    fp.write(jsonDumps)
    fp.close()


if __name__ == '__main__':
    if os.path.exists(outfile):
        os.remove(outfile)

    parse_json()
