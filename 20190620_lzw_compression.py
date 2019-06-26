# coding:utf-8
import dataclasses
import unittest
from typing import Optional


@dataclasses.dataclass()
class Node:
    char: str
    val: int = dataclasses.field(default=None)
    children: dict = dataclasses.field(default_factory=dict)


class Trie:
    def __init__(self):
        self.root = Node('root')

    def put(self, s: str, val: int):
        self._put(self.root, s, 0, val)

    def get(self, s):
        return self._get(self.root, s, 0)

    def _get(self, root: Node, s: str, idx: int) -> Optional[int]:
        if idx == len(s):
            return root.val
        if s[idx] not in root.children:
            return None
        return self._get(root.children[s[idx]], s, idx + 1)

    def _put(self, root: Node, s: str, idx: int, val: int):
        if idx == len(s):
            root.val = val
            return
        if s[idx] not in root.children:
            root.children[s[idx]] = Node(s[idx])
        self._put(root.children[s[idx]], s, idx + 1, val)

    def longest_path(self, s: str):
        return self._longest_path(self.root, s, 0, '')

    def _longest_path(self, root: Node, s: str, idx: int, path: str):
        if idx == len(s):
            return path
        if s[idx] not in root.children:
            return path
        return self._longest_path(root.children[s[idx]], s, idx + 1,
                                  path + s[idx])


class TestTrie(unittest.TestCase):
    def test(self):
        trie = Trie()
        trie.put('abc', 3)
        trie.put('ad', 4)

        self.assertEqual(trie.get(''), None)
        self.assertEqual(trie.get('a'), None)
        self.assertEqual(trie.get('ad'), 4)
        self.assertEqual(trie.get('adc'), None)
        self.assertEqual(trie.get('abc'), 3)

        self.assertEqual(trie.longest_path(''), '')
        self.assertEqual(trie.longest_path('a'), 'a')
        self.assertEqual(trie.longest_path('ad'), 'ad')
        self.assertEqual(trie.longest_path('adc'), 'ad')


class LZWCompression:
    L = 4096
    R = 128
    W = 12

    def compress(self, input):
        output = []
        st = Trie()
        for i in range(self.R):
            st.put(chr(i), i)
        code = self.R
        i = 0
        while i < len(input):
            s = st.longest_path(input[i: i + 5000])
            output.append(st.get(s))

            code += 1
            st.put(input[i: i + len(s) + 1], code)
            i += len(s)
        output.append(self.R)
        return ' '.join([hex(c)[2:] for c in output])

    def expand(self, input):
        input = input.split(' ')

        output = []
        st = [None] * self.L
        for i in range(self.R):
            st[i] = chr(i)
        st[self.R] = ' '
        i = self.R + 1
        codeword = int(input[0], 16)
        pre_s = st[codeword]
        for codeword_str in input[1:]:
            output.append(pre_s)

            codeword = int(codeword_str, 16)
            s = st[codeword]
            if i == codeword:
                s = pre_s + pre_s[0]
            if i < self.L:
                st[i] = pre_s + s[0]
            i += 1
            pre_s = s
        return ''.join(output)


class TestLzwCompression(unittest.TestCase):
    def test_compress(self):
        result = LZWCompression().compress('ABABABA')
        self.assertEqual(result, '41 42 81 83 80')

    def test_expand(self):
        result = LZWCompression().compress('ABABABA')
        self.assertEqual(result, '41 42 81 83 80')

        expand = LZWCompression().expand(result)
        self.assertEqual(expand, 'ABABABA')
