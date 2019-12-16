# -*- coding: utf-8 -*-

import numpy as np
from random import randint, choice


def gen(n):
    mtx = np.matrix( [[randint(0, 1) for _ in range(n)] for _ in range(n)], dtype='bool' )
    for i in range(n):
        mtx[i, i] = 0 # Diagonal
    return mtx

def isConnected(mtx, n):
    if (mtx == mtx.transpose()).all(): # Symmetrix
        return sum(mtx**i for i in range(1, n+1)).all() # Reachable
    else:
        return False

def count(mtx, n):
    """
    Count the degrees of all nodes in the graph.
    """
    return [mtx[i].sum() for i in range(n)]

def constructTrace(mtx, n, odd):
    cnt = count(mtx, n)
    if odd:
        start, end = 0, n-1 # The nodes to start and end to.
        while cnt[start] & 1 == 0:
            start += 1
        while cnt[end] & 1 == 0:
            end -= 1
    else:
        start = end = 0

    trace = []
    i, j = start, 0
    # print(start, end)
    while sum(cnt) > 2:
        while not mtx[i, j] or (i, j) in trace or (j, i) in trace or j==end and cnt[end]==1:
            j = choice(range(n))
        cnt[i] -= 1
        cnt[j] -= 1
        trace.append((i, j))
        # print(trace)
        i = j
    trace.append((j, end))
    return trace


def main():
    n = int(input("Please input the number of nodes: "))

    mtx = gen(n)
    print(f"Matrix:\n{mtx}")

    if isConnected(mtx, n):
        odds = sum(i&1 for i in count(mtx, n))
        if odds == 0:
            # print(f"Matrix:\n{mtx}")
            print("The graph is a Eulerian graph.")
            print(constructTrace(mtx, n, odd=False))
        elif odds == 2:
            # print(f"Matrix:\n{mtx}")
            print("The graph is a semi-Eulerian graph.")
            print(constructTrace(mtx, n, odd=True))
        else:
            print("The graph is not a Eulerian graph.")
    else:
        print("The graph is not a Eulerian graph.")


if __name__ == "__main__":
    main()