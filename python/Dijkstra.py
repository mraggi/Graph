from Grafica import *
import copy

class Camino():
    def __init__():
        self.lista = []
        self.peso_total = 0.
    
    def agregar_arista(v,w):
        self.lista.append((v,w))
        self.peso_total += w

class cola_prioridad():
    def __init__():

def agregar_vecinos_frontera(G, frontera, p, l):
    for u, w in zip(*G.vecinos(l)):
        q = copy.copy(p)
        q.agregar_arista(u, w)
        frontera.insert(q)

def dijkstra_lento(G, vertice_inicial, objetivo):
    frontera = cola_prioridad()
    camino_trivial = Camino()
    camino_trivial.agregar_arista(vertice_inicial, 0)
    frontera.insert(camino_trivial)
    while not frontera.empty():
        p = frontera.pop()
        l = p.ultimo()
        if objetivo(l):
            return p
        agregar_vecinos_frontera(G, frontera, p, l)
    return None
    
if __name__ == "__main__":
    G = Grafica(5)
    G.conectar(0,1,2)
    G.conectar(0,2,3)
    G.conectar(1,4,1)
    G.conectar(1,2,3)
    G.conectar(2,3,4)
    G.conectar(3,4,1)
    
    camino = dijkstra_lento(G,0,lambda x: x == 4)
    for a in camino.lista:
        print(a)

    
