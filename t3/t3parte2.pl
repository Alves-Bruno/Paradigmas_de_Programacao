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
