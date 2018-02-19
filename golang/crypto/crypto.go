package main

import (
	"crypto/aes"
	"crypto/cipher"
	"fmt"
)

// AESCTREncrypt aes ctr 암호화
func AESCTREncrypt(key, iv, plaintext string) string {
	byteKey := []byte(key)
	byteIV := []byte(iv)
	bytePlainText := []byte(plaintext)

	block, err := aes.NewCipher(byteKey)
	if err != nil {
		panic(err)
	}

	ciphertext := make([]byte, len(bytePlainText))
	stream := cipher.NewCTR(block, byteIV)
	stream.XORKeyStream(ciphertext, bytePlainText)

	return string(ciphertext)
}

// AESCTRDecrypt aes ctr 복호화
func AESCTRDecrypt(key, iv, encryptedtext string) string {
	byteKey := []byte(key)
	byteIV := []byte(iv)
	byteEncryptedText := []byte(encryptedtext)

	block, err := aes.NewCipher(byteKey)
	if err != nil {
		panic(err)
	}

	plaintext2 := make([]byte, len(byteEncryptedText))
	stream := cipher.NewCTR(block, byteIV)
	stream.XORKeyStream(plaintext2, byteEncryptedText)

	return string(plaintext2)
}

func main() {

	// key 의 길이에 따라 16bytes(AES-128), 24bytes(AES-192), 32bytes(AES-256) 로 구분된다.
	key := "ysoftmanAesKey12ysoftmanAesKey12"
	// iv 는 16bytes 여야 한다.
	iv := "abcdefghijklmnop"
	plaintext := "(PlainText) 암호(AES) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다."
	fmt.Printf("[key]\n%s\n", key)
	fmt.Printf("[iv]\n%s\n", iv)
	fmt.Printf("[plaintext]\n%s\n", plaintext)
	fmt.Println()

	encrypted := AESCTREncrypt(key, iv, plaintext)
	fmt.Printf("[AESCTREncrypt]\n%X\n", encrypted)
	decrypted := AESCTRDecrypt(key, iv, encrypted)
	fmt.Printf("[AESCTRDecrypt]\n%s\n", decrypted)
}
