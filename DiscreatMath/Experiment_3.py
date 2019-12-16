# -*- coding: utf-8 -*-

def parser(s):
    '''
    Parse the expression.
    '''
    return sorted(list(set( map( int, s.strip("{}").split(',') ) )))

divide = lambda x, y: y % x == 0

def paritalOrder(s):
    '''
    Find all the divide relations in set *s*.
    '''
    res = []
    l = len(s)
    for i in range(l):
        for j in range(i, l):
            if divide(s[i], s[j]):
                res.append( tuple([s[i], s[j]]) )
    return res

def COV(p, s):
    '''
    Find all the cover relations in set *s*.
    '''
    res = []
    for pair in p:
        a, b = pair
        if a == b: continue
        
        for i in range(2*a, b, a):
            if i in s and divide(i, b):
                break
        else:
            res.append(pair)
    return res

def outputCOV(s):
    print("COV: {", end='')
    for pair in s[:-1]:
        print(f"<{pair[0]}, {pair[1]}>, ", end='')
    if len(s):
        print(f"<{s[-1][0]}, {s[-1][1]}>", end='')
    print("}")


def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

lcm = lambda a, b: a*b // gcd(a,b)

def isComplement(s):
    _max, _min = max(s), min(s)
    for a in s:
        if not any(gcd(a,b)==_min for b in s) or not any(lcm(a,b)==_max for b in s):
            return False
    return True


if __name__ == "__main__":
    s = parser(input('Please input a set: '))
    p = paritalOrder(s)
    cov = COV(p, s)
    outputCOV(cov)
    
    print(f"{s} is a complemented lattice: {isComplement(s)}")