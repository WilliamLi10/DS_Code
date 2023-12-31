/*
A Node class is required (see the provided one in Rope.h), must have 
  weight, value, left, and right members.
  You can add other members.
The Rope class must have a constructor that takes a Node* 
  and uses that Node* as a root.
The Rope class must also have a function, expose_root() to return a pointer to the root Node.
  (This is poor class design, but will be necessary for us to autograde your data structure.)
*/

#include <cassert>
#include <string>
#include "Rope.h"

void StudentTests();
bool SAME(const Rope& r, const std::string& s);
bool ValidRope(Node* root);
int countWeights(Node* root);
void BasicTests();
Node* IndexTestRope();
Node* ConcatTestRopeLeft();
Node* ConcatTestRopeRight();
void Test1();
void Test2();
void Test3();

int main(){
	BasicTests();
	std::cout << "***Basic tests passed." << std::endl;
	StudentTests();
	std::cout << "***Student tests passed." << std::endl;
	return 0;
}

void StudentTests(){
	Test1();
	Test2();
	Test3();
}

//Used to compare a string and a rope that should be the same.
//You can uncomment the .report assert to test report on the whole string
bool SAME(const Rope& r, const std::string& s){
	/*std::cout << "Comparing string \"" << s << "\" to Rope:" << std::endl;
	r.print(std::cout);*/
	assert(r.size() == (int)s.length() && "ERROR: ROPE SIZE DOES NOT MATCH STRING SIZE");
	char c;
	for(unsigned int i=0; i<s.size(); i++){
	
		//std::cout << i << std::endl;
		assert(r.index(i,c) && c == s[i] && "MISMATCH BETWEEN A CHARACTER IN ROPE AND STRING USING INDEX");
	}
	/*
	std::string s2;
	assert(r.report(0,s.length()-1,s2) && s2 == s && "MISMATCH BETWEEN ROPE.REPORT(0,length-1) AND STRING");
	*/
	return true;
}

//Function to check that the weights and structure from a root form a valid Rope.
bool ValidRope(Node* root){
	int left_sub = 0;

	if(!root){
		return true;
	}

	//Check that weight is correct as a leafe
	if(!root->left && !root->right){
		return root->weight == (int)root->value.length();
	}

	//Check that I'm at least one of the children of my parent.
	if(root->parent && (root->parent->left != root) && (root->parent->right != root)){
		return false;
	}

	//Check my weight if I'm not a leaf
	if(root->left){
		/* ON SUBMITTY, THE INSTRUCTOR VERSION OF THE CODE
		 * IMPLEMENTS countWeights(). IF YOU ALSO WANT TO
		 * USE THIS CODE YOU WILL NEED TO IMPLEMENT countWeights().
		 * YOU MAY FIND USING assert() STATEMENTS OR PRINTING SPECIFIC
		 * ERRORS HELPFUL FOR DEBUGGING.
		 */
		left_sub = countWeights(root->left);
	}

	return (root->weight == left_sub) && ValidRope(root->left) && ValidRope(root->right);
}

int countWeights(Node* root){
	/* ON SUBMITTY, THE INSTRUCTOR VERSION OF THE CODE
	 * IMPLEMENTS countWeights(). YOU DO NOT NEED TO MAKE
	 * YOUR IMPLEMENTATION TO RECEIVE FULL CREDIT.
	 * YOU MAY WANT TO IMPLEMENT THIS FUNCTION SO THAT YOU CAN
	 * USE ValidRope() IN YOUR OWN TESTING.
	 */

	// Remove this assert if you actually implement countWeights()
	assert(0 && "countWeights() HAS NOT BEEN IMPLEMENTED");
}

void BasicTests(){
	Rope r1(IndexTestRope());
	std::string s1 = "Hello my name is Simon";
	std::string rs1;

	r1.print(std::cout);
	r1.print_strings(std::cout);
	assert(SAME(r1, s1));
	std::cout << "***Index test passed." << std::endl;
	assert(r1.report(0, s1.length() - 1, rs1) && rs1 == s1);
	std::cout << "***Basic report test passed." << std::endl;

	//Concat test
	Rope r2(ConcatTestRopeLeft());
	Rope r3(ConcatTestRopeRight());
	std::string s2 = "Hello my ";
	std::string s3 = "name i";

	assert(SAME(r2, s2));
	assert(SAME(r3, s3));
	std::cout << "***More index tests passed." << std::endl;

	r2.concat(r3);
	s2 += s3;
	assert(SAME(r2, s2));
	std::cout << "***Concatenation test passed" << std::endl;

	//Split test
	Rope r4(IndexTestRope()); //Wikipedia split @ 11
	std::string s4 = "Hello my name is Simon";
	Rope r5;
	std::string s5 = s4.substr(0, 11);
	std::string s6 = s4.substr(11, 11);
	r4.split(11, r5);
	r4.print_strings(std::cout);
	r5.print_strings(std::cout);
	assert(SAME(r4, s5));
	assert(SAME(r5, s6));
	std::cout << "***Split test passed" << std::endl;
	r4.print(std::cout);
	//Copy & Assignment tests
	Rope r9(IndexTestRope());
	Rope r10(r9);
	std::string rs2;
	assert(r10.expose_root() != r9.expose_root());
	assert(r10.size() == r9.size());
	assert(r10.report(0, r10.size() - 1, rs1) && r9.report(0, r9.size() - 1, rs2) && rs1 == rs2);
	std::cout << "***Copy test passed" << std::endl;
	Rope r11;
	r11 = r9;
	assert(r11.expose_root() != r9.expose_root());
	assert(r11.size() == r9.size());
	assert(r11.report(0, r11.size() - 1, rs1) && r9.report(0, r9.size() - 1, rs2) && rs1 == rs2);
	std::cout << "***Assignment test passed" << std::endl;
}

//Also used for split() test
Node* IndexTestRope(){
	Node* ret = new Node;
	ret->weight = 22;
	ret->left = new Node;
	ret->left->parent = ret;
	ret->left->weight = 9;
	ret->left->left = new Node;
	ret->left->left->parent = ret->left;
	ret->left->left->weight = 6;
	ret->left->right = new Node;
	ret->left->right->parent =	ret->left;
	ret->left->right->weight = 6;
	ret->left->left->left = new Node;
	ret->left->left->left->parent = ret->left->left;
	ret->left->left->left->weight = 6;
	ret->left->left->left->value = "Hello ";
	ret->left->left->right = new Node;
	ret->left->left->right->parent = ret->left->left;
	ret->left->left->right->weight = 3;
	ret->left->left->right->value = "my ";
	ret->left->right->left = new Node;
	ret->left->right->left->parent = ret->left->right;
	ret->left->right->left->weight = 2;
	ret->left->right->right = new Node;
	ret->left->right->right->parent = ret->left->right;
	ret->left->right->right->weight = 1;
	ret->left->right->left->left = new Node;
	ret->left->right->left->right = new Node;
	ret->left->right->left->left->parent = ret->left->right->left;
	ret->left->right->left->left->weight = 2;
	ret->left->right->left->left->value = "na";
	ret->left->right->left->right->parent = ret->left->right->left;
	ret->left->right->left->right->weight = 4;
	ret->left->right->left->right->value = "me i";
	ret->left->right->right->left = new Node;
	ret->left->right->right->left->parent = ret->left->right->right;
	ret->left->right->right->left->weight = 1;
	ret->left->right->right->left->value = "s";
	ret->left->right->right->right = new Node;
	ret->left->right->right->right->parent = ret->left->right->right;
	ret->left->right->right->right->weight = 6;
	ret->left->right->right->right->value = " Simon";
	return ret;
}

Node* ConcatTestRopeLeft(){
	Node* ret = new Node;
	ret->weight = 6;
	ret->left = new Node;
	ret->right = new Node;
	ret->left->parent = ret;
	ret->left->weight = 6;
	ret->left->value = "Hello ";
	ret->right->parent = ret;
	ret->right->weight = 3;
	ret->right->value = "my ";
	return ret;
}

Node* ConcatTestRopeRight(){
	Node* ret = new Node;
	ret->weight = 2;
	ret->left = new Node;
	ret->right = new Node;
	ret->left->parent = ret;
	ret->left->weight = 2;
	ret->left->value = "na";
	ret->right->parent = ret;
	ret->right->weight = 4;
	ret->right->value = "me i";
	return ret;
}
//More in depth test for split
void Test1()
{
	for (int i = 0; i < 22; ++i) {
		//std::cout << i << std::endl;
		Rope r4(IndexTestRope()); //Wikipedia split @ 11
		std::string s4 = "Hello my name is Simon";
		Rope r5;
		std::string s5 = s4.substr(0, i);
		std::string s6 = s4.substr(i);
		r4.split(i, r5);
		//r4.print(std::cout);
		assert(SAME(r4, s5));
		//std::cout << "Assert 1 done" << std::endl;
		assert(SAME(r5, s6));
		//std::cout << "Assert 2 done" << std::endl;
	}
	std::cout << "Test 1 passed" << std::endl;
}
//Test 2 and 3 are used to test all functions to make sure they work by splitting and concatting multiple times.
void Test2()
{
	Rope R1(IndexTestRope());
	std::string s4 = "Hello my name is Simon";
	Rope R2;
	R1.split(11, R2);
	Rope R3(R1);
	R3.concat(R2);
	assert(SAME(R3, s4));
	std::cout << "Test 2 passed" << std::endl;

}

void Test3()
{
	Rope R1(IndexTestRope());
	Rope R2(ConcatTestRopeLeft());
	Rope R3;
	R1.split(R2.size(),R3);
	Rope R4(ConcatTestRopeRight());
	Rope R5;
	R3.split(R4.size(), R5);
	std::string s2 = "Hello my ";
	std::string s3 = "name i";
	assert(SAME(R1, s2));
	assert(SAME(R3, s3));
	std::cout << "Test 3 passed" << std::endl;
}