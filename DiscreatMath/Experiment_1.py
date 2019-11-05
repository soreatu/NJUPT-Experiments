# -*- coding: utf-8 -*-

VARIBLES = ('P', 'Q', 'R')
OPERATORS = ('￢', '∧', '∨', '->', '<=>')
PRIORITY  = {'￢':5, '∧':4, '∨':3, '-':2, '<':1, '(':0}

def GetInput() -> str:
    '''
    Get expression from user's input.
    '''
    eps = input('\nPlease input the expression (empty to quit): ')
    if eps == '':
        quit()
    return eps

def ParseExpreesion(eps:str) -> str:
    '''
    Convert the expression to postfix expression.
    '''
    stackOperator = []
    # stackVarible = []
    res = ''
    for s in eps:
        if s in ('P', 'Q', 'R'):
            res += s
        elif s in ('￢', '∧', '∨', '-', '<'):
            while len(stackOperator) != 0 and PRIORITY[s] <= PRIORITY[stackOperator[-1]]:
                res += stackOperator.pop()
            stackOperator.append(s)
        elif s == '(':
            stackOperator.append(s)
        elif s == ')':
            while stackOperator[-1] != '(':
                res += stackOperator.pop()
            stackOperator.pop()             # pop '('
    while len(stackOperator) != 0:
        res += stackOperator.pop()
    return res

def CalExpression(eps:str) -> bool:
    '''
    Calculate the result given the postfix expression.
    '''
    stack = []
    for s in eps:
        if s in ('0', '1'):
            stack.append(bool(int(s)))
        elif s == '￢':
            stack.append(not stack.pop())
        elif 1:
            op2, op1 = stack.pop(), stack.pop()
            if s == '∧':
                res = op1 & op2
            elif s == '∨':
                res = op1 | op2
            elif s == '-':
                res = False if op1 and not op2 else True
            elif s == '<':
                res = True if op1 == op2 else False
            stack.append(res)
    return bool(stack.pop())

def GenTruthFalseTable(eps:str) -> list:
    '''
    Generate the true false table according to the parsed expression.
    '''
    # varibles = CountVaribles(eps)
    table = []
    for P in (True, False):
        for Q in (True, False):
            for R in (True, False):
                transTable = str.maketrans('PQR', ''.join(map(str, map(int, (P, Q, R)))))
                tmp = eps.translate(transTable)
                res = CalExpression(tmp)
                table.append([P, Q, R, res])
    return table

def PrintTable(t:list, eps:str):
    '''
    Print the true false table.
    '''
    print(f"{'P':10s}{'Q':10s}{'R':10s}{eps:10s}")
    for row in t:
        for i in row:
            if i:
                print(f"{'T':10s}", end='')
            else:
                print(f"{'F':10s}", end='')
        print()

def GenCNF(t:list) -> list:
    '''
    Generate the conjunctive normal forms according to the truth table.
    '''
    res = []
    for row in t:
        if row[-1] == True:
            continue
        res.append('∨'.join(map(lambda iv: ('' if iv[0] else '￢') + VARIBLES[iv[0]], enumerate(row[:-1]))))
    return res

def PrintCNF(cnfs:list):
    '''
    Print the conjunctive normal forms.
    '''
    print('cnf: ' + '∧'.join(cnf.join('()') for cnf in cnfs))

def GenDNF(t:list) -> str:
    '''
    Generate the disjunctive normal forms according to the truth table.
    '''
    res = []
    for row in t:
        if row[-1] == False:
            continue
        res.append('∧'.join(map(lambda iv: ('' if iv[1] else '￢') + VARIBLES[iv[0]], enumerate(row[:-1]))))
    return res

def PrintDNF(dnfs:list):
    '''
    Print the disjunctive normal forms.
    '''
    print('dnf: ' + '∨'.join(dnf.join('()') for dnf in dnfs))


def main():
    while True:
        eps = GetInput()
        parsedEps = ParseExpreesion(eps)
        
        table = GenTruthFalseTable(parsedEps)
        PrintTable(table, eps)

        DNFs = GenDNF(table)
        PrintDNF(DNFs)
        CNFs = GenCNF(table)
        PrintCNF(CNFs)

if __name__ == '__main__':
    main()