package yuan

import (
		"bytes"
		"errors"
	   )

type YBuf struct {
	CBC
}

func (y *YBuf)seekmagic() bool {
	var found int = -1
	var ret bool = false

	if y.Count() < 2 {
		return ret
	}
	for i := 0; i < y.Count() - 1; i++ {
		b := y.At(i)
		if b == Magic1 && y.At(i+1) == Magic2 {
			found = i
			break
		}
	}

	if found == -1 {
		if y.Last() == Magic1 {
			y.DropN(y.Count()-1)
		} else {
			y.Reset()
		}
	} else {
		if found > 0 {
			y.DropN(found)
		}
		ret = true
	}
	return ret
}

// is Complete YuanBlock
func (y *YBuf)ScanBlock() bool {
	if ok := y.seekmagic(); !ok {
		return false
	}

	if y.Count() < 4 {
		return false
	}

	var length uint16 = uint16(y.At(2)) << 8 | uint16(y.At(3))

	// 2:magic, 2:length, length:data_payload
	if y.Count() < int(2 + 2 + length) {
		return false
	}

	return true
}

// firstBlockSize
func (y *YBuf)firstBlockSize() int {
	return int( uint16(y.At(2)) << 8 | uint16(y.At(3)))
}
// firstBlockData
// FIXME: use "block copy" instead of "byte copy"
func (y *YBuf)firstBlockData() []byte {
	l := y.firstBlockSize()
	b := make([]byte, l)
	for i := 0; i < l; i++ {
		b[i] = y.At(i + 4)
	}
   return b
}

// ReadBlock
func (y *YBuf)ReadBlock(b *bytes.Buffer) bool {
	if !y.ScanBlock() {
		return false
	}

	b.Write(y.firstBlockData())
	return true
}
// Write
func (y *YBuf)Write(p []byte) (n int, err error) {
	left := y.Space()

	if left < len(p) {
		return 0, errors.New("no space")
	}

	var i int
	for i = 0; i < len(p); i++ {
		y.Push(p[i])
	}
	return i, nil
}
