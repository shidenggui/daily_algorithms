class PriorityQueue:
    def __init__(self, size):
        self._arr = [None] * size
        self._size = 0
        self._capacity = size

    def is_empty(self):
        return self._size == 0

    def is_full(self):
        return self._size == self._capacity

    def __bool__(self):
        return not self.is_empty()

    def insert(self, value):
        if self.is_full():
            raise Exception('queue is full, cant insert')

        self._size += 1
        i = self._size - 1
        while i != 0 and self._arr[i // 2] > value:
            self._arr[i] = self._arr[i // 2]
            i //= 2
        self._arr[i] = value

    def delete_min(self):
        if self.is_empty():
            raise Exception('queue is empty, cant delete min')

        poped = self._arr[0]
        value = self._arr[self._size - 1]
        self._size -= 1
        i = 0
        while 2 * i + 1 <= self._size - 1:
            child = 2 * i + 1
            if child + 1 <= self._size - 1 and self._arr[child + 1] < self._arr[child]:
                child += 1

            if value <= self._arr[child]:
                break

            self._arr[i] = self._arr[child]
            i = child
        self._arr[i] = value
        return poped

import dataclasses


@dataclasses.dataclass(order=True)
class TreeNode:
    weight: int
    char: str = ''
    left: 'TreeNode' = None
    right: 'TreeNode' = None

def print_tree(root, space=0, interval=20):
    if root is None:
        return

    print_tree(root.right, space + interval)

    print()
    print(' ' * space, root.char, ':', root.weight)

    print_tree(root.left, space + interval)

def print_huffman_code(root, code=None, parent=''):
    # char leaves
    if root.left is None and root.right is None:
        print(root.char, parent)
        code[root.char] = len(parent)
        return

    print_huffman_code(root.left, code, parent + '0')
    print_huffman_code(root.right, code, parent + '1')


def huffman_code(freqs):
    n = len(freqs)
    q = PriorityQueue(n)
    for char, weight in freqs:
        q.insert(TreeNode(weight=weight, char=char, left=None, right=None))

    for _ in range(n - 1):
        tree1 = q.delete_min()
        tree2 = q.delete_min()
        union_tree = TreeNode(weight=tree1.weight + tree2.weight, left=tree1, right=tree2)
        q.insert(union_tree)


    huffman_tree = q.delete_min()

    return huffman_tree

def test_huffman_code():
    freqs = [
        ('a', 10),
        ('e', 15),
        ('i', 12),
        ('s', 3),
        ('t', 4),
        ('sp', 13),
        ('nl', 1),
    ]
    huffman_tree = huffman_code(freqs)
    print('huffman tree:')
    print_tree(huffman_tree)
    code = {}
    print('\nhuffman code:')
    print_huffman_code(huffman_tree, code=code)
    print('\nhuffman code result:')
    char_sum = 0
    for char, freq in freqs:
        print('char:', char, 'freq: ', freq, 'total: ', freq * code[char])
        char_sum += freq * code[char]
    print('total_sum:', char_sum)

test_huffman_code()
