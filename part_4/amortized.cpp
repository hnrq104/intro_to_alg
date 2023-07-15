#include <bits/stdc++.h>

/*
no notebook

17.4-1
in an open hash table we need a low load factor to garantee that we
make fast insertions. The amortized cost would be bound by a constant still
The insertion O(1) is not true in all occasions, it's usually true,
but it might happen that we need to probe many times before finally finding a suited spot



17.4-2

phi(T)= 2*T.num - T.size if a(t) >= 1/2
        T.size/2 - T.num if a(t) < 1/2

if T.num >= 1/2 in a deletion, no contraction will ocur

we have
if a(Ti) >= 1/2
c^ = 1 + (2*T.num - T.size) - (2*(T.num + 1) - T.size) = -1?

if a(Ti) < 1/2
then we must have a(Ti-1) = 1/2

we have c^ = 1 + (T.size/2 - T.num) - (2*(T.num + 1) - T.size)
t.num + 1 = t.size/2
we find c^ = 1 + T.size/2 - T.num
T.num is at most 1 less t.size/2
we find c^ <= 1 + 1 = 2 


17.4-3
its literally the same calculations
but the constants change

*/


/*chapter 17 problems
*/

/*17.3*/

/*can USE O(SIZE.X) OF MEMORY, this wont do then
struct node{
	int size;
	node* left;
	node* right;
};

void rotate_left(node* &root){
	node* l = root->right->left;
	root->right->left = root;
	root->right = l;
	root = root->right;
	return;
}

void rotate_right(node* &root){
	node* r = root->left->right;
	root->left->right = root;
	root->left = r;
	root = root->left;
	return;
}

int get_size(node* x){
	if(x == nullptr) return 0;
	x->size = get_size(x->left) + get_size(x->right);
	return x->size + 1;
}

void balance_alg(node* &x){
}
*/

/*the tree can be represented as an array
take in order traverse then make tree out of sequence*/

/*
b
search is of the form T(n) = T(alfa*n) + O(1)
as by the master theorem this is log(n) base 1/alfa
*/