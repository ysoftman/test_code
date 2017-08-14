#include "cryptography.h"

/**
*	@brief					Crypto 클래스 생성자
*	@author					윤병훈
*	@param					None
*	@return					None
*/
Crypto::Crypto()
{
}

/**
*	@brief					Crypto 클래스 소멸자
*	@author					윤병훈
*	@param					None
*	@return					None
*/
Crypto::~Crypto()
{
	// 현재 쓰레드의 Error Queue 삭제
	ERR_remove_state(0);
	// Errot String 해제
	ERR_free_strings();
	// ENGIN 삭제
	ENGINE_cleanup();
	// EVP 삭제
	EVP_cleanup();

	//This function is used to cleanup application specific data and should be called before the application shuts down to avoid memory leaks.
	//CRYPTO_cleanup_all_ex_data();
}


/**
*	@brief						Crypto 키 해제
*	@author						윤병훈
*	@param			p			RSA key
*	@return						None
*/
void Crypto::RSA_Free(RSA *p)
{
	if (p)
	{
		RSA_free(p);
	}
}


/**
*	@brief						RSA 키 생성하는 함수
*	@author						윤병훈
*	@param			KeySize		생성할 키 사이즈(비트사이즈로 512bit, 1024bit, 2048bit ...)
*	@return						성공하면 RSA 키 리턴
*/
RSA* Crypto::RSA_GenerateKey(int KeySize)
{
	// 키 생성을 위한 씨드값 생성
	//const char seed[] = "2$#^B@$^B)@VM*@)#$^*C)MPTSVDMPSVCSPRM_^*X#^*V#*&#*&%)CF*";
	//RAND_seed(seed, sizeof(seed));

	// 키사이즈에 따른 키 생성
	// 두번째 파라미터는 지수(exponent) 값으로 보통 3 17 65537 의 소수를 사용한다.
	RSA *rsa = RSA_generate_key(KeySize, 17, NULL, NULL);
	if (NULL == rsa)
	{
		return NULL;
	}

	// 생성된 키를 체크
	int ret = RSA_check_key(rsa);
	if (ret != 1)
	{
		return NULL;
	}

	return rsa;
}

/**
*	@brief						RSA 공개키로 암호화
*	@author						윤병훈
*	@param			rsa			rsa 키
*	@param			pPlain		암호화할 데이터
*	@return						암호화된 데이터
*/
char* Crypto::RSA_EncryptPublic(RSA *rsa, char *pPlain)
{
	// 키 사이즈 파악(bit -> byte 로 변환)
	int KeySize = RSA_size(rsa);

	int PlainLen = strlen(pPlain);

	// RSA_PKCS1_OAEP_PADDING 사용시 평문의 최대 크기 체크
	if (PlainLen > KeySize - 41)
	{
		return NULL;
	}

	// 암호결과가 저정될 버퍼
	char *pBuffer = new char[KeySize];
	memset(pBuffer, 0, sizeof(char)*KeySize);

	// 암호화
	int CipherLen = RSA_public_encrypt(PlainLen, reinterpret_cast<const unsigned char *>(pPlain), reinterpret_cast<unsigned char*>(pBuffer), rsa, RSA_PKCS1_OAEP_PADDING);

	if (CipherLen <= 0)
	{
		ERR_load_crypto_strings();
		ERR_print_errors_fp(stderr);
		delete[] pBuffer;
		return NULL;
	}

	// 바이트 배열 중간에 '\0' 값을 없애기 위해서 Base64인코딩한다.
	char* pBase64Cipher = Base64_Encoding(pBuffer, CipherLen);
	delete[] pBuffer;

	return pBase64Cipher;
}


/**
*	@brief								RSA 개인키로 복호화
*	@author								윤병훈
*	@param			rsa					rsa 키
*	@param			pBase64Cipher		암호화된 데이터
*	@return								복호화된 데이터
*/
char* Crypto::RSA_DecryptPrivate(RSA *rsa, char *pBase64Cipher)
{
	// 키 사이즈 파악
	int KeySize = RSA_size(rsa);

	if (pBase64Cipher == NULL)
	{
		return NULL;
	}

	// Base64인코딩은 원래데이터보다 크다.
	int CipherBase64Len = strlen(pBase64Cipher);
	// Base64 디코딩한다.
	char* pCipher = Base64_Decoding(pBase64Cipher, CipherBase64Len);
	if (pCipher == NULL)
	{
		return NULL;
	}
	// pCipher 에는 '\0' 값이 중간에 포함될 수 있기때문에 strlen으로 크기를 파악하면 안된다.
	int CipherLen = 0;
	for (int i=CipherBase64Len-1; i>=0; i--)
	{
		if (pCipher[i] != '\0')
		{
			CipherLen = i+1;
			break;
		}
	}

	// 복호화된 결과가 저정될 버퍼
	// 키사이즈보다 클 수 없기때문에
	char *pBuffer = new char[KeySize];
	memset(pBuffer, 0, sizeof(char)*KeySize);

	// 복호화
	int PlainLen = RSA_private_decrypt(CipherLen, reinterpret_cast<const unsigned char *>(pCipher), reinterpret_cast<unsigned char*>(pBuffer), rsa, RSA_PKCS1_OAEP_PADDING);

	delete[] pCipher;

	if (PlainLen <= 0)
	{
		ERR_load_crypto_strings();
		ERR_print_errors_fp(stderr);
		ERR_free_strings();
		return NULL;
	}

	return pBuffer;
}


/**
*	@brief							AES 암호화, 128bit(16byte) 블록 단위로 암호화한다.
*	@author							윤병훈
*	@param			userKey			암호화에 사용할 키(128bit, 192bit, 256bit 크기를 가질 수 있다.)
*	@param			iv				암호화에 사용할 초기 벡터
*	@param			Plain			암호화할 데이터
*	@return							암호화된 데이터
*/
char* Crypto::AES_CBC_Encrypt(const unsigned char *userKey, unsigned char *iv, string Plain)
{
	if (Plain.length() == 0)
	{
		return NULL;
	}

	// 한글의 경우2바이트를 차지하기때문에
	// string 문자열 길이의 2배 크기의 바이트가 할당되어야 한다.
	// 암호화된 문자열은 최소 128bit(16byte) 크기를 메모리 공간이 필요하다.
	// 16byte 이하의 문자열에 대해서도 처리할 수 있도록 기본적으로 16byte 메모리 공간을 확보하도록 한다.
	int size = (Plain.length() * 2) + 16;
	char *pPlain = new char[size];
	char *pCipher = new char[size];
	memset(pPlain, 0, sizeof(char)*size);
	memset(pCipher, 0, sizeof(char)*size);

	strcpy(pPlain, Plain.c_str());
	int PlainLen = strlen(pPlain);


	AES_KEY encKey;
	// AES encryption key 설정
	if (AES_set_encrypt_key(userKey, 128, &encKey) < 0)
	{
		delete[] pPlain;
		delete[] pCipher;

		return NULL;
	}

	// 16bit 블럭만 처리된다.
	//AES_encrypt(reinterpret_cast<const unsigned char *>(pPlain), reinterpret_cast<unsigned char *>(pCipher), &encKey);
	// Cipher Block Chaining mode (암호 블럭 연쇄 모드)아래 함수를 수행하면 iv 값이 변경된다.
	//AES_cbc_encrypt(reinterpret_cast<const unsigned char*>(pPlain), reinterpret_cast<unsigned char*>(pCipher), PlainLen, &encKey, iv, AES_ENCRYPT);
	// pCipher 에는 '\0' 값이 중간에 포함될 수 있기때문에 strlen으로 크기를 파악하면 안된다.
	//int CipherLen = 0;
	//for (int i=size-1; i>=0; i--)
	//{
	//	if (pCipher[i] != '\0')
	//	{
	//		CipherLen = i+1;
	//		break;
	//	}
	//}

	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	if (1 != EVP_EncryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL, userKey, iv))
	{
		delete[] pPlain;
		delete[] pCipher;

		return NULL;
	}
	int CipherLen = 0;
	if (1 != EVP_EncryptUpdate(&ctx, reinterpret_cast<unsigned char*>(pCipher), &CipherLen, reinterpret_cast<const unsigned char*>(pPlain), PlainLen))
	{
		delete[] pPlain;
		delete[] pCipher;

		return NULL;
	}
	int addlen = 0;
	if (1 != EVP_EncryptFinal_ex(&ctx, reinterpret_cast<unsigned char*>(pCipher+CipherLen), &addlen))
	{
		delete[] pPlain;
		delete[] pCipher;

		return NULL;
	}
	CipherLen += addlen;
	EVP_CIPHER_CTX_cleanup(&ctx);

	delete[] pPlain;


	// 바이트 배열 중간에 '\0' 값을 없애기 위해서 Base64인코딩한다.
	char* pBase64Cipher = Base64_Encoding(pCipher, CipherLen);

	delete[] pCipher;

	//fprintf(stderr, "\nSize = %d, PlainLen = %d, CipherLen = %d\n", size, PlainLen, CipherLen);
	return pBase64Cipher;
}


/**
*	@brief							AES 복호화, 128bit(16byte) 블록 단위로 복호화한다.
*	@author							윤병훈
*	@param			userKey			복호화에 사용할 키(128bit, 192bit, 256bit 크기를 가질 수 있다.)
*	@param			iv				복호화에 사용할 초기 벡터
*	@param			pBase64Cipher	복호화할 데이터
*	@return							복호화된 데이터
*/
string Crypto::AES_CBC_Decrypt(const unsigned char *userKey, unsigned char *iv, char *pBase64Cipher)
{
	if (pBase64Cipher == NULL || strlen(pBase64Cipher) <= 0)
	{
		return NULL;
	}
	// Base64인코딩은 원래데이터보다 크다.
	int CipherBase64Len = strlen(pBase64Cipher);

	// Base64 디코딩한다.
	char* pCipher = Base64_Decoding(pBase64Cipher, CipherBase64Len);
	if (pCipher == NULL)
	{
		return NULL;
	}
	// pCipher 에는 '\0' 값이 중간에 포함될 수 있기때문에 strlen으로 크기를 파악하면 안된다.
	int CipherLen = 0;
	for (int i=CipherBase64Len-1; i>=0; i--)
	{
		if (pCipher[i] != '\0')
		{
			CipherLen = i+1;
			break;
		}
	}

	// 한글의 경우2바이트를 차지하기때문에
	// string 문자열 길이의 2배 크기의 바이트가 할당되어야 한다.
	int size = CipherLen * 2;
	char *pPlain = new char[size];
	memset(pPlain, 0, sizeof(char)*size);

	AES_KEY decKey;
	// AES encryption key 설정
	if (AES_set_decrypt_key(userKey, 128, &decKey) < 0)
	{
		delete[] pPlain;
		delete[] pCipher;

		return "";
	}

	// 16bit 블럭만 처리된다.
	//AES_decrypt(reinterpret_cast<const unsigned char *>(pCipher), reinterpret_cast<unsigned char *>(pPlain), &decKey);
	// Cipher Block Chaining mode (암호 블럭 연쇄 모드)아래 함수를 수행하면 iv 값이 변경된다.
	//AES_cbc_encrypt(reinterpret_cast<const unsigned char*>(pCipher), reinterpret_cast<unsigned char*>(pPlain), CipherLen, &decKey, iv, AES_DECRYPT);

	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	if (1 != EVP_DecryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL, userKey, iv))
	{
		delete[] pPlain;
		delete[] pCipher;

		return "";
	}
	int PlainLen = 0;
	if (1 != EVP_DecryptUpdate(&ctx, reinterpret_cast<unsigned char*>(pPlain), &PlainLen, reinterpret_cast<const unsigned char*>(pCipher), CipherLen))
	{
		delete[] pPlain;
		delete[] pCipher;

		return "";
	}
	int addlen = 0;
	if (1 != EVP_DecryptFinal_ex(&ctx, reinterpret_cast<unsigned char*>(pPlain+PlainLen), &addlen))
	{
		ERR_load_crypto_strings();
		ERR_print_errors_fp(stderr);
		ERR_free_strings();

		delete[] pPlain;
		delete[] pCipher;

		return "";
	}
	PlainLen += addlen;
	EVP_CIPHER_CTX_cleanup(&ctx);


	*(pPlain+PlainLen) = '\0';
	string result;
	result.assign(pPlain);

	delete[] pPlain;
	delete[] pCipher;

	//fprintf(stderr, "\nSize = %d, PlainLen = %d, CipherLen = %d\n", size, PlainLen, CipherLen);
	return result;
}

/**
*	@brief							Base64Encoding 하기
*	@author							윤병훈
*	@param			pInput			입력 문자열
*	@param			Len				입력 문자열 길이
*	@return							Base64Encoding 문자열
*/
char *Crypto::Base64_Encoding(char *pInput, int Len)
{
	if (pInput == NULL || Len <= 0)
	{
		return NULL;
	}
	BIO *base64;
	BIO *bmem;
	BIO *bio;
	BUF_MEM *mem;

	base64 = BIO_new(BIO_f_base64());
	if (!base64)
	{
		return NULL;
	}
	// 줄바꿈없도록 설정
	BIO_set_flags(base64, BIO_FLAGS_BASE64_NO_NL);

	// 메모리 확보
	bmem = BIO_new(BIO_s_mem());
	if (!bmem)
	{
		return NULL;
	}
	bio = BIO_push(base64, bmem);
	// base64인코딩하기
	if (BIO_write(bio, pInput, Len) < 0)
	{
		return NULL;
	}
	BIO_flush(bio);
	int len = BIO_get_mem_ptr(bio, &mem);

	// base64인코딩된 메모리에서 버퍼로 읽어 들이기
	char *buffer = new char[mem->length+1];
	memset(buffer, 0, sizeof(char)*(mem->length+1));
	memcpy(buffer, mem->data, mem->length);

	BIO_free_all(bio);

	return buffer;
}

/**
*	@brief							Base64Decoding 하기
*	@author							윤병훈
*	@param			pInput			입력 문자열
*	@param			Len				입력 문자열 길이
*	@return							Base64Decoding 문자열
*/
char *Crypto::Base64_Decoding(char *pInput, int Len)
{
	if (pInput == NULL || Len <= 0)
	{
		return NULL;
	}
	BIO *base64;
	BIO *bmem;
	BIO *bio;

	base64 = BIO_new(BIO_f_base64());
	if (!base64)
	{
		return NULL;
	}
	// 줄바꿈없도록 설정
	BIO_set_flags(base64, BIO_FLAGS_BASE64_NO_NL);

	// 입력 문자열 메모리 공간으로 옮기기
	bmem = BIO_new_mem_buf(pInput, Len);
	if (!bmem)
	{
		return NULL;
	}

	// base64디코딩하기
	bio = BIO_push(base64, bmem);

	// base64인코딩된 메모리에서 버퍼로 읽어 들이기
	char *buffer = new char[Len];
	memset(buffer, 0, sizeof(char)*Len);
	BIO_read(bio, buffer, Len);

	BIO_free_all(bio);

	return buffer;
}

/**
*	@brief							Base64Encoding 크기 파악하기
*	@author							윤병훈
*	@param			Len				입력 문자열 길이
*	@return							Base64Encoding 크기
*/
int Crypto::Base64_GetEncodeLength(int Len)
{
	if (Len % 4 == 0)
	{
		return Len;
	}
	else if ((Len+1) % 4 == 0)
	{
		return Len+1;
	}
	else if ((Len+2) % 4 == 0)
	{
		return Len+2;
	}
	else
	{
		//fprintf(stderr, "Incorrect Base64 Encoding...\n");
		return Len;
	}
}

