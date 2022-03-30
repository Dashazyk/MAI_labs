import numpy as np
from matplotlib import pyplot as plt
from numpy import random
# где то тут есть теорема Байеса
def exp(x,lamda):
    result = lamda*np.exp(-lamda*x)
    return result

# метод, который определяет парметры распределений заданного набора числей, входящих в смесь распределений
def EM_method(x,k,eps = 1e-10, tries = 30, Qmax = 100):
    g_delta = 1
    g_w = np.zeros(k)
    g_lamda = np.zeros(k)

    for tr in range(tries):
        n = len(x)
        g = np.random.rand(k,n) # матрица рандомных вещей
        w = np.random.rand(k) # вероятность гипотезы B[j]
        lamda = np.random.rand(k)

        delta = 1
        iter = 0
        prev_delta = 2
        prev_w = np.zeros(k)
        prev_lamda = np.zeros(k)

        # цикл выполняется пока дельта больше нужного минимума или не выполнено макс кол-во итераций или дельта не стала минимальной
        while delta >= eps and iter <= Qmax and delta < prev_delta:
            prev_delta = delta
            prev_lamda = lamda
            prev_w = w
            iter += 1

            #E step
            g0 = g.copy() # предыдущее состояние матрицы

            for i in range(k):
                for j in range(n):
                    det = 0
                    for v in range(k):
                        det += w[v]*exp(x[j],lamda[v])
                    g[i][j] = w[i]*exp(x[j],lamda[i])/det

            delta = np.max(np.absolute(g0-g)) # из матрицы разницы матриц выбирается max значение

            #M step
            for i in range(k): # строки
                sumG = 0
                sumGX = 0

                for j in range(n): # столбцы
                    sumG += g[i][j]
                    sumGX += g[i][j]*x[j]

                lamda[i] = sumG / sumGX
                w[i] = sumG/np.sum(g)
        
            #print('Delta')
            #print(delta)
    
        #print('Itterations')
        #print(iter)
        
        if (prev_delta < delta):
            delta = prev_delta
            lamda = prev_lamda
            w = prev_w

        if (delta < g_delta):
            print('Found good delta')
            print(delta)
            g_delta = delta
            g_w = w
            g_lamda = lamda
    
        print('Try')
        print(tr+1)
    
    print('Done')
    print(g_delta)
    return g_w, g_lamda

#P[i] = w[i] * norm(x,lamda[i])
#P = sum(P[i])

###############################

#scale = 1/lamda

a1 = (random.exponential(scale=0.5, size=(1, 1000)))
a2 = (random.exponential(scale=4, size=(1, 1000)))

X = np.concatenate((a1,a2),axis = None)

plt.hist(X)

X.shape
k = 2

eps = 0.6

Qmax = 100
tryes = 5

w,lamda = EM_method(X,k,eps,tryes,Qmax)
print(w)
print(lamda)
# 100 linearly spaced numbers
x = np.linspace(0,24,100)

# the function, which is y = x^2 here
y = 0
for i in range(k):
    print(w[i])
    y += w[i] * exp(x,lamda[i]) /k

# setting the axes at the centre
fig = plt.figure()



y1 = w[0] * exp(x,lamda[0])
y2 = w[1] * exp(x,lamda[1])

# plot the function
plt.plot(x,y1, 'r')
plt.plot(x,y2, 'b')

plt.show()

# setting the axes at the centre
fig = plt.figure()

# plot the function
plt.plot(x,y, 'r')



# show the plot
plt.show()

plt.hist(X, density=True)