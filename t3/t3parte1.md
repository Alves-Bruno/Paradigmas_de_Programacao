# T3 parte 1

#### Consulta: ?- avo(joao,Y)
| Prolog trace output | Descrição |
| :--------- | :--------- |
| ?- avo(joao,Y) |  Chama avo(). |
|  Call: (7) avo(joao, _G2216) ? creep | Realiza a consulta, subistituindo Y por um valor único. |
|  Call: (8) pai(joao, _G2292) ? creep | Testa a primeira condição. Tenta encontrar um Y que seja filho de joao. | 
|   Exit: (8) pai(joao, jose) ? creep | Retorna verdadeiro para Y = jose (2º fato). |
|   Call: (8) pai(jose, _G2216) ? creep | Testa a segunda condição. Tenta encontrar um Z que seja filho de jose(Y). | 
|  Fail: (8) pai(jose, _G2216) ? creep | Nao encontra um Z que seja filho de jose. Retorna falso. |
| Fail: (7) avo(joao, _G2216) ? creep | Continua procurando por um filho de joao. Retorna falso. |
| false. | Retorna falso. | 

--------------------------------

#### Consulta: ?- avo(roberto,Y).
| Prolog trace output | Descrição |
| :--------- | :--------- |
| ?- avo(roberto,Y).| Chama avo(). |
|  Call: (7) avo(roberto, _G3178) ? creep| Realiza a consulta, subistituindo Y por um valor único. |
|   Call: (8) pai(roberto, _G3254) ? creep| Testa a primeira condição. Tenta encontrar um Y que seja filho de roberto. | 
|   Exit: (8) pai(roberto, joao) ? creep|  Retorna verdadeiro para Y = joao (1º fato). |
|   Call: (8) pai(joao, _G3178) ? creep| Testa a segunda condição. Tenta encontrar um Z que seja filho de joao(Y). | 
|   Exit: (8) pai(joao, jose) ? creep| Retorna verdadeiro para Z = jose (2º fato). |
|  Exit: (7) avo(roberto, jose) ? creep| As duas condições são verdadeiras para Y = jose. | 
|Y = jose ;| Retorna Y = jose. | 
|   Redo: (8) pai(roberto, _G3254) ? creep|  Realiza a consulta novamente. |
 |  Exit: (8) pai(roberto, julio) ? creep| Retorna verdadeiro para Y = julio (3º fato). |
| Call: (8) pai(julio, _G3178) ? creep| Testa a segunda condição. Tenta encontrar um Z que seja filho de julio(Y). | 
|   Exit: (8) pai(julio, marcos) ? creep| Retorna verdadeiro para Z = marcos (4º fato). |
|   Exit: (7) avo(roberto, marcos) ? creep| As duas condições são verdadeiras para Y = marcos. | 
|Y = marcos ;| Retorna Y = marcos. | 
|   Redo: (8) pai(julio, _G3178) ? creep| Realiza a consulta novamente para a 2ª condição. |
|  Exit: (8) pai(julio, mario) ? creep| Retorna verdadeiro para Z = mario (5º fato). |
|   Exit: (7) avo(roberto, mario) ? creep| As duas condições são verdadeiras para Y = mario. | 
|Y = mario.| Retorna Y = mario. | 

----------------------------------

#### Consulta: ?- azulejos(120, A).
| Prolog trace output | Descrição |
| :--------- | :--------- |
| ?- azulejos(120, A).| Chama azulejos(). |
|   Call: (7) azulejos(120, _G2218) ? creep|  Realiza a consulta, subistituindo A por um valor único. |
|   Call: (8) 120>0 ? creep| Chama a função para verifcar se Na é maior que 0. |
|   Exit: (8) 120>0 ? creep| Retorna verdadeiro. |
|   Call: (8) _G2297 is floor(sqrt(120)) ? creep| Chama a função para verificar qual o menor valor inteiro mais próximo de raiz quadrada de 120. |
|   Exit: (8) 10 is floor(sqrt(120)) ? creep| Q recebe o valor retornado pela função (Q = 10). |
|   Call: (8) _G2303 is 120-10*10 ? creep| Chama a função para calcular a expressão: Na - Q*Q. |
|   Exit: (8) 20 is 120-10*10 ? creep| R recebe o valor da expressão (R = 20). |
|   Call: (8) azulejos(20, _G2304) ? creep| Chama azulejos(20, _). | 
|   Call: (9) 20>0 ? creep| Chama a função para verifcar se Na é maior que 0. |
|   Exit: (9) 20>0 ? creep| Retorna verdadeiro. |
|   Call: (9) _G2307 is floor(sqrt(20)) ? creep|  Chama a função para verificar qual o menor valor inteiro mais próximo de raiz quadrada de 20. |
|   Exit: (9) 4 is floor(sqrt(20)) ? creep| Q recebe o valor retornado pela função (Q = 4). |
|   Call: (9) _G2313 is 20-4*4 ? creep| Chama a função para calcular a expressão: Na - Q*Q. |
|   Exit: (9) 4 is 20-4*4 ? creep| R recebe o valor da expressão (R = 4). |
|   Call: (9) azulejos(4, _G2314) ? creep|  Chama azulejos(4, _). | 
|   Call: (10) 4>0 ? creep| Chama a função para verifcar se Na é maior que 0. |
|   Exit: (10) 4>0 ? creep| Retorna verdadeiro. |
|   Call: (10) _G2317 is floor(sqrt(4)) ? creep| Chama a função para verificar qual o menor valor inteiro mais próximo de raiz quadrada de 4. |
|   Exit: (10) 2 is floor(sqrt(4)) ? creep|  Q recebe o valor retornado pela função (Q = 2). |
|   Call: (10) _G2323 is 4-2*2 ? creep| Chama a função para calcular a expressão: Na - Q*Q. |
|   Exit: (10) 0 is 4-2*2 ? creep| R recebe o valor da expressão (R = 0). |
|   Call: (10) azulejos(0, _G2324) ? creep| Chama azulejos(0, _). | 
|   Exit: (10) azulejos(0, 0) ? creep| Retorna _= 0. | 
|   Call: (10) _G2326 is 1+0 ? creep| Chama a função para calcular a expressão: 1 + C (C = 0).|
|   Exit: (10) 1 is 1+0 ? creep| Nq recebe 1. | 
|   Exit: (9) azulejos(4, 1) ? creep| Nq = 1, para Na=4.|
|   Call: (9) _G2329 is 1+1 ? creep| Chama a função para calcular a expressão: 1 + C (C = 1).|
|   Exit: (9) 2 is 1+1 ? creep| Nq recebe 2.| 
|   Exit: (8) azulejos(20, 2) ? creep| Nq = 2, para Na=20. |
|   Call: (8) _G2218 is 1+2 ? creep| Chama a função para calcular a expressão: 1 + C (C = 2).|
|   Exit: (8) 3 is 1+2 ? creep| Nq recebe 3.| 
|   Exit: (7) azulejos(120, 3) ? creep|Nq = 3, para Na = 120. |
|A = 3 ;| A recebe 3. |

---------------------
#### Consulta: ?- fat(3, A).

```prolog
% Código que calcula fatorial de um número.

fat(0,1).
fat(N,F) :-
	N > 0,
	Aux is N-1,
	fat(Aux, M),
	F is N*M.
```

| Prolog trace output | Descrição |
| :--------- | :--------- |
| ?- fat(3, A).| Chama fat(). |
|   Call: (7) fat(3, _G2218) ? creep| Realiza a consulta, subistituindo A por um valor único. | 
|   Call: (8) 3>0 ? creep| Chama a função para verifcar se N é maior que 0 (N = 3). |
|   Exit: (8) 3>0 ? creep| Retorna verdadeiro. | 
|   Call: (8) _G2296 is 3+ -1 ? creep| Chama a função para calcular a expressão: N - 1. |
|   Exit: (8) 2 is 3+ -1 ? creep| Aux recebe o valor calculado (Aux = 2). | 
|   Call: (8) fat(2, _G2297) ? creep| Chama a função fat(2, _). | 
|   Call: (9) 2>0 ? creep| Chama a função para verifcar se N é maior que 0 (N = 2). |
|   Exit: (9) 2>0 ? creep| Retorna verdadeiro. | 
|   Call: (9) _G2299 is 2+ -1 ? creep| Chama a função para calcular a expressão: N - 1. |
|   Exit: (9) 1 is 2+ -1 ? creep| Aux recebe o valor calculado (Aux = 1). | 
|   Call: (9) fat(1, _G2300) ? creep| Chama a função fat(1, _). | 
|   Call: (10) 1>0 ? creep| Chama a função para verifcar se N é maior que 0 (N = 1). |
|   Exit: (10) 1>0 ? creep| Retorna verdadeiro. | 
|   Call: (10) _G2302 is 1+ -1 ? creep| Chama a função para calcular a expressão: N - 1. |
|   Exit: (10) 0 is 1+ -1 ? creep| Aux recebe o valor calculado (Aux = 0). | 
|   Call: (10) fat(0, _G2303) ? creep|  Chama a função fat(0, F). | 
|   Exit: (10) fat(0, 1) ? creep| F recebe 1, de acordo com o fato fat(0,1). | 
|   Call: (10) _G2305 is 1*1 ? creep| Chama a função para calcular a expressão: N*M. |
|   Exit: (10) 1 is 1*1 ? creep| F recebe 1.| 
|   Exit: (9) fat(1, 1) ? creep| Para N = 1, F = 1. |
|   Call: (9) _G2308 is 2*1 ? creep| Chama a função para calcular a expressão: N*M. |
|   Exit: (9) 2 is 2*1 ? creep|  F recebe 2.| 
|   Exit: (8) fat(2, 2) ? creep| Para N = 2, F = 2. |
|   Call: (8) _G2218 is 3*2 ? creep| Chama a função para calcular a expressão: N*M. |
|  Exit: (8) 6 is 3*2 ? creep|  F recebe 6.|
|   Exit: (7) fat(3, 6) ? creep| Para N = 3, F = 6. |
|A = 6 .| Fatorial de 3 igual a 6. A = 6. |



