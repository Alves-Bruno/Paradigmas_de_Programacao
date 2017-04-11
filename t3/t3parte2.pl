% 1. Defina um predicado `somaQuad(X,Y,Q)` que seja verdadeiro se Q for a soma dos quadrados de X e Y.

somaQuad(X, Y, Q) :-
	A is X*X + Y*Y,
	A = Q. 
	

% 2. Defina um predicado `zeroInit(L)` que é verdadeiro se L for uma lista que inicia com o número 0 (zero).

zeroInit(L):-
	[H|_] = L,
	H = 0.

% 3. Defina um predicado `hasEqHeads(L1,L2)` que seja verdadeiro se as listas L1 e L2 possuírem o mesmo primeiro elemento. 

hasEqHeads(L1, L2):-
	[H1|_] = L1,
	[H2|_] = L2,
	H1 = H2.

% 4. Defina um predicado `has5(L)` que seja verdadeiro se L for uma lista de 5 elementos. Lembre de como funciona a unificação
% em Prolog e resolva este exercício sem usar o predicado pré-definido `length`.

has5(L):- 
	[_,_,_,_,_] = L.

% 5. Defina um predicado `hasN(L,N)` que seja verdadeiro se L for uma lista de N elementos. Agora você pode usar um predicado pré-definido.

hasN(L,N):-
	length(L, Len),
	Len = N.

% 6. Defina um predicado `isBin(L)` que seja verdadeiro se L for uma lista contendo somente elementos `0` e `1`. Use recursão.

isBin([]).

isBin(L):-
	[H|T] = L,
	member(H, [1, 0]),
	isBin(T).
	
% 7. Defina um predicado `mesmaPosicao(A,L1,L2)` para verificar se um elemento A está na mesma posição nas listas L1 e L2. Assuma 
% que L1 e L2 sejam permutações de uma lista de elementos distintos, sem repetições. Dica: procure auxílio em predicados pré-definidos.

mesmaPosicao(A, L1, L2):-
	nth0(N1, L1, A),
	nth0(N2, L2, A),
	N1 = N2.

% 8. Defina um predicado `repete5(E,L)` que seja verdadeiro se a lista L for composta por exatamente 5 repetições do elemento E.
% Não use recursão.

repete5(E, L):-
	L = [E, E, E, E, E].


% 9. Defina um predicado recursivo `sumQuads(L,S)` que seja verdadeiro se S for o somatório dos quadrados dos elementos da lista L.

sumQuads([], 0).

sumQuads(L,S):-
	[H|T] = L,
	sumQuads(T, Aux),
	S is H*H + Aux.

% 10. Defina um predicado recursivo `repete(N,E,L)` que seja verdadeiro se a lista L for composta por exatamente N
% repetições do elemento E.

repete(0,E,[]).
aux(1,T,T).
aux(0,E,M).

repete(N,E,L):-
	[H|T] = L,
	repete(Aux, E, T),
	aux(X,E,H),
	N is X + Aux.
	
% 11. Defina um predicado recursivo `mapop(L1,L2)` que seja verdadeiro se a lista L2 for formada aplicando-se a operação `2*x+1` a 
% cada elemento x da lista L1.

mapop([],[]).

mapop(L1,L2):-
	[H1|T1] = L1,
	[H2|T2] = L2,
	X is 2*H1+1,
	H2 = X,
	mapop(T1,T2).	

% 12. Defina um predicado `positivos(L1,L2)`, de forma que L2 seja uma lista só com os elementos positivos de L1.

positivos([],[]).
positivos([H1|T1],[H1|T2]):-
	H1 > 0,
	positivos(T1,T2).

positivos([H1|T1],L2):-
	H1 =< 0,
	positivos(T1,L2).
