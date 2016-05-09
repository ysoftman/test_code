////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// libcurl �׽�Ʈ
//
// [linux]
// curl-7.21.3.tar.gz �� �ٿ�޾� ���� ���� �� ��ġ
// wget http://curl.haxx.se/download/curl-7.21.3.tar.gz
// tar zxvf curl-7.21.3.tar.gz
// cd crul-7.21.3
// ./configure
// make
// sudo make install
// ������
// gcc curltest.cc -lcurl -o curltest
// 
// [windows]
// http://curl.haxx.se/download/curl-7.21.3.zip �ٿ�ε� �� ���� Ǯ��
// cmake ���� configure -> visual studio 11 2012 ���� -> generate
// visual studio �� �����ϱ� (�ڵ� ���� MT)
// ��������� curl �ҽ��� include ���
// ����
// visual studio ���� .c ��� .cpp Ȯ���ڸ� ����ϵ��� �Ѵ�.
// ����� zlib1.dll ���� ������ �߻��Ѵٸ� 
// ������� zlib �ٿ�ε� http://gnuwin32.sourceforge.net/downlinks/zlib-bin-zip.php
// ���� ���� �� zlib1.dll �� �����ؼ� ������Ѵ�.
//
// curl ����
// http://curl.haxx.se/libcurl/c/example.html
// http://www.joinc.co.kr/modules/moniwiki//wiki.php/Site/Web/documents/UsedCurl
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#ifdef linux
#include "/usr/local/include/curl/curl.h"
#endif

#if defined(_WIN32) || defined(_WIN64)
#include "include/curl/curl.h"
#pragma comment(lib, "lib/libcurl_imp_mtd_2012.lib")
#endif


#define MAX_CURL_RESP_SIZE 8192

struct CURL_DATA_INFO {
	char szData[MAX_CURL_RESP_SIZE];
	size_t size;
	size_t pos;
};

// ���� ��Ŷ ���� ���� �Լ�(�ݹ�)
static size_t WriteData(void *contents, size_t size, size_t nmemb, void *userdata)
{
	size_t realsize = size * nmemb;
	struct CURL_DATA_INFO *mem = (struct CURL_DATA_INFO *)userdata;
	if (mem->pos+realsize >= MAX_CURL_RESP_SIZE)
	{
		fprintf(stderr, "buffer overflow\n");
		return -1;
	}

	// ������ �ݹ�� �� �־� ���� �����Ϳ� �̾���δ�.
	memcpy((char*)mem->szData + mem->pos, contents, realsize);
	mem->pos += realsize;

	return realsize;
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage(example) : %s www.naver.com\n", argv[0]);
		return 0;
	}

	CURL *curl;
	CURLcode curlcode;

	// �ʱ�ȭ
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (!curl)
	{
		fprintf(stderr, "Can't initialize cURL.\n");
		return -1;
	}

	// ��� URL ����
	//curl_easy_setopt(curl, CURLOPT_URL, "http://www.naver.com");
	curl_easy_setopt(curl, CURLOPT_URL, argv[1]);

	// ����� �ٵ� ���� ���� �Լ� ����
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteData);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);

	// ����� �ٵ� ���� ��� ��� ����
	//curl_easy_setopt(curl, CURLOPT_WRITEHEADER, stderr);
	//curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
	CURL_DATA_INFO header;
	header.size = 0;
	header.pos = 0;
	memset(header.szData, 0, sizeof(char)*MAX_CURL_RESP_SIZE);
	curl_easy_setopt(curl, CURLOPT_WRITEHEADER, &header);

	CURL_DATA_INFO body;
	body.size = 0;
	body.pos = 0;
	memset(body.szData, 0, sizeof(char)*MAX_CURL_RESP_SIZE);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);

	// id, pw ����
	//curl_easy_setopt(curl, CURLOPT_USERNAME, "ysoftman");
	//curl_easy_setopt(curl, CURLOPT_PASSWORD, "qwer1234");
	//curl_easy_setopt(curl, CURLOPT_USERPWD, "ysoftman:qwer1234");
	// �� ���� ����(�ֿܼ� request/body ���� ������ ��µȴ�.)
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	// redirect �� ��� �ش� ��θ� ���󰡵��� ��
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	// Ÿ�Ӿƿ�(second) ����
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10);

	// ����
	curlcode = curl_easy_perform(curl);
	if (curlcode != CURLE_OK)
	{
		printf("\n\n\ncurl error : %s\n", curl_easy_strerror(curlcode));
	}
	else
	{
		int nHttpRespCode;
		double dDownloadSize;
		char *szContentType;
		curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &nHttpRespCode);
		curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &szContentType);
		curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &dDownloadSize);

		fprintf(stderr, "curl success!\n");
		fprintf(stderr, "HttpResponseCode: %d\n", nHttpRespCode);
		fprintf(stderr, "ContentType: %s\n", szContentType);
		fprintf(stderr, "DownloadSize: %f (bytes)\n", dDownloadSize);
		fprintf(stderr, "Response Header: %s\n", header.szData);
		fprintf(stderr, "Response Body: %s\n", body.szData);
	}

	// context ����
	curl_easy_cleanup(curl);

	curl_global_init(CURL_GLOBAL_ALL);

	return 0;
}

