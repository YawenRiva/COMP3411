% YAWEN LUO
% Z5134924
% COMP3411
% ASSIGNMENT1 - PROLOG PROGRAMMING




% QUESTION1 - SUM THE SQUARE OF EVEN NUMBERS
% 3-5-2019

% if the list is empty then the result should be zero
sumsq_even([],0).

% if the head is not even the discard/ignore it
% check the tail(rest of the list)
sumsq_even([HEAD|TAIL], SUM):-
    1 is mod(HEAD,2),
    sumsq_even(TAIL,SUM).

% if the head is even
% keep calculate the tail, get the result for the tail
% sum equals to tails sum plus the square of the current head
sumsq_even([HEAD|TAIL],SUM):-
    0 is mod(HEAD,2),
    sumsq_even(TAIL,TAIL_SUM),
    SUM is TAIL_SUM + HEAD*HEAD. 





% QUESTION2 - SAME FAMILY NAME
% 3-5-2019

% first cases = they have the same parent
same_name(Person1,Person2):-
    parent(Parent1, Person1),
    parent(Parent2, Person2),
    Parent1 = Parent2.
same_name(Person1,Person2):-
    descendant(Person1,Person2).
same_name(Person1,Person2):-
    descendant(Person2,Person1).

% second cases = person1 is person2s descendants

descendant(Person1,Person2):-
    male(Person1),
    parent(Person1, Person2).
descendant(Person1, Person2):-
    parent(Person1, CHILD),
    descendant(CHILD, Person2).



% QUESTION3 - PRINTOUT SQUAREROOT
% 3-6-2019
% first possibility is empty list
sqrt_list([], []).

% if its not empty
sqrt_list([HEAD|TAIL], [[HEAD,RESULT]|LIST]):-
    sqrt_list(TAIL,LIST),
    RESULT is sqrt(HEAD).




% QUESTION4 - SIGN RUNS, NEGATIVE/NON NEGATIVE NUMBERS
% 3-14-2019
% when the list is empty
sign_runs([],[]).
% when the list only contains one number
sign_runs([HEAD],[[HEAD]]).
% positive+positive
sign_runs([HEAD|TAIL],[[HEAD|NEWTAIL]|LIST]):-
    sign_runs(TAIL,[NEWTAIL|LIST]),
    NEWTAIL = [NEWHEAD|_],
    HEAD >= 0,
    NEWHEAD >= 0.
% negative+negative
sign_runs([HEAD|TAIL],[[HEAD|NEWTAIL]|LIST]):-
    sign_runs(TAIL,[NEWTAIL|LIST]),
    NEWTAIL = [NEWHEAD|_],
    HEAD < 0,
    NEWHEAD < 0.   
% positive+negative then new list formed
sign_runs([HEAD|TAIL],[[HEAD]|LIST]):-
    sign_runs(TAIL,LIST),
    LIST = [[NEWHEAD|_]|_],
    HEAD >= 0,
    NEWHEAD < 0. 
% negative+positive then new list formed
sign_runs([HEAD|TAIL],[[HEAD]|LIST]):-
    sign_runs(TAIL,LIST),
    LIST = [[NEWHEAD|_]|_],
    HEAD < 0,
    NEWHEAD >= 0. 


    
    
    
    
    
% QUESTION5 - TREE
% 3-14-2019
% tree contains left mid(number) and right there are few possibilities
% first-its an empty tree
is_heap(tree(empty,_,empty)).
% right side is empty
is_heap(tree(LEFT,DATA,empty)) :-
    % the data of the left child need to be greater than the root data
    LEFT = tree(_, LeftData, _),
    LeftData >= DATA,
    is_heap(LEFT). 
% left side is empty
is_heap(tree(empty, DATA, RIGHT)):-
    RIGHT = tree(_, RightData, _),
    RightData >= DATA,
    is_heap(RIGHT).
% both side not empty
is_heap(tree(LEFT, DATA, RIGHT)):-
    LEFT = tree(_, LeftData, _),
    LeftData >= DATA,
    RIGHT = tree(_, RightData, _),
    RightData >= DATA,
    is_heap(LEFT),
    is_heap(RIGHT). 
