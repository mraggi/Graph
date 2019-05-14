from Grafica import Grafica
from ComponentesConexas import componentes_conexas
import math

def es_arbol(G: Grafica):
    num_componentes, _ = componentes_conexas(G)
    return num_componentes == 1 and G.num_vertices == G.num_aristas+1

def dfs(G, v, padres):
    for u in G.vecinos(v):
        if u != padres[v]:
            padres[u] = v
            dfs(G, u, padres)

def encontrar_padres(G:Grafica, raiz:int):
    assert(es_arbol(G))
    padres = [-1] * G.num_vertices
    padres[raiz] = None
    dfs(G, raiz, padres)
    return padres

def ancestros(p, u):
    resultado = [u]
    while resultado[-1] != None:
        resultado.append(p[resultado[-1]])
    return resultado[:-1]

def lca_ingenua(p, u, v):
    ancestros_u = ancestros(p, u)
    for x in ancestros(p, v):
        if x in ancestros_u:
            return x
    
    return None

def children(p):
    hijos = [[] for _ in p]
    for i,pi in enumerate(p):
        if pi is not None:
            hijos[pi].append(i)
    return hijos

def dfs_alturas(children, v, h_actual, h):
    h[v] = h_actual
    for c in children[v]:
        dfs_alturas(children, c, h_actual + 1, h)

def alturas(children, raiz):
    h = [-1]*len(children)
    dfs_alturas(children, raiz, 0, h)
    return h

def dfs_ambsa(v, nmbsa, h, children, s):
    nmbsa[v] = s
    section_v = math.ceil(math.sqrt(h[v]))
    section_c = math.ceil(math.sqrt(h[v]+1))
    if section_v != section_c:
        s = v
    for c in children[v]:
        dfs_ambsa(c, nmbsa, h, children, s)

def ambsa(raiz,h,C):
    nbmsa = [0]*len(h)
    dfs_ambsa(raiz, nmbsa, h, C, -1)
    return nbmsa

class lca_sqrt():
    def __init__(self, p):
        self.raiz = p.index(None)
        self.C = children(p)
        self.h = alturas(C,raiz)
        self.A = ambsa(raiz,h,C)
        self.p = p
    
    #to do
    def lca(self,u,v):
        if self.A[u] == self.A[v]:
            return lca_ingenuo(p, u, v, A[u]) 
        else:
            if self.h[u] < self.h[v]:
                v, u = u, v
            while self.h[u] > self.h[v]:
                u = self.A[u]
                
            if self.A[u] == self.A[v]:
                return lca_ingenuo(p, u, v, A[u])
            else:
                u = self.A[u]
                v = self.A[v]
                return self.lca(u, v)

if __name__ == "__main__":
    G = Grafica(5)
    G.conectar(0,1)
    G.conectar(1,2)
    G.conectar(0,3)
    G.conectar(3,4)
    print(es_arbol(G))
    p = encontrar_padres(G, 0)
    print(p)
    print(ancestros(p,4))
    print(lca_ingenua(p,4,1))
