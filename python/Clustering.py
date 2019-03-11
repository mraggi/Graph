from Grafica import Grafica
from ErdosRenyi import *
import math

def num_parejas_conectadas(G,u):
    resultado = 0
    vecinos, _ = G.vecinos(u)
    for v in vecinos:
        if v < u:
            continue
        for w in vecinos:
            if w < v:
                continue
            if G.conectados(v,w):
                resultado += 1
    return resultado

def binomial(n, k):
    return math.factorial(n)/(math.factorial(k)*math.factorial(n-k))

def num_triangulos(G):
    resultado = 0
    for u in G.vertices():
        resultado += num_parejas_conectadas(G,u)
    return resultado

def num_eles(G):
    resultado = 0
    for u in G.vertices():
        resultado += binomial(G.grado(u), 2)
    return resultado
    

def clustering(G):
    return 3*num_triangulos(G)/num_eles(G)


def clustering_local(G, v):
    num_vecinos_conectados = num_parejas_conectadas(G, v)
    return num_vecinos_conectados/binomial(G.grado(v), 2)
    

if __name__ == "__main__":
    G = GNP(1000,0.2)
    print(clustering(G))
