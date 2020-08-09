package yuan

import (
		"fmt"
		"testing"
	   )

var cb CB

func TestNew(t *testing.T) {
	y := NewCB(100)
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

func TestAt(t *testing.T) {
	if e := cb.At(0); e != nil {
		yb := e.(YuanBlock)
		fmt.Printf("yb[0]: id %d len %d buf: %s\n", yb.servId, yb.dataLen, string(yb.data))
	} else {
		t.Errorf("At 0 failed")
	}

}

func TestPop(t *testing.T) {

	for i:= 0; i < 10; i++ {
		if e := cb.Pop(); e == nil {
			t.Errorf("pop2 error")
		} else {
			yb := e.(YuanBlock)
			fmt.Printf("yb: id %d len %d buf: %s\n", yb.servId, yb.dataLen, string(yb.data))
		}

	}
}
