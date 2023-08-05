HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME:  < William Li >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Oscar Li Terry Lin/ None >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 420 >



COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.

------------------------------------------------------------------------------
|          |          | remove   |          | closest  | first f  | longest  |
|          | sort     | dups     | mode     | pair     | sorted   | substr   | 
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| vector   | nlogn    |     n^2  | nlogn    |   nlogn  | nlogn    |l^2*n^2   |
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| list     |   nlogn  |    n^2   |nlogn     | nlogn    | nlogn    | l^2*n^2  |
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| bst      | nlogn    |  nlogn   |   nlogn  |   nlogn  |nlogn     | n*l^2log(n*l^2)|
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| pq       |    nlogn |    x     |  nlogn   | nlogn    |n+flogn   |     x    |
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| hash     |   x      |  n       | n        |  x       |   x      |    n^2*l^2 |
------------------------------------------------------------------------------



RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.

< insert your performance measurements and coefficient estimates >
Vector:
	sort: 0.125  coefficient:7.25 E-8
	remove dups: 70.53   coefficient:7.053E-9
	closest pair: 0.134 coefficient: 6.89 E-8
	mode: .11    coefficient:6.6E-8
	first f sorted: 0.06    coefficient:3.61E-8
	longest substr: 3.67     coefficient:9.17E-7
List:
	sort: 0.1875  coefficient:  1.13E-7
	remove dups: 167.12  coefficient: 1.67E-8
	closest pair: 0.2003 coefficient: 2.34E-7
	mode: 0.2   coefficient: 1.2 E -7
	first f sorted: 0.14   coefficient: 1.14 E-7
	longest substr: 7.09	coefficient:1.77E-6
BST:
	sort: 0.28   coefficient: 1.68E-7
	remove dups: 0.984   coefficient: 5.9E-7
	closest pair: 0.301      coefficient:  8.2E-7
	mode: 0.26     coefficient: 1.56E-7
	first f sorted: 0.18 coefficient:1.08E-7
	longest substr:7.17  coefficient:1.8E-6
Hash Table:
	remove_dups: 0.828  coefficient: 8.28E-6
	mode: 0.14         coefficient: 1.4E-6
	longest substr:7.125     coefficent: 1.8E-6       

Priority Queue:
	Sort: 0.23475 coefficient:1.4E-7
	closest_pair: 0.14 coefficient: 8.42E-8
	first f sorted: 0.0468  coefficient:1.3E-7
	Mode: 0.1875     coefficient: 1.5E-7



DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words.  


< The results were in line with my original Big O notation. I did not have to alter any of my
original predictions from the chart. The results do show that although many operations for some of the data structures
have similar runtimes, some do run faster than others. I think this is due to the intricacies related to each of the data
structures, and I will be using this data moving forward to decide which data structure to use when dealing with a certain task. 
Although the time difference right now isn't extremely significant. I'm sure the difference
will become much more noticeable with even larger data sets than what I tested with
right now. For every function except longest substring and remove duplicates
, files with 100000 entries were used. For longest substring and remove duplicates, 2000 entries were used. After testing,
I've determined that a vector would be best for most of these operations except remove duplicates which would be best given to
either a hashtable or bst.>



MISC. COMMENTS TO GRADER:  
Optional, please be concise!
