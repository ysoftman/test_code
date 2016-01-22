#include "Cryptography.h"

/**
*	@brief					Crypto Ŭ���� ������
*	@author					������
*	@param					None
*	@return					None
*/
Crypto::Crypto()
{
}

/**
*	@brief					Crypto Ŭ���� �Ҹ���
*	@author					������
*	@param					None
*	@return					None
*/
Crypto::~Crypto()
{
	// ���� �������� Error Queue ����
	ERR_remove_state(0);
	// Errot String ����
	ERR_free_strings();
	// ENGIN ����
	ENGINE_cleanup();
	// EVP ����
	EVP_cleanup();

	//This function is used to cleanup application specific data and should be called before the application shuts down to avoid memory leaks.
	//CRYPTO_cleanup_all_ex_data();
}


/**
*	@brief						Crypto Ű ����
*	@author						������
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
*	@brief						RSA Ű �����ϴ� �Լ�
*	@author						������
*	@param			KeySize		������ Ű ������(��Ʈ������� 512bit, 1024bit, 2048bit ...)
*	@return						�����ϸ� RSA Ű ����
*/
RSA* Crypto::RSA_GenerateKey(int KeySize)
{
	// Ű ������ ���� ���尪 ����
	//const char seed[] = "2$#^B@$^B)@VM*@)#$^*C)MPTSVDMPSVCSPRM_^*X#^*V#*&#*&%)CF*";
	//RAND_seed(seed, sizeof(seed));

	// Ű����� ���� Ű ����
	// �ι�° �Ķ���ʹ� ����(exponent) ������ ���� 3 17 65537 �� �Ҽ��� ����Ѵ�.
	RSA *rsa = RSA_generate_key(KeySize, 17, NULL, NULL);
	if (NULL == rsa)
	{
		return NULL;
	}

	// ������ Ű�� üũ
	int ret = RSA_check_key(rsa);
	if (ret != 1)
	{
		return NULL;
	}

	return rsa;
}

/**
*	@brief						RSA ����Ű�� ��ȣȭ
*	@author						������
*	@param			rsa			rsa Ű
*	@param			pPlain		��ȣȭ�� ������
*	@return						��ȣȭ�� ������
*/
char* Crypto::RSA_EncryptPublic(RSA *rsa, char *pPlain)
{
	// Ű ������ �ľ�(bit -> byte �� ��ȯ)
	int KeySize = RSA_size(rsa);

	int PlainLen = strlen(pPlain);

	// RSA_PKCS1_OAEP_PADDING ���� ���� �ִ� ũ�� üũ
	if (PlainLen > KeySize - 41)
	{
		return NULL;
	}

	// ��ȣ����� ������ ����
	char *pBuffer = new char[KeySize];
	memset(pBuffer, 0, sizeof(char)*KeySize);

	// ��ȣȭ
	int CipherLen = RSA_public_encrypt(PlainLen, reinterpret_cast<const unsigned char *>(pPlain), reinterpret_cast<unsigned char*>(pBuffer), rsa, RSA_PKCS1_OAEP_PADDING);

	if (CipherLen <= 0)
	{
		ERR_load_crypto_strings();
		ERR_print_errors_fp(stderr);
		delete[] pBuffer;
		return NULL;
	}

	// ����Ʈ �迭 �߰��� '\0' ���� ���ֱ� ���ؼ� Base64���ڵ��Ѵ�.
	char* pBase64Cipher = Base64_Encoding(pBuffer, CipherLen);
	delete[] pBuffer;

	return pBase64Cipher;
}


/**
*	@brief								RSA ����Ű�� ��ȣȭ
*	@author								������
*	@param			rsa					rsa Ű
*	@param			pBase64Cipher		��ȣȭ�� ������
*	@return								��ȣȭ�� ������
*/
char* Crypto::RSA_DecryptPrivate(RSA *rsa, char *pBase64Cipher)
{
	// Ű ������ �ľ�
	int KeySize = RSA_size(rsa);

	if (pBase64Cipher == NULL)
	{
		return "";
	}

	// Base64���ڵ��� ���������ͺ��� ũ��.
	int CipherBase64Len = strlen(pBase64Cipher);
	// Base64 ���ڵ��Ѵ�.
	char* pCipher = Base64_Decoding(pBase64Cipher, CipherBase64Len);
	if (pCipher == NULL)
	{
		return NULL;
	}
	// pCipher ���� '\0' ���� �߰��� ���Ե� �� �ֱ⶧���� strlen���� ũ�⸦ �ľ��ϸ� �ȵȴ�.
	int CipherLen = 0;
	for (int i=CipherBase64Len-1; i>=0; i--)
	{
		if (pCipher[i] != '\0')
		{
			CipherLen = i+1;
			break;
		}
	}

	// ��ȣȭ�� ����� ������ ����
	// Ű������� Ŭ �� ���⶧����
	char *pBuffer = new char[KeySize];
	memset(pBuffer, 0, sizeof(char)*KeySize);

	// ��ȣȭ
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
*	@brief							AES ��ȣȭ, 128bit(16byte) ��� ������ ��ȣȭ�Ѵ�.
*	@author							������
*	@param			userKey			��ȣȭ�� ����� Ű(128bit, 192bit, 256bit ũ�⸦ ���� �� �ִ�.)
*	@param			iv				��ȣȭ�� ����� �ʱ� ����
*	@param			Plain			��ȣȭ�� ������
*	@return							��ȣȭ�� ������
*/
char* Crypto::AES_CBC_Encrypt(const unsigned char *userKey, unsigned char *iv, string Plain)
{
	if (Plain.length() == 0)
	{
		return NULL;
	}

	// �ѱ��� ���2����Ʈ�� �����ϱ⶧����
	// string ���ڿ� ������ 2�� ũ���� ����Ʈ�� �Ҵ�Ǿ�� �Ѵ�.
	// ��ȣȭ�� ���ڿ��� �ּ� 128bit(16byte) ũ�⸦ �޸� ������ �ʿ��ϴ�.
	// 16byte ������ ���ڿ��� ���ؼ��� ó���� �� �ֵ��� �⺻������ 16byte �޸� ������ Ȯ���ϵ��� �Ѵ�.
	int size = (Plain.length() * 2) + 16;
	char *pPlain = new char[size];
	char *pCipher = new char[size];
	memset(pPlain, 0, sizeof(char)*size);
	memset(pCipher, 0, sizeof(char)*size);

	strcpy(pPlain, Plain.c_str());
	int PlainLen = strlen(pPlain);


	AES_KEY encKey;
	// AES encryption key ����
	if (AES_set_encrypt_key(userKey, 128, &encKey) < 0)
	{
		delete[] pPlain;
		delete[] pCipher;

		return NULL;
	}

	// 16bit ���� ó���ȴ�.
	//AES_encrypt(reinterpret_cast<const unsigned char *>(pPlain), reinterpret_cast<unsigned char *>(pCipher), &encKey);
	// Cipher Block Chaining mode (��ȣ �� ���� ���)�Ʒ� �Լ��� �����ϸ� iv ���� ����ȴ�.
	//AES_cbc_encrypt(reinterpret_cast<const unsigned char*>(pPlain), reinterpret_cast<unsigned char*>(pCipher), PlainLen, &encKey, iv, AES_ENCRYPT);
	// pCipher ���� '\0' ���� �߰��� ���Ե� �� �ֱ⶧���� strlen���� ũ�⸦ �ľ��ϸ� �ȵȴ�.
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


	// ����Ʈ �迭 �߰��� '\0' ���� ���ֱ� ���ؼ� Base64���ڵ��Ѵ�.
	char* pBase64Cipher = Base64_Encoding(pCipher, CipherLen);

	delete[] pCipher;

	//fprintf(stderr, "\nSize = %d, PlainLen = %d, CipherLen = %d\n", size, PlainLen, CipherLen);
	return pBase64Cipher;
}


/**
*	@brief							AES ��ȣȭ, 128bit(16byte) ��� ������ ��ȣȭ�Ѵ�.
*	@author							������
*	@param			userKey			��ȣȭ�� ����� Ű(128bit, 192bit, 256bit ũ�⸦ ���� �� �ִ�.)
*	@param			iv				��ȣȭ�� ����� �ʱ� ����
*	@param			pBase64Cipher	��ȣȭ�� ������
*	@return							��ȣȭ�� ������
*/
string Crypto::AES_CBC_Decrypt(const unsigned char *userKey, unsigned char *iv, char *pBase64Cipher)
{
	if (pBase64Cipher == NULL || strlen(pBase64Cipher) <= 0)
	{
		return "";
	}
	// Base64���ڵ��� ���������ͺ��� ũ��.
	int CipherBase64Len = strlen(pBase64Cipher);

	// Base64 ���ڵ��Ѵ�.
	char* pCipher = Base64_Decoding(pBase64Cipher, CipherBase64Len);
	if (pCipher == NULL)
	{
		return "";
	}
	// pCipher ���� '\0' ���� �߰��� ���Ե� �� �ֱ⶧���� strlen���� ũ�⸦ �ľ��ϸ� �ȵȴ�.
	int CipherLen = 0;
	for (int i=CipherBase64Len-1; i>=0; i--)
	{
		if (pCipher[i] != '\0')
		{
			CipherLen = i+1;
			break;
		}
	}

	// �ѱ��� ���2����Ʈ�� �����ϱ⶧����
	// string ���ڿ� ������ 2�� ũ���� ����Ʈ�� �Ҵ�Ǿ�� �Ѵ�.
	int size = CipherLen * 2;
	char *pPlain = new char[size];
	memset(pPlain, 0, sizeof(char)*size);

	AES_KEY decKey;
	// AES encryption key ����
	if (AES_set_decrypt_key(userKey, 128, &decKey) < 0)
	{
		delete[] pPlain;
		delete[] pCipher;

		return "";
	}

	// 16bit ���� ó���ȴ�.
	//AES_decrypt(reinterpret_cast<const unsigned char *>(pCipher), reinterpret_cast<unsigned char *>(pPlain), &decKey);
	// Cipher Block Chaining mode (��ȣ �� ���� ���)�Ʒ� �Լ��� �����ϸ� iv ���� ����ȴ�.
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
*	@brief							Base64Encoding �ϱ�
*	@author							������
*	@param			pInput			�Է� ���ڿ�
*	@param			Len				�Է� ���ڿ� ����
*	@return							Base64Encoding ���ڿ�
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
	// �ٹٲ޾����� ����
	BIO_set_flags(base64, BIO_FLAGS_BASE64_NO_NL);

	// �޸� Ȯ��
	bmem = BIO_new(BIO_s_mem());
	if (!bmem)
	{
		return NULL;
	}
	bio = BIO_push(base64, bmem);
	// base64���ڵ��ϱ�
	if (BIO_write(bio, pInput, Len) < 0)
	{
		return NULL;
	}
	BIO_flush(bio);
	int len = BIO_get_mem_ptr(bio, &mem);

	// base64���ڵ��� �޸𸮿��� ���۷� �о� ���̱�
	char *buffer = new char[mem->length+1];
	memset(buffer, 0, sizeof(char)*(mem->length+1));
	memcpy(buffer, mem->data, mem->length);

	BIO_free_all(bio);

	return buffer;
}

/**
*	@brief							Base64Decoding �ϱ�
*	@author							������
*	@param			pInput			�Է� ���ڿ�
*	@param			Len				�Է� ���ڿ� ����
*	@return							Base64Decoding ���ڿ�
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
	// �ٹٲ޾����� ����
	BIO_set_flags(base64, BIO_FLAGS_BASE64_NO_NL);

	// �Է� ���ڿ� �޸� �������� �ű��
	bmem = BIO_new_mem_buf(pInput, Len);
	if (!bmem)
	{
		return NULL;
	}

	// base64���ڵ��ϱ�
	bio = BIO_push(base64, bmem);

	// base64���ڵ��� �޸𸮿��� ���۷� �о� ���̱�
	char *buffer = new char[Len];
	memset(buffer, 0, sizeof(char)*Len);
	BIO_read(bio, buffer, Len);

	BIO_free_all(bio);

	return buffer;
}

/**
*	@brief							Base64Encoding ũ�� �ľ��ϱ�
*	@author							������
*	@param			Len				�Է� ���ڿ� ����
*	@return							Base64Encoding ũ��
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

