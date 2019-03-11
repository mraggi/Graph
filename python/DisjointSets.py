class DisjointSets():
    def __init__(self, n):
        self.padres = [-1]*n 
    
    def es_raiz(self, nodo):
        return self.padres[nodo] == -1
    
    def raiz(self, nodo):
        if self.es_raiz(nodo):
            return nodo
        
        r = self.raiz(self.padres[nodo])
        self.padres[nodo] = r
        
        return r
    
    def misma_componente(self, a, b):
        return self.raiz(a) == self.raiz(b)
    
    def juntar(self, a, b):
        ra = self.raiz(a)
        rb = self.raiz(b)
        self.padres[ra] = rb

if __name__ == "__main__":
    D = DisjointSets(6)

    print("3 es raiz?", D.es_raiz(3))

    D.juntar(0,1)
    D.juntar(1,2)

    print("misma_componente 0 y 1?", D.misma_componente(0,1))
