
% remove_dups(LIST, NEWLIST)

% if the list is empty then the newlist should be empty as well
remove_dups([],[]).

% if the 1st element is a member of the tail then remove it
remove_dups([HEAD|TAIL], NEWREST):-
    member(HEAD, TAIL),
    remove_dups(TAIL, NEWLIST).

% if the 1st element is not a member of the tail
% then keep the head and check the rest
remove_dups([HEAD|TAIL],[HEAD|NEWREST]):-
    not(member(HEAD, TAIL)),
    % the head keeps being head in the newlist
    remove_dups(TAIL, NEWREST).
    