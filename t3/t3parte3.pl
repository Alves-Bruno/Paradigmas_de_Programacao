/*
Fonte: Olimpıada Brasileira de Inform ́atica – OBI2010
Escola colorida

Uma escola ocupa um pr ́edio com seis andares, nume-
rados de 1 a 6 (1  ́e o andar mais baixo, 6 o mais alto).
Os alunos e professores decidiram em conjunto que
cada andar ser ́a pintado com uma cor diferente, entre
amarelo, branco, rosa, azul, laranja e verde.  Ficou
tamb́em decidido que as seguintes condi ̧c ̃oes devem ser
obedecidas:

• Branco deve ser usado para pintar ou o andar 3
ou o andar 4.

• O andar pintado de laranja  ́e mais baixo do que
o andar pintado de rosa.

• O andar pintado de azul  ́e mais baixo do que o
andar pintado de laranja, mas mais alto do que
o andar pintado de amarelo.

*/

% CORES = [amarelo, branco, rosa, azul, laranja, verde]

regra1(A):-
	nth1(3,A,branco);
	nth1(4,A,branco).


regra2(A):-
	nth1(Laranja,A,laranja),
	nth1(Rosa,A,rosa),
	Laranja < Rosa.

regra3(A):-
	nth1(Azul,A,azul),
	nth1(Laranja,A,laranja),
	nth1(Amarelo,A,amarelo),
	Azul < Laranja,
	Azul > Amarelo.


cores(E):-
	E = [_,_,_,_,_,_],
  	Cores = [amarelo,branco,rosa,azul,laranja,verde],
	permutation(Cores, E),
 	regra1(E),
   	regra2(E),
	regra3(E).

/*----------------------------------------------------------
Questao 16.
Qual das alternativas abaixo  ́e uma lista
correta de cores para os andares da escola, do andar 1
ao andar 6?
(A)  amarelo, azul, branco, verde, laranja, rosa. <<-- CORRETA.
(B)   amarelo, azul, laranja, rosa, branco, verde.
(C)  amarelo, laranja, branco, azul, rosa, verde.
(D)  azul, amarelo, laranja, branco, rosa, verde.
(E)   verde, amarelo, rosa, branco, azul, laranja.

?- cores([amarelo,azul,branco,verde,laranja,rosa]).
true .

?- cores([amarelo, azul, laranja, rosa, branco, verde]).
false.

?- cores([amarelo, laranja, branco, azul, rosa, verde]).
false.

?- cores([azul, amarelo, laranja, branco, rosa, verde]).
false.

?- cores([erde, amarelo, rosa, branco, azul, laranja]).
false.
*/


/*----------------------------------------------------------
Questao 17.
Qual das seguintes cores pode ser usada
para pintar qualquer um dos seis andares?
(A)  amarelo
(B)   rosa
(C)  azul
(D)  laranja
(E)   verde <<-- CORRETA.

(A)
?- cores([amarelo,_,_,_,_,_]).
true .
?- cores([_,amarelo,_,_,_,_]).
true .
?- cores([_,_,amarelo,_,_,_]).
false.

(B)
?- cores([rosa,_,_,_,_,_]).
false.

(C)
?- cores([azul,_,_,_,_,_]).
false.

(D)
?- cores([laranja,_,_,_,_,_]).
false.

(E)
?- cores([verde,_,_,_,_,_]).
true .
?- cores([_,verde,_,_,_,_]).
true .
?- cores([_,_,_,verde,_,_]).
true .
?- cores([_,_,_,_,verde,_]).
true .
?- cores([_,_,_,_,_,verde]).
true .
*/

/*----------------------------------------------------------
Questao 18.
Qual das seguintes cores NAO PODE
ser usada para pintar o andar 3?
(A)  amarelo <<-- CORRETA.
(B)   branco
(C)  azul
(D)  laranja
(E)   verde

?- cores([_,_,amarelo,_,_,_]).
false.

?- cores([_,_,branco,_,_,_]).
true .

?- cores([_,_,azul,_,_,_]).
true .

?- cores([_,_,laranja,_,_,_]).
true .

?- cores([_,_,verde,_,_,_]).
true 
*/


/*----------------------------------------------------------
Questao 19.
Se o andar 5 n ̃ao  ́e pintado de laranja,
qual das seguintes afirmativas  ́e necessariamente ver-
dadeira?
(A)  O andar 6  ́e pintado de rosa.
(B)   O andar 5  ́e pintado de verde.
(C)  O ander 4  ́e pintado de branco.
(D)  O andar 3  ́e pintado de laranja.
(E)   O andar 2  ́e pintado de azul. <<-- CORRETA.

(A)
?- cores([_,_,_,_,A,rosa]).
A = verde ;
A = laranja .

(B)
?- cores([laranja,_,_,_,A,_]).
false.
?- cores([_,laranja,_,_,A,_]).
false.
?- cores([_,_,laranja,_,A,_]).
A = rosa ;
A = verde ;
false.

(C)
?- cores([_,_,_,X,A,_]).
X = laranja,
A = rosa ;
X = laranja,
A = verde ;
X = verde,
A = laranja ;
X = branco,
A = rosa ;
X = branco,
A = verde ;
X = branco,
A = laranja ;
X = azul,
A = laranja ;
X = branco,
A = laranja ;
X = azul,
A = laranja ;
X = branco,
A = laranja ;
false.

(D)
?- cores([_,_,_,laranja,_,_]).
true .

(E)
?- cores([_,Y,laranja,_,_,_]).
Y = azul ;
Y = azul ;
false.
?- cores([_,Y,_,laranja,_,_]).
Y = azul ;
Y = azul ;
false.

*/

/*----------------------------------------------------------
Quest ̃ao 20.
Se o andar 3  ́e pintado de laranja, qual
 ́e o andar mais baixo que pode ser pintado de verde?
(A)  6
(B)   5 <<-- CORRETA.
(C)  4
(D)  2
(E)   1

?- cores([_,verde,laranja,_,_,_]).
false.

?- cores([verde,_,laranja,_,_,_]).
false.

?- cores([_,_,laranja,verde,_,_]).
false.

?- cores([_,_,laranja,_,verde,_]).
true .

?- cores([_,_,laranja,_,_,verde]).
true .

*/
