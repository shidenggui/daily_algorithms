symbols = {
    'I': 1,
    'V': 5,
    'X': 10,
    'L': 50,
    'C': 100,
    'D': 500,
    'M': 1000
}

class Solution:
    def romanToInt(self, s):
        """
        :type s: str
        :rtype: int
        """
        # 默认 prev 为 0 非常巧妙，这样初始的 prev 就不会影响 result
        prev = 0
        result = 0
        for c in s:
            cur = symbols[c]
            # prev == symbols[c] 也是累加，比如 III 为 3，所以这里是 prev >= symbols[c]
            result += symbols[c] if prev >= symbols[c] else symbols[c] - 2 * prev
            prev = symbols[c]
        return result
        
