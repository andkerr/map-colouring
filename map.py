from math import log
from typing import List


class Map:
    def __init__(self, states: dict):
        self.states = [State(state, neighbours) for
                       state, neighbours in states.items()]
        self.num_states = len(states)

    def __str__(self):
        out = f'this map contains {self.num_states} states\n'
        out += '=================' + int(log(self.num_states)) * '=' + '========\n'
        for state in self.states:
            out += f'State: {state.name}, Neighbours: '
            for neighbour in state.neighbours:
                out += f'{neighbour}, '
            out += '\n'

        return out


class State:
    def __init__(self, name: str, neighbours: List, colour: str = None):
        self.name = name
        self.neighbours = neighbours
        self.colour = colour


def main():
    states = {
        'me': ['nh'],
        'nh': ['me', 'vt'],
        'vt': ['nh', 'ma', 'ny'],
        'ma': ['vt', 'nh', 'ri', 'ct', 'ny'],
        'ct': ['ri', 'ma', 'ny'],
        'ny': ['vt', 'ma', 'ct']
    }

    the_northeast = Map(states)
    print(the_northeast)


if __name__ == '__main__':
    main()
