from sympy import *
def J0(x1,x2,x3):
    return -x1-4*x2
    #return -x1 - 5*x2
def J1(x1,x2,x3):
    return x1+x2**2-1
    #return x1+x2**2 - 1
def J2(x1,x2,x3):
    return -x1+x2
    #return -x1 + 2*x2
def MAX(x,y):
    if x > y:
        return x*x
    else:
        return y*y
def F(x1,x2,x3,k):
    return J0(x1,x2,x3)+k*MAX(J1(x1,x2,x3),0) + k*MAX(J2(x1,x2,x3),0)
def dJ0x1(x1,x2,x3):
    x_1, x_2, x_3 = symbols('x1 x2 x3')
    return diff(J0(x_1,x_2,x_3),x_1).subs([(x_1,x1),(x_2,x2),(x_3,x3)])
def dJ1x1(x1,x2,x3):
    x_1, x_2, x_3 = symbols('x1 x2 x3')
    return diff(J1(x_1,x_2,x_3)**2,x_1).subs([(x_1,x1),(x_2,x2),(x_3,x3)])
def dJ0x2(x1,x2,x3):
    x_1, x_2, x_3 = symbols('x1 x2 x3')
    return diff(J0(x_1,x_2,x_3),x_2).subs([(x_1,x1),(x_2,x2),(x_3,x3)])
def dJ1x2(x1,x2,x3):
    x_1, x_2, x_3 = symbols('x1 x2 x3')
    return diff(J1(x_1,x_2,x_3)**2,x_2).subs([(x_1,x1),(x_2,x2),(x_3,x3)])
def dJ2x1(x1,x2,x3):
    x_1, x_2, x_3 = symbols('x1 x2 x3')
    return diff(J2(x_1,x_2,x_3)**2,x_1).subs([(x_1,x1),(x_2,x2),(x_3,x3)])
def dJ2x2(x1,x2,x3):
    x_1, x_2, x_3 = symbols('x1 x2 x3')
    return diff(J2(x_1,x_2,x_3)**2,x_2).subs([(x_1,x1),(x_2,x2),(x_3,x3)])
#in tribute of POlya Matvei ans Simen SHIsh
def dx(x1,x2,x3,k):
    if J2(x1,x2,x3) > 0 and J1(x1,x2,x3) > 0:
        return dJ0x1(x1,x2,x3) + k*(dJ1x1(x1,x2,x3)+dJ2x1(x1,x2,x3))
    if J2(x1,x2,x3) <= 0 and J1(x1,x2,x3) > 0:
        return dJ0x1(x1,x2,x3) + k*(dJ1x1(x1,x2,x3))
    if J2(x1,x2,x3) > 0 and J1(x1,x2,x3) <= 0:
        return dJ0x1(x1,x2,x3) + k*dJ2x1(x1,x2,x3)
    if J2(x1,x2,x3) <= 0 and J1(x1,x2,x3) <= 0:
        return dJ0x1(x1,x2,x3)
def dy(x1,x2,x3,k):
    if J2(x1,x2,x3) > 0 and J1(x1,x2,x3) > 0:
        return dJ0x2(x1,x2,x3) + k*(dJ1x2(x1,x2,x3)+dJ2x2(x1,x2,x3))
    if J2(x1,x2,x3) <= 0 and J1(x1,x2,x3) > 0:
        return dJ0x2(x1,x2,x3) + k*(dJ1x2(x1,x2,x3))
    if J2(x1,x2,x3) > 0 and J1(x1,x2,x3) <= 0:
        return dJ0x2(x1,x2,x3) + k*(dJ2x2(x1,x2,x3))
    if J2(x1,x2,x3) <= 0 and J1(x1,x2,x3) <= 0:
        return dJ0x2(x1,x2,x3)
def dz(x1,x2,x3,k):
    return 0
def Norma(x1,x2,x3):
    return (x1**2+x2**2+x3**2)**(1/2)
x1 = 1
x2 = 1
x3 = 0
epsi = 0.01
a = 0.1
i = 0
k = 1
j = 0
c = []
v = []
m = []
while True:
    if j >= 4:
        if Norma(x1-c[j//2],x2-v[j//2],x3-m[j//2]) <= epsi:
            break
    while Norma(dx(x1,x2,x3,k),dy(x1,x2,x3,k),dz(x1,x2,x3,k)) >= epsi:
        f0 = F(x1,x2,x3,k)
        x1 -= a*dx(x1,x2,x3,k)
        x2 -= a * dy(x1, x2, x3,k)
        x3 -= a * dz(x1, x2, x3,k)
        if f0 <= F(x1,x2,x3,k):
            a = a/2
        i+=1
    j+=1
    k=2**j
    c.append(x1)
    v.append(x2)
    m.append(x3)

print("x1 = ",x1," x2 = ",x2, " x3 = ",x3)
print("Jmin = ",F(x1,x2,x3,k))
print("число итераций", j)