// ysoftman
// aho_corasick 알고리즘으로 문자열 찾기
package main

import (
	"container/list"
	"fmt"
)

// Node 그래프를 구성할 노드
type Node struct {
	depth  int              // 현재 노드의 깊이(for debugging)
	parent *Node            // 현재 노드의 부모(for debugging)
	isRoot bool             // 루트노드 여부
	value  string           // 현재 노드까이 왔을때의 문자열
	child  map[string]*Node // 문자하나:자식노드 를 맵으로 구성
	fail   *Node            // 현재 노드까지 와서 찾는 정보가 없을 경우 이동할 노드
	out    *Node            // 현재 노드까지 왔을때까지 word 찾았다면(성공) 다음 으로 이동할 노드, 찾은 word 의 suffix 가 다른 찾을 word 의 substring이 되는 경우 사용
}

// aho_corasick algorithm
// sentence : 문자열이 포함될수 있는 문장
// words : 찾을 문자열들
// sentence길이(m) + word수(n) + mismatch(트라이에서 찾으면서 발생하는 실패회수,a) = O(m+n+a) 의 선형시간으로 빠르게 문자열을 찾는다.
func ahocorasick(sentence string, words []string) (indexes []int, results []string) {
	fmt.Println("sentence: ", sentence)
	fmt.Println("words: ", words)

	// Trie 구성
	root := makeTrie(words)

	// TODO
	// 트라이를 참조해서 sentence 에서 패턴들(words) 찾기
	node := root
	node.depth = 0
	for i, s := range sentence {
		fmt.Printf("%2d %c\n", i, s)

		indexes = append(indexes, i)
		results = append(results, string(sentence[i]))
	}
	return indexes, results
}

// words 들로 Trie(tree 의 일종) 생성
func makeTrie(words []string) *Node {
	// words 들로 그래프 구성
	root := &Node{
		isRoot: true,
		value:  "",
		fail:   nil, // 루트의 실패노드는 갈곳 이 없다.(그대로 종료)
		out:    nil, // 루트의 성공
	}
	for i := 0; i < len(words); i++ {
		fmt.Println("insertNode:", words[i])
		insertNode(root, words[i])
	}
	printTrie(root)

	// 그래프에서 각노드의 실패(fail)와 성공(out)시 이동할 노드 설정된 완벽한 트라이(Trie) 구성
	// list 로 트라이의 부모 -> 자식 순서로 리스트의 front 부터 너비 우선 탐색이 되도록 한다.
	lst := list.New()
	lst.PushBack(root)
	for lst.Len() > 0 {
		// 리스트의 처음(부모 노드)는 삭제한다.
		// lst.Remove 는 해당 노드를 삭제하고 삭제된 노의 값을 리턴
		curnode := lst.Remove(lst.Front()).(*Node)
		for _, v := range curnode.child {
			child := v
			// 자식 노드가 있으면 리스트로 추가
			if child != nil {
				lst.PushBack(child)
			}
			// 실패노드는 현재 노드보다 부모노들중 가장 긴 매칭 문자열을 가지는 노드여야 한다.
			// 현재 노드까지 매칭된 값으로 보모노드들중 실패노드가 될 수 있는 것을 찾는다.
			for i := 1; i < len(child.value); i++ {
				// 현재 노드까지의 스트링과 같은 노드를 찾으면 안되니, 첫 스트링부터 제외하고 찾아야 하다.(suffix 를 줄여가며)
				fmt.Println(child.value, "-", child.value[i:])
				child.fail = setFailNode(root, child.value[i:])
				if child.fail != nil {
					fmt.Println("setFailNode:", child.depth, child.value, "->", child.fail.depth, child.fail.value)

					if child.fail.child == nil {
						fmt.Println("setOutNode:", child.value, "->", child.fail.depth, child.fail.value)

					}
					break
				}
				// 실패노드를 찾지못하면 루트노드로 설정
				if child.fail == nil {
					child.fail = root
					fmt.Println("setFailNode:", child.depth, child.value, "->", child.fail.depth, child.fail.value)
				}
			}
		}
	}

	return root
}

func insertNode(node *Node, w string) {
	for i := 0; i < len(w); i++ {
		if node.child == nil {
			node.child = make(map[string]*Node)
		}
		// 현재 노드의 자식노들중 해당 문자가 없는 경우만 새로 추가(생성)
		if node.child[string(w[i])] != nil {
			// fmt.Println("exist-node", string(w[i]))
			node = node.child[string(w[i])]
		} else {
			// fmt.Println("new-node ", string(w[i]), " set value:", string(w[:i+1]))
			node.child[string(w[i])] = &Node{
				depth:  node.depth + 1,
				parent: node,
				isRoot: false,
				value:  string(w[:i+1]),
				child:  nil,
				fail:   nil,
				out:    nil,
			}
			node = node.child[string(w[i])]
		}
	}
}

func setFailNode(root *Node, w string) *Node {
	// 루트부타 w 와 매칭되는 노드들을 찾아본다.
	node := root
	for node != nil && len(w) > 0 {
		fmt.Println(string(w[0]))
		if node.child[string(w[0])] != nil {
			node = node.child[string(w[0])]
		} else {
			node = nil
			break
		}
		w = w[1:]
	}
	// fmt.Println("node:", node)
	return node
}

func printTrie(root *Node) {
	lst := list.New()
	lst.PushBack(root)
	// BFS(Breadth First Search)
	for lst.Len() > 0 {
		node := lst.Remove(lst.Front()).(*Node)
		for k, v := range node.child {
			fmt.Println("depth:", v.depth, "(key:", k, ", string:", v.value, ")")
			if v != nil {
				lst.PushBack(v)
			}
		}
	}
}
