from Grafica import Grafica
import random

def GNP(n,p):
    G = Grafica(n)
    for u in range(n):
        for v in range(u+1, n):
            r = random.random()
            if r < p:
                G.conectar(u,v)
    return G

def generar_parejas(n):
    parejas = []
    for u in range(n):
        for v in range(u+1, n):
            parejas.append([u, v])
    return parejas

def generar_grafica(n, A):
    G = Grafica(n)
    for u,v in A:
        G.conectar(u,v)
    return G
        
def GNM(n,m):
    A = generar_parejas(n)
    random.shuffle(A)
    return generar_grafica(n, A[:m])

if __name__ == "__main__":
    G=GNM(20,40)
    for a in G.aristas():
        print(a)
