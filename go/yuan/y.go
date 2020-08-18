package yuan

import (
	   )

type YBuf struct {
	buf CB
}

func (b *YBuf)seekmagic() error {
	for i := 0; i < b.buf.Count(); i++ {
		if item, err := b.buf.At(i); err != nil {
			item.Dump()
		}
	}
	return nil
}

