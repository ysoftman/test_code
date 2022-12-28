package main

import (
	"fmt"

	aq "github.com/emirpasic/gods/queues/arrayqueue"
	llq "github.com/emirpasic/gods/queues/linkedlistqueue"
	"github.com/emirpasic/gods/queues/priorityqueue"
	"github.com/emirpasic/gods/utils"
)

// LinkedListQueueExample to demonstrate basic usage of LinkedListQueue
func queue_linkedlistqueue() {
	queue := llq.New() // empty
	queue.Enqueue(1)   // 1
	queue.Enqueue(2)   // 1, 2
	fmt.Println(queue)
	_ = queue.Values()     // 1, 2 (FIFO order)
	_, _ = queue.Peek()    // 1,true
	_, _ = queue.Dequeue() // 1, true
	_, _ = queue.Dequeue() // 2, true
	_, _ = queue.Dequeue() // nil, false (nothing to deque)
	queue.Enqueue(1)       // 1
	queue.Clear()          // empty
	queue.Empty()          // true
	_ = queue.Size()       // 0
}

// ArrayQueueExample to demonstrate basic usage of ArrayQueue
func queue_arrayqueue() {
	queue := aq.New() // empty
	queue.Enqueue(1)  // 1
	queue.Enqueue(2)  // 1, 2
	fmt.Println(queue)
	_ = queue.Values()     // 1, 2 (FIFO order)
	_, _ = queue.Peek()    // 1,true
	_, _ = queue.Dequeue() // 1, true
	_, _ = queue.Dequeue() // 2, true
	_, _ = queue.Dequeue() // nil, false (nothing to deque)
	queue.Enqueue(1)       // 1
	queue.Clear()          // empty
	queue.Empty()          // true
	_ = queue.Size()       // 0
}

type Element struct {
	name     string
	priority int
}

func byPriority(a, b interface{}) int {
	priorityA := a.(Element).priority
	priorityB := b.(Element).priority
	// - : descending order
	return -utils.IntComparator(priorityA, priorityB)
}
func queue_priorityqueue() {
	a := Element{name: "a", priority: 1}
	b := Element{name: "b", priority: 2}
	c := Element{name: "c", priority: 3}
	pq := priorityqueue.NewWith(byPriority)
	fmt.Println(pq)
	pq.Enqueue(a)
	pq.Enqueue(b)
	pq.Enqueue(c)
	fmt.Println(pq.Values(), pq.Size())
	val, ok := pq.Peek()
	fmt.Println(val, ok)
	val, ok = pq.Dequeue()
	fmt.Println(val, ok)
	val, ok = pq.Dequeue()
	fmt.Println(val, ok)
	val, ok = pq.Dequeue()
	fmt.Println(val, ok)
	val, ok = pq.Dequeue()
	fmt.Println(val, ok)
	// pq.Clear()
	if pq.Empty() {
		fmt.Println("pq is empty")
	}
}
