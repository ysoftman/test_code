/*
############################
��  �� : OpenSSL ����
�ۼ��� : ������
############################
[������ ����]
1. openssl-1.0.1c.tar.gz ���� ����

2. cd openssl-1.0.1c

3. �ܼ�â���� VC++ ����� �� �ֵ��� ȯ�� ����
   "c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcvarsall.bat"

4. perl �� �������� �����(perl ��ġ���� http://downloads.activestate.com/ActivePerl/releases/)
   win32 ��� ==> perl Configure VC-WIN32 --openssldir=C:\OpenSSL1.0.1
   win64 ��� ==> perl Configure VC-WIN64A --openssldir=C:\OpenSSL1.0.1

5. ������ ȯ�� ���� ��ġ ����
   win32 ��� ==> ms\do_ms.bat
   win64 ��� ==> ms\do_win64a.bat

6. ����
   .lib ���� ==> nmake -f ms\nt.mak install
   .dll ���� ==> nmake -f ms\ntdll.mak install

7. ��� Ȯ��
   include ���� ==> C:\OpenSSL1.0.1\include\openssl
   .lib(.dll) ���� ==> C:\OpenSSL1.0.1\lib

[������ ����]
1. openssl-1.0.1c.tar.gz ���� ����
   tar zxvf openssl-1.0.1c.tar.gz

2. cd openssl-1.0.1c

3. �������� �����
   ./config --openssldir=/home/ysoftman/openssl1.0.1

4. ���� �� �׽�Ʈ
   make && make test

5. ��ġ
   make install

6. ��� Ȯ��
   include ���� ==> /home/ysoftman/openssl1.0.1/include/openssl
   .a ���� ==> /home/ysoftman/openssl1.0.1/lib
*/
////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// OpenSSL �׽�Ʈ
// �ռ� ����� ��ο��� include �� lib ���
// ������Ʈ �������� �߰� ���Ե��丮�� ���� ���丮(.) �߰�
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
#else // linux
#pragma comment(lib, "libcrypto")
#endif

using namespace std;

/**
*	@brief			Crypto Ŭ����
*	@author			������
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
