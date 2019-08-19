:- initialization main.

lastE(X,[X]).
lastE(X,[_|Z]) :- lastE(X, Z).

remove_last([],[]) :- !, fail.

remove_last([_],[]) :- !.

remove_last([X | T],[X | T2]) :- remove_last(T,T2).

main :-
	remove_last([1],X),
	write(X),nl.