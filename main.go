package main

import (
	"fmt"
	"log"
	"time"

	"go.bug.st/serial"
)

func main() {
	mode := &serial.Mode{
		BaudRate: 250000,
		DataBits: 8,
		StopBits: serial.TwoStopBits,
	}
	port, err := serial.Open("/dev/ttyAMA0", mode)
	if err != nil {
		log.Fatal(err)
	}
	data := make([]byte, 513)
	data[0] = 0
	iter := 0
	for {
		iter += 1
		if iter%2 == 0 {
			data[1] = 100
		} else {
			data[1] = 0
		}
		fmt.Println(data[1])
		port.Break(88 * time.Microsecond)
		time.Sleep(8 * time.Microsecond)
		n, err := port.Write(data)
		if err != nil {
			log.Fatal(err)
		}
		fmt.Printf("Sent %v bytes\n", n)
		port.Break(50 * time.Microsecond)
		time.Sleep(500 * time.Millisecond)
	}
}
