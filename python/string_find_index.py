str1="lemon apple orange"


# find() 로 index 찾기
print(str1.find("apple"))
print(str1.find("a"))
print(str1.find("a", 10)) # 10위치부터 찾기
print(str1.find("zzz")) # 못찾으면 -1

# index() 로 index 찾기
print(str1.index("apple"))
print(str1.index("e", 3))
# print(str1.index("zzz")) # 못찾으면 에러로 중딘
