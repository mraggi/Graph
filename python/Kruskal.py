from DisjointSets import DisjointSets
from Grafica import Grafica
from Prim import prim

def aristas_sin_ciclos(aristas, D):
    mst = []
    for w, u, v in aristas:
        if D.misma_componente(u, v):
            continue
        mst.append((u, v, w))
        D.juntar(u, v)
    return mst

def kruskal(G):
    aristas = G.aristas()
    aristas.sort()
    D = DisjointSets(G.num_verts)
    return aristas_sin_ciclos(aristas, D)


if __name__ == "__main__":
    G = Grafica(5)
    G.conectar(0,1,2)
    G.conectar(0,2,3)
    G.conectar(1,4,1)
    G.conectar(1,2,3)
    G.conectar(2,3,4)
    G.conectar(3,4,1)
    print("Prim:")
    for arista in prim(G):
        print(arista)

    print("Kruskal:")
    for arista in kruskal(G):
        print(arista)

    



