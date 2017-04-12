////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// windows build
// openssl-1.0.1c.tar.gz 압축 해제
// cd openssl-1.0.1c
// 콘솔창에서 VC++ 사용할 수 있도록 환경 설정
// "c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcvarsall.bat"
//
// perl 로 설정파일 만들기(perl 설치파일 http://downloads.activestate.com/ActivePerl/releases/)
// win32 경우 ==> perl Configure VC-WIN32 --prefix=C:\OpenSSL1.0.1
// win64 경우 ==> perl Configure VC-WIN64A --prefix=C:\OpenSSL1.0.1
//
// 컴파일 환경 설정 배치 실행
// win32 경우 ==> ms\do_ms.bat
// win64 경우 ==> ms\do_win64a.bat
//
// 빌드
// .lib 빌드 ==> nmake -f ms\nt.mak install
// .dll 빌드 ==> nmake -f ms\ntdll.mak install
//
// 결과 확인
// include 파일 ==> C:\OpenSSL1.0.1\include\openssl
// .lib(.dll) 파일 ==> C:\OpenSSL1.0.1\lib
// 
// linux build -> build.sh 참고
////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

#include <stdio.h>
#include <string.h>

#include "./openssl/ossl_typ.h"
#include "./openssl/ssl.h"
#include "./openssl/rsa.h"
#include "./openssl/evp.h"
#include "./openssl/bio.h"
#include "./openssl/buffer.h"
#include "./openssl/aes.h"
#include "./openssl/rsa.h"
#include "./openssl/rand.h"
#include "./openssl/crypto.h"
#include "./openssl/err.h"
#include "./openssl/engine.h"
#include "./openssl/sha.h"


#if defined(_WIN32) || defined(_WIN64)
#pragma comment(lib, "./openssl/lib/libeay32")
#endif

using namespace std;

/**
*	@brief			Crypto 클래스
*	@author			윤병훈
*	@param			None
*	@return			None
*/
class Crypto
{

public:
	Crypto();
	~Crypto();


	RSA* RSA_GenerateKey(int KeySize);
	void RSA_Free(RSA *p);
	char* RSA_EncryptPublic(RSA *rsa, char *pPlain);
	char* RSA_DecryptPrivate(RSA *rsa, char *pBase64Cipher);


	char* AES_CBC_Encrypt(const unsigned char *userKey, unsigned char *iv, string Plain);
	string AES_CBC_Decrypt(const unsigned char *userKey, unsigned char *iv, char *pBase64Cipher);


	char *Base64_Encoding(char *pInput, int Len);
	char *Base64_Decoding(char *pInput, int Len);

	int Base64_GetEncodeLength(int Len);

};
