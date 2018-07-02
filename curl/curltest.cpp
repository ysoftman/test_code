/*
# ysoftman
# libcurl 테스트
# linux/mac

# openssl 설치
wget https://www.openssl.org/source/openssl-1.0.2k.tar.gz
tar zxvf openssl-1.0.2k.tar.gz
cd openssl-1.0.2k
./config
make -j4
sudo make install
cd ..

# curl 설치
wget https://curl.haxx.se/download/curl-7.60.0.tar.gz
tar zxvf curl-7.60.0.tar.gz
cd curl-7.60.0

# linux
./configure --prefix=${HOME}/workspace/curl-7.60.0 --with-ssl

# mac
export MACOSX_DEPLOYMENT_TARGET="10.6"
./configure --prefix=${HOME}/workspace/curl-7.60.0 --with-darwinssl

make -j4 && make install
cd ..

gcc curltest.cpp -I${HOME}/workspace/curl-7.60.0/include/curl -L${HOME}/workspace/curl-7.60.0/lib -lcurl -o curltest


# windows
# https://curl.haxx.se/download/curl-7.60.0.tar.gz 다운로드 후 압축 풀기
# cmake 에서 configure -> visual studio 11 2012 선택 -> generate
# visual studio 로 빌드하기 (코드 생성 MT)
# 헤더파일은 curl 소스의 include 사용
# 참고
# visual studio 에서 .c 대신 .cpp 확장자를 사용하도록 한다.
# 실행시 zlib1.dll 관련 에러가 발생한다면
# 윈도우용 zlib 다운로드 http://gnuwin32.sourceforge.net/downlinks/zlib-bin-zip.php
# 압축 해제 후 zlib1.dll 를 복사해서 사용해한다.
# curl 참고
https://curl.haxx.se/libcurl/c/getinmemory.html
http://curl.haxx.se/libcurl/c/example.html
http://www.joinc.co.kr/modules/moniwiki//wiki.php/Site/Web/documents/UsedCurl
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "curl.h"

#if defined(_WIN32) || defined(_WIN64)
#include "include/curl/curl.h"
#pragma comment(lib, "lib/libcurl_imp_mtd_2012.lib")
#endif

struct CURL_DATA_INFO
{
	char *pData;
	size_t size;
};

// 응답 패킷 내용 쓰는 함수(콜백)
static size_t WriteData(void *contents, size_t size, size_t nmemb, void *userdata)
{
	size_t realsize = size * nmemb;
	struct CURL_DATA_INFO *mem = (struct CURL_DATA_INFO *)userdata;

	// 여러번 콜백될 수 있어 기존 데이터에 이어붙인다.
	mem->pData = (char *)realloc(mem->pData, mem->size + realsize + 1);
	if (mem->pData == NULL)
	{
		fprintf(stderr, "realloc failed\n");
		return 0;
	}

	memcpy(&(mem->pData[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->pData[mem->size] = 0;

	return realsize;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage(example) : %s https://www.google.com\n", argv[0]);
		return 0;
	}

	CURL *curl;
	CURLcode curlcode;

	// 초기화
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (!curl)
	{
		fprintf(stderr, "Can't initialize cURL.\n");
		return -1;
	}

	// 대상 URL 설정
	curl_easy_setopt(curl, CURLOPT_URL, argv[1]);

	// 헤더와 바디 내용 쓰기 함수 설정
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteData);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);

	// 헤더와 바디 내용 출력 대상 설정
	//curl_easy_setopt(curl, CURLOPT_WRITEHEADER, stderr);
	//curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
	CURL_DATA_INFO header;
	header.size = 0;
	header.pData = (char *)calloc(1, sizeof(char) * 1);
	curl_easy_setopt(curl, CURLOPT_WRITEHEADER, &header);

	CURL_DATA_INFO body;
	body.size = 0;
	body.pData = (char *)calloc(1, sizeof(char *) * 1);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);

	// id, pw 설정
	//curl_easy_setopt(curl, CURLOPT_USERNAME, "ysoftman");
	//curl_easy_setopt(curl, CURLOPT_PASSWORD, "qwer1234");
	//curl_easy_setopt(curl, CURLOPT_USERPWD, "ysoftman:qwer1234");
	// 상세 정보 보기(콘솔에 request/body 관련 정보가 출력된다.)
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	// redirect 된 경우 해당 경로를 따라가도록 함
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	// 타임아웃(second) 설정
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10);

	// 실행
	curlcode = curl_easy_perform(curl);
	if (curlcode != CURLE_OK)
	{
		printf("\n\n\ncurl error : %s\n", curl_easy_strerror(curlcode));
	}
	else
	{
		long nHttpRespCode;
		double dDownloadSize;
		char *szContentType;
		curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &nHttpRespCode);
		curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &szContentType);
		curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &dDownloadSize);

		fprintf(stderr, "curl success!\n");
		fprintf(stderr, "HttpResponseCode: %ld\n", nHttpRespCode);
		fprintf(stderr, "ContentType: %s\n", szContentType);
		fprintf(stderr, "DownloadSize: %f (bytes)\n", dDownloadSize);
		fprintf(stderr, "Response Header: %s\n", header.pData);
		fprintf(stderr, "Response Body: %s\n", body.pData);
	}

	free(header.pData);
	free(body.pData);

	// context 제거
	curl_easy_cleanup(curl);

	curl_global_init(CURL_GLOBAL_ALL);

	return 0;
}
