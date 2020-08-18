package yuan

import (
		"log"
		"fmt"
		"errors"
	   )

var ErrEmpty = errors.New("empty")

type CB struct {
	capb	int
	count		int
	head		int
	tail		int
	data []interface{}
}

func NewCB(capb int) CB {
	var cb CB
	cb.data = make([]interface{}, capb+1, capb+1)

	return CB{}
}

func (cb *CB)Resize(n int) {
	cb.capb = n
	cb.data = make([]interface{}, n+1)
	cb.Reset()
	log.Println("Resize")
}

func (cb CB)String() string {
	return fmt.Sprintf("cap %d count %d head %d tail %d",
			cb.capb, cb.count, cb.head, cb.tail)
}

func (cb CB)Dump() {
	fmt.Println(cb.String())
}

func (cb *CB)Reset() {
	cb.count = 0
	cb.head  = 0
	cb.tail  = 0
}

func (cb CB)IsEmpty() bool {
	return cb.count == 0
}
func (cb CB)IsFull() bool {
	return cb.count == cb.capb
}
func (cb CB)Count() int {
	return cb.count
}

// Push
func (cb *CB)Push(x interface{}) bool {
	if cb.IsFull() {
		cb.head++;
		if (cb.head > cb.capb) {
			cb.head = 0
		}
	} else {
		cb.count++
	}

	cb.data[cb.tail] = x
	cb.tail++
	if cb.tail > cb.capb {
		cb.tail = 0
	}

	return true
}

// Pop
func (cb *CB)Pop() (interface{}) {
	if cb.IsEmpty() {
		return nil
	}

	e := cb.data[cb.head]
	cb.head++
	if cb.head > cb.capb {
		cb.head = 0
	}
	cb.count--
	if cb.head == cb.tail {
		cb.Reset()
	}

	return e
}

// At

func (cb CB)At(index int) interface{} {
	var e interface{}

	if index < 0 {
		index += cb.count
		if index < 0 {
			return e
		}
	}

	if index + 1 > cb.count {
		return e
	}

	index += cb.head
	if index > cb.capb {
		index -= (cb.capb + 1)
	}
	e = cb.data[index]

	return e
}
