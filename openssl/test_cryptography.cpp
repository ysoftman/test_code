#include "cryptography.h"

// Base64 인코딩/디코딩 테스트
void Base64_test()
{
	Crypto crypto;
	char PlainText[512] = "Base64인코딩/디코딩 테스트입니다. 이 문장이 보이면 Base64인코딩/디코딩이 정상적인것입니다.\n";
	char *base64 = crypto.Base64_Encoding(PlainText, strlen(PlainText));
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
void AES_test()
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
void RSA_test()
{
	Crypto crypto;
	RSA *rsa = crypto.RSA_GenerateKey(2048);
	// RSA_PKCS1_OAEP_PADDING 일때 평문의 길이는 keysize(2048bits(256bytes)-41(bytes)) 보다 작아야 한다
	char PlainText[512];
	memset(PlainText, 0, 512);
	sprintf(PlainText, "암호(RSA) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다.\n");
	char *pEncryptedRSA = crypto.RSA_EncryptPublic(rsa, PlainText);
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

void RSA_decrypt_with_keystring_test()
{
	char key[2048];
	memset(key, 0, 2048);
	// https://www.devglan.com/online-tools/rsa-encryption-decryption 에서 예시 키 생성
	// -----BEGIN RSA PRIVATE KEY-----\n키스트링\n-----END RSA PRIVATE KEY----- 로 감싸줘야 한다.
	sprintf(key, "-----BEGIN RSA PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCGUal3+YYt3jcnLfGstjh4FagLhB8vGhCq58Q5x/bh631XJEvN7cDIzn6vNFNwOgO8M8D1v49+ndjJL8tU7SRBLp/vTUPuos8olKLdiDuEVdh39ZseFxGhTxMRKdgwi90oQk2BZK5bPZRhhAZF5Vb57MkaYri/g3bofX6pPbs5XK13noX7lvp4AsgYcIibRjUtB0/8yzEy0Nlu1y/AiM0an6Y/pc9qByFxT/+CaZhC7ZZ/lxNvodD8Avn8Yl3egbdZSHYlOzGcAt7FtdGaKt4j38PI+yVEXHprXQ0H7eWQ8KHMV1SPGHuP4ajgy/hAmtnURHdAuVp9EyZFzXV0vpDXAgMBAAECggEALuH0D/9VWU812wQLVehof2m3tQVRySQE61JoSG7GeoaywibWGrPA1ZZV25udABAP27IIyP4q/NvlnhuDkkoPnHzEsEc8zd+gBR8UVdTGSWOZYg2lLfSJX8907Um4vwEimXnDCcX1ob01vG/TrLPnDucaLo6Ew7wEVhPvkO0OG2/+3v29r2e6poSfM1zINMu3U5bCGlahGcVhRnx23J4n2ZDmOKeDU5vSfUaWrb0gT8MoMY/Y58JOd6YBVbeoIg661zkjmwgv50a+/nb3qzdIh3HgZicYWs/vKfZZ9gMe++Ukhy0JPMFKjSATZgZu8xVIm8m68UEAt+MqcDJG+f6s6QKBgQDKVymP/iwzj49D2j1TYkg++sESKG3jzUq/vvNaBUSC8oYPvlkQqGRLYfRlCusCuL1y3k3lpo4oVvo/jR2ShbPRIWFMTfVt9acafHZMCTaB/wo6/cK45ZjhMEvdfaniFaTdRbsKBigHNb9NQ2k2oC4XuxLr0jXURr7SueaKa74sAwKBgQCp8IpOZjI6GMte/6b8fNhyfofZHkwBxdSVh/Cq2H+FDzDm1Gi2WbOCknZoLkiQOaaIL8XBM3sbs9W3/KMD42jX58Bdgk+RipjNA1B8dzcVxrvGGWWhXJ+QH0jfzzyJsrxs4i6oL4mgNLnb91fM5tOQhTUvUQ8aGD+kKgyB8jsxnQKBgQCa1/Mlj4Rx/NXNPjEaI6dYEvs3kxrtbshaTp3acReKAmDXoXp1Rfhiu9aUkLNiRNAuHLOOIFS/yDf/9FUCMTF3xEy6YRqGCKzVlxPMgmxlNTC2DkY6yvGgux4DpUwhiSC+eMN3G1j8k4QPc5wLwq8jV/VV5GtvRKh5iOxFV8iT0wKBgF+tgBD31NuEziukQD3zhGGh/5YsSprM6Q1vRf7KebFOhjfP60yPYFPpZiTtugkJjEssqmhGNc+5BmDaKmWsCYFVh6aeEXJd1/3FGfGZpTfrdhjof6HD5kpccskfgnP8X73l8mLasN+0D9haf+JrKz444WLMfnYwpNQmoHghC1a5AoGAZGkosuEFKfRGgF1fOu1VT4dbhEtCq8dVB70f//b3104dnF9x0ABrLlTUR3muDmGp22xgBAbaG0+qV3sip8i9Rzfxt11ksZtU+kybVk4q7nmcHW/BqCSMbv93N9NeoD7TYroY0W1w5RSWk7Zf8oFhXqtnRwQ5HYxBt5Qt2Dovj8Y=\n-----END RSA PRIVATE KEY-----");
	BIO *bo = BIO_new(BIO_s_mem());
	BIO_write(bo, key, strlen(key));

	EVP_PKEY *pkey = 0;
	PEM_read_bio_PrivateKey(bo, &pkey, 0, 0);
	BIO_free(bo);
	RSA *rsa = EVP_PKEY_get1_RSA(pkey);

	Crypto crypto;
	char EncryptedRSA[2048];
	memset(EncryptedRSA, 0, 2048);
	sprintf(EncryptedRSA, "g29BE33A0kxBAepemy2DN8h/sFVgukJeBVHGwOCzzmQYyLGurkpU7VojPGaoOv1ARIiiV1rTt19JOTLFpLhP7ZYx9N3iB6UAJMGu0eVXzYidtLOqsekJIPP8SbUSWUSEXZUJ/oEEf9SHjD2ZO7uIBsjh7cSY9gFEwjfYqTqxI1JFBkm5inPcvuvK247fKbnQj41lXUMTGM71cXtl0X8YdImC/3IFX/oDstpBcug+AEjGkdGfRHZHeW2KhqEL866cCsUmrz/YDixgnvQvOTtlgjWaDrLoXSkmMntzoXm1mwWuU/Ms3DE/DpaGmnXrwg/O8DVlc9RR1mCEGkkJofzI7g==");
	char *pDecryptedRSA = crypto.RSA_DecryptPrivate(rsa, EncryptedRSA);
	if (pDecryptedRSA != NULL)
	{
		// 복호화 결과: ysoftman lemon apple
		printf("RSA decrypted: %s\n", pDecryptedRSA);
		delete[] pDecryptedRSA;
	}
	crypto.RSA_Free(rsa);
}

int main()
{
	Base64_test();
	AES_test();
	RSA_test();
	RSA_decrypt_with_keystring_test();
	return 0;
}
