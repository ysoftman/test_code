package main

import (
	"fmt"

	aq "github.com/emirpasic/gods/queues/arrayqueue"
	llq "github.com/emirpasic/gods/queues/linkedlistqueue"
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
