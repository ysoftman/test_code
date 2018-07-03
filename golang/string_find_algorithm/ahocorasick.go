// aho_corasick 알고리즘으로 문자열 찾기
package main

import "fmt"

// Node 그래프를 구성할 노드
type Node struct {
	isRoot bool
	value  string
	child  map[string]*Node
	fail   *Node // 현재 노드까지 와서 찾는 정보가 없을 경우 이동할 노드
	output *Node // 현재 노드까지 왔을때까지 word 찾았다면 다음 으로 이동할 노드
}

// sentence : 문자열이 포함될수 있는 문장
// words : 찾을 문자열들
func ahocorasick(sentence string, words []string) (indexes []int, results []string) {
	fmt.Println("sentence: ", sentence)
	fmt.Println("words: ", words)

	makeTire(words)
	return indexes, results
}

// words 들로 Tire(tree 의 일종) 생성
func makeTire(words []string) {
	// maxwordlen := len(words[findmaxlenwords(words)])

	// words 들로 그래프 구성
	root := &Node{
		isRoot: true,
	}
	for i := 0; i < len(words); i++ {
		fmt.Println("insertNode: ", words[i])
		insertNode(root, words[i])
	}

	// TODO
	// 1. 그래프에서 각노드의 실패와 성공(output)시 이동할 노드 설정된 완벽한 타이어(Tire) 구성
	// 2. 타이어를 참조해서 sentence 에서 words 찾기

}

func insertNode(node *Node, w string) {
	for i := 0; i < len(w); i++ {
		if node.child == nil {
			node.child = make(map[string]*Node)
		}
		if node.child[string(w[i])] != nil {
			fmt.Println("exist ", string(w[i]))
			node = node.child[string(w[i])]
		} else {
			fmt.Println("new ", string(w[i]))
			node.child[string(w[i])] = &Node{
				isRoot: false,
				value:  string(w[i]),
				child:  nil,
				fail:   nil,
				output: nil,
			}
			node = node.child[string(w[i])]
		}
	}
}

// func findmaxlenwords(words []string) int {
// 	idx, maxlen := 0, 0
// 	for i := 0; i < len(words); i++ {
// 		if len(words[i]) > maxlen {
// 			idx = i
// 			maxlen = len(words[i])
// 		}
// 	}
// 	fmt.Println("max_word_idx:", idx)
// 	fmt.Println("max_word_len:", maxlen)
// 	fmt.Println("max_word:", words[idx])
// 	return idx
// }
