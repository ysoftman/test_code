
# *가변인자 표현
def func1(a, b, *c):
    print("a,b=", a, b, sep=",")
    print("c=", end=" ")
    for i in c:
        print(i, end=" ")
    print("")
    print("---")

func1(1,2,3,4,5,6,7)
func1(1,2)
func1(1,2,3,4,"lemon")


def func2():
    return "a", "b", 123

print(func2())
