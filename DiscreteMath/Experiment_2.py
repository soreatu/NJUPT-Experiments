# -*- coding: utf-8 -*-

import numpy as np

def GetInput():
    print('Please input the number of elements:')
    n = int(input())
    
    rlt = set()
    print('Please input the relation (empty to end):')
    i = input()
    while i != '':
        rlt.add(eval(i))
        i = input()
    return n, rlt

def Transform(n, rlt):
    mtx = np.matrix(np.zeros((n, n), dtype='bool'))
    for x, y in rlt:
        mtx[x-1, y-1] = 1
    return mtx

Reflexivity = lambda m: m.diagonal().all()
Irreflexivity = lambda m: not m.diagonal().any()
Symmetry = lambda m: (m == m.transpose()).all()
Irsymmetry = lambda m: not any(x!=y and m[x,y]==True and m[y,x]==True  for x in range(m.shape[0]) for y in range(m.shape[0]))
Transmission = lambda m: all(m[i, k]==1 for i in range(m.shape[0]) for j in range(m.shape[0]) for k in range(m.shape[0]) if m[i, j]==m[j, k]==1)

def main():
    while True:
        n, rlt = GetInput()
        m = Transform(n, rlt)
        print(f"Reflexivity: {Reflexivity(m)}")
        print(f"Irreflexivity: {Irreflexivity(m)}")
        print(f"Symmetry: {Symmetry(m)}")
        print(f"Irsymmetry: {Irsymmetry(m)}")
        print(f"Transmission: {Transmission(m)}\n")

if __name__ == '__main__':
    main()