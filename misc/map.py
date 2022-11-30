#!/usr/bin/python3

from collections import defaultdict, deque
from typing import Dict, List

Map = Dict[str, List[str]]

def init_map(fname: str, sort: bool=True) -> Map:
    '''Initialize a adjacency list representation of a map, reading in
    territory - territority edges from a given filename. By default, map
    entries are sorted in descending order by neighbour list length.'''
    m = defaultdict(list)
    with open(fname, 'r') as f:
        for line in f:
            parent, child = line.split()
            m[parent].append(child)
            m[child].append(parent)

    if sort:
        return dict(sorted(m.items(),
                    key=lambda item : len(item[1]), reverse=True))
    else:
        return m

def colour_map(m: Map) -> Dict[str, int]:
    colours = dict({region: -1 for region in m.keys()})
    colour_opts = set({'orange', 'green', 'purple', 'yellow'})

    first = tuple(m.keys())[0]
    visited = set({first})
    to_visit = deque([first])
    while len(to_visit) > 0:
        current = to_visit.popleft()
        allowed = colour_opts.copy()
        for neighbour in m[current]:
            if neighbour not in visited:
                to_visit.append(neighbour)
                visited.add(neighbour)
            allowed -= {colours[neighbour]}
        colours[current] = tuple(allowed)[0]

    for region, neighbours in m.items():
        for neighbour in neighbours:
            assert colours[region] != colours[neighbour]

    return colours

def main():
    usa = init_map('usa_edges.in')
    colouring = colour_map(usa)
    print(colouring)

if __name__ == '__main__':
    main()
