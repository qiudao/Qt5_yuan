package yuan

import (
		"log"
		"fmt"
	   )

type CBC struct {
	buf []byte
	capb		int
	count		int
	head		int
	tail		int
}

func (cb *CBC)Init(n int) {
	cb.capb = n
	cb.buf = make([]byte, n+1)
	cb.Reset()
	log.Println("Resize")
}

func (cb *CBC)String() string {
	return fmt.Sprintf("cap %d count %d head %d tail %d",
			cb.capb, cb.count, cb.head, cb.tail)
}

func (cb *CBC)Dump() {
	fmt.Println(cb.String())
}

func (cb *CBC)Reset() {
	cb.count = 0
	cb.head  = 0
	cb.tail  = 0
}

func (cb *CBC)IsEmpty() bool {
	return cb.count == 0
}
func (cb *CBC)IsFull() bool {
	return cb.count == cb.capb
}
func (cb *CBC)Count() int {
	return cb.count
}

// Push
func (cb *CBC)Push(c byte) bool {
	if cb.IsFull() {
		cb.head++;
		if (cb.head > cb.capb) {
			cb.head = 0
		}
	} else {
		cb.count++
	}

	cb.buf[cb.tail] = c
	cb.tail++
	if cb.tail > cb.capb {
		cb.tail = 0
	}

	return true
}
// Pop
func (cb *CBC)Pop() (byte, error) {
	var c byte

	if cb.IsEmpty() {
		return c, ErrEmpty
	}

	c = cb.buf[cb.head]
	cb.head++
	if cb.head > cb.capb {
		cb.head = 0
	}
	cb.count--
	if cb.head == cb.tail {
		cb.Reset()
	}

	return c, nil
}

// At
func (cb CBC)At(index int) (byte, error) {
	var c byte

	if index < 0 {
		index += cb.count
		if index < 0 {
			return c, ErrEmpty
		}
	}

	if index + 1 > cb.count {
		return c, ErrEmpty
	}

	index += cb.head
	if index > cb.capb {
		index -= (cb.capb + 1)
	}
	c = cb.buf[index]

	return c, nil
}
