package yuan

import (
		"fmt"
		"testing"
	   )

var cb CB

func TestNew(t *testing.T) {
	var yb YuanBlock
	y := NewCB(yb, 100)
	y.Dump()
}

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
		yb.servId	= id
		yb.dataLen	= length
		yb.data		= append(yb.data, []byte("hello, yuan")...)

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

		fmt.Printf("yb: id %d len %d buf: %s\n", yb.servId, yb.dataLen, string(yb.data))
	}
}
