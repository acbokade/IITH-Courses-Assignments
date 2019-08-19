% Ajinkya Bokade
% CS17BTECH11001
% Given a list of N numbers give the sequence of arithmetic operations(+|-|*|/) on first N-1 elements to produce the Nth element

% obtaining last element of list
lastElementOfList(X,[X]).
lastElementOfList(X,[_|Z]) :- lastElementOfList(X, Z).

% removing last element of list
removeLastElemOfList([],[]) :- !, fail.
removeLastElemOfList([_],[]) :- !.
removeLastElemOfList([X | T],[X | T1]) :- removeLastElemOfList(T,T1).

% Various operations performed among elements in list and then equating it to last element of list 
isSatisfying(L,OL,VAL) :-
   operatedList(L,OL),   
   OL =:= VAL, !.               

% splitting the list in all possible ways and performing arithmetic operations among the elements of list 
operatedList([S],S).                    
operatedList(L,FINAL) :-                  
   splitList(L,LEFTL,RIGHTL),              
   operatedList(LEFTL,LEFTOL),               
   operatedList(RIGHTL,RIGHTOL),                 
   operationsOnList(LEFTOL,RIGHTOL,FINAL).            

% performing basic arithmetic operations on elements of list
operationsOnList(LEFTOL,RIGHTOL,LEFTOL+RIGHTOL).
operationsOnList(LEFTOL,RIGHTOL,LEFTOL-RIGHTOL).
operationsOnList(LEFTOL,RIGHTOL,LEFTOL*RIGHTOL).
operationsOnList(LEFTOL,RIGHTOL,LEFTOL/RIGHTOL) :- RIGHTOL =\= 0.  % making sure denominator is not zero

% splitting list into left and right parts
splitList(L,L1,R1) :- append(L1,R1,L), L1 = [_|_], R1 = [_|_].

% loop through all n lists and checking if its possible to perform arithmetic operations of first n-1 elements to obtain last element of list 
loop(ITER, END) :-
   ITER > END;
   read(LIST),
   lastElementOfList(LAST,LIST),
   removeLastElemOfList(LIST,NEW_LIST),
   (isSatisfying(NEW_LIST, OL,LAST) -> writef('%w=%w\n',[OL,LAST]);
   write('IMPOSSIBLE'),nl),
   ITER1 is ITER + 1,
   loop(ITER1,END).

% reading input file and looping through all n lists
main :-
   see('input.txt'),
   read(LEN),
   loop(1,LEN),
   seen.