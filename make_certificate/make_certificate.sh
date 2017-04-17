#!bin/bash
# ysoftman
# 인증서 만들기

# openssl 설치
if [ $(uname) == 'Darwin' ]; then
    brew install openssl
    export PATH="/usr/local/opt/openssl/bin:$PATH"
    source ~/.zshrc
fi
# openssl 버전 확인()
openssl version

CA_NAME='ysoftman'
DOMAIN="${CA_NAME}.com"

# 참고 https://www.lesstif.com/pages/viewpage.action?pageId=6979614#OpenSSL로ROOTCA생성및SSL인증서발급-ROOTCA인증서생성

##########
# root-ca(root Certificate Authority, 최상위 인증기관) SSC(Self Signed Certificate, 스스로 서명한 인증서) 만들기
# 1. ca 에서 사용할 개인키 생성(rsa방식, aes256암호화), 2048bit 생성시 암호 입력
openssl genrsa -aes256 -out ./${CA_NAME}-rootca.key 2048

# 2. CSR(Certificate Signing Request, 인증기관에 인증서 발급을 요청하는 파일) 만들기
# 2-1. csr 생성에 사용할 설정 파일 생성
echo "[ req ]
default_bits            = 2048
default_md              = sha1
default_keyfile         = ${CA_NAME}-rootca.key
distinguished_name      = req_distinguished_name
extensions              = v3_ca
req_extensions          = v3_ca
  
[ v3_ca ]
basicConstraints            = critical, CA:TRUE, pathlen:0
subjectKeyIdentifier        = hash
##authorityKeyIdentifier    = keyid:always, issuer:always
keyUsage                    = keyCertSign, cRLSign
nsCertType                  = sslCA, emailCA, objCA

[req_distinguished_name ]
countryName                 = Country Name (2 letter code)
countryName_default         = KR
countryName_min             = 2
countryName_max             = 2
 
organizationName                = Organization Name (eg, company)
organizationName_default        = ${CA_NAME}
#organizationalUnitName         = Organizational Unit Name (eg, section)
#organizationalUnitName_default = Organizational Unit Name

commonName                     = Common Name
commonName_default             = ${CA_NAME} Self Signed CA
commonName_max                 = 64 
" > ./${CA_NAME}-rootca-openssl.conf

# 2-2. 앞서 생성한 개인키와 설정파일을 이용하여 csr 생성
openssl req -new -key ./${CA_NAME}-rootca.key -config ./${CA_NAME}-rootca-openssl.conf -out ./${CA_NAME}-rootca.csr

# 3. crt 생성
openssl x509 -req -days 3650 -extensions v3_ca -set_serial 1 -in ./${CA_NAME}-rootca.csr -signkey ./${CA_NAME}-rootca.key -out ./${CA_NAME}-rootca.crt -extfile ./${CA_NAME}-rootca-openssl.conf


##########
# SSL 인증서 만들기
# 1. SSL 서버에서 사용할 개인키
openssl genrsa -aes256 -out ./${DOMAIN}.key 2048

# 1-1. 웹서버 구동시 마다 암호 입력을 피하기 위해 암호 제거
cp  ./${DOMAIN}.key ./${DOMAIN}.key.enc
openssl rsa -in  ./${DOMAIN}.key.enc -out ./${DOMAIN}.key

# 2. CSR(Certificate Signing Request, 인증기관에 인증서 발급을 요청하는 파일) 만들기
# 2-1. csr 생성에 사용할 설정 파일 생성
echo "[ req ]
default_bits            = 2048
default_md              = sha1
default_keyfile         = ${CA_NAME}-rootca.key
distinguished_name      = req_distinguished_name
extensions              = v3_user
# 인증서 요청시에도 extension 이 들어가면 authorityKeyIdentifier 를 찾지 못해 에러가 나므로 막아둔다.
# req_extensions          = v3_user
 
[ v3_user ]
basicConstraints        = CA:FALSE
authorityKeyIdentifier  = keyid,issuer
subjectKeyIdentifier    = hash
keyUsage                = nonRepudiation, digitalSignature, keyEncipherment
## SSL 용 확장키 필드
extendedKeyUsage        = serverAuth,clientAuth
subjectAltName          = @alt_names

[ alt_names ]
DNS.1   = www.${DOMAIN}
DNS.2   = ${DOMAIN}
DNS.3   = *.${DOMAIN}
 
[req_distinguished_name ]
countryName                     = Country Name (2 letter code)
countryName_default             = KR
countryName_min                 = 2
countryName_max                 = 2

organizationName                = Organization Name (eg, company)
organizationName_default        = ${DOMAIN}
organizationalUnitName          = Organizational Unit Name (eg, section)
organizationalUnitName_default  = Organizational Unit Name

commonName                      = Common Name
commonName_default              = ${DOMAIN}
commonName_max                  = 64
" > ./${DOMAIN}-host-openssl.conf

# 2-2. 앞서 생성한 개인키와 설정파일을 이용하여 csr 생성
openssl req -new  -key ./${DOMAIN}.key -out ./${DOMAIN}.csr -config ./${DOMAIN}-host-openssl.conf

# 3. crt 생성
openssl x509 -req -days 3650 -extensions v3_user -set_serial 1 -in ./${DOMAIN}.csr -signkey ./${DOMAIN}.key -out ./${DOMAIN}.crt -extfile ./${DOMAIN}-host-openssl.conf
