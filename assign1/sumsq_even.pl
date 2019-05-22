
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

