# coding:utf-8


class SuffixArray:
    def __init__(self, text: str):
        self.text = text
        self.arr = self._generate_suffix(text)
        self.arr.sort()

    def _generate_suffix(self, text: str):
        arr = []
        for i in range(len(text)):
            arr.append((text[i:], i))
        return arr

    def max_lcp(self, s1, s2):
        idx = 0
        while idx < len(s1) and idx < len(s2):
            if s1[idx] != s2[idx]:
                break
            idx += 1
        return idx

    def lcp(self):
        max_length = -1
        max_idx = -1
        for i, [s, _] in enumerate(self.arr[:-1]):
            length = self.max_lcp(s, self.arr[i + 1][0])
            if length > max_length:
                max_length = length
                max_idx = i
        return max_idx, max_length, self.arr[max_idx][0][:max_length]


import unittest


class TestSuffixArray(unittest.TestCase):
    def test(self):
        sa = SuffixArray('aacaagtttacaagc')
        self.assertEqual(sa.lcp(), (3, 5, 'acaag'))

        sa = SuffixArray("""
it was the best of times it was the worst of times it was the age of wisdom it was the age of fool i shness it was the epoch of belief it was the epoch of incredulity it was the season of light it was the season of darkness it was the spring of hope it was the winter of despair
        """)
        self.assertEqual(sa.lcp(), (3, 5, 'acaag'))
