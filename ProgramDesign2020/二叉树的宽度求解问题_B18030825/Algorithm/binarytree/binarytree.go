package main

import (
	"fmt"
)

type DataField interface{}

type BtNode struct {
	data   DataField
	lChild *BtNode
	rChild *BtNode
	level  uint
}

type BinaryTree struct {
	root *BtNode
}

// 合并两棵树
func MakeTree(x DataField, left *BinaryTree, right *BinaryTree) *BinaryTree {
	if left == right {
		panic("Left tree and right tree cannot be the same.")
	}
	if left == nil || right == nil {
		panic("left tree or right tree cannot be nil.")
	}
	AddLevel(left.root)
	AddLevel(right.root)
	newTree := &BinaryTree{
		root: &BtNode{x, left.root, right.root, 0},
	}
	left.root, right.root = nil, nil
	return newTree
}

func AddLevel(node *BtNode) {
	if node == nil {
		return
	}
	node.level += 1
	AddLevel(node.lChild)
	AddLevel(node.rChild)
}


// 层次遍历
func (bt *BinaryTree) LevelOrderTree() []*BtNode {
	nodes := make([]*BtNode, 0)
	queue := make([]*BtNode, 0)

	queue = append(queue, bt.root)
	for len(queue) != 0 {
		// pop 1 node from queue
		node := queue[0]
		queue = queue[1:]
		// push, if any, child node of this node to queue
		if node.lChild != nil {
			queue = append(queue, node.lChild)
		}
		if node.rChild != nil {
			queue = append(queue, node.rChild)
		}
		// add this node to the slice of all nodes
		nodes = append(nodes, node)
	}

	return nodes
}


// 结点个数
func (bt *BinaryTree) SizeOfNodes() uint {
	return bt.root.SizeOfNodes()
}

func (node *BtNode) SizeOfNodes() uint {
	if node == nil {
		return 0
	}
	return 1 + node.lChild.SizeOfNodes() + node.rChild.SizeOfNodes()
}

// 二叉树高度
func (bt *BinaryTree) Height() uint {
	return bt.root.Height()
}

func (node *BtNode) Height() uint {
	if node == nil {
		return 0
	}
	if node.lChild == nil && node.rChild == nil {
		return 1
	}
	lHeight, rHeight := node.lChild.Height(), node.rChild.Height()
	if lHeight > rHeight {
		return 1 + lHeight
	}
	return 1 + rHeight
}

// 二叉树宽度
func (bt *BinaryTree) Width() uint {
	// 层次遍历出所有结点
	nodes := bt.LevelOrderTree()

	// 计算每一层的结点数
	widths := make([]uint, bt.Height())
	for _, node := range nodes {
		widths[node.level] += 1
	}

	// 找最大的结点数
	maxWidth := uint(0)
	for _, width := range widths {
		if width > maxWidth {
			maxWidth = width
		}
	}

	return maxWidth
}

// 输出各结点的高度
func (bt *BinaryTree) HeightOfAllNodes() {
	// 层次遍历出所有结点
	nodes := bt.LevelOrderTree()

	// 输出每个结点的高度
	for _, node := range nodes {
		fmt.Printf("The level of node %v is: %d\n", node.data, node.level)
	}
}

// 输出指定层数的所有结点及其总个数
func (bt *BinaryTree) AllNodesOfLevel(level uint) {
	// 判断高度
	if level > bt.Height() {
		fmt.Printf("level %d is beyond level of the tree %d\n", level, bt.Height())
		return
	}

	// 层次遍历出所有结点
	nodes := bt.LevelOrderTree()

	// 输出指定高度的所有结点
	sum := 0
	for _, node := range nodes {
		if node.level == level {
			sum += 1
			fmt.Printf("node: %v\n", node.data)
		}
	}
	fmt.Printf("Level %d contains %d nodes in total\n", level, sum)
}


func main() {
	y := &BinaryTree{
		root: &BtNode{"E", nil, nil, 0},
	}
	z := &BinaryTree{
		root: nil,
	}
	x := MakeTree("C", y, z)
	y = &BinaryTree{
		root: &BtNode{"D", nil, nil, 0},
	}
	tree := MakeTree("B", y, x)
	/*
				  B
				 / \
				D   C
		           /
		          E
	*/
	println(`树：
	  B
	 / \
	D   C
	   / 
	  E  
`)

	fmt.Printf("Width of the tree is %d\n", tree.Width())

	tree.HeightOfAllNodes()

	println("\nAll nodes of level 1 is: ")
	tree.AllNodesOfLevel(1)
}