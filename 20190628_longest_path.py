import unittest


# Algo P 661
# O(2^n)
def longest_path(edges, n, start, end):
    graph = [[] for _ in range(n)]
    for src, dest, weight in edges:
        graph[src].append((dest, weight))
    max_path_len = 0
    max_path = []
    visited = [False] * n
    path = [None] * n

    def dfs(vertex, path_len):
        nonlocal max_path_len, max_path

        if vertex == end and path_len > max_path_len:
            max_path_len = path_len
            max_path = collect_path(path, end)
        # 如果到达 end 直接 return
        if vertex == end:
            return

        visited[vertex] = True
        for adj, weight in graph[vertex]:
            if visited[adj]:
                continue
            path[adj] = vertex
            dfs(adj, path_len + weight)
        # 需要重置  visited 数组
        visited[vertex] = False

    dfs(start, 0)
    return max_path_len, max_path


def collect_path(path_tree, cur):
    path = [cur]
    while path_tree[cur] is not None:
        cur = path_tree[cur]
        path.append(cur)
    return list(reversed(path))

# Algo P 991
# O(V + E)
def longest_path_in_DAG(edges, n, start, end):
    graph = [[] for _ in range(n)]
    for src, dest, weight in edges:
        graph[src].append((dest, weight))

    visited = [False] * n
    topo_path = []

    def dfs(vertex):
        visited[vertex] = True
        for adj, _ in graph[vertex]:
            if visited[adj]:
                continue
            dfs(adj)
        topo_path.append(vertex)

    dfs(start)
    topo_path.reverse()
    print(topo_path)

    dist = [float('-inf')] * n
    dist[start] = 0
    path_tree = [None] * n

    def dfs(vertex):
        # DAG 不需要 visited，因为 DAG 不会变成环
        # visited[vertex] = True
        for adj, weight in graph[vertex]:
            # DAG 不需要 visited
            # if visited[adj]:
            #   continue
            updated_dis = dist[vertex] + weight
            if updated_dis > dist[adj]:
                dist[adj] = updated_dis
                path_tree[adj] = vertex
                dfs(adj)

    dfs(start)

    max_path = collect_path(path_tree, end)
    max_path_len = dist[end]
    return max_path_len, max_path


class TestLongestPath(unittest.TestCase):
    def test(self):
        edges = [(0, 1, 1), (1, 3, 2), (0, 4, 1), (4, 3, 3)]
        excepted = (4, [0, 4, 3])
        result = longest_path(edges, 5, 0, 3)
        print(result)
        self.assertEqual(result, excepted)

        edges = [
            (5, 4, 0.35),
            (4, 7, 0.37),
            (5, 7, 0.28),
            (5, 1, 0.32),
            (4, 0, 0.38),
            (0, 2, 0.26),
            (3, 7, 0.39),
            (1, 3, 0.29),
            (7, 2, 0.34),
            (6, 2, 0.40),
            (3, 6, 0.52),
            (6, 0, 0.58),
            (6, 4, 0.93),
        ]

        excepted = (2.44, [5, 1, 3, 6, 4, 0])
        result = longest_path(edges, 8, 5, 0)
        print(result)
        self.assertEqual(result, excepted)

    def test_DAG(self):
        edges = [(0, 1, 1), (1, 3, 2), (0, 4, 1), (4, 3, 3)]
        excepted = (4, [0, 4, 3])
        result = longest_path_in_DAG(edges, 5, 0, 3)
        print(result)
        self.assertEqual(result, excepted)

        edges = [
            (5, 4, 0.35),
            (4, 7, 0.37),
            (5, 7, 0.28),
            (5, 1, 0.32),
            (4, 0, 0.38),
            (0, 2, 0.26),
            (3, 7, 0.39),
            (1, 3, 0.29),
            (7, 2, 0.34),
            (6, 2, 0.40),
            (3, 6, 0.52),
            (6, 0, 0.58),
            (6, 4, 0.93),
        ]

        excepted = (2.44, [5, 1, 3, 6, 4, 0])
        result = longest_path_in_DAG(edges, 8, 5, 0)
        print(result)
        self.assertEqual(result, excepted)


unittest.main()
