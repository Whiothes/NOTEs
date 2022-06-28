package main

import (
	"os"
	"fmt"
)


func main() {
	for i, v := range os.Args[1:] {
		fmt.Println(i, v)
	}
}
