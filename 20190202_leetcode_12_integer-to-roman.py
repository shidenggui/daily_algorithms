# 事先统计好所有对应的值
symbols = [('M', 1000), 
           ('CM', 900),
           ('D', 500),
           ('CD', 400),
           ('C', 100),
           ('XC', 90),
           ('L', 50),
           ('XL', 40),
           ('X', 10),
           ('IX', 9),
           ('V', 5),
           ('IV', 4),
           ('I', 1)]

class Solution:
    def intToRoman(self, num):
        """
        :type num: int
        :rtype: str
        """
        result = []
        for symbol, value in symbols:
            result.append(num // value * symbol) 
            num -= num // value * value
        return ''.join(result)
