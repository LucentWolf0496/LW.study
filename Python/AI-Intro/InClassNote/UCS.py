class USCPriorityQueue:
    """基于二叉堆（最小堆）的优先队列，用于一致代价搜索（USC）。
    内部使用列表存储完全二叉树，元素格式为 (cost, node)，按 cost 排序。
    """
    def __init__(self):
        self._heap = []  # 存储堆元素的列表

    def is_empty(self):
        """判断队列是否为空"""
        return len(self._heap) == 0

    def push(self, node, cost):
        """插入一个新节点及其代价"""
        item = (cost, node)
        self._heap.append(item)          # 先添加到末尾
        self._sift_up(len(self._heap) - 1)  # 向上调整，维持堆序

    def pop(self):
        """弹出并返回代价最小的节点（元组 (cost, node)）"""
        if self.is_empty():
            raise IndexError("pop from empty priority queue")
        # 将堆顶（最小元素）与最后一个元素交换，然后弹出最后一个
        self._swap(0, len(self._heap) - 1)
        item = self._heap.pop()
        # 从新的堆顶开始向下调整
        if not self.is_empty():
            self._sift_down(0)
        return item

    def _sift_up(self, idx):
        """将 idx 处的元素向上调整，直到满足堆序（父节点 <= 子节点）"""
        parent = (idx - 1) // 2
        while idx > 0 and self._heap[idx][0] < self._heap[parent][0]:
            self._swap(idx, parent)
            idx = parent
            parent = (idx - 1) // 2

    def _sift_down(self, idx):
        """将 idx 处的元素向下调整，直到满足堆序"""
        child = 2 * idx + 1  # 左子节点
        while child < len(self._heap):
            # 如果右子节点存在且更小，选择右子节点
            if child + 1 < len(self._heap) and self._heap[child + 1][0] < self._heap[child][0]:
                child += 1
            if self._heap[idx][0] <= self._heap[child][0]:
                break
            self._swap(idx, child)
            idx = child
            child = 2 * idx + 1

    def _swap(self, i, j):
        """交换堆中两个位置的元素"""
        self._heap[i], self._heap[j] = self._heap[j], self._heap[i]

    def __repr__(self):
        """便于调试的显示"""
        return str([(c, n) for c, n in self._heap])

# 使用示例
if __name__ == "__main__":
    pq = USCPriorityQueue()
    pq.push('A', 5)
    pq.push('B', 2)
    pq.push('C', 8)
    pq.push('D', 1)

    while not pq.is_empty():
        cost, node = pq.pop()
        print(f"Node: {node}, Cost: {cost}")