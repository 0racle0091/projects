from math import cos, sin, sqrt
from matplotlib import pyplot as plt
from operator import itemgetter
import sympy


def j1(x):
    x1 = x[0]
    x2 = x[1]
    return (x1 ** 2 + x2 ** 2 + 1) ** 0.5 + x1 / 2 - x2 / 2


def d_j1(x):
    x1 = x[0]
    x2 = x[1]
    return [x1 / ((x1 ** 2 + x2 ** 2 + 1) ** 0.5) + 0.5, x2 / ((x1 ** 2 + x2 ** 2 + 1) ** 0.5) - 0.5]


def j2(x):
    x1 = x[0]
    x2 = x[1]
    x3 = x[2]
    return x1 ** 2 + 5 * (x2 ** 2) + 2 * (x3 ** 2) + cos(x1 - x2 + x3)


def d_j2(x):
    x1 = x[0]
    x2 = x[1]
    x3 = x[2]
    return [2 * x1 - sin(x1 - x2 + x3), 10 * x2 + sin(x1 - x2 + x3), 4 * x3 - sin(x1 - x2 + x3)]


# def j2(x):
#     x1 = x[0]
#     x2 = x[1]
#     x3 = x[2]
#     return 4*x1**2+5*x2**2+7*x3**2-2*x1*x2+x1*x3+x1-x2+x3
#
#
# def d_j2(x):
#     x1 = x[0]
#     x2 = x[1]
#     x3 = x[2]
#     return [8*x1-2*x2+x3+1, -2*x1+10*x2-1, x1+14*x3+1]


# Норма для метода Нелдора-Мида
# f - исследуемая функция, x- список точек на текущем шаге, xc - центр тяжести


def norm(f, x, xc):
    N = len(x)  # Кол-во точек (размерность многогранника (симплекса))
    sigma = 0.0
    for i in range(N):
        sigma += (f(x[i][0]) - f(xc)) ** 2
    return (sigma / N) ** 0.5


# График сходимости
def plot_convergence(best):
    plt.plot(range(len(best)), best)
    plt.show()
    return 0


# J - минимизируемая функция, X0 - начальное приближение, eps - заданная точность, step - шаг
def d_p_m(J, x0, eps):
    # Параметры метода Нелдера-Мида
    alpha = 1.0
    beta = 0.5
    gamma = 2.0

    N = len(x0[0][0])  # Размерность пространства, где определена исследуемая функция
    x0.sort(key=itemgetter(1))  # Сортируем по возрастанию значений функции в точках
    X = [x0] # Список найденных точек
    iteration = 0  # Номер итерации

    BEST = [J(x0[0][0])]  # Список лучших значений точек

    x = []
    while True:
        worse = X[iteration][N][0]  # Наихудшая точка
        point_found_on_step = False  # Найдена ли точка на текущем шаге (для дальнейшего при проверке)

        # Находим центр тяжести
        xc = [0.0 for i in range(N)]  # Центр тяжести
        for i in range(N):
            for j in range(N):
                xc[j] += X[iteration][i][0][j] / N

        # Условие выхода из поиска
        if norm(J, X[iteration], xc) <= eps:
            plot_convergence(BEST)
            return X

        # Отражение наихудшей вершины
        xr = [0.0 for i in range(N)]
        for i in range(N):
            xr[i] = (1 + alpha) * xc[i] - alpha * X[iteration][N][0][i]

        if J(xr) <= J(X[iteration][0][0]): # сравниваем отраженную с лучшей
            # Выполняем растяжение
            xe = [0.0 for i in range(N)]
            for i in range(N):
                xe[i] = gamma * xr[i] + (1 - gamma) * xc[i]

            if J(xe) < J(X[iteration][0][0]): # сравниваем, стала ли точка после растяжения наилучшей
                worse = xe
            else:
                worse = xr

        if J(X[iteration][int(N / 2)][0]) < J(xr) <= J(worse): # шаг 4с
            # Выполняем сжатие
            xk = [0.0 for i in range(N)]
            for i in range(N):
                xk[i] = (1 - beta) * xc[i] + beta * X[iteration][N][0][i]
            worse = xk

        if J(X[iteration][0][0]) < J(xr) <= J(X[iteration][int(N / 2)][0]): # шаг 4b
            worse = xr

        if J(xr) > J(worse):
            # Выполняем уменьшение
            x = []  # Новая точка, которую находим
            for i in range(N + 1):
                xx = [0.0 for k in range(N)]  # Вспомогательный
                for j in range(N):
                    if i == N:
                        xx[j] = X[iteration][0][0][j] + 0.5 * (worse[j] - X[iteration][0][0][j])
                    else:
                        xx[j] = X[iteration][0][0][j] + 0.5 * (X[iteration][i][0][j] - X[iteration][0][0][j])
                x.append([xx, J(xx)])
            point_found_on_step = True

        if point_found_on_step:
            X.append(x)
        else:
            x = []  # Новая точка, которую находим
            for i in range(N + 1):
                if i == N:
                    x.append([worse, J(worse)])
                else:
                    x.append([X[iteration][i][0], J(X[iteration][i][0])])
            X.append(x)

        iteration += 1
        X[iteration].sort(key=itemgetter(1))

        BEST.append(J(X[iteration][0][0]))


# Нелдер-Мид
#Начальная точка

#значение функции 1
# x0 = [[[0, 0, 0], j2([0, 0, 0])],
#     [[1, 0, 0], j2([1, 0, 0])],
#     [[1, 1, 0], j2([1, 1, 0])],
#     [[0, 1, 0], j2([0, 1, 0])],
#     [[0.5, 0.5, sqrt(2)/2], j2([0.5, 0.5, sqrt(2)/2])]]


x0 = [[[0.5, 0, 0], j2([0.5, 0, 0])],
    [[1.5, 0, 0], j2([1.5, 0, 0])],
    [[1.5, 1, 0], j2([1.5, 1, 0])],
    [[0.5, 1, 0], j2([0.5, 1, 0])],
    [[1, 0.5, sqrt(2)/2], j2([1, 0.5, sqrt(2)/2])]]


# x0 = [[[1, 0, 0], j2([1, 0, 0])],
#     [[2, 0, 0], j2([2, 0, 0])],
#     [[2, 1, 0], j2([2, 1, 0])],
#     [[1, 1, 0], j2([1, 1, 0])],
#     [[1.5, 0.5, sqrt(2)/2], j2([1.5, 0.5, sqrt(2)/2])]]


# x0 = [[[-10, 0, 0], j2([-10, 0, 0])],
#     [[-11, 0, 0], j2([-11, 0, 0])],
#     [[-11, 1, 0], j2([-11, 1, 0])],
#     [[-10, 1, 0], j2([-10, 1, 0])],
#     [[-9.5, 0.5, sqrt(2)/2], j2([-9.5, 0.5, sqrt(2)/2])]]


#значение функции 56.80178
# x0 = [[[-5, 0, 0], j2([-5, 0, 0])],
#     [[-4, 0, 0], j2([-4, 0, 0])],
#     [[-4, 1, 0], j2([-4, 1, 0])],
#     [[-5, 1, 0], j2([-5, 1, 0])],
#     [[-4.5, 10.5, sqrt(2)/2], j2([-4.5, 10.5, sqrt(2)/2])]]


# x0 = [[[0, 0], j1([0, 0])],
#     [[1, 0], j1([1, 0])],
#     [[0.5, sqrt(3)/2], j1([0.5, sqrt(3)/2])],
#      [[0.5,sqrt(3)/6], j1([0.5, sqrt(3)/6])]]

print("Нелдер-Мид")
answer = d_p_m(j2, x0, 0.0001)
print("Минимум =", answer[len(answer) - 1][0])
print("Кол-во итераций = ", len(answer))



