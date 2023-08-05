HOMEWORK 8: ROPES


NAME:  <William Li >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< None / None >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 >

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Copy Constructor:
Balanced: will be O(p) because it needs to copy from the root to the leaf.
Unbalanced: Unbalanced tree could be where each node holds only one char, and the amount of different levels is equal to the size of the string. 
time complexity is O(n)
Construct from Node*:
Balanced: It will also be O(p) b/c it needs to go down to the rightmost leaf to calculate the size.
Unbalanced: Same thingas before, it will also be O(n) because it needs to go down to the rightmost node to 
calculate size.
Index:
Balanced: O(p) b/c it needs to traverse down from the root to the leaf.
Unbalanced. O(n) using the unbalanced tree definition from before, and worst case being the last index.
Report:
Balanced: O(m*p) b/c it needs to loop for m chars and calls index on each one.
Unbalanced: O(m*n) b/c longest path will be the size of the number of chars in the string.
iterator operator++:
Balanced: O(1) b/c it is just traversing to the next node in the sequence.
Unbalanced: O(1) b/c of the same reason as balanced.
Split:
Balanced: O(p^2) b/c it moves down the tree multiple times. First to find the node to split at, and then again to find out whether the node 
it is at should be disconnected from the original rope.
Unbalanced: O(n^2) same reasoning as balanced, however the amount of levels will be equal to the size of the string. 
Concat:
Time complexity of Concat is the same as teh copy constructor because it has to copy the right hand rope. Everything else
it does is in constant time.

TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?
Test 1 tests split on the index test but it tests it on every single index of the string. This would test for all corner cases as it 
tests every possibility for split to be used.
Test 2 splits a rope, and then concats it back, and then tests to see if it equals the original.
Test 3 splits the rope based on the size of the other rope, and then checks to see if it was done correctly. 

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

