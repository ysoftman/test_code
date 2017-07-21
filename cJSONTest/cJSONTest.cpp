#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

// ysoftman
// JSON 문서 http://www.json.org
// cJSON http://sourceforge.net/projects/cjson/
// g++ cJSON.c cJSONTest.cpp
int main()
{
	std::string strFileName = "json_sample.json";
	std::string strJson;
	
	FILE *fp = fopen(strFileName.c_str(), "r");
	if (fp == NULL)
	{
		std::cout << "Can't load ... " << strFileName  << std::endl;
		return 0;
	}

	char buff[1024];
	memset(buff, 0, sizeof(buff));
	while (fgets(buff, sizeof(buff), fp))
	{
		strJson += buff;
	}
	fclose(fp);

	
	// json 파싱
	cJSON *root = cJSON_Parse(strJson.c_str());
	if (root != NULL)
	{
		char *out = cJSON_Print(root);

		if (out != NULL)
		{
			// json 출력해보기
			std::cout << out << std::endl;
			free(out);
		}
		// json 삭제
		cJSON_Delete(root);
	}

	return 0;
}
