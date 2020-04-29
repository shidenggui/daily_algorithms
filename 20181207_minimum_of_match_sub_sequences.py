# C(i+1) = Min(C(i) + 1, C(j) + 1 if is_custom(s[j:i + 1])) ( j >= 0 and j <= i )

def minimum_of_match_sub_sequences(fields, seqs):
    path = [None] * (len(fields) + 1)
    cost = [0] * len(fields)
    for i, field in enumerate(fields):
        cost[i] = cost[i - 1] + 1
        for j in range(i - 1, -1, -1):
            if tuple(fields[j: i + 1]) in seqs:
                if cost[j - 1] + 1 < cost[i]:
                    cost[i] = cost[j - 1] + 1
                    path[i] = j
    return cost, path

def print_result_by_path(path, node, fields, seqs):
    if node < 0:
        return

    if path[node] is None:
        print_result_by_path(path, node - 1, fields, seqs)
        print(fields[node], end=' ')
        return
    print_result_by_path(path, path[node] - 1, fields, seqs)
    print('-'.join(fields[path[node]: node + 1]), end=' ')

def main():
    fields = ('A', 'B', 'C', 'D', 'E', 'F')
    seqs = {
            ('A', 'B'),
            ('B', 'C'),
            ('C', 'D', 'E'),
            ('E', 'F'),
            }
    print('fields: ', fields)
    print('seqs: ', seqs)
    cost, path = minimum_of_match_sub_sequences(fields, seqs)
    print('intermediate cost: ', cost, 'result path: ', path)
    print('final fields: ', cost[len(fields) - 1])
    print('output: ', end='')
    print_result_by_path(path, len(fields) - 1, fields, seqs)

main()

# output:
# fields:  ('A', 'B', 'C', 'D', 'E', 'F')
# seqs:  {('A', 'B'), ('C', 'D', 'E'), ('B', 'C'), ('E', 'F')}
# intermediate cost:  [1, 1, 2, 3, 2, 3] result path:  [None, 0, None, None, 2, None]
# final fields:  3
# output: A-B C-D-E F
