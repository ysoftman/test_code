////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// libjson �׽�Ʈ
// json ���� Ȩ������ http://json.org
// libjson http://sourceforge.net/projects/libjson/
// ������ ȯ�濡���� ����� �׽�Ʈ���� �ʰ� �����Ǵ� ������ ����
// �����쿡�� 7.6.1 �����
// .vcproj ���� ���ϴ� ���� �߻� -> .vcproj xml ������ �߸��� �� ����
// libjson ����� ���� �߻� -> libjson.h 43 ��° ���� �ּ�ó��
// �׽�Ʈ ����� ���� �߻� -> jsondefs.h 159 ��° ���� �ּ�ó��
////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <sstream>	// istringstream, stringstream, ostringstream, stringbuf
#include <string>
#include <vector>

#include "./libJson/libjson.h"

using namespace std;

#if defined(_WIN32) || defined(_WIN64)
#if defined(_DEBUG)
#define JSON_DEBUG
#pragma comment(lib, "./libJson/statLibJson-mdd")
#else
#pragma comment(lib, "./libJson/statLibJson-md")
#endif
#else // linux
#if defined(_DEBUG)
#pragma comment(lib, "libjson")
#else
#pragma comment(lib, "libjson")
#endif
#endif

/**
*	@brief						JSON �� ��� ��ο� ���� �����Ѵ�.
*	@author						������
*	@param			pNode		JSON ������ ���
*	@param			output		ã�� ��� ��θ� ������ ����
*	@param			curpath		������ġ������ ��θ� ������ ����
*	@param			depth		stack overflow ������ ���� ī��Ʈ
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
		// ���� ��ġ�� ��� ����
		json_char *cur_key = json_name(*iter);
		if (cur_key != NULL && strlen(cur_key) > 0)
		{
			curpath.push_back(cur_key);
		}
		json_free(cur_key);

		char type = json_type(*iter);
		// ���� ��ġ�� �迭�̳� ����� ���ȣ���Ѵ�.
		if (type == JSON_ARRAY || type == JSON_NODE)
		{
			ParseJsonToGetAllPath(*iter, output, curpath, depth+1);

			if (iter+1 == json_end(pNode))
			{
				return;
			}
			// ���� ��ġ�� �迭�̳� �ڽĳ���� curpath �� �����ؾ� �Ѵ�.
			char nexttype = json_type(*(iter+1));
			if (!(curpath.empty()) && nexttype != JSON_ARRAY && nexttype != JSON_NODE)
			{
				curpath.pop_back();
			}
		}
		else
		{
			temp.clear();
			// curpath �� ���Ұ��� ������ ���� ��θ� �ľ��Ѵ�.
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
				// ��Ʈ�� Ÿ������ ��ȯ
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
	string strJSON = "{\"�̸�\": \"������\", \
					 \"����\": 30, \
					 \"����\": \"��\", \
					 \"ģ��\": [\"ȫ�浿\", \"�����ں���\"], \
					 \"��ġ\": \"�¾�� ����\" }";

	// json �Ľ�
	JSONNODE *pNode = json_parse(strJSON.c_str());

	// json ������ ��� path�� value �� �����Ѵ�.
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
