////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// libjson 테스트
// json 공식 홈페이지 http://json.org
// 다운로드 http://sourceforge.net/projects/libjson/
// linux build
// unzip libjson_7.6.1.zip
// cd libjson 
// make 
// g++ libjsontest.cpp -L./libjson/ -ljson
// windows build
// 윈도우 환경에서는 제대로 테스트되지 않고 배포되는 문제가 있음
// .vcproj 열지 못하는 문제 발생 -> .vcproj xml 형식이 잘못된 곳 수정
// libjson 빌드시 에러 발생 -> libjson.h 43 번째 라인 주석처리
// 테스트 빌드시 에러 발생 -> jsondefs.h 159 번째 라인 주석처리
////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <sstream>	// istringstream, stringstream, ostringstream, stringbuf
#include <string>
#include <vector>

#include "./libjson/libjson.h"

using namespace std;

#if defined(_WIN32) || defined(_WIN64)
#if defined(_DEBUG)
#define JSON_DEBUG
#pragma comment(lib, "./libjson/statLibJson-mdd")
#else
#pragma comment(lib, "./libjson/statLibJson-md")
#endif
#else // linux
#if defined(_DEBUG)
#pragma comment(lib, "./libjson/libjson")
#else
#pragma comment(lib, "./libjson/libjson")
#endif
#endif

/**
*	@brief						JSON 의 모든 경로와 값을 추출한다.
*	@author						윤병훈
*	@param			pNode		JSON 형식의 노드
*	@param			output		찾은 모든 경로를 저정할 벡터
*	@param			curpath		현재위치까지의 경로를 저장할 벡터
*	@param			depth		stack overflow 방지를 위한 카운트
*	@return						None
*/
void ParseJsonToGetAllPath(JSONNODE *pNode, vector<string> &output, vector<string> curpath, int depth)
{
	if (depth > 20)
	{
		printf("ParseJsonToGetAllPath() stack overflow ... depth %d", depth);
		return;
	}
	if (pNode == NULL)
	{
		return;
	}

	string temp;
	JSONNODE_ITERATOR iter = json_begin(pNode);
	while (iter != json_end(pNode))
	{
		// 현재 위치의 경로 설정
		json_char *cur_key = json_name(*iter);
		if (cur_key != NULL && strlen(cur_key) > 0)
		{
			curpath.push_back(cur_key);
		}
		json_free(cur_key);

		char type = json_type(*iter);
		// 현재 위치가 배열이나 노드라면 재귀호출한다.
		if (type == JSON_ARRAY || type == JSON_NODE)
		{
			ParseJsonToGetAllPath(*iter, output, curpath, depth+1);

			if (iter+1 == json_end(pNode))
			{
				return;
			}
			// 다음 위치가 배열이나 자식노드라면 curpath 를 유지해야 한다.
			char nexttype = json_type(*(iter+1));
			if (!(curpath.empty()) && nexttype != JSON_ARRAY && nexttype != JSON_NODE)
			{
				curpath.pop_back();
			}
		}
		else
		{
			temp.clear();
			// curpath 의 원소값의 순서로 현재 경로를 파악한다.
			vector<string>::iterator curpathiter;
			for (curpathiter = curpath.begin(); curpathiter != curpath.end(); curpathiter++)
			{
				temp += *curpathiter;
				if (curpathiter+1 != curpath.end())
				{
					temp += ".";
				}
			}
			temp += ":";
			if (type == JSON_STRING)
			{
				json_char *node_str_value = json_as_string(*iter);
				temp += node_str_value;
				json_free(node_str_value);
			}
			else if (type == JSON_NUMBER)
			{
				json_int_t node_int_value = json_as_int(*iter);
				ostringstream ostr;
				ostr.str("");
				// 스트링 타입으로 변환
				ostr << node_int_value;
				temp += ostr.str();
			}
			else if (type == JSON_NULL)
			{
				temp += "0";
			}
			output.push_back(temp);
			if (!(curpath.empty()))
			{
				curpath.pop_back();
			}
		}

		iter++;
	}
	return;
}

int main()
{
	string strJSON = "{\"이름\": \"윤병훈\", \
					 \"나이\": 30, \
					 \"성별\": \"남\", \
					 \"친구\": [\"홍길동\", \"엘리자베스\"], \
					 \"위치\": \"태양계 지구\" }";

	// json 파싱
	JSONNODE *pNode = json_parse(strJSON.c_str());

	// json 에서의 모든 path와 value 를 추출한다.
	vector<string> vecTemp;
	vector<string> vecPath;
	vector<string>::iterator iter;
	ParseJsonToGetAllPath(pNode, vecPath, vecTemp, 0);
	for (iter = vecPath.begin(); iter != vecPath.end(); ++iter)
	{
		printf("%s\n", iter->c_str());
	}

	json_delete(pNode);

	return 0;
}
