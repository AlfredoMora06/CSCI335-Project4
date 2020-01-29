// Homework 4
// Testing	Quick Sort Algorithm 
// Alfredo Morales
/*
 * Test some variations of the quicksort algorithm. Median of three, 
 * middle pivot (always select the middle item in the array), and
 * first pivot (always select the first item in the array).
*/

#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;


template <typename Comparable, typename Comparator>
class Quick{

 public:

  // The following will be the driver for quickSort 
  // less_than added as a Comparator
  void quickSort( vector<Comparable> & a,Comparator less_than )
  {
    quicksort( a, 0, a.size( ) - 1,less_than );
  }

  // Regular quicksort provided from the book, used for median3
  // less_than added as a Comparator
  void quicksort( vector<Comparable> & a, int left, int right, Comparator less_than )
  {
      if( left + 10 <= right ){
          const Comparable & pivot = median3( a, left, right, less_than );	// median3 will be pivot

          // 	Begin partitioning
          int i = left, j = right - 1;
          for( ; ; ) {
              while( less_than(a[ ++i ],pivot )) { }
              while( less_than(pivot, a[ --j ])) { }
              if( i < j )
                  std::swap( a[ i ], a[ j ] );
              else
                  break;
          }
          std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot
          quicksort( a, left, i - 1,less_than );     // Sort small elements
          quicksort( a, i + 1, right,less_than );    // Sort large elements
      }
      else  // Do an insertion sort on the subarray
          insertionSort( a, left, right,less_than );
  }//end regular quick sort

 /**
  * Internal insertion sort routine for subarrays
  * that is used by quicksort.
  * a is an array of Comparable items.
  * left is the left-most index of the subarray.
  * right is the right-most index of the subarray.
  * less_than added as a Comparator
  */
  void insertionSort( vector<Comparable> & a, int begin, int end, Comparator less_than )
  {
      for( int p = begin; p < end+1; ++p )
      {
          Comparable tmp = std::move( a[ p ] );
          int j;

          for( j = p; j > 0 && less_than(tmp, a[ j - 1 ]); --j )
              a[ j ] = std::move( a[ j - 1 ] );
          a[ j ] = std::move( tmp );
      }
  }//end insert sort


/*****************************************************************************************/

/*****************************      PIVOT FUNCTIONS       ********************************/

/*****************************************************************************************/

  /**
   * Body provided by the book , partitioning method
   * First element of vector as pivot
   * Added a comparator (less_than)for all cases of '<' when comparing elements not indexes 
  */ 
  void first(vector<Comparable> &a, int left, int right, Comparator less_than){
  if( left + 10 < right )
      {
          int start = left;			//	First element in the vector 
          std::swap(a[start],a[right - 1]);
          const Comparable & pivot = a[right - 1];

              // Begin partitioning
          int i = left;   
          int j = right - 1;
          for( ; ; )
          {
              while( less_than(a[ i ],pivot )) {
                i++; //added this here to avoid skipping the first and last element
               }
              while( less_than(pivot, a[ j ])) { 
                --j; //added to read first and last element 
              }
              if( i < j )
                  std::swap( a[ i ], a[ j ] );
              else
                  break;
          }
          std::swap( a[ i ], a[right - 1 ] );  // Restore pivot
          first( a, left, i - 1,less_than );     // Sort small elements
          first( a, i + 1, right,less_than );    // Sort large elements
      }
      else  // Do an insertion sort on the subarray
          insertionSort( a, left, right,less_than );
  }
  
 

  /**
   * Body provided by the book, partitioning method
   * Declared middle element as pivot.
   * Added a comparator (less_than)for all cases of '<' when comparing elements not indexes  
  */ 
  void middlePivot(vector<Comparable>& a, int left, int right, Comparator less_than){
  if( left + 10 <= right )
      {
          int mid = (left+right)/2; 		//	Middle element of vector becomes the pivot
          std::swap(a[mid],a[right - 1]);
          const Comparable & pivot = a[right - 1];

              // Begin partitioning
          int i = left;
          int j = right - 1;
          for( ; ; ){
              while( less_than(a[ ++i ],pivot )) { }
              while( less_than(pivot, a[ --j ])) { }
              if( i < j )
                  std::swap( a[ i ], a[ j ] );
              else
                  break;
          }
          std::swap( a[ i ], a[right - 1 ] );  // Restore pivot
          middlePivot( a, left, i - 1,less_than );     // Sort small elements
          middlePivot( a, i + 1, right,less_than );    // Sort large elements
      }
      else  // Do an insertion sort on the subarray
          insertionSort( a, left, right,less_than );
  }
 


  /**
  * Return median of left, center, and right.
  * Order these and hide the pivot.
  * Median	of	three	(as	in	the	slides)
  * Added a comparator (less_than)for all cases of '<' when comparing elements not indexes 
  */
const Comparable & median3( vector<Comparable> & a, int left, int right,Comparator less_than ){
     int center = ( left + right ) / 2;
    
     if( less_than(a[ center ], a[ left ] ))
          std::swap( a[ left ], a[ center ]);
      if( less_than(a[ right ] , a[ left ] ))
         std::swap( a[ left ], a[ right ] );
      if( less_than(a[ right ],a[ center ] ))
          std::swap( a[ center ], a[ right ] );

          // Place pivot at position right - 1
      std::swap( a[ center ], a[ right - 1 ] );
      return a[ right - 1 ];
  }
}; //end quicksort


namespace {

/*****************************************************************************************/

/*********************        GENERATE RAND & VERIFY ORDER       *************************/

/*****************************************************************************************/

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector) {
  vector<int> a;
  for (size_t i = 0; i < size_of_vector; ++i)
    a.push_back(rand());
  return a;
}

// Verify Order Function
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

/****************************        TEST FUNCTIONS       ********************************/

/*****************************************************************************************/


//	For Median of Three (as shown in the book)
template <typename Comparable, typename Comparator>
void QuickSort1(vector<Comparable> &a, Comparator less_than) {
  Quick<int,Comparator> test_median; //object of type quicksort
  
  const auto begin = chrono::high_resolution_clock::now();
  // Time this piece of code;
  test_median.quickSort(a,less_than); //calls the quicksort which was supplied by the book
  // End of piece of code to time.
  const auto end = chrono::high_resolution_clock::now();  

  cout << "Median of three" << endl;
  cout << "Runtime:  " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ns " << endl;
  cout << "Verified: " << VerifyOrder(a,less_than) << endl << endl; //reports verified status
  cout << "----" << endl;
}

//	For middle element as pivot
template <typename Comparable, typename Comparator>
void QuickSort2(vector<Comparable> &a, Comparator less_than) {
  Quick<int,Comparator> middle_pivot; //object of type quicksort
  
  const auto begin = chrono::high_resolution_clock::now();
  // Time this piece of code.
  middle_pivot.middlePivot(a,0,a.size()-1,less_than); 
  // End of piece of code to time.
  const auto end = chrono::high_resolution_clock::now();  

  cout << "Middle " << endl;
  cout << "Runtime:  " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ns " << endl;
  cout << "Verified: " << VerifyOrder(a,less_than) << endl << endl;
  cout << "----" << endl;
}

//	For First Element as the pivot
template <typename Comparable, typename Comparator>
void QuickSort3(vector<Comparable> &a, Comparator less_than) {
  Quick<int, Comparator> first_pivot; //object of type quicksort
  
  const auto begin = chrono::high_resolution_clock::now();
  // Time this piece of code.
  first_pivot.first(a,0,a.size()-1,less_than); //call to the first_pivot function
  // End of piece of code to time.
  const auto end = chrono::high_resolution_clock::now(); 
  
  cout << "First" << endl;  
  cout << "Runtime:  " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ns " << endl;
  cout << "Verified: " << VerifyOrder(a,less_than) << endl << endl;
  cout << "----" << endl;
}
 


// Test function that calls each quicksort, the median3, the first pivot and middle pivot
// I modified this function to take two params and test all sorts at once.
template <typename Comparable, typename Comparator>
void TestTiming(vector<Comparable> &a, Comparator less_than) {
  QuickSort1(a,less_than); 
  QuickSort2(a,less_than);
  QuickSort3(a,less_than);
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


  cout << "Testing quicksort: " << input_type << " " << input_size << " numbers " << comparison_type << endl;
  cout << endl;
  vector<int> input_vector;
  
  if (input_type == "random") {
    input_vector = GenerateRandomVector(input_size);
    
  }else if(input_type == "sorted") {			// Generate sorted vector.
    for (int i = 1; i <= input_size; i++) {
		  input_vector.push_back(i);
	  }
	  
  }else{
    cout << "Invlaid input type" << endl; 
    return 0; 
  }

  if(comparison_type == "greater"){				// Check comparison types, can only be greater or less than
    TestTiming(input_vector,greater<int>()); 
  
  }else if(comparison_type == "less"){
    TestTiming(input_vector,less<int>()); 
    
  }else{
    cout << "Invalid comparison_type" << endl; 
  }
  
  return 0;
}
