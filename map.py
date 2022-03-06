#!/usr/bin/python3

from collections import defaultdict
from typing import Dict, List

def init_map(fname: str, sort: bool=True) -> Dict[str, List[str]]:
    '''Initialize a adjacency list representation of a m, reading in
    territory - territority edges from a given filename. By default, m
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

def main():
    usa = init_map('usa_edges.in')
    print(usa)
    colours = {state: None for state in usa.keys()}

if __name__ == '__main__':
    main()
