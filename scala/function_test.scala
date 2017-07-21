// scala 함수 테스트
val string="scala function test"
println(string)
val num1 = 1
val num2 = 2
println(num1,num2)
println(num1+num2)

// 함수 사용
def addInt(num: Int): Int = {
    num + 1
}
// 재할당 할 수 없다.
// num1 = addInt(1)
val num3 = addInt(1)
// s"" 리터럴 출력
println(s"addInt=$num3")
println("addInt="+addInt(1))

def addInt2(num1: Int, num2: Int) = {
    num1 + num2 + 1
}
println("addInt="+addInt2(2, 2))

def addInt2_1(num1: Int)(num2: Int) = {
    num1 + num2 + 1
}
println("addInt="+addInt2(2, 2))

// 함수 인자 미리 설정해 놓기
val addInt3 = addInt2(5, _:Int)
val addInt4 = addInt2(_:Int, 7)
println("addInt="+addInt3(5))
println("addInt="+addInt4(5))
