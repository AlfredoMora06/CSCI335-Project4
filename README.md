# CSCI335-Project4
Sorting Algorithms

In this	assignment we compared various sorting algorithms. 
We also modified the algorithms in order for a Comparator class
to be used for comparisons.


You can compile everything by typing 

make clean
make all

----------------------------------------------------------------------------------
(i). All parts of the assignment were executed
	PART(1).
	Write a small function that verifies that a collection is in sorted order.
	Write a	function that should return true if the input is in sorted order 
	according to the Comparator.
	Modify the code of heapsort, quicksort and mergesort, such that a Comparator
	is used.
	PART(2).
	Test some variations of the quicksort algorithm. Median of three, 
	middle pivot (always select the middle item in the array), and
	first pivot (always select the first item in the array).


(ii). There are no known bugs in the program. 
	However, due to differences in computer architecture,
	different machines will run the sorts in different times. 
	Though, quick sort and median3 will always be the fastest.

(iii). To run the following program:
	PART(1).
	Created	a driver program that will be executed as follows:
	./test_sorting_algorithms   <input_type>   <input_size>   <comparison_type>,
	where	<input_type> can be random or sorted, <input_size> is the number of
	elements of the input, and <comparison_type> is either less or greater.

	For example, you can run
	./test_sorting_algorithms   random   20000   less
	The above will produce a random	vector of 20000 integers, and apply
	all three algorithms using the less<int>{} Comparator.

	You can also run
	./test_sorting_algorithms   sorted   10000   greater
	The above will produce the vector of integers containing 1 through 10000 in that
	order, and will	test the three algorithms using the greater<int>{} Comparator.
	
	PART(2).
	The executable should run using the same parameters as in Part 1:
	./test_qsort_algorithm   <input_type>   <input_size>   <comparison_type>


(iii). Does not require any input files
