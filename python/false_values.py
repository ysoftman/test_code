def noneFunc():
    print("noneFunc()")


def trueFunc():
    print("trueFunc()")
    return True


def falseFunc():
    print("falseFunc()")
    return False


print(True)
# false values
print(bool(None))
print(False)
print(bool(0))
print(bool(""))
print(bool(()))
print(bool([]))
print(bool({}))

if noneFunc() or falseFunc() or trueFunc():
    print("ok")
