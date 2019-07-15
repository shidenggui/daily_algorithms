def cc(edges, n):
    graph = [[] for _ in range(n)]
    for src, dest in edges:
        graph[src].append(dest)
        graph[dest].append(src)

    count = [0]
    marked = [False] * n
    for vertex in range(n):
        if not marked[vertex]:
            dfs(vertex, graph, marked, count)
            count[0] += 1
    return count[0]

def dfs(vertex, graph, marked, count):
    marked[vertex] = True
    for adj in graph[vertex]:
        if not marked[adj]:
            dfs(adj, graph, marked, count)


print(cc([[0, 1], [0, 2], [0, 5], [0, 6], [3, 4], [3, 5], [4, 6], [7, 8], [9, 10], [9, 11], [9, 12], [11, 12]], 13))
