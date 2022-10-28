import unicodedata

# 공백은 0xa0 NBSP(Non-breaking space) 문자이다.
print(" _is_nbsp")

# NBSP 문자 출력 방법
print("\u00A0")
print("\xa0")
test = "a \u00A0 b"
print("add nbsp:", test)
test = "a \xa0 b"
print("add nbsp:", test)

# NBSP 문자 제거
test2 = test.replace("\xa0", "")
print("remove nbsp:", test2)


# 출처 위키피디아
# NFD
# Normalization Form Canonical Decomposition	Characters are decomposed by canonical equivalence, and multiple combining characters are arranged in a specific order.
# NFC
# Normalization Form Canonical Composition	Characters are decomposed and then recomposed by canonical equivalence.
# NFKD
# Normalization Form Compatibility Decomposition	Characters are decomposed by compatibility, and multiple combining characters are arranged in a specific order.
# NFKC
# Normalization Form Compatibility Composition	Characters are decomposed by compatibility, then recomposed by canonical equivalence.

# NO-BREAK SPACE  U+00A0
# NO-BREAK SPACE, NARROW  U+202F
# NO-BREAK SPACE, ZERO WIDTH  U+FEFF
test = "a \u00a0\u202f\u202f\ufeff\ufeff b"
print("befere:", test)
# 공백문자로 모두 치환할 경우
test2 = unicodedata.normalize("NFKD", test)
print("after:", test2)
