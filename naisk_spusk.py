from math import sqrt
from scipy.optimize import minimize


def j1(x):
    x1 = x[0]
    x2 = x[1]
    return x1**4 + 2*x2**4 +(x1**2)*(x2**2) +2*x1 + x2


def d_j1(x):
    x1 = x[0]
    x2 = x[1]
    return [4*x1**3 + x1*2*x2**2 + 2, 8*x2**3 + 2*x2*x1**2 + 1]


def j2(x):
    x1 = x[0]
    x2 = x[1]
    x3 = x[2]
    return 4*(1+x1**2 + x2**2 + 3*x3**2)(1/2) + x1 - 2*x2


def d_j2(x):
    x1 = x[0]
    x2 = x[1]
    x3 = x[2]
    return [1 + (4*x1/((1+x1**2 + x2**2 + 3*x3**2)(1/2))), (4*x2/((1+x1**2 + x2**2 + 3*x3**2)(1/2))) - 2, (12*x3/((1 + x1**2 + x2**2 + 3*x3**2)(1/2)))]


eps = 10  -6
alpha = 0.1 #шаг градиентного метода


# Евклидова норма
def norm(values):
    N = len(values)  # Кол-во производных или переменных функции J
    n = 0
    for i in range(N):
        n += values[i]  2
    return sqrt(n)


def Naisk_Spusk(J, J_, x0, eps, step):
    N = len(x0)  # Кол-во производных или переменных функции J
    X = [x0]  # Список найденных точек
    iteration = 0  # Номер итерации
    if norm(J_(X[iteration])) < eps:  # Если сразу попали в точку минимума
        return X
    while norm(J_(X[iteration])) > eps:
        while True:
            x = []  # Вспомогательный список (точки x(k+1))

            #тут надо считать альфа(step)

            def phi(step_):
                x_=[]
                for i in range(N):
                    x_.append(X[-1][i] - step_ * J_(X[-1])[i])
                return J(x_)

            step = float(minimize(phi, step).x)

            for i in range(N):  # Идем по переменным
                x.append(X[iteration][i] - step * J_(X[iteration])[i])
            if J(x) - J(X[iteration]) < 0.0:
                X.append(x)
                break
        iteration += 1
    return X


print("Наискорейший спуск")
answer = Naisk_Spusk(j1, d_j1, [1,1], 0.000001, 0.1)
print("Минимум = ", answer[len(answer) - 1])
print("Кол-во итераций = ", len(answer))
print(f"Значение функции в точке минимума: {j1(answer[len(answer) - 1])}")