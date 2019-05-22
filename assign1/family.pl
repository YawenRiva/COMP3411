parent(xinuan, xiaoli).
parent(dijun, xiaoli).
parent(yuqing, yawen).
parent(xiaoli, yawen).
parent(fanwen, yuqing).
parent(jinbi, yawen).
parent(fanwen, yuhong).
parent(jinbi,yuhong).

female(dijun).
female(yuqing).
female(yuhong).
female(jinbi).
female(yawen).
male(fanwen).
male(xiaoli).
male(xinuan).

% first cases = they have the same parent
same_name(Person1,Person2):-
    parent(Parent1, Person1),
    parent(Parent2, Person2),
    Parent1 = Parent2.
same_name(Person1,Person2):-
    male(Person1),
    descendant(Person1,Person2).
same_name(Person1,Person2):-
    male(Person2),
    descendant(Person2,Person1).

% person1 is person2s descendant
% person2 is person1s descendant
% ONLY parent-side is MALE then the kid can have the same name

descendant(Person1,Person2):-
    male(Person1),
    parent(Person1, Person2).
descendant(Person1, Person2):-
    parent(Person1, CHILD),
    descendant(CHILD, Person2).

