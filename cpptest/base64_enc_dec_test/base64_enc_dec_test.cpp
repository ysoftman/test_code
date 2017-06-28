////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Base64 인코딩/디코딩
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;


// BASE64 
static char base64_table[] ={
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', '\0' 
};
static char base64_pad = '=';

typedef union {
	struct {
		unsigned char c1,c2,c3;
	};
	struct {
		unsigned int e1:6,e2:6,e3:6,e4:6;
	};
} BF;


// 한글문자도 인코딩이 된다.
char* Base64Encoding(char *src, int Length)
{
	char *result = new char[Length*4];
	memset(result, 0, sizeof(char)*Length*4);

	int i, j = 0;
	BF temp;
	for (i = 0 ; i < Length ; i = i+3, j = j+4)
	{
		temp.c3 = src[i];
		
		if((i+1) > Length)
			temp.c2 = 0;
		else
			temp.c2 = src[i+1];

		if((i+2) > Length) 
			temp.c1 = 0;
		else
			temp.c1 = src[i+2];

		result[j]   = base64_table[temp.e4];
		result[j+1] = base64_table[temp.e3];
		result[j+2] = base64_table[temp.e2];
		result[j+3] = base64_table[temp.e1];

		if((i+2) > Length) result[j+2] = '=';
		if((i+3) > Length) result[j+3] = '=';
	}

	return result;
}

// 문자열을 Base64 인코딩(64개문자 표현을 위해 6bit문자를 사용, 때문에 기존의 8bit 문자는 4byte(24bit) 단위로 인코딩) 한다.
// 한글문자는 인코딩이 안되는 문제가 있다
string Base64EncodingOld(char *pIn, int Length)
{
	string result;
	char temp = '\0';
	// 24bit 가 유지될 동안 진행한다.
	while (Length > 2)
	{
		// 4byte(24bit) 단위로 처리한다.
		// 첫번째 바이트 : 하위 2bit 를 잘라내고 상위 6bit로 새로운 1바이트 구성
		temp = pIn[0] >> 2;
		result += base64_table[temp]; 
		// 두번째 바이트 : 이전의 잘린 하위 2bit와 다음 바이트의 상위 4bit 를 합친 6bit로 새로운 1바이트 구성
		temp = ((pIn[0] & 0x03) << 4) + (pIn[1] >> 4);
		result += base64_table[temp];
		// 세번째 바이트 : 이전의 남은 하위 4bit와 다음 바이트의 상위 2bit 를 합친 6bit로 새로운 1바이트 구성
		temp = ((pIn[1] & 0x0f) << 2) + (pIn[2] >> 6);
		result += base64_table[temp];
		// 네번째 바이트 : 남은 하위 6bit로 새로운 1바이트 구성
		temp = pIn[2] & 0x3f;
		result += base64_table[temp];

		// 입력 바이트 3바이트를 처리한 상태이다.
		pIn += 3;
		// 길이도 줄여준다.
		Length -= 3;
	}

	
	// 입력문자의 1바이트나 2바이트 처리가 남았을 경우
	if (Length != 0)
	{
		if (Length > 1)
		{
			result += base64_table[pIn[0] >> 2];
			result += base64_table[((pIn[0] & 0x03) << 4) + (pIn[1] >> 4)];
			result += base64_table[(pIn[1] & 0x0f) << 2];
			// 네번째 바이트 : 24bit 단위에 맞추가 위해 패딩문자(=)를 넣어 준다.
			result += base64_pad;
		}
		else
		{
			result += base64_table[pIn[0] >> 2];
			result += base64_table[(pIn[0] & 0x03) << 4];
			// 세번째 바이트 : 24bit 단위에 맞추가 위해 패딩문자(=)를 넣어 준다.
			result += base64_pad;
			// 네번째 바이트 : 24bit 단위에 맞추가 위해 패딩문자(=)를 넣어 준다.
			result += base64_pad;
		}
	}

	result += '\0';


	return result;
}


char* Base64Decoding(char *pIn, int Length)
{
	int ch, i = 0, j = 0, k;
	
	short reverse_table[256];
	
	char *chp; 
	for(ch = 0; ch < 256; ch++)
	{
		chp = strchr(base64_table, ch); 
		if (chp)
		{
			reverse_table[ch] = chp - base64_table;
		}
		else
		{
			reverse_table[ch] = -1;
		}
	}

	char *result = new char[Length];
	memset(result, 0, sizeof(char)*Length);

	// run through the whole string, converting as we go
	while ((ch = *pIn++) != '\0')
	{
		if (ch == base64_pad)
		{
			break;
		}

		//When Base64 gets POSTed, all pluses are interpreted as spaces. 
		//This line changes them back.  It's not exactly the Base64 spec, 
		//but it is completely compatible with it (the spec says that 
		//spaces are invalid).  This will also save many people considerable 
		//headache.  - Turadg Aleahmad <turadg@wise.berkeley.edu> 
		if (ch == ' ')
		{
			ch = '+';
		}
		ch = reverse_table[ch];
		if (ch < 0)
		{
			continue;
		}

		switch(i % 4)
		{
		case 0:
			result[j] = ch << 2;
			break;
		case 1:
			result[j++] |= ch >> 4;
			result[j] = (ch & 0x0f) << 4;
			break;
		case 2:
			result[j++] |= ch >> 2; 
			result[j] = (ch & 0x03) << 6;
			break;
		case 3:
			result[j++] |= ch;
			break;
		}
		i++;
	}

	k = j;
	// mop things up if we ended on a boundary
	if (ch == base64_pad)
	{
		switch (i % 4)
		{
		case 0:
		case 1:
			free(result);
			return NULL;
		case 2:
			k++;
		case 3:
			result[k++] = 0;
		}
	}
	result[k] = '\0';

	return result;
}

int main()
{
	char teststring[100] = "윤병훈 yoon byoung hoon 1234 !@#$";
	char *pInput = teststring;
	
	fprintf(stdout, "[intput text] = %s\n", pInput);

	char *Base64EncodeResult = Base64Encoding(pInput, strlen(pInput));
	fprintf(stdout, "[Base64 Encoding] = %s\n", Base64EncodeResult);

	char *Base64DecodeResult = Base64Decoding((char*)Base64EncodeResult, strlen(Base64EncodeResult));
	fprintf(stdout, "[Base64 Decoding] = %s\n", Base64DecodeResult);

	if (Base64EncodeResult != NULL)
	{
		delete[] Base64EncodeResult;
	}
	if (Base64DecodeResult != NULL)
	{
		delete[] Base64DecodeResult;
	}
	return 0;
}
