class DisjointSet:
    def __init__(self, size):
        self._arr = [-1] * size

    def find(self, s1):
        if self._arr[s1] < 0:
            return s1
        self._arr[s1] = self.find(self._arr[s1])
        return self._arr[s1]

    def union(self, s1, s2):
        s1 = self.find(s1)
        s2 = self.find(s2)
        if s1 == s2:
            return

        if self._arr[s1] < self._arr[s2]:
            self._arr[s2] = s1
            return

        if self._arr[s1] == self._arr[s2]:
            self._arr[s2] -= 1
        self._arr[s1] = s2

class PriorityQueue:
    @classmethod
    def build_heap(cls, arr):
        i = len(arr) // 2
        while i >= 0:
            cls.percolate_down(i, arr, len(arr) - 1)
            i -= 1

    @classmethod
    def percolate_down(cls, i, arr, n):
        value = arr[i]
        while 2 * i + 1 <= n:
            child = 2 * i + 1
            if child + 1 <= n and arr[child + 1] < arr[child]:
                child += 1

            if value <= arr[child]:
                break

            arr[i] = arr[child]
            i = child
        arr[i] = value

    @classmethod
    def delete_min(cls, arr):
        if len(arr) == 0:
            raise Exception('arr is empty, cant delete min')
        value = arr[0]
        arr[0] = arr[-1]
        cls.percolate_down(0, arr, len(arr) - 1)
        arr.pop()
        return value

def weighted_indirect_minimum_spanning_tree(n, edges):
    arr = [(weight, src, dest) for (src, dest, weight) in edges]
    PriorityQueue.build_heap(arr)

    s = DisjointSet(n)
    edge_count = 0
    result = []
    # usually should be n -1 ,but example in book not add number zero vertex,
    # so, test equal for n - 2
    while edge_count < n - 2:
        weight, src, dest = PriorityQueue.delete_min(arr)
        if s.find(src) == s.find(dest):
            continue

        s.union(src, dest)
        edge_count += 1
        result.append((src, dest))
    return result


def test_weighted_indirect_minimum_spanning_tree():
    edges = [
        (1, 2, 2), (1, 3, 4), (1, 4, 1),
        (2, 4, 3), (2, 5, 10),
        (3, 4, 2), (3, 6, 5),
        (4, 5, 7), (4, 6, 8), (4, 7, 4),
        (5, 7, 6),
        (6, 7, 1)
    ]
    result = weighted_indirect_minimum_spanning_tree(8, edges)
    result.sort()
    print(result)
    expected = [(1, 2), (1, 4), (3, 4), (4, 7), (5, 7), (6, 7)] 
    for a, b in zip(result, expected):
        assert a == b 

test_weighted_indirect_minimum_spanning_tree()
