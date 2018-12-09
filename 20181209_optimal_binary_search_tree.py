def optimal_binary_search_tree(words, n):
    matrix = [[float('inf')] * n for _ in range(n)]
    for i in range(n):
        matrix[i][i] = words[i]

    path = [[-1] * n for _ in range(n)]

    for k in range(1, n):
        for left in range(n - k):
            right = left + k
            for i in range(left, right + 1):
                if i - 1 < left:
                    left_cost = 0
                else:
                    left_cost = matrix[left][i - 1]

                if i + 1 > right:
                    right_cost = 0
                else:
                    right_cost = matrix[i + 1][right]
                min_cost = left_cost + right_cost + sum(words[left: right + 1])
                if min_cost < matrix[left][right]:
                    matrix[left][right] = min_cost
                    path[left][right] = i
    return matrix[left][right], matrix, path

CHARS = {
    'a': 0.22,
    'am': 0.18,
    'and': 0.20,
    'egg': 0.05,
    'if': 0.25,
    'the': 0.02,
    'two': 0.08,
}

def to_list(chars):
    keys = sorted(chars.keys())
    probs = []
    for k in keys:
        probs.append(chars[k])
    return probs

min_cost, matrix, path = optimal_binary_search_tree(to_list(CHARS), len(CHARS))
import pprint

assert abs(min_cost - 2.15) < 0.001
print('min_cost: ', min_cost)
print('matrix: ')
pprint.pprint(matrix)
print('path: ')
pprint.pprint(path)
