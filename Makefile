all: avl bst

bst: bst.cpp
	g++ -o bst bst.cpp

avl: avl.cpp
	g++ -o avl avl.cpp