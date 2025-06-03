from math import cos, sin, sqrt
from matplotlib import pyplot as plt


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


eps = 10 ** -4
alpha = 0.01 #шаг градиентного метода


# Евклидова норма
def norm(values):
    N = len(values)  # Кол-во производных или переменных функции J
    n = 0
    for i in range(N):
        n += values[i] ** 2
    return sqrt(n)


# Построение графика сходимости метода
def plot_convergence(f, values):
    list_of_values = [norm(f(x)) for x in values]
    plt.plot(range(len(values)), list_of_values)
    plt.show()
    return 0


def Grad_Spusk(J, J_, x0, eps, step):
    N = len(x0)  # Кол-во производных или переменных функции J
    X = [x0]  # Список найденных точек
    iteration = 0  # Номер итерации
    while norm(J_(X[iteration])) > eps:
        while True:
            x = []  # Вспомогательный список (точки x(k+1))
            for i in range(N):  # Идем по переменным
                x.append(X[iteration][i] - step * J_(X[iteration])[i])
            if J(x) - J(X[iteration]) < 0.0:
                X.append(x)
                break
            else:
                step /= 2
        iteration += 1
    plot_convergence(J_, X)
    return X


print("Градиентный спуск")
answer = Grad_Spusk(j2, d_j2, [0.01, 0.01, 0.01], 0.0001, 100)
print("Минимум = ", answer[len(answer) - 1])
print("Кол-во итераций = ", len(answer))
print(f"Значение функции в точке минимума: {j2(answer[len(answer) - 1])}")