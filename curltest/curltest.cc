////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// libcurl 테스트
//
// curl-7.21.3.tar.gz 을 다운받아 압축 해제 후 설치
// wget http://curl.haxx.se/download/curl-7.21.3.tar.gz
// tar zxvf curl-7.21.3.tar.gz
// cd crul-7.21.3
// ./configure
// make
// sudo make install
//
// curl 예제
// http://curl.haxx.se/libcurl/c/example.html
// http://www.joinc.co.kr/modules/moniwiki//wiki.php/Site/Web/documents/UsedCurl
//
// 컴파일
// gcc curltest.cc -lcurl -o curltest
////////////////////////////////////////////////////////////////////////////////////
#ifdef linux
#include <stdio.h>
#include "/usr/local/include/curl/curl.h"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage(example) : TestCURL www.naver.com\n");
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
	//curl_easy_setopt(curl, CURLOPT_URL, "http://www.naver.com");
	curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
	// 헤더와 바디 내용 출력 대상 설정
	curl_easy_setopt(curl, CURLOPT_WRITEHEADER, stderr);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
	// id, pw 설정
	//curl_easy_setopt(curl, CURLOPT_USERNAME, "ysoftman");
	//curl_easy_setopt(curl, CURLOPT_PASSWORD, "qwer1234");
	curl_easy_setopt(curl, CURLOPT_USERPWD, "ysoftman:qwer1234");
	// 상세 정보 보기
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
	}

	// context 제거
	curl_easy_cleanup(curl);

	curl_global_init(CURL_GLOBAL_ALL);

	return 0;
}
#endif
