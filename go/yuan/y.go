package yuan

import (
		"fmt"
	   )

type YBuf struct {
	CBC
}

func (y *YBuf)seekmagic() bool {
	var found int
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

	if found == 0 {
		if y.Last() == Magic1 {
			y.DropN(y.Count()-1)
		} else {
			y.Reset()
		}
	} else {
		y.DropN(found)
		ret = true
	}
	return ret
}

// is Complete YuanBlock
func (y *YBuf)IsComplete() bool {
	if ok := y.seekmagic(); !ok {
		return false
	}

	if y.Count() < 4 {
		return false
	}

	var length uint16 = uint16(y.At(2)) << 8 | uint16(y.At(3))
	fmt.Printf("length %d\n", length)

	// 2(magic) + 2(length) + length(data_payload)
	if y.Count() < int(2 + 2 + length) {
		return false
	}

	return true
}
