#include "cryptography.h"

// Base64 인코딩/디코딩 테스트
void Base64_Test()
{
	Crypto crypto;
	char pPlain[512] = "Base64인코딩/디코딩 테스트입니다. 이 문장이 보이면 Base64인코딩/디코딩이 정상적인것입니다.\n";
	char *base64 = crypto.Base64_Encoding(pPlain, strlen(pPlain));
	if (base64 != NULL)
	{
		printf("base64 encoded: %s\n", base64);
		char *output = crypto.Base64_Decoding(base64, strlen(base64));
		if (output != NULL)
		{
			printf("base64 decoded: %s\n", output);
			delete[] output;
		}
		delete[] base64;
	}
}

// AES 암호화/복호화 테스트
void AES_Test()
{
	Crypto crypto;
	const short AES_LEN = 16 + 1; // (16벡터 + NULL terminated)
	const unsigned char AES_Key[AES_LEN] = "ysoftmanAesKey";
	const unsigned char AES_InitialVector[AES_LEN] = "abcdefghijklmnop";
	unsigned char iv[AES_LEN];
	memcpy(iv, AES_InitialVector, AES_LEN);
	char *pEncryptedAES = crypto.AES_CBC_Encrypt(AES_Key, iv, "암호(AES) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다.\n");
	// iv 한번 사용하면 값이 변하게 된다.
	memset(iv, 0, sizeof(unsigned char) * AES_LEN);
	memcpy(iv, AES_InitialVector, AES_LEN);
	string result = crypto.AES_CBC_Decrypt(AES_Key, iv, pEncryptedAES);
	if (pEncryptedAES != NULL)
	{
		printf("AES encrypted: %s\n", pEncryptedAES);
		delete[] pEncryptedAES;
	}
	if (result.length() > 0)
	{
		printf("AES encrypted: %s\n", result.c_str());
	}
}

// RSA 암호화/복호화 테스트
void RSA_Test()
{
	Crypto crypto;
	RSA *rsa = crypto.RSA_GenerateKey(2048);
	// RSA_PKCS1_OAEP_PADDING 일때 평문의 길이는 keysize(2048bits(256bytes)-41(bytes)) 보다 작아야 한다
	char pPlain[512];
	memset(pPlain, 0, 512);
	sprintf(pPlain, "암호(RSA) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다.\n");
	char *pEncryptedRSA = crypto.RSA_EncryptPublic(rsa, pPlain);
	char *pDecryptedRSA = crypto.RSA_DecryptPrivate(rsa, pEncryptedRSA);
	if (pEncryptedRSA != NULL)
	{
		printf("RSA encrypted: %s\n", pEncryptedRSA);
		delete[] pEncryptedRSA;
	}
	if (pDecryptedRSA != NULL)
	{
		printf("RSA decrypted: %s\n", pDecryptedRSA);
		delete[] pDecryptedRSA;
	}
	crypto.RSA_Free(rsa);
}

int main()
{
	Base64_Test();
	AES_Test();
	RSA_Test();

	return 0;
}

