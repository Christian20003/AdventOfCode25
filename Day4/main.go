package main

import (
	"fmt"
	"log"
	"os"
	"strings"
)

func solveTask2(stock [][]bool) int {
	lines := len(stock)
	columns := len(stock[0])
	run := true
	result := 0

	directions := [][2]int{
		{-1, -1}, {-1, 0}, {-1, 1},
		{0, -1}, {0, 1},
		{1, -1}, {1, 0}, {1, 1},
	}

	for run {
		run = false
		for line := range lines {
			for column := range columns {
				if !stock[line][column] {
					continue
				}
				neighbours := 0

				for _, direction := range directions {
					neighbourLine := line + direction[0]
					neighbourColumn := column + direction[1]

					if neighbourLine >= 0 &&
						neighbourLine < lines &&
						neighbourColumn >= 0 &&
						neighbourColumn < columns &&
						stock[neighbourLine][neighbourColumn] {
						neighbours++
					}
				}

				if neighbours < 4 {
					stock[line][column] = false
					run = true
					result++
				}
			}
		}
	}

	return result
}

func solveTask1(stock [][]bool) int {
	lines := len(stock)
	columns := len(stock[0])
	result := 0

	directions := [][2]int{
		{-1, -1}, {-1, 0}, {-1, 1},
		{0, -1}, {0, 1},
		{1, -1}, {1, 0}, {1, 1},
	}

	for line := range lines {
		for column := range columns {
			if !stock[line][column] {
				continue
			}
			neighbours := 0

			for _, direction := range directions {
				neighbourLine := line + direction[0]
				neighbourColumn := column + direction[1]

				if neighbourLine >= 0 &&
					neighbourLine < lines &&
					neighbourColumn >= 0 &&
					neighbourColumn < columns &&
					stock[neighbourLine][neighbourColumn] {
					neighbours++
				}
			}

			if neighbours < 4 {
				result++
			}
		}
	}

	return result
}

func parseInput() [][]bool {
	content, err := os.ReadFile("./Day4/Input.txt")
	if err != nil {
		log.Fatal(err)
	}
	data := string(content)
	paperLines := strings.Split(data, "\n")
	matrix := make([][]bool, len(paperLines))
	for idx, paperLine := range paperLines {
		line := make([]bool, len(paperLine))
		for rollIdx, roll := range paperLine {
			line[rollIdx] = roll == '@'
		}
		matrix[idx] = line
	}
	return matrix
}

func main() {
	stock := parseInput()
	accessible1 := solveTask1(stock)
	accessible2 := solveTask2(stock)

	fmt.Printf("The result of task 1: %d\n", accessible1)
	fmt.Printf("The result of task 2: %d\n", accessible2)
}
