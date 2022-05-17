def noneFunc():
    print("noneFunc()")
    return None


def trueFunc():
    print("trueFunc()")
    return True


def falseFunc():
    print("falseFunc()")
    return False


print(bool(True))
# false values
print(bool(None))
print(bool(False))
print(bool(0))
print(bool(""))
print(bool(()))
print(bool([]))
print(bool({}))

if noneFunc() or falseFunc() or trueFunc():
    print("ok")
