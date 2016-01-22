#include <iostream>
#include <string>

#include <Windows.h>

#include "cJSON.h"

// ysoftman
// JSON ���� http://www.json.org
// cJSON http://sourceforge.net/projects/cjson/
// cJSON ��� ����
int main()
{
#if defined(WIN32) || defined(WIN64)
#ifdef _DEBUG
#include <crtdbg.h>
	// _CRTDBG_ALLOC_MEM_DF ==> _CLIENT_BLOCK �� �޸𸮸� �Ҵ翡 ���ؼ� ����
	// _CRTDBG_LEAK_CHECK_DF ==> ���α׷��� ����� �� �ڵ����� _CrtDumpMemoryLeaks() �� ȣ���Ͽ� �޸� ������ ����
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// ���� �ȵǴ� new �� ���ϰ� ���μ��� �ľ��Ѵ�.
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
	// �޸� ������ ��ϼ��ڰ�(���â��{1234})�� �ָ� �޸� ������ Ȯ���ϴ� ������ �극��ũ����Ʈ�� �ɸ���.
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

	
	// json �Ľ�
	cJSON *root = cJSON_Parse(strJson.c_str());
	if (root != NULL)
	{
		char *out = cJSON_Print(root);

		if (out != NULL)
		{
			// json ����غ���
			std::cout << out << std::endl;
			free(out);
		}
		// json ����
		cJSON_Delete(root);
	}


	return 0;
}

