package yuan

import (
		"fmt"
		"testing"
	   )

var cb CB

func TestCBResize(t *testing.T) {
	cb.Resize(20)
	fmt.Println(cb.String())
}

func TestPush(t *testing.T) {
	var id uint16		= 111
	var length	uint32  = 222

	// push few times
	for i := 0; i < 21; i++ {
		var yb YuanBlock
		yb.serviceId = id
		yb.length	 = length
		yb.buf = append(yb.buf, []byte("hello, yuan")...)

		if ok := cb.Push(yb); !ok {
			t.Errorf("test push error %d", 3)
		}

		id++
		length++
	}

	cb.Dump()
}

func TestPop(t *testing.T) {

	for i:= 0; i < 10; i++ {
		yb, err := cb.Pop()
			if err != nil {
				t.Errorf("test pop error: %v", err)
			}

		fmt.Printf("yb: id %d len %d buf: %s\n", yb.serviceId, yb.length, string(yb.buf))
	}
}