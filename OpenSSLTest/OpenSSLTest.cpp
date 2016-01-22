#include "Cryptography.h"

int main()
{
	Crypto crypto;
	// Base64 ���ڵ�/���ڵ� �׽�Ʈ
	char *pPlain = "Base64���ڵ�/���ڵ� �׽�Ʈ�Դϴ�. �� ������ ���̸� Base64���ڵ�/���ڵ��� �������ΰ��Դϴ�.\n";
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


	// RSA ��ȣȭ/��ȣȭ �׽�Ʈ
	RSA *rsa = crypto.RSA_GenerateKey(1024);

	// RSA_PKCS1_OAEP_PADDING �϶� ���� ���̴� keysize(1024bit(128byte)-41(byte)) ���� �۾ƾ� �Ѵ�
	char *pCipher = crypto.RSA_EncryptPublic(rsa, "��ȣ(RSA) �׽�Ʈ�Դϴ�. �� ������ ���̸� ��ȣ/��ȣȭ�� �������ΰ��Դϴ�.\n");
	char *pPlain2 = crypto.RSA_DecryptPrivate(rsa, pCipher);
	if (pCipher != NULL)
	{
		printf("RSA encrypted: %s\n", pCipher);
		delete[] pCipher;
	}			
	if (pPlain2 != NULL)
	{
		printf("RSA decrypted: %s\n", pPlain2);
		delete[] pPlain2;
	}			
	crypto.RSA_Free(rsa);

	const short	AES_LEN								= 16+1; // (16���� + NULL terminated)
	const unsigned char AES_Key[AES_LEN]			= "ysoftmanAesKey";
	const unsigned char AES_InitialVector[AES_LEN]	= "abcdefghijklmnop";

	// AES ��ȣȭ/��ȣȭ �׽�Ʈ
	unsigned char iv[AES_LEN];
	memcpy(iv, AES_InitialVector, AES_LEN);
	char *pCipher2 = crypto.AES_CBC_Encrypt(AES_Key, iv, "��ȣ(AES) �׽�Ʈ�Դϴ�. �� ������ ���̸� ��ȣ/��ȣȭ�� �������ΰ��Դϴ�.\n");
	// iv �ѹ� ����ϸ� ���� ���ϰ� �ȴ�.
	memset(iv, 0, sizeof(unsigned char)*AES_LEN);
	memcpy(iv, AES_InitialVector, AES_LEN);
	string result = crypto.AES_CBC_Decrypt(AES_Key, iv, pCipher2);
	if (pCipher2 != NULL)
	{
		printf("AES encrypted: %s\n", pCipher2);
		delete[] pCipher2;
	}
	if (result.length() > 0)
	{
		printf("AES encrypted: %s\n", result.c_str());
	}
	return 0;
}

