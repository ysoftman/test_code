# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : sort json test
import sys
import json

reload(sys)
sys.setdefaultencoding('utf-8')

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

jsonstr = unicode(jsonstr, errors='ignore')
data = json.loads(jsonstr)
print data
for obj in data['data']:
    print obj['name'], obj['uptime']


# data 부분 uptime 필드 기준으로 내림차순
result = sorted(data['data'], key=lambda x: x['uptime'], reverse=True)
print result[0]['name']
