package hfmtree

import (
	"fmt"
	"testing"
)

// 哈夫曼树相关操作测试
func TestHFMTree(t *testing.T) {
	statistics := map[ElemType]int{
		"A": 28,
		"B": 10,
		"C": 24,
		"D": 20,
		"E": 14,
		"F": 27,
		"G": 17,
		"H": 9,
	}

	hfmTrees := MakeHFMTrees(statistics)
	pq := CreatePriorityQueue(hfmTrees)
	for len(pq) > 1 {
		pq.Merge()
	}

	finalTree := pq.Pop()
	finalTree.Show()

}

// 哈夫曼编码测试
func TestCoding(t *testing.T) {
	msg := "THE FOX JUMPS OVER THE LAZY DOG"
	code, table := Encoding(msg)
	fmt.Printf("Message: %s\n", msg)
	fmt.Printf("After encoding: %s\n", code)
	//fmt.Print("Encoding table: ", table)

	decoded := Decoding(code, table)
	fmt.Printf("Decoded: %s\n", decoded)
}