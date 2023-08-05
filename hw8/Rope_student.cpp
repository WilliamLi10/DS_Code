/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "Rope.h"
#include<iostream>

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves

//taken from ds set class
rope_iterator& rope_iterator::operator++(){
	
	if (ptr_->right != NULL) { // find the leftmost child of the right node
		ptr_ = ptr_->right;
		while (ptr_->left != NULL) { ptr_ = ptr_->left; }
	}
	else { // go upwards along right branches...  stop after the first left
		while (ptr_->parent != NULL && ptr_->parent->right == ptr_) { ptr_ = ptr_->parent; }
		ptr_ = ptr_->parent;
	}
	//std::cout << this->ptr_->weight << " " << this->ptr_->value << std::endl;
	return *this;
}

//Point to the first Node for in-order traversal most left node.
rope_iterator Rope::begin() const{
	Node* tmp = root;
	while (tmp->left)
	{
		tmp = tmp->left;
	}
	return tmp;
}

//default constructor creates empty rope.
Rope::Rope()
	:size_(0), root(nullptr) {}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
	root = p;
	size_ = p->weight;
	while (p->right)
	{
		p = p->right;
		size_ += p->weight;
	}

}
//destructor
Rope::~Rope(){
	this->destroy_rope(root);
}
//copy constructor
Rope::Rope(const Rope& r){
	root = copy_rope(r.root);
	size_ = r.size_;
}
//assignment operator
Rope& Rope::operator= (const Rope& r){
	if (this != &r)
	{
		this->destroy_rope(root);
		root = copy_rope(r.root);
		size_ = r.size_;
	}
	return *this;
}

//MUST BE ITERATIVE
//Get a single character at index i
/*if the node is not an index, it will go left or right based on the current i value
and the weight of the node. It will subtract the weight of the node from i if i >= weight. At the end, it will
set c to the value of the ith char in the string.*/
bool Rope::index(int i, char& c) const{
	Node* tmp = root;
	while (!is_leaf(tmp))
	{
		if (i >= tmp->weight)
		{
			i -= tmp->weight;
			tmp = tmp->right;
		}
		else
		{
			tmp = tmp->left;
		}
	}
	c = tmp->value[i];
	return true;
}

//Add the other rope (r)'s string to the end of my string
/*copies the rope that is passed in. Creates a new node for the root, and then sets the pointers accordingly.*/
void Rope::concat(const Rope& r){
	Node* right = copy_rope(r.root);
	Node* tmp = new Node;
	tmp->left = root;
	tmp->right = right;
	tmp->weight = size_;
	root = tmp;
	root->left->parent = root;
	root->right->parent = root;
	size_ += r.size_;
	

}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{
	if (i >= size_)
		return false;
	s = "";
	for (; i != j + 1; ++i)
	{
		char c;
		this->index(i, c);
		s += c;
	}
	return true;
}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
//calls recursive function to do all the work, and then sets size. Returns reference to itself.
Rope& Rope::split(int i, Rope& rhs){
	if (i >= size_ )
		return *this;
	
	split_this(i, rhs, root);
	 this->size_ = i;
	 root->weight = 0;
	 for (rope_iterator it = begin(); it != end(); it++) {
		 if (is_leaf(it.ptr_))
		 {
			 root->weight += it.ptr_->weight;
		 }
	 }
	 return *this;
}

/*destructor helper function. it will recurse until it reaches a nullptr, and then go up deleting each node it visits.
once done with left, it will go to right.*/
void Rope::destroy_rope(Node*& ptr)
{
	if (ptr == nullptr)
	{
		return;
	}
	else
	{
		destroy_rope(ptr->left);
		destroy_rope(ptr->right);
		delete ptr;
	}
}
/*if pointer is null, it will return. Otherwise, it will create a new node and copy the contents from ptr
to the new node. it will then recurse left and then right setting pointers accordingly.*/
Node* Rope::copy_rope(Node* ptr)
{
	if (ptr == nullptr)
	{
		return NULL;
	}
	else
	{
		Node* tmp = new Node;
		//std::cout << ptr->weight << std::endl;
		tmp->weight = ptr->weight;
		tmp->value = ptr->value;
		tmp->left = copy_rope(ptr->left);
		if(tmp->left)
			tmp->left->parent = tmp;
		tmp->right = copy_rope(ptr->right);
		if(tmp->right)
			tmp->right->parent = tmp;
		return tmp;
	}
}
/*recursive function to split tree. If it is not a leaf, it will traverse down the tree similra to index function.
If it is a leaf, it will split the node into two if needed, otherwise it will create a new root for the new
tree, and adjust pointers accordingly. When going back up the tree, it will call splittable predicate on each visited node
and if it is true, it will concat the right subtree with the new rope.*/
void Rope::split_this(int i, Rope& rhs, Node* ptr)
{
	if (!is_leaf(ptr))
	{
		if (ptr->weight - 1 < i)
		{
			split_this(i - ptr->weight, rhs, ptr->right);
		}
		else
		{
			split_this(i, rhs, ptr->left);
		}
		if (splittable(ptr))
		{
			ptr->weight -= rhs.root->left->weight;
			Node* tmp = ptr->right;
			ptr->right = NULL;
			split_concat(rhs, tmp);
			//std::cout << rhs.size_ << std::endl;
		}
	}
	else
	{
		if (i == 0)
		{
			rhs.root = new Node;
			rhs.root->left = ptr;
			rhs.root->weight = ptr->weight;
			if (ptr->parent->left == ptr)
				ptr->parent->left = NULL;
			else
				ptr->parent->right = NULL;
			rhs.size_ += rhs.root->weight;
			ptr->parent = rhs.root;
		}
		else
		{
			Node* LeftNode = new Node;
			Node* RightNode = new Node;
			for (int j = 0; j != i; ++j)
			{
				LeftNode->value += ptr->value[j];
				LeftNode->weight++;
			}
			for (int j = i; j != ptr->value.size(); ++j)
			{
				RightNode->value += ptr->value[j];
				RightNode->weight++;
			}
			ptr->weight = LeftNode->weight;
			//LeftNode->parent = ptr;
			ptr->value = "";
			ptr->left = LeftNode;
			rhs.root = new Node;
			rhs.root->left = RightNode;
			rhs.root->weight = RightNode->weight;
			RightNode->parent = rhs.root;
			rhs.size_ += RightNode->weight;
		}
	}
}
//goes down the right till it either hits a leaf with a useful value or reaches null.
//if it is null, return false. if it s a useful leaf, return true.
bool Rope::splittable(Node* ptr)
{
	if (!ptr)
		return false;
	else if (is_leaf(ptr) && ptr->value != "")
		return true;
	else
		return splittable(ptr->right);
}
//similar to concat except it doesnt make a copy. Also checks to see if the right of the current root
//is null so extra nodes don't need to be created.
void Rope::split_concat(Rope& rhs, Node* right)
{
	if (rhs.root->right == NULL)
	{
		rhs.root->right = right;
	}
	else
	{
		Node* tmp = new Node;
		tmp->left = rhs.root;
		tmp->right = right;
		tmp->weight = rhs.size_;
		rhs.root = tmp;
	}
	rhs.root->right->parent = rhs.root;
	rhs.root->left->parent = rhs.root;
	Node* tmp2 = right;
	while (tmp2)
	{
		rhs.size_ += tmp2->weight;
		tmp2 = tmp2->right;
	}
}