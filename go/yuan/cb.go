package yuan

import (
		"log"
		"fmt"
		"errors"
	   )

var ErrEmpty = errors.New("empty")

type CB struct {
	buf []YuanBlock
	capability	int
	count		int
	head		int
	tail		int
}

func (cb *CB)Resize(n int) {
	cb.capability = n
	cb.buf = make([]YuanBlock, n+1)
	cb.Reset()
	log.Println("Resize")
}

func (cb CB)String() string {
	return fmt.Sprintf("cap %d count %d head %d tail %d",
			cb.capability, cb.count, cb.head, cb.tail)
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
	return cb.count == cb.capability
}

// Push
func (cb *CB)Push(yb YuanBlock) bool {
	if cb.IsFull() {
		cb.head++;
		if (cb.head > cb.capability) {
			cb.head = 0
		}
	} else {
		cb.count++
	}

	cb.buf[cb.tail] = yb
	cb.tail++
	if cb.tail > cb.capability {
		cb.tail = 0
	}

	return true
}
// Pop
func (cb *CB)Pop() (YuanBlock, error) {
	if cb.IsEmpty() {
		return YuanBlock{}, ErrEmpty
	}

	var yb YuanBlock
	yb = cb.buf[cb.head]
	cb.head++
	if cb.head > cb.capability {
		cb.head = 0
	}
	cb.count--
	if cb.head == cb.tail {
		cb.Reset()
	}

	return yb, nil
}

// At
func (cb CB)At(index int) (YuanBlock, error) {
	var yb YuanBlock

	if index < 0 {
		index += cb.count
		if index < 0 {
			return yb, ErrEmpty
		}
	}

	if index + 1 > cb.count {
		return yb, ErrEmpty
	}

	index += cb.head
	if index > cb.capability {
		index -= (cb.capability + 1)
	}
	yb = cb.buf[index]

	return yb, nil
}
