package yuan

import (
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

