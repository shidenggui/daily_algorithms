from collections import defaultdict


def to_abc(vertex):
    return 'ABCDE'[vertex]


def dfs(vertex, visit, graph):
    visit[vertex] = True
    print('visit: ', to_abc(vertex))
    for adjacent in graph[vertex]:
        print('from ', to_abc(vertex), ' see ', to_abc(adjacent))
        if not visit[adjacent]:
            dfs(adjacent, visit, graph)

def is_connected(n, edges):
    visit = [False] * n
    graph = [[] for _ in range(n)]
    for src, dest in edges:
        graph[src].append(dest)
        graph[dest].append(src)
    dfs(0, visit, graph)
    if all(visit):
        return True
    return False

def test_is_connected():
    edges = [
        (0, 1), (0, 3), (0, 4),
        (1, 2), (1, 3),
        (2, 3), (2, 4),
    ]
    assert is_connected(5, edges) == True

test_is_connected()
