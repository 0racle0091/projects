from math import cos, sin, sqrt
from itertools import product


def j4(x):
    x1 = x[0]
    x2 = x[1]
    x3 = x[2]
    x4 = x[3]
    return x1 ** 2 + x2 ** 2 + x3 ** 2 + x4 ** 2
    # return -1 / ((x1 + 1) ** 2 + x2 ** 2)


def j1(x):
    x1 = x[0]
    x2 = x[1]
    return x1**4 + 2*x2**4 + (x1**2)*(x2**2) + 2*x1 + x2


def j2(x):
    x1 = x[0]
    x2 = x[1]
    x3 = x[2]
    return 4*(1+x1**2 + x2**2 + 3*x3**2)**(1/2) + x1 - 2*x2


# Евклидова норма
def norm(values):
    N = len(values)  # Кол-во производных или переменных функции J
    n = 0
    for i in range(N):
        n += values[i] ** 2
    return sqrt(n)


def exploratory_search(x0, lmb0, J):
    x=[]
    lmb_ = lmb0
    for i in range(len(x0)):
        x.append([])
        x_plus = x0[i] + lmb_[i]
        x[i].append(x_plus)
        x_minus = x0[i] - lmb_[i]
        x[i].append(x_minus)
    x = list(product(*x)) #скалярным произведением группирует все "иксы" и "игрики"
    min_f = 10 ** 10
    iteration = 0
    for i in range(len(x)):
        if J(x[i]) < min_f:
            min_f = J(x[i])
            iteration = i
    return x[iteration]


def sample_search(x_b, x_k, J):
    x = []
    for i in range(len(x_b)):
        x.append(x_b[i] + 2 * (x_k[i] - x_b[i]))
    return x


def lambda_decrease(lmb):
    for i in range(len(lmb)):
        lmb[i] /= 2
    return lmb


def h_j(x0, lmb0, J, eps,i):
    N = len(x0)
    lmb = lmb0
    X = [x0] #список найденных точек
    while norm(lmb) > eps:
        while True:
            x_ = exploratory_search(X[-1], lmb, J)
            if J(x_) < J(X[-1]):
                X.append(x_)
                if J(sample_search(X[-2], X[-1], J)) < J(X[-1]):
                    X.append(sample_search(X[-2], X[-1], J))
            else:
                break
        lmb = lambda_decrease(lmb)
        i += 1
    print("Количество итераций :",i)
    return X[-1]


answer = h_j([1, 1,1], [0.6, 0.5,0.8], j2, 0.000001, 1)
print("Минимум = ", answer)
print(f"Значение функции в точке минимума: {j2(answer)}")