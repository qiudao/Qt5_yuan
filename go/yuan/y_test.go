package yuan

import (
		"testing"
		//"fmt"
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