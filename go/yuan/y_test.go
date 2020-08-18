package yuan

import (
		"testing"
	   )

var b YBuf

func TestInit(t *testing.T) {
	var yb YuanBlock
	yb.servId = 3
	b.buf.Resize(10)
	b.buf.Push(yb)
}

func TestSeekMagic(t *testing.T) {
	if err := b.seekmagic(); err != nil {
		t.Errorf("seek failed: %v", err)
	}

}
