:- initialization main.

loop(START,END) :-
	START > END;
	write('hello'),nl,
	loop(START+1,END).


main :-
	loop(1,5).
