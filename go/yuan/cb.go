package yuan

import (
		"log"
	   )

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

func (cb *CB)Reset() {
	cb.count = 0
	cb.head  = 0
	cb.tail  = 0
}
