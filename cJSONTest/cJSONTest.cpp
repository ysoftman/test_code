#include <iostream>
#include <string>

#include <Windows.h>

#include "cJSON.h"

// ysoftman
// JSON 문서 http://www.json.org
// cJSON http://sourceforge.net/projects/cjson/
// cJSON 사용 예제
int main()
{
#if defined(WIN32) || defined(WIN64)
#ifdef _DEBUG
#include <crtdbg.h>
	// _CRTDBG_ALLOC_MEM_DF ==> _CLIENT_BLOCK 에 메모리를 할당에 대해서 덤프
	// _CRTDBG_LEAK_CHECK_DF ==> 프로그램이 종료될 때 자동으로 _CrtDumpMemoryLeaks() 를 호출하여 메모리 누수시 덤프
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// 해제 안되는 new 의 파일과 라인수를 파악한다.
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
	// 메모리 누수시 블록숫자값(출력창의{1234})을 주면 메모리 공간을 확보하는 시점에 브레이크포인트가 걸린다.
	_CrtSetBreakAlloc(3532);
#endif
#endif

	std::string strFileName = "json_sample.txt";
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

