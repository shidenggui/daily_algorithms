def find_art(v, num, low, visit, parent, count, art_points, graph):
    visit[v] = True
    count[0] += 1
    num[v] = count[0]
    low[v] = num[v] # rule 1: self num

    for w in graph[v]:
        # error1: if not visit[v]: test not visit for w, not v
        if not visit[w]: # forward edge
            parent[w] = v
            # error2: find_art(v, num, low, visit, parent, count, art_points, graph)
            # also update low for w, not for v
            find_art(w, num, low, visit, parent, count, art_points, graph)
            if low[w] >= num[v]:
                art_points.add(v)
            low[v] = min(low[w], low[v]) # rule 3: tree_edge's low
        elif parent[w] != v: # back edge
            low[v] = min(num[w], low[v]) # rule 2: back edge's num

    
def find_articulation_points(n, edges, start):
    graph = [[] for _ in range(n)]
    for src, dest in edges:
        graph[src].append(dest)

    num = [None] * n
    visit = [False] * n
    count = [0]

    low = [None] * n
    parent = [None] * n

    art_points = set()
    find_art(start, num, low, visit, parent, count, art_points, graph)

    # check root
    if len(list(filter(lambda x: x == start, art_points))) <= 1:
        art_points.discard(start)
    return art_points

def to_abc(v):
    return 'ABCDEFG'[v]

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
