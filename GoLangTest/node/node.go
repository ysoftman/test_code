// ysoftman
// 노드 및 링크 정보를 저장
package main

import (
	"fmt"
	"os"
)

type nodeinfo struct {
	name string
	node []int
}

func main() {
	var node map[int]nodeinfo
	node = make(map[int]nodeinfo)
	// 노드에 링크 정보 추가
	node[3] = nodeinfo{
		"node",
		[]int{1, 2},
	}
	node[3] = nodeinfo{
		"node",
		append(node[3].node, 4),
	}
	node[1] = nodeinfo{
		"node",
		[]int{3},
	}
	node[2] = nodeinfo{
		"node",
		[]int{3},
	}
	node[4] = nodeinfo{
		"node",
		[]int{3},
	}
	fmt.Println(node)
	fmt.Println(node[3])
	fmt.Println(node[1])
	fmt.Println(node[2])
	fmt.Println(node[4])

	// map struct 포인터타입으로 사용
	var node2 map[int]*nodeinfo
	node2 = make(map[int]*nodeinfo)
	node2[3] = &nodeinfo{}
	node2[3].name = "aaa"
	node2[3].node = []int{1, 2}
	fmt.Fprintln(os.Stderr, "node2", node2)
	// fmt.Println("node2", node2)
	fmt.Fprintln(os.Stderr, "node2[3]", node2[3])
	// fmt.Println("node2[3]", node2[3])
}
