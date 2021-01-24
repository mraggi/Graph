from utils import unzip

class Grafica():
    def __init__(self, num_vertices):
        self.num_vertices = num_vertices
        self.num_aristas = 0
        self.lista_vecinos = [[] for i in range(num_vertices)]
        self.pesos = [[] for i in range(num_vertices)]
        self.vecinos_ordenados = True
        
    def conectar(self, x, y, w = 1.):
        self.lista_vecinos[x].append(y)
        self.lista_vecinos[y].append(x)
        self.pesos[x].append(w)
        self.pesos[y].append(w)
        self.num_aristas += 1
        self.vecinos_ordenados = False
    
    def vecinos(self, x):
        return self.lista_vecinos[x]
    
    def vecinos_pesos(self, x):
        return self.lista_vecinos[x], self.pesos[x]
    
    def vertices(self):
        return range(self.num_vertices)
    
    def grado(self, x):
        return len(self.lista_vecinos[x])
    
    def conectados(self, x, y):
        self.ordenar_vecinos()
        return busqueda_binaria(y, self.lista_vecinos[x])
    
    def ordenar_vecinos(self):
        if self.vecinos_ordenados:
            return
        for u in self.vertices():
            self.lista_vecinos[u], self.pesos[u] = unzip(sorted(list(zip(*self.vecinos(u)))))
        self.vecinos_ordenados = True
    
    def aristas(self):
        A = []
        for u in range(self.num_vertices):
            for v, w in zip(*self.vecinos(u)):
                if u < v:
                    A.append((w, u, v))
        return A
    
if __name__ == "__main__":
    G = Grafica(5)
    G.conectar(0,1,2)
    G.conectar(0,2,3)
    G.conectar(1,4,1)
    G.conectar(1,2,3)
    G.conectar(2,3,4)
    G.conectar(3,4,1)
    G.ordenar_vecinos()
    for i in G.vertices():
        print(G.vecinos(i))
