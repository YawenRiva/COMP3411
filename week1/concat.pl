% concat(LIST1, LIST2, CONCAT_LIST1_LIST2)
% CONCAT_LIST1_LIST2 is the concatenation of list1 and list2

concat([], List2, List2).

concat([HEAD | TAIL], LIST2, [HEAD | CONCAT_TAIL_LIST2]):-
    concat(TAIL, LIST2, CONCAT_TAIL_LIST2).