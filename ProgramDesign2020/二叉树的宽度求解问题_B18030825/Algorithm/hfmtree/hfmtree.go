package hfmtree

import (
	"fmt"
)

type ElemType interface{}

type hfmNode struct {
	element  ElemType
	priority int
	lChild   *hfmNode
	rChild   *hfmNode
}

type hfmTree struct {
	root *hfmNode
}




// 比较两个哈夫曼树的根部优先权大小
func (self *hfmTree) Less(other *hfmTree) bool {
	return self.root.priority < other.root.priority
}


// 哈夫曼树的优先权队列（最小堆）
type PriorityQueue []*hfmTree

// 交换优先权队列中两个元素的位置
func (pq PriorityQueue) Swap(i, j int) {
	pq[i], pq[j] = pq[j], pq[i]
}

// 向下调整
func (pq PriorityQueue) AdjustDown(i int) {
	n := len(pq)
	if 2*i + 2 > n {  // 已经是叶结点了，无需再调整
		return
	}

	var minChildIndex int
	if 2*i + 2 == n {	// 该结点只有左儿子
		minChildIndex = 2*i + 1
	} else {
		if pq[2*i+1].Less(pq[2*i+2]) { // 左儿子比右儿子小
			minChildIndex = 2*i + 1
		} else {
			minChildIndex = 2*i + 2
		}
	}

	if pq[minChildIndex].Less(pq[i]) { // 该结点比他最小的孩子大，不满足最小堆的条件
		pq.Swap(i, minChildIndex)      // 与其最小的孩子进行交换
		pq.AdjustDown(minChildIndex)   // 继续考察该结点
	}

}

// 向上调整
func (pq PriorityQueue) AdjustUp(i int) {
	if i == 0 {   // 已经是根节点了，无需再调整
		return
	}

	node   := pq[i]
	parent := pq[(i-1)/2]

	if node.Less(parent) {      // 该结点比其父结点小，需要往上调
		pq.Swap(i, (i-1)/2)   // 与其父结点交换
		pq.AdjustUp((i-1)/2)  // 继续考察该结点
	}
}


// 向优先权队列中添加一个元素
func (pq *PriorityQueue) Push(x *hfmTree) {
	*pq = append(*pq, x)			// 插在末尾
	(*pq).AdjustUp(len(*pq)-1)      // 是否有机会向上调整？（插入的这个元素可能很小）
}


// 取出优先权队列中的一个元素（权值最小的哈夫曼树）
func (pq *PriorityQueue) Pop() (res *hfmTree) {
	if len(*pq) == 0 {
		panic("Queue is empty, cannot pop any more elements!")
	}
	res = (*pq)[0]
	*pq = (*pq)[1:]
	(*pq).AdjustDown(0)
	return
}

// 从优先权队列中连续取出两个元素，合并，再插入
func (pq *PriorityQueue) Merge() {
	first   := pq.Pop()
	second  := pq.Pop()

	newTree := &hfmTree{
		root: &hfmNode{
			element: nil,
			priority: first.root.priority + second.root.priority,
			lChild: first.root,
			rChild: second.root,
		},
	}
	pq.Push(newTree)

	first.root = nil
	second.root = nil
}


// 根据给定的哈夫曼树切片创建一个优先权队列
func CreatePriorityQueue(trees []*hfmTree) PriorityQueue {
	pq := PriorityQueue(trees)
	n  := len(pq)
	for i := (n-2)/2; i > -1; i-- {
		pq.AdjustDown(i)
	}
	return pq
}

// 根据给定的数据，创建哈夫曼树切片
func MakeHFMTrees(stat map[ElemType]int) (hfmTrees []*hfmTree) {
	for elem, priority := range stat {
		newTree := &hfmTree{
			root: &hfmNode{
				element: elem,
				priority: priority,
				lChild: nil,
				rChild: nil,
			},
		}
		hfmTrees = append(hfmTrees, newTree)
	}

	return hfmTrees
}

// 展示哈夫曼树
func (tree *hfmTree) Show() {
	tree.root.lChild.Show("0")
	tree.root.rChild.Show("1")
}

func (node *hfmNode) Show(s string) {
	if node.element != nil {
		fmt.Printf("%v : %s\n", node.element, s)
	}
	if node.lChild != nil {
		node.lChild.Show(s + "0")
	}
	if node.rChild != nil {
		node.rChild.Show(s + "1")
	}
}

// 从词频表获取编码表
func GetCodingTable(stat map[ElemType]int) (table map[ElemType]string){
	hfmTrees := MakeHFMTrees(stat)      // 根据词频表生成哈夫曼树切片
	pq := CreatePriorityQueue(hfmTrees) // 根据哈夫曼切片创建优先权队列
	for len(pq) > 1 {
		pq.Merge()							// 生成哈夫曼编码树
	}

	finalTree := pq.Pop()					// 得到哈夫曼编码树

	// 根据哈夫曼编码树得到编码表
	table = make(map[ElemType]string, 1)
	finalTree.root.lChild.NodeGetCodingTable("0", &table)
	finalTree.root.rChild.NodeGetCodingTable("1", &table)
	return table
}

func (node *hfmNode) NodeGetCodingTable(s string, table *map[ElemType]string) {
	if node.element != nil {
		(*table)[node.element.(string)] = s
	}
	if node.lChild != nil {
		node.lChild.NodeGetCodingTable(s + "0", table)
	}
	if node.rChild != nil {
		node.rChild.NodeGetCodingTable(s + "1", table)
	}
}

// 从给定的字符串生成词频表
func GenerateStat(msg string) (stat map[ElemType]int) {
	stat = make(map[ElemType]int, 1)
	for _, s := range msg {
		if stat[string(s)] == 0 {
			stat[string(s)] = 1
		} else {
			stat[string(s)] += 1
		}
	}
	return stat
}

// 对指定的一串字符串进行哈夫曼编码，返回编码后的字符串
func Encoding(msg string) (code string, table map[ElemType]string) {
	stat  := GenerateStat(msg)   // 先获取这串字符串的词频表
	table = GetCodingTable(stat) // 再从词频表生成编码表
	for _, s := range msg {
		code += table[string(s)]			// 逐一对字符串中的字符进行编码
	}
	return code, table
}

// 哈夫曼解码
func Decoding(code string, encodingTable map[ElemType]string) (msg string) {
	// 交换map中的键值对
	decodingTable := map[string]string{} // "10" : "B"
	for k, v := range encodingTable {
		decodingTable[v] = k.(string)
	}

	// 根据解码表进行解码（注意这边是变长编码）
	for i := 0; i < len(code);  {
		for l := 1; ; l++ {
			s := code[i:i+l]
			if val, ok := decodingTable[s]; ok { // 逐长度取字符串，看在不在table里
				msg += val		// 有的话就解码
				i += l			// 下一个
				break
			}
			// 否则，继续，长度加1
		}
	}

	return msg
}



