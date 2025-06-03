import subprocess
from typing import Any


import numpy as np
from pyswarms.single import GlobalBestPSO
from sklearn.svm import SVR
from scipy.optimize import minimize


parameters_file_path = 'D:\\parameters.txt'
stress_values_file_path = 'D:\\stress_values.txt'

pathstress = 'D:\\o.txt'
stressf = []

with open(pathstress, 'r') as file1:
    for line in file1:
        stressf.append(float(line.strip()))


def write_parameters_to_file(params, file_path):
    h0, eta_star, v, taustarprom = params
    with open(file_path, 'w') as file:
        file.write(f"{h0}\n{eta_star}\n{v}\n{taustarprom}\n")


def run_cpp_program():
    subprocess.run([r'D:\\языки прог\identy\x64\Debug\identy.exe'])


def read_stress_values(file_path):
    stress_values = []
    with open(file_path, 'r') as file:
        for line1 in file:
            if line1.startswith('nan') or line1.startswith('inf') or line1.startswith('-inf') or line1.startswith('-nan'):
                continue
            stress_values.append(float(line1.strip()))
    return stress_values


def objective_function(param):
    errors = []
    print(len(param))
    for i in range(len(param)):
        params = 1800000000*param[i][0], param[i][1], 83*param[i][2], 16000000*param[i][3]
        write_parameters_to_file(params, parameters_file_path)

        run_cpp_program()
        error = 0
        stress_values = read_stress_values(stress_values_file_path)
        for stress in stress_values:
            for stressId in stressf:
                error += ((stress - stressId) ** 2)
        if i % 10 == 0:
            print(stress_values[499])
        errors.append(error/500)
        positions.append(param[i])
        values.append(error/500)
    return errors


options = {'c1': 0.5, 'c2': 0.3, 'w': 0.7}


bounds = (np.array([1, 0.5, 0.5, 1]), np.array([2, 1.5,1.5, 2]))

lower_bounds, upper_bounds = bounds
n=10
initial_optimizer = GlobalBestPSO(n_particles=n, dimensions=4, options=options, bounds=bounds)

iterations = 120

positions = []
values = []
best_cost = float('inf')
best_pos = None
best_cost_all_time = []

for i in range(iterations):
    cost, pos = initial_optimizer.optimize(objective_function, 1)
    best_cost_all_time.append(cost)
    if cost < best_cost:
        best_cost = cost
        best_pos = pos
    print(i)

print("pso ", best_cost_all_time)
print(best_pos)

svr = SVR(kernel='rbf', C=1.0, epsilon=0.5)

x_train = np.array([]).reshape(0, 4)
y_train = np.array([])

def pso_objective(param):
    predicted_min = []

    global x_train, y_train,positions, values

    positions=[]
    values=[]

    objective = objective_function(param)

    print("kuku")
    x_train = np.vstack([x_train, positions])
    y_train = np.append(y_train, values)

    print("leny",len(y_train))

    svr.fit(x_train, y_train)

    return objective

total_iterations = 120
best_cost = float('inf')
best_pos = None
best_cost_all_time = []

def svrPredict(x):
    x = np.array(x).reshape(1, -1)
    predicted_min = svr.predict(x)[0]
    return predicted_min


for i in range(total_iterations):
    optimizer = GlobalBestPSO(n_particles=n, dimensions=4, options=options, bounds=bounds)
    cost, pos = optimizer.optimize(pso_objective, 1)
    print(i)
    if cost < best_cost:
        best_cost = cost
        best_pos = pos
    best_cost_all_time.append(best_cost)

    xfs = best_pos
    point = minimize(svrPredict, xfs, method='COBYLA', bounds=((0.7,1.3),(0.5,1.5),(0.5,1.5),(0.7,1.3)),tol=0.1)

    print("point for best svr ",point.x)
    print("point for best fun ", point.fun)

    new_positions = np.vstack((optimizer.swarm.position, point.x))
    new_velocity = np.vstack((optimizer.swarm.velocity, np.zeros((1, 4))))

    optimizer.swarm.n_particles += 1

    n += 1

    print(optimizer.swarm.n_particles)

    optimizer.swarm.position = new_positions
    optimizer.swarm.velocity = new_velocity


print(best_cost)
print(best_pos)

print("best cost all time", best_cost_all_time)