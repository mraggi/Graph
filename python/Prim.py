import random
import heapq
import Grafica


def extraer_menor(aristas):
    return heapq.heappop(aristas) 

def add_links(G, AE, v, vertices_explorados):
    for x, w in zip(*G.vecinos(v)):
        if vertices_explorados[x] == 0:
            heapq.heappush(AE,(w, v, x))

def prim(G):
    n = G.num_verts
    v = random.randint(0, n-1)
    
    vertices_explorados = [0]*n
    vertices_explorados[v] = 1
    
    AE = [(w, v, x) for x, w in zip(*G.vecinos(v))]
    heapq.heapify(AE)
    arbol = []
    
    while AE:
        w,u,v = extraer_menor(AE)
        if vertices_explorados[v] == 0:
            arbol.append((u,v,w))
            vertices_explorados[v] = 1
            add_links(G, AE, v, vertices_explorados)
    return arbol


# Quiero hacer esto:

if __name__ == "__main__":
    G = Grafica(5)
    G.conectar(0,1,2)
    G.conectar(0,2,3)
    G.conectar(1,4,1)
    G.conectar(1,2,3)
    G.conectar(2,3,4)
    G.conectar(3,4,1)
    for arista in prim(G):
        print(arista)
