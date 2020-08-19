package yuan

import (
		"testing"
		"bytes"
	   )

var y YBuf

func TestInit(t *testing.T) {
	y.Init(10)
	y.Push('c')
	y.Push('f')
	y.Push('z')
	y.Push(Magic1)
	y.Push(Magic2)
	y.Push('h')
	//y.Push('p')
}

func TestSeekMagic1(t *testing.T) {
	y.Reset()
	y.Init(10)
	y.Push('c')
	y.Push('f')
	y.Push('z')
	y.Push(Magic1)
	//y.Push(Magic2)
	//y.Push('h')
	//y.Push('p')
	if ok := y.seekmagic(); ok {
		t.Errorf("seek failed, should be false ")
	}
	if y.Count() != 1 {
		t.Errorf("seek failed, y.Count(%d) should be 1", y.Count())
	}
}


func TestSeekMagic2(t *testing.T) {
	y.Reset()
	y.Init(10)
	y.Push('c')
	y.Push('f')
	y.Push('z')
	y.Push(Magic1)
	y.Push(Magic2)
	y.Push('h')
	y.Push('p')
	if ok := y.seekmagic(); !ok {
		t.Errorf("seek failed, should be true")
	}
	if y.Count() != 4 {
		t.Errorf("seek failed, y.Count(%d) should be 4", y.Count())
	}
}

func TestSeekMagic3(t *testing.T) {
	y.Reset()
	y.Init(10)
	y.Push('c')
	y.Push('f')
	y.Push('z')
	y.Push(Magic1)
	y.Push(Magic2)
	if ok := y.seekmagic(); !ok {
		t.Errorf("seek failed, should be true")
	}
	if y.Count() != 2 {
		t.Errorf("seek failed, y.Count(%d) should be 2", y.Count())
	}
}

func TestLength(t *testing.T) {
	y.Reset()
	y.Init(10)
	y.Push('c')
	y.Push('f')
	y.Push('z')
	y.Push(Magic1)
	y.Push(Magic2)
	y.Push(0x00)
	y.Push(0x03)

	if y.IsComplete() {
		t.Errorf("IsComplete() fail, should not be ok")
	}
}


func TestLength2(t *testing.T) {
	y.Reset()
	y.Init(10)
	y.Push('c')
	y.Push('f')
	y.Push('z')
	y.Push(Magic1)
	y.Push(Magic2)
	y.Push(0x00)
	y.Push(0x03)
	for i := 0; i < 5; i++ {
		y.Push(0x01)
	}

	if !y.IsComplete() {
		t.Errorf("IsComplete() fail, should be ok")
	}
}

func TestReadBlock(t *testing.T) {
	y.Reset()
	y.Init(30)
	y.Push('c')
	y.Push('f')
	y.Push('z')
	y.Push(Magic1)
	y.Push(Magic2)
	y.Push(0x00)
	y.Push(0x0f)
	s := []byte("hello,world,oknow")
	for i := 0; i < len(s); i++ {
		y.Push(s[i])
	}

	if !y.IsComplete() {
		t.Errorf("IsComplete() fail, should be ok")
	}

	var b bytes.Buffer
	if ok := y.ReadBlock(&b); !ok {
		t.Errorf("ReadBlock failed.")
	} else {
		if b.Len() != 0x0f {
			t.Errorf("ReadBlock data failed, return %d, should be %d\n", b.Len(), 0x0f)
		}
	}
	y.Dump()
}
