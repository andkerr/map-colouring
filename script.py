import subprocess
import sys


def main():
    if len(sys.argv) != 2:
        print("usage python3 script.py [edge list file]")

    node_ids = {}
    n_nodes = 0

    edges = []

    with open(sys.argv[1], 'r') as f:
        for line in f:
            if line != '\n':
                (u, v) = line.split()
                if node_ids.get(u) is None:
                    node_ids[u] = n_nodes
                    n_nodes += 1
                if node_ids.get(v) is None:
                    node_ids[v] = n_nodes
                    n_nodes += 1
                edges.append((node_ids[u], node_ids[v]))

    colouring_input = '\n'.join([' '.join(map(str, edge)) for edge in edges])
    p = subprocess.run(['./colouring'],
                       input=colouring_input,
                       encoding='ascii',
                       capture_output=True) 

    node_lookup = {v : k for (k, v) in node_ids.items()}
    colour_strings = ['red', 'green', 'blue', 'yellow']

    for line in p.stdout.rstrip().split('\n'):
        (node, colour) = line.split()
        print(node_lookup[int(node)], colour_strings[int(colour)])    

if __name__ == '__main__':
    main()
