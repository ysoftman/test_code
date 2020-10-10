# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : sort json test
# import sys
import json

# python 2.x 에서만 unicode 로 변경이 필요하다.
# reload(sys)
# sys.setdefaultencoding('utf-8')

jsonstr = """
{
  "title": "ysoftman",
  "data": [
    {
      "name": "bill",
      "uptime": 30
    },
    {
      "name": "james",
      "uptime": 10
    },
    {
      "name": "lina",
      "uptime": 20
    }
  ]
}
"""

# python 2.x 에서만 unicode 로 변경이 필요하다.
# jsonstr = unicode(jsonstr, errors='ignore')

data = json.loads(jsonstr)
print(data)
for obj in data['data']:
    print(obj['name'], obj['uptime'])


# data 부분 uptime 필드 기준으로 내림차순
result = sorted(data['data'], key=lambda x: x['uptime'], reverse=True)
print(result[0]['name'])
