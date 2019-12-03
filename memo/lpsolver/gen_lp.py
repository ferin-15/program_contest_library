import pulp
import sys
import random

# 入力の生成
n = 8
m = 5

while(1):
    # a = [[random.randint(-100, 100) for i in range(n)] for j in range(m)]
    a = [list(map(int,input().split())) for j in range(m)]
    # b = [random.randint(-100, 100) for i in range(m)]
    b = list(map(int,input().split()))
    # c = [random.randint(-100, 100) for i in range(n)]
    c = list(map(int,input().split()))

    problem = pulp.LpProblem("problem-1", pulp.LpMaximize)

    # 変数
    x = [pulp.LpVariable("x"+str(i), cat='Conitinuous') for i in range(n)]

    # 目的関数
    problem += sum(c[i]*x[i] for i in range(n)), "objective"

    # 制約
    for i in range(m):
        problem += sum(a[i][j]*x[j] for j in range(n)) <= b[i], "constraint_{:}".format(i)

    solver = pulp.solvers.PULP_CBC_CMD()
    result_status = problem.solve(solver)

    print(pulp.LpStatus[result_status])

    if pulp.LpStatus[result_status] == "Optimal":
        print(n,m)
        for i in range(m):
            for j in range(n):
                print(a[i][j],end=' ')
            print()
        for i in range(m):
            print(b[i],end=' ')
        print()
        for i in range(n):
            print(c[i],end=' ')
        print()
        print(pulp.LpStatus[result_status], pulp.value(problem.objective))
        break