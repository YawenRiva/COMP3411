
% when the list is empty
sign_runs([],[]).

% when the list only contains one number
sign_runs([HEAD],[[HEAD]]).

% positive+positive
sign_runs([HEAD|TAIL],[[HEAD|NEWTAIL]|LIST]):-
    sign_runs(TAIL,[NEWTAIL|LIST]),
    NEWTAIL = [NEWHEAD|_],
    HEAD>=0,
    NEWHEAD>=0.
% negative+negative
sign_runs([HEAD|TAIL],[[HEAD|NEWTAIL]|LIST]):-
    sign_runs(TAIL,[NEWTAIL|LIST]),
    NEWTAIL = [NEWHEAD|_],
    HEAD<0,
    NEWHEAD<0.
    
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


