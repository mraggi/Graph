def unzip(L):
    return [l[0] for l in L],[l[1] for l in L]

def busqueda_binaria(L, x):
    primero = 0
    ultimo = len(L)
    while primero+1 < ultimo:
        medio = (ultimo + primero)//2
        if x < L[medio]:
            ultimo = medio
        else:
            primero = medio
    return L[primero] == x

if __name__ == "__main__":
    print(busqueda_binaria([1,1,2,2,2,3,3,4], 3))
    print(busqueda_binaria([1,1,2,2,2,3,3,4], 4))
    print(busqueda_binaria([1,1,2,2,2,4,4,4], 3))
    print(busqueda_binaria([1,1,2,2,2,3,3,4], 8))
    
