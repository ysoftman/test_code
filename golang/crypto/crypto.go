package main

import (
	"bytes"
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"fmt"
	"io"
)

// encryptAESCTR aes ctr 암호화
func encryptAESCTR(key, iv, plaintext string) string {
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

// decryptAESCTR aes ctr 복호화
// CTR : block counter mode, cipher block size 와 iv 길이는 같아야 한다.
func decryptAESCTR(key, iv, encryptedtext string) string {
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

func encryptAESCBC(key, plain string) string {
	plaintext := []byte(plain)

	// aes_cbc 에서 데이터는 iv(16) 의 배수 크기여야 한다.
	// 16의 배수라도 16바이틀들 더 붙여(padding)
	// decrypt 시에 ciphertext[마지막바이트] 명시된 개수 만큰 padding 부분을 슬라이싱해서 제거 할 수 있다.
	paddingSize := aes.BlockSize - len(plaintext)%aes.BlockSize
	fmt.Println("length of plaintext: ", len(plaintext))
	fmt.Println("length of aes.BlockSize: ", aes.BlockSize)
	fmt.Println("length of paddingSize: ", paddingSize)
	padtext := bytes.Repeat([]byte{byte(paddingSize)}, paddingSize)
	fmt.Println("padtext: ", padtext)
	plaintext = append(plaintext, padtext...)

	block, err := aes.NewCipher([]byte(key))
	if err != nil {
		panic(err)
	}

	ciphertext := make([]byte, aes.BlockSize+len(plaintext))
	// aes_cbc 에서 iv 는 encrypt 의 첫 16바이트를 사용한다.
	iv := ciphertext[:aes.BlockSize]
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext[aes.BlockSize:], plaintext)

	fmt.Printf("ciphertext: %x\n", ciphertext)
	// return (hex.EncodeToString([]byte(ciphertext)))
	return string(ciphertext)
}

// CBC : block chainning mode, cipher block size 와 iv 길이는 같아야 하고 encrypt 시에 사용한 iv 데이터가 있어야 한다.
func decryptAESCBC(key, cipherhex string) string {
	// ciphertext, _ := hex.DecodeString(cipherhex)
	ciphertext := (cipherhex)

	block, err := aes.NewCipher([]byte(key))
	if err != nil {
		panic(err)
	}

	iv := ciphertext[:aes.BlockSize]
	ciphertext = ciphertext[aes.BlockSize:]

	// CBC mode always works in whole blocks.
	if len(ciphertext)%aes.BlockSize != 0 {
		panic("ciphertext is not a multiple of the block size")
	}

	mode := cipher.NewCBCDecrypter(block, []byte(iv))
	decrypted := make([]byte, len(ciphertext))
	mode.CryptBlocks([]byte(decrypted), []byte(ciphertext))
	fmt.Println("decrypted bytes: ", decrypted)
	// padding 부분이 까지 추가되어 원본데이터의 길이보다 길다.
	// encrypt 시 16의 배수라도 16바이틀들 더 붙여(padding)놓은 상태다
	// decrypt 시에 ciphertext[마지막바이트] 에 명시된 개수 만큼 padding 부분을 슬라이싱해서 제거 할 수
	l := len(decrypted)
	cutcnt := decrypted[l-1]
	fmt.Println("decrypted[len(decrypted)-1]:\n", cutcnt)
	decrypted = decrypted[:(l - int(cutcnt))]
	fmt.Println("decrypted bytes(unpadding):\n", decrypted)
	return string(decrypted)
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

	encrypted := encryptAESCTR(key, iv, plaintext)
	fmt.Printf("[encryptAESCTR]\n%X\n", encrypted)

	// hexadecimal string 으로 변환
	hexstring := hex.EncodeToString([]byte(encrypted))
	fmt.Printf("[encryptAESCTR hex]\n%s\n", hexstring)

	decrypted := decryptAESCTR(key, iv, encrypted)
	fmt.Printf("[decryptAESCTR]\n%s\n", decrypted)
	fmt.Println()
	fmt.Println()

	fmt.Println("--- aes-256-cbc ---")
	key = "abcdefghijklmnop"
	plaintext = "(PlainText) 암호(AES) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다."
	fmt.Println("[key]")
	fmt.Println(key)
	fmt.Println("[plaintext]")
	fmt.Println(plaintext)
	fmt.Println()

	encrypted = encryptAESCBC(key, plaintext)
	fmt.Printf("[encryptAESCBC]\n%s  len:%d\n", encrypted, len(encrypted))
	decrypted = decryptAESCBC(key, string(encrypted))
	fmt.Printf("[decryptAESCBC]\n%s len:%d\n", decrypted, len(decrypted))
}
