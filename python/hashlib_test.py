# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : hash 생성 테스트

# MD5, SHA1, SHA224, SHA256, SHA384, SHA512
import hashlib

data = b"ysoftman"

# md5 해싱
md5 = hashlib.md5()
md5.update(data)
print("md5 = %s" % md5.hexdigest())

# sha1 해싱
sha1 = hashlib.sha1()
sha1.update(data)
print("sha1 = %s" % sha1.hexdigest())

# sha224 해싱
sha224 = hashlib.sha224()
sha224.update(data)
print("sha224 = %s" % sha224.hexdigest())

# sha256 해싱
sha256 = hashlib.sha256()
sha256.update(data)
print("sha256 = %s" % sha256.hexdigest())

# sha512 해싱
sha512 = hashlib.sha512()
sha512.update(data)
print("sha512 = %s" % sha512.hexdigest())
