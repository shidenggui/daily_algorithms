from collections import deque


def unweighted_shortest_path(n, edges, start):
    graph = [[] for _ in range(n)]
    for src, dest in edges:
        graph[src].append(dest)

    dis = [float('inf')] * n
    dis[start] = 0
    path = [-1] * n

    q = deque()
    q.append(start)
    while q:
        vertex = q.popleft()
        for adjacent in graph[vertex]:
            if dis[adjacent] != float('inf'):
                continue
            dis[adjacent] = dis[vertex] + 1
            path[adjacent] = vertex
            q.append(adjacent)
    return dis, path

def test_unweighted_shortest_path():
    edges = [
        (1, 2), (1, 4),
        (2, 4), (2, 5),
        (3, 1), (3, 6),
        (4, 3), (4, 5), (4, 6), (4, 7),
        (5, 7),
        (7, 6),
    ]
    print(unweighted_shortest_path(8, edges, 3))

test_unweighted_shortest_path()
