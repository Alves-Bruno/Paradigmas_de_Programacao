import sys

def main():

    list_a = [1, 2, 3, 4, 5, 6, 7]
    list_b = list_a #list_b recebe o ponteiro da list_a

    list_c = list_a[:] #Uma copia da list_a eh feita em list_c

    if list_a == list_c: #Compara se todos os elementos das listas sao iguais
        print('Esses listas sao iguas')

    # Executar um loop por todo a list
    for it in list_a:
        print(it)

    # Verificar se existe um valor em uma lista
    if (5 in list_a) == True:
        print('5 esta nessa lista')
    else:
        print('5 NAO esta nessa lista')

    # Adicionar um elemento no final da lista
    list_a.append(100)
    print(list_a)

     # Remover um elemento da lista
    value = list_a.pop(0)
    print('elemento[0] da lista eh', value)
    print(list_a)

    del list_a[0] #Deleta o elemento[0] da lista
    print(list_a)

    # Ordenar listas
    list_a = sorted(list_a)
    print(list_a)
    list_a = sorted(list_a, reverse=True)
    print(list_a)
    
    

#Calling the main function
if __name__ == '__main__':
    main()