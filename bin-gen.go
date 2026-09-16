package main

import (
	"fmt"
	"os"
)

func main() {
	code := make([]byte, 200)

	for i := range code {
		code[i] = 0x90
	}

	err := os.WriteFile("binary", code, 0644)
	if err != nil {
		panic(err)
	}

	fmt.Println("Generated 200 NOPs")
}
