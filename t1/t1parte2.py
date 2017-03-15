from datetime import datetime
import sys

'''
1. Escreva uma função que receba uma lista de nomes
e retorne uma lista com a string "Sr. " adicionada
ao início de cada nome.'''
def addSr(lista):
  return list(map(lambda x: 'Sr. ' + x, lista))

'''
2. Escreva uma função que, dada uma lista de números,
calcule 3*n**2 + 2/n + 1 para cada número n da lista.'''
def funcao(lista):
    return list(map(lambda n: 3*n**2 + 2/n + 1, lista))

'''
3. Crie uma função que receba uma lista de nomes e retorne
outra lista com somente aqueles nomes que terminarem com a letra 'a'.'''
def somente_a(lista):
    return list(filter(lambda x: x[-1] == 'a', lista))

'''4. Escreva uma função que, dada uma lista de idades de
pessoas no ano atual, retorne uma lista somente com as
idades de quem nasceu depois de 1970. Para testar a condição,
sua função deverá subtrair a idade do ano atual.'''
def idade(lista):
    tempo = datetime.now()
    ano = int(tempo.year)
    return list(filter(lambda x: ano - x > 1970, lista))

'''5. O código abaixo é escrito em Python imperativo. Escreva um
código equivalente usando programação funcional.'''
def multiplica_2(lista):
    return list(map(lambda x: x * 2, lista))
