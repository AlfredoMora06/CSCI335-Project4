// Homework 4
// Testing Sorting Algorithms
// Alfredo Morales
/*
 * For this part we wrote a small function that verifies that a collection is in sorted order.
 * We also wrote a function that should return true if the input is in sorted order according to the Comparator.
 * Finally, we modified the code of heapsort, quicksort and mergesort, such that a Comparator is used.
*/

#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

namespace {
// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector) {
  vector<int> a;
  for (size_t i = 0; i < size_of_vector; ++i)
    a.push_back(rand());
  return a;
}

// Verifies the order of the vector to make sure it is sorted.
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) {
	for (unsigned int i = 1; i < input.size(); i++) {
		if (!less_than(input[i], input[i-1])){}		//a <= b can be implemented as NOT less_than(b, a)
		else{
			return false;
			}
	}
	return true;
}


/*****************************************************************************************/

/****************************   METHODS FOR QUICK SORT    ********************************/

/*****************************************************************************************/

/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 * This and the following methods are from the book.
 */
template <typename Comparable, typename Comparator>
const Comparable& median3(vector<Comparable>& a, int left, int right, Comparator less_than)
{
	int center = (left + right) / 2;

	if (less_than(a[center], a[left]))
		std::swap(a[left], a[center]);

	if (less_than(a[right], a[left]))
		std::swap(a[left], a[right]);

	if (less_than(a[right], a[center]))
		std::swap(a[center], a[right]);

	// Place pivot at position right - 1
	std::swap(a[center], a[right - 1]);
	return a[right - 1];
}

/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void insertionSort(vector<Comparable>& a, int left, int right, Comparator less_than)
{
	for (int p = left + 1; p <= right; ++p)
	{
		Comparable tmp = std::move(a[p]);
		int j;

		for (j = p; j > left && less_than(tmp, a[j - 1]); --j)
			a[j] = std::move(a[j - 1]);
		a[j] = std::move(tmp);
	}
}


// Signature for quicksort (heapsort / mergesort similar signatures)
template <typename Comparable, typename Comparator>
void quickSort(vector<Comparable>& a, int left, int right, Comparator less_than) {

	if( left + 10 <= right )
	{
		const Comparable & pivot = median3( a, left, right, less_than );

			// Begin partitioning
		int i = left, j = right - 1;
		for( ; ; )
		{
			while(less_than(a[++i], pivot)) { }
			while (less_than(pivot, a[--j])) {}
			if (i < j)
				std::swap(a[i], a[j]);
			else
				break;
		}

		std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot

		quickSort( a, left, i - 1, less_than );     // Sort small elements
		quickSort( a, i + 1, right, less_than );    // Sort large elements
	}
	else  // Do an insertion sort on the subarray
		insertionSort( a, left, right, less_than );

}


// The following will be the driver for quickSort 
template <typename Comparable, typename Comparator>
void quickSort(vector<Comparable>& a, Comparator less_than)
{
	quickSort(a, 0, a.size() - 1, less_than);
}


/*****************************************************************************************/

/****************************   METHODS FOR HEAP SORT     ********************************/

/*****************************************************************************************/

/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild(int i)
{
	return 2 * i + 1;
}


/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
template <typename Comparable, typename Comparator>
void percDown(vector<Comparable>& a, int i, int n, Comparator less_than)
{
	int child;
	Comparable tmp;

	for (tmp = std::move(a[i]); leftChild(i) < n; i = child)
	{
		child = leftChild(i);
		if (child != n - 1 && less_than(a[child], a[child + 1]))
		++child;
		if (less_than(tmp, a[child]))
			a[i] = std::move(a[child]);
		else
			break;
	}
	a[i] = std::move(tmp);
}


/**
 * Standard heapsort.
 */
template <typename Comparable, typename Comparator>
void heapsort(vector<Comparable>& a, Comparator less_than)
{
	for (int i = a.size() / 2 - 1; i >= 0; --i) /* buildHeap */
	{
		percDown(a, i, a.size(), less_than);
	}	//End of first for loop
	for (int j = a.size() - 1; j > 0; --j)
	{
		std::swap(a[0], a[j]);               /* deleteMax */
		percDown(a, 0, j, less_than);
	}	//End of second for loop

}	//End of heapsort


/*****************************************************************************************/

/****************************   METHODS FOR MERGE SORT    ********************************/

/*****************************************************************************************/

/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void merge(vector<Comparable>& a, vector<Comparable>& tmpArray, int leftPos, int rightPos, int rightEnd, Comparator less_than)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;

	// Main loop
	while (leftPos <= leftEnd && rightPos <= rightEnd)
		if (!less_than(a[rightPos],a[leftPos]))
			tmpArray[tmpPos++] = std::move(a[leftPos++]);
		else
			tmpArray[tmpPos++] = std::move(a[rightPos++]);

	while (leftPos <= leftEnd)    // Copy rest of first half
		tmpArray[tmpPos++] = std::move(a[leftPos++]);

	while (rightPos <= rightEnd)  // Copy rest of right half
		tmpArray[tmpPos++] = std::move(a[rightPos++]);

	// Copy tmpArray back
	for (int i = 0; i < numElements; ++i, --rightEnd)
		a[rightEnd] = std::move(tmpArray[rightEnd]);
}

/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void mergeSort(vector<Comparable>& a, vector<Comparable>& tmpArray, int left, int right, Comparator less_than)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort(a, tmpArray, left, center, less_than);
		mergeSort(a, tmpArray, center + 1, right,less_than);
		merge(a, tmpArray, left, center + 1, right, less_than);
	}
}

/**
 * // The following will be the driver for mergeSort 
 */
template <typename Comparable, typename Comparator>
void mergeSort(vector<Comparable>& a, Comparator less_than)
{
	vector<Comparable> tmpArray(a.size());

	mergeSort(a, tmpArray, 0, a.size() - 1, less_than);
}


/*****************************************************************************************/

/****************************          TEST TIMING        ********************************/

/*****************************************************************************************/

// Test function that shows how you can time a piece of code.

// I modified this function to take two params.
// And test all sorts at once.
template <typename Comparable, typename Comparator>
void TestTiming(vector<Comparable>& a, Comparator less_than) {
	const auto heapBegin = chrono::high_resolution_clock::now();
	// Time this piece of code.
	heapsort(a, less_than);											//	HEAP SORT CHECK
	// End of piece of code to time.
	const auto heapEnd = chrono::high_resolution_clock::now();
	cout << "Heapsort: Runtime: ";
	cout << chrono::duration_cast<chrono::nanoseconds>(heapEnd - heapBegin).count() << "ns" << endl;
	// cout << chrono::duration_cast<chrono::milliseconds>(heapEnd - heapBegin).count() << "ms" << endl;
	cout << "Verified: " << VerifyOrder(a, less_than) << endl;
	cout << endl;


	const auto mergeBegin = chrono::high_resolution_clock::now();
	// Time this piece of code.
	mergeSort(a, less_than);										//	MERGE SORT CHECK
	// End of piece of code to time.
	const auto mergeEnd = chrono::high_resolution_clock::now();
	cout << "MergeSort: Runtime: ";
	cout << chrono::duration_cast<chrono::nanoseconds>(mergeEnd - mergeBegin).count() << "ns" << endl;
	// cout << chrono::duration_cast<chrono::milliseconds>(mergeEnd - mergeBegin).count() << "ms" << endl;
	cout << "Verified: " << VerifyOrder(a, less_than) << endl;
	cout << endl;


	const auto quickBegin = chrono::high_resolution_clock::now();
	
	// Time this piece of code.
	quickSort(a, less_than);										//	QUICK SORT CHECK
	// End of piece of code to time.
	
	const auto quickEnd = chrono::high_resolution_clock::now();
	cout << "quickSort: Runtime: ";
	cout << chrono::duration_cast<chrono::nanoseconds>(quickEnd - quickBegin).count() << "ns" << endl;
	//  cout << chrono::duration_cast<chrono::milliseconds>(quickEnd - quickBegin).count() << "ms" << endl;
	cout << "Verified: " << VerifyOrder(a, less_than) << endl;


}


}  // namespace



int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
 

  cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers "  << comparison_type << endl << endl;
  vector<int> input_vector;

  if (input_type == "random") {
    input_vector = GenerateRandomVector(input_size);
  
  }else if (input_type == "sorted") {				// Generate sorted vector.
	  for (int i = 1; i <= input_size; i++) {
		  input_vector.push_back(i);
	  }
  
  }else{
	  cout << "Invlaid input type" << endl;
  }

  if (comparison_type == "greater") {				// Check comparison types, can only be greater or less than
	  TestTiming(input_vector, greater<int>{});
	  
  }else if (comparison_type == "less") {
	  TestTiming(input_vector, less<int>{});
  
  }else {
	  cout << "Invalid comparison_type" << endl;
  }
 
  return 0;
}
