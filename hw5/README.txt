HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  < William Li>


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Noah Mack  / https://stackoverflow.com/questions/879603/remove-an-array-element-and-shift-the-remaining-ones >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 12 >



TESTING & DEBUGGING STRATEGY:
I commented out almost everything in basic tests and slowly uncommented 
them as I implemented each of the functions. I would then use this to test 
as I created each of the new needed functions. If I had errors, I would put in std::cout statements
to find out what the error exactly was.



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 
pop_front:
O(1) if there was a node that needed to be removed. otherwise, 
it is O(n) where n is the number of elements inside the node - 1

pop_back
O(1) in all cases

push_front
if a new head node needed to be added, it is O(1). If not, it is O(n)
where n is the number of elements in the node - 1
push_back
O(1) in all cases

insert
O(n) in all cases where n is the number of elements in the node
erase
O(1) if there is a node that needs to be erased
O(n) otherwise where n is the number of elements in the node 


EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  


Yes!


