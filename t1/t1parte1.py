import sys

#1. Defina uma função `somaQuad(x,y)` que calcule
#a soma dos quadrados de dois números x e y.
def somaQuad(x, y):
  return x**2 + y**2


#2. Crie uma função `hasEqHeads(l1,l2)` que verifique
#se as listas l1 e l2 possuem o mesmo primeiro elemento.
def hasEqHeads(l1, l2):
  return l1[0] == l2[0]

#3. Escreva uma função que receba uma lista de nomes e
#retorne uma lista com a string "Sr. " adicionada ao
#início de cada nome. Defina uma função auxiliar para ajudar neste exercício.
def addSr_aux(nome):
  return 'Sr. ' + nome

def addSr(lista):
  return list(map(addSr_aux, lista))

#4. Crie uma função que receba uma string e retorne o
#número de espaços nela contidos.  Defina uma função
#auxiliar para ajudar neste exercício.
def isEspace(char):
  return char == ' '

def lenEspaces(string):
  return len(list(filter(isEspace, string)))


#5. Escreva uma função que, dada uma lista de números, calcule
#3*n**2 + 2/n + 1 para cada número n da lista. Defina uma
# função auxiliar para ajudar neste exercício.
def funcao_aux(n):
  return 3*n**2 + 2/n + 1

def funcao(lista):
  return list(map(funcao_aux, lista))

#6. Escreva uma função que, dada uma lista de números, retorne
#uma lista com apenas os que forem negativos. Defina uma
#função auxiliar para ajudar neste exercício.
def listaNegativos_aux(n):
  return n<0

def listaNegativos(lista):
  return list(filter(listaNegativos_aux,lista))

#7. Escreva uma função que receba uma lista de números e retorne
#somente os que estiverem entre 1 e 100, inclusive. Defina uma
#função auxiliar para ajudar neste exercício.
def lista_1_100_aux(n):
  return n >= 1 and n <= 100

def lista_1_100(lista):
  return list(filter(lista_1_100_aux, lista))

#8. Escreva uma função que receba uma lista de números e retorne
#somente aqueles que forem pares. Defina uma função auxiliar
#para ajudar neste exercício.
def lista_par_aux(n):
  return n%2 == 0

def lista_par(lista):
  return list(filter(lista_par_aux, lista))

#9. Crie uma função `charFound(c,s)` que verifique se o caracter c
#está contido na string. O resultado deve ser `True` ou `False`.
#Você não deve usar o operador `in`. Defina uma função auxiliar
#para ajudar neste exercício.

def charFound(c, s):

  def aux(charc):
    return charc == c

  return len(list(filter(aux, s))) > 0

#10. Escreva uma função que receba uma lista de strings e retorne uma
#nova lista com adição de marcações HTML (p.ex.: `<B>` e `</B>`) antes
#e depois de cada string.
def html(lista):
  return list(map(lambda x: '<B>' + x + '</B>', lista))
