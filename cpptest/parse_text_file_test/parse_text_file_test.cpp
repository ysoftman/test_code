////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 텍스트 파일내용 파싱하기
// 텍스트 파일의 내용은 다음과 같은 형식으로 N 개까지 존재한다.
// filename (tab) answer_string (tab) recog_string
// 위 내용을 파싱하여 다음의 작업을 수행한다.
// answer_string 내용을 담은 filename 파일 생성 (./answer)
// recog_string 내용을 담은 filename 파일 생성 (./recog)
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <memory.h>
#include <string>

//	@brief				메인함수
//	@author				윤병훈
//	@param		argc	인자의 수 exe파일명까지 포함
//	@param		argv	인자의 값
//	@return				종료코드
int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		// Show Options...
		fprintf(stderr, "Usage) TestCode [textfile.txt]\n");
		exit(0);
	}	

	FILE *fpInput = NULL;
	if ((fpInput = fopen(argv[1], "rb")) == NULL)
	{
		fprintf(stderr, "Faile to open text-file.\n");
		exit(-1);
	}

	// 디렉토리 생성
	const char *pAnswerDIR = "@answer/";
	const char *pRecogDIR = "@recog/";
	
	_mkdir(pAnswerDIR);
	_mkdir(pRecogDIR);
	

	bool bUnicode = false;
	bool bUTF8 = false;
	int code_check[3] = {0,0,0};
	// unicode(utf-16) 코드 검사(2바이트 헤더 검사)
	for(int i=0; i<=1; i++)
	{
		code_check[i] = fgetc(fpInput);
	}
	// Little Endian 일때 FF FE(참고로 Bing Endian 일때 FE FF)
	if(!(code_check[0] == 0xFF && code_check[1] == 0xFE))
	{
		// unicode(utf-16) 가 아니면 다시 처음 부터 읽기
		fseek(fpInput, -2, SEEK_CUR);

		// utf-8 코드 검사(3바이트 헤더 검사)
		for(int i=0; i<=2; i++)
		{
			code_check[i] = fgetc(fpInput);
		}
		if(!(code_check[0] == 0xEF && code_check[1] == 0xBB && code_check[2] == 0xBF))
		{
			// utf-8 이 아니면 다시 처음 부터 읽기
			fseek(fpInput, -3, SEEK_CUR);
		}
		else
		{
			bUTF8 = true;
		}
	}
	else
	{
		bUnicode = true;
	}

	FILE *fpOutput = NULL;

	std::string strAnswerFileName;
	std::string strRecogFileName;
	std::string strAnswer;
	std::string strRecog;
	std::string strTemp;

	char c = 0;
	int len = 0;
	int tabcnt = 0;
	bool bLine = false;
	while (!feof(fpInput))
	{
		c = (char)fgetc(fpInput);

		// 0x09(9->Tab) 0x0A(10->LineFeed) 0x0D(13->CarriageReturn)
		
		// LF와CR 이 같이 있는 텍스트 파일의 경우를 위한 처리
		bLine = false;
		if (c == 0x0D)
		{
			c = fgetc(fpInput);
			if (c == 0x0A)
			{
				bLine = true;
			}
			else
			{
				fseek(fpInput, -1, SEEK_CUR);
			}
		}

		if (c == 0x09 || bLine == true)
		{
			tabcnt++;
			if (tabcnt == 1)
			{
				strAnswerFileName += pAnswerDIR;
				strAnswerFileName += strTemp;
				strAnswerFileName += ".txt";

				strRecogFileName += pRecogDIR;
				strRecogFileName += strTemp;
				strRecogFileName += ".txt";			
				strTemp.clear();
			}
			else if (tabcnt == 2)
			{
				strAnswer += strTemp;
				strTemp.clear();
			}
			else if (tabcnt == 3)
			{
				strRecog += strTemp;
				strTemp.clear();
			}
			if (tabcnt == 3)
			{
				// 정답텍스트파일 생성하기
				fpOutput = fopen(strAnswerFileName.c_str(), "wb");			
				// unicode 헤더 만들기
				if (bUnicode)
				{
					fputc(0xFF, fpOutput);
					fputc(0xFE, fpOutput);
				}
				// utf-8 헤더 만들기
				if (bUTF8)
				{
					fputc(0xEF, fpOutput);
					fputc(0xBB, fpOutput);
					fputc(0xBF, fpOutput);
				}
				len = strlen(strAnswer.c_str());
				fwrite(strAnswer.c_str(), sizeof(char)*len, 1, fpOutput);
				fclose(fpOutput);

				fprintf(stderr, "%s created.\n", strAnswerFileName.c_str());

				// 인식텍스트파일 생성하기
				fpOutput = fopen(strRecogFileName.c_str(), "wb");
				// unicode 헤더 만들기
				if (bUnicode)
				{
					fputc(0xFF, fpOutput);
					fputc(0xFE, fpOutput);
				}
				// utf-8 헤더 만들기
				if (bUTF8)
				{
					fputc(0xEF, fpOutput);
					fputc(0xBB, fpOutput);
					fputc(0xBF, fpOutput);
				}
				len = strlen(strRecog.c_str());
				fwrite(strRecog.c_str(), sizeof(char)*len, 1, fpOutput);
				fclose(fpOutput);

				fprintf(stderr, "%s created.\n", strRecogFileName.c_str());

				strAnswerFileName.clear();
				strRecogFileName.clear();
				strAnswer.clear();
				strRecog.clear();
				strTemp.clear();
				strTemp.clear();
				len = 0;
				tabcnt = 0;
			}
		}
		else
		{
			strTemp += c;
		}
	}
	fclose(fpInput);
	
	return 0;
}

