import subprocess
import sys


# convert a plaintext edge list with arbitrary vertex identifiers to an
# edge list containing only integer values
def standardize_edge_list(fname):
    node_ids = {}
    n_nodes = 0
    edges = []

    with open(fname, 'r') as f:
        for line in f.read().rstrip().split('\n'):
            (u, v) = line.split()
            if node_ids.get(u) is None:
                node_ids[u] = n_nodes
                n_nodes += 1
            if node_ids.get(v) is None:
                node_ids[v] = n_nodes
                n_nodes += 1
            edges.append((node_ids[u], node_ids[v]))

    return node_ids, edges


def main():
    if len(sys.argv) != 2:
        print("usage python3 script.py [edge list file]")
        return

    node_ids, edges = standardize_edge_list(sys.argv[1])
    colouring_input = '\n'.join([' '.join(map(str, edge)) for edge in edges])
    try:
        p = subprocess.run(['./colouring'],
                           input=colouring_input,
                           encoding='ascii',
                           capture_output=True) 
    except FileNotFoundError:
        print('Could not find the colouring executable in this directory')
        return

    node_lookup = {v : k for (k, v) in node_ids.items()}
    colour_strings = ['red', 'green', 'blue', 'yellow']

    for line in p.stdout.rstrip().split('\n'):
        (node, colour) = line.split()
        print(node_lookup[int(node)], colour_strings[int(colour)])    


if __name__ == '__main__':
    main()
