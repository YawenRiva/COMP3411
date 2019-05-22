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
