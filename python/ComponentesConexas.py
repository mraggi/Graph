from Grafica import *

def dfs_componentes(G, v, colores, num_componente):
    if colores[v] != -1:
        return
    colores[v] = num_componente
    for u in G.vecinos(v):
        dfs_componentes(G,u,colores,num_componente)

# Regresa una lista de tamaño n, donde el i-ésimo es el número de componente del i-ésimo vértice
def componentes_conexas(G):
    colores = [-1]*G.num_vertices
    num_componente = 0
    for v in G.vertices():
        if colores[v] >= 0:
            continue
        dfs_componentes(G,v,colores,num_componente)
        num_componente += 1
    return num_componente, colores
    
if __name__ == "__main__":
    G = Grafica(6)
    G.conectar(0,1,2)
    G.conectar(0,2,3)
    G.conectar(5,4,1)
    print(componentes_conexas(G))
