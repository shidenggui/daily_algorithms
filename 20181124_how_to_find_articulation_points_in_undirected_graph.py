def to_abc(v):
    return 'ABCDEFG'[v]

count = 0
def find_art(v, num,  low, parent, visit,art_points, graph):
    global count
    visit[v] = True

    count += 1
    num[v] = count
    low[v] = num[v] # rule 1

    for adj in graph[v]:
        # forward edge
        if not visit[adj]:
            parent[adj] = v
            find_art(adj, num, low, parent, visit, art_points, graph)
            if low[adj] >= num[v]:
                art_points.add(v)
            low[v] = min(low[v], low[adj]) # rule 3
        # back edge
        elif parent[v] != adj:
            low[v] = min(low[v], num[adj]) # rule 2

def find_articulation_points(n, edges, start):
    graph = [[] for _ in range(n)]
    for src, dest in edges:
        graph[src].append(dest)

    visit = [False] * n
    num = [None] * n
    low = [None] * n
    parent = [-1] * n
    art_points = set()

    find_art(start, num, low, parent, visit, art_points, graph)

    # check root
    root_childs = list(filter(lambda x: x == start, parent))
    if len(root_childs) <= 1:
        art_points.discard(start)
    
    print('final parent: ', parent)
    print('final num: ', num)
    print('final low: ', low)
    return art_points

def test_find_articulation_points():
    undirected_edges = [
        (0, 1), (0, 3),
        (1, 2),
        (2, 3), (2, 6),
        (3, 5), (3, 4),
        (4, 5)
    ]

    edges = []
    for src, dest in undirected_edges:
        edges.extend([(src, dest), (dest, src)])
    result = tuple(to_abc(v) for v in find_articulation_points(7, edges, 0))
    assert result == ('C', 'D')
    print(result)

test_find_articulation_points()
