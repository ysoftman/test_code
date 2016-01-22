////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// �ؽ�Ʈ ���ϳ��� �Ľ��ϱ�
// �ؽ�Ʈ ������ ������ ������ ���� �������� N ������ �����Ѵ�.
// filename (tab) answer_string (tab) recog_string
// �� ������ �Ľ��Ͽ� ������ �۾��� �����Ѵ�.
// answer_string ������ ���� filename ���� ���� (./answer)
// recog_string ������ ���� filename ���� ���� (./recog)
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <memory.h>
#include <string>

//	@brief				�����Լ�
//	@author				������
//	@param		argc	������ �� exe���ϸ���� ����
//	@param		argv	������ ��
//	@return				�����ڵ�
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

	// ���丮 ����
	const char *pAnswerDIR = "@answer/";
	const char *pRecogDIR = "@recog/";
	
	_mkdir(pAnswerDIR);
	_mkdir(pRecogDIR);
	

	bool bUnicode = false;
	bool bUTF8 = false;
	int code_check[3] = {0,0,0};
	// unicode(utf-16) �ڵ� �˻�(2����Ʈ ��� �˻�)
	for(int i=0; i<=1; i++)
	{
		code_check[i] = fgetc(fpInput);
	}
	// Little Endian �϶� FF FE(����� Bing Endian �϶� FE FF)
	if(!(code_check[0] == 0xFF && code_check[1] == 0xFE))
	{
		// unicode(utf-16) �� �ƴϸ� �ٽ� ó�� ���� �б�
		fseek(fpInput, -2, SEEK_CUR);

		// utf-8 �ڵ� �˻�(3����Ʈ ��� �˻�)
		for(int i=0; i<=2; i++)
		{
			code_check[i] = fgetc(fpInput);
		}
		if(!(code_check[0] == 0xEF && code_check[1] == 0xBB && code_check[2] == 0xBF))
		{
			// utf-8 �� �ƴϸ� �ٽ� ó�� ���� �б�
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
		
		// LF��CR �� ���� �ִ� �ؽ�Ʈ ������ ��츦 ���� ó��
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
				// �����ؽ�Ʈ���� �����ϱ�
				fpOutput = fopen(strAnswerFileName.c_str(), "wb");			
				// unicode ��� �����
				if (bUnicode)
				{
					fputc(0xFF, fpOutput);
					fputc(0xFE, fpOutput);
				}
				// utf-8 ��� �����
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

				// �ν��ؽ�Ʈ���� �����ϱ�
				fpOutput = fopen(strRecogFileName.c_str(), "wb");
				// unicode ��� �����
				if (bUnicode)
				{
					fputc(0xFF, fpOutput);
					fputc(0xFE, fpOutput);
				}
				// utf-8 ��� �����
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

