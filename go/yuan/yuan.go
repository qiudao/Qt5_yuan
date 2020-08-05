package yuan

import (
	"log"
	"net"
	"os"
	"strconv"
)

const (
	Magic1 = 0xAA
	Magic2 = 0x55
)

type YuanBlock struct {
	connId	uint16
	servId	uint16
	dataLen uint32
	data	[]byte
}

type Yuan struct {
	server string
	connId	int
}

func init() {
    log.SetFlags(log.LstdFlags | log.Lmicroseconds | log.Lshortfile)
	//f, _ := os.OpenFile("testlogfile.log", os.O_RDWR | os.O_CREATE | os.O_APPEND, 0666)
    log.SetOutput(os.Stdout)
}

func (y Yuan)String() string {
	log.Println("yuan")
	return "this is yuan"
}

func (y Yuan)ListenAndServe(serverAddr string) {

	log.Println("yuan start...")

	l, err := net.Listen("tcp",  serverAddr)
	if err != nil {
		log.Println("Error Listening: ", err.Error())
		os.Exit(1)
	}

	defer l.Close()

	log.Println("Listening on " + serverAddr)

	for {
		conn, err := l.Accept()
		if err != nil {
			log.Println("Error Accepting: " + err.Error())
			os.Exit(1)
		}

		go y.handleRequest(conn)
	}
}

func (y Yuan)handleRequest(conn net.Conn) {
	buf := make([]byte, 1024)
	reqLen, err := conn.Read(buf)
	if err != nil {
		log.Println("Error reading:", err.Error())
	}
	conn.Write([]byte("I'm Server, received bytesMesssage : " + string(buf) + strconv.Itoa(reqLen) + "\n"))
	conn.Close()

	log.Printf("yuan: %s\n", y.String())
}

func (y Yuan)ConnId() int {
	return y.connId
}

// Read & Write stream
func (y Yuan)ReadStream(buf []byte) (n int) {
	return 0
}

func (y Yuan)WriteStream(buf []byte) (n int) {
	return 0
}
// Read & Write Block
func (y Yuan)ReadBlock() (*YuanBlock, error) {
	return &YuanBlock{}, nil
}
func (y Yuan)WriteBlock(yb YuanBlock) (error) {
	return nil
}


// YuanBlock
// 
func (yb YuanBlock)ServiceId() uint16 {
	return yb.servId
}
