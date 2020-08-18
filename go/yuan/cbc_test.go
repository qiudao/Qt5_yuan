package yuan

import (
		"fmt"
		"testing"
	   )

var cbc CBC

func TestNewCBC(t *testing.T) {
	cbc.Init(5)
}

func TestCBCPush(t *testing.T) {
	var c byte

	c = 'e'
	for i := 0; i < 8; i++ {
		cbc.Push(c)
		c++
	}

	//cbc.Dump()
}

func TestCBCPop(t *testing.T) {
	for i := 0; i < 5; i++ {
		if c, err := cbc.Pop(); err != nil {
			t.Errorf("pop failed %d\n", i)
		} else {
			fmt.Printf("Pop[%d]:  %c\n", i, c)
		}
	}
}
