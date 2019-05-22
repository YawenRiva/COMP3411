% first possibility is empty list
sqrt_list([], []).

% if its not empty
% list to store the number and its squareroot value
% out list to store the sqrtlist for the numbers
sqrt_list([HEAD|TAIL], [[HEAD,RESULT]|LIST]):-
    sqrt_list(TAIL,LIST),
    RESULT is sqrt(HEAD).
