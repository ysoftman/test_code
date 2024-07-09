// ysoftman
// util 함수 구현
package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

// Swap 함수
func Swap(a, b int) (c, d int) {
	c, d = a, b
	if a == b {
		return c, d
	}
	c ^= d
	d ^= c
	c ^= d
	return c, d
}

// IAbs : int 형 절대값 구하기
func IAbs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

// ConvertToFloat : , 를 소수점으로 계산해서 변환
func ConvertToFloat(str string) float32 {
	numberSplit := strings.Split(str, ",")
	high := numberSplit[0]
	low := numberSplit[1]

	out1, _ := strconv.Atoi(high)
	out2, _ := strconv.Atoi(low)
	result := float32(0.0)
	result += float32(out1)

	// 소수점으로 만들기
	out3 := float32(out2)
	for out3 > 1 {
		out3 = float32(out3) / float32(10)
		// fmt.Println("out1:", out1, " out2:", out2, " out3:", out3)
	}

	result += float32(out3)
	return result
}

// RemoveCommaAndAtoi : , 제거후 int 형으로 변환
func RemoveCommaAndAtoi(str string) int {
	numberSplit := strings.Split(str, ",")
	newnumber := ""
	for _, value := range numberSplit {
		newnumber += value
	}
	out, _ := strconv.Atoi(newnumber)
	return out
}

type NodeInfo struct {
	num  int
	node []NodeInfo
}

// AddChildNode 자식 노드 추가
func AddChildNode(parent *NodeInfo, num int) {
	parent.node = append(parent.node, NodeInfo{num, nil})
	fmt.Fprintf(os.Stdout, "add parent.node[%v].num:%v\n", len(parent.node)-1, parent.node[len(parent.node)-1].num)
}

// TraverseNode 노드 탐색
func TraverseNode(node *NodeInfo, cnt *int, depth int) {
	for i := 0; i < len(node.node); i++ {
		(*cnt)++
		for j := 0; j < depth; j++ {
			fmt.Fprintf(os.Stdout, "    ")
		}
		fmt.Fprintf(os.Stdout, "node[%v].num:%v\n", i, node.node[i].num)
		TraverseNode(&node.node[i], cnt, depth+1)
	}
}

// FloatToString 부동 끝자리 0 으로 매워지는 부분 제거
func FloatToString(f float64) string {
	str := fmt.Sprintf("%f", f)
	str = strings.TrimRight(str, "0")
	str = strings.TrimRight(str, ".")

	return str
}

// IsInfiniteDecimal 무한 소수 인지 체크
func IsInfiniteDecimal(n int) bool {
	// 참고 http://study.zum.com/book/13777
	// 분모를 소인수 분해 했을대 2, 5외것이 있다면 무한 소수이다
	var ele []int
	i := 2
	for n != 1 {
		for n%i == 0 {
			n = n / i
			ele = append(ele, i)
		}
		i++
	}
	// fmt.Fprintln(os.Stderr, "ele:", ele)
	for i := range ele {
		// fmt.Fprintln(os.Stderr, ele[i])
		if ele[i] != 2 && ele[i] != 5 {
			return true
		}
	}
	return false
}

// util 함수 테스트
func main() {
	fmt.Println("util test...")

	// swap
	a, b := 2, 30
	fmt.Println("before swap a:", a, "b:", b)
	a, b = Swap(a, b)
	fmt.Println("after swap a:", a, "b:", b)

	// 문자열 -> float 변환
	number1 := "12345,6789"
	fmt.Println("number1 string:", number1)
	fmt.Println("RemoveCommaAndAtoi(number1):", RemoveCommaAndAtoi(number1))
	fmt.Println("ConvertToFloat(number1):", ConvertToFloat(number1))

	// abs
	op1 := 2
	op2 := 5
	floatResult := float32(IAbs(op1-op2))/2 + 0.5
	fmt.Printf("floatResult:%f\n", floatResult)
	intResult := int(float32(IAbs(op1-op2))/2 + 0.5)
	fmt.Printf("intResult:%d\n", intResult)

	// 다중 링크 노드 테스트
	var mynode NodeInfo
	mynode.num = 1
	mynode.node = nil
	// 새 노드를 링크로 추가
	// mynode.node[0] = NodeInfo{} --> index out of range 에러 발생!
	// mynode.node[0] = NodeInfo{1, nil} --> index out of range 에러 발생!
	mynode.node = append(mynode.node, NodeInfo{2, nil})
	mynode.node = append(mynode.node, NodeInfo{3, nil})
	mynode.node[0].node = append(mynode.node[0].node, NodeInfo{4, nil})
	mynode.node[1].node = append(mynode.node[1].node, NodeInfo{5, nil})
	// mynode.node[1].node[0].node = append(mynode.node[1].node[0].node, NodeInfo{6, nil})
	AddChildNode(&mynode.node[1].node[0], 6)
	AddChildNode(&mynode.node[1].node[0], 7)
	// AddChildNode(&mynode.node[1].node[0].node[1], 8)
	rootnode := mynode
	// 노드변수(struct 포인터변수를 사용한다.)
	mynode2 := &mynode.node[1].node[0].node[1]
	AddChildNode(mynode2, 8)

	fmt.Println(mynode)
	nodecnt := 0
	TraverseNode(&rootnode, &nodecnt, 0)
	fmt.Println("rootnode total node cnt:", nodecnt)

	// 부동 끝자리 0 으로 매워지는 부분 제거
	f1 := 1 / float64(25000)
	fmt.Println("f1:", f1)
	fmt.Printf("f1:%f\n", f1)
	fmt.Printf("f1:%e\n", f1)
	fmt.Printf("f1:%g\n", f1)
	fmt.Printf("f1:%s\n", FloatToString(f1))

	// 무한 소수 판단
	for i := 1; i < 100; i++ {
		fmt.Printf("1/%d IsInfiniteDecimal:%t\n", i, IsInfiniteDecimal(i))
	}
}
