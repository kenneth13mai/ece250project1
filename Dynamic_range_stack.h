/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  h4mai @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"
#include "ece250.h"

using namespace std;

class Dynamic_range_stack {
	private:
		int entry_count;
		int max_count;
		int min_count;
		int initial_capacity;
		int current_capacity;

		int *stack_array;
		int *maximum_array;
		int *minimum_array;

		// You may wish to include a number of helper functions
		// in order to abstract out some operations

	public:
		Dynamic_range_stack( int = 10 );
		Dynamic_range_stack( Dynamic_range_stack const & );
		~Dynamic_range_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		int maximum() const;
		int minimum() const;


		void push( int const & );
		int pop();
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );
};

Dynamic_range_stack::Dynamic_range_stack( int n ):
entry_count( 0 ),
min_count( 0 ),
max_count( 0 ),
initial_capacity( std::max( 1, n ) ),
current_capacity( initial_capacity ),
stack_array( new int[current_capacity] ),
maximum_array( new int[current_capacity] ),
minimum_array( new int[current_capacity] )
{
	// empty constructor
}

Dynamic_range_stack::~Dynamic_range_stack() {
	// Enter your implementation here.
	// The destructor deletes the memory allocated for the arrays.
	// release all the memory
	delete [] stack_array   ;
	delete [] maximum_array ;
	delete [] minimum_array ;

	// clear the counters by calling the clear() function
	clear();


}

int Dynamic_range_stack::top() const {
	// Enter your implementation here.
	// Return the object at the top of the stack (stack_array). It may throw an underflow exception (𝑂(1)).
	if (empty()==true)
    {
        underflow ex;
        throw ex;
    }
    return stack_array[entry_count-1];

}

int Dynamic_range_stack::maximum() const {
	// Enter your implementation here.
	// Return the maximum object currently in the stack. It may throw an underflow exception (𝑂(1))).
	if (entry_count < 1)
    {
        underflow ex;
        throw ex;
    }
	return maximum_array[max_count-1];
}

int Dynamic_range_stack::minimum() const {
	// Enter your implementation here.
	// Return the minimum object currently in the stack. It may throw an underflow exception (𝑂(1))).
	if (entry_count < 1)
    {
        underflow ex;
        throw ex;
    }
	return minimum_array[min_count-1];
}

int Dynamic_range_stack::size() const {
	// Enter your implementation here.
	// Returns the number of elements currently stored in the stack (𝑂(1))).
	return current_capacity;
}

bool Dynamic_range_stack::empty() const {
	// Enter your implementation here.
	// Determines whether the stack is empty or not (𝑂(1)).
	if (entry_count == 0)
        return true;

	if ( entry_count > 0)
        return false;
}

int Dynamic_range_stack::capacity() const {
	// Enter your implementation here.
	// Return the current capacity of the arrays in (𝑂(1))).
	return current_capacity;
}

void Dynamic_range_stack::push( int const &obj ) {
	// Enter your implementation here.
	// Check if it reach the maximum of the array.
	if ( entry_count >= current_capacity )
    {   // when the entry count reach the size of the current array, create a new array with two times of its size.
        current_capacity = current_capacity*2;
        // create new temp arrays, with double of the size.
        int *stack_array_temp;
		int *maximum_array_temp;
		int *minimum_array_temp;
		stack_array_temp   = new int[current_capacity] ;
        maximum_array_temp = new int[current_capacity] ;
        minimum_array_temp = new int[current_capacity] ;
        // use copy function in the std library
        // (the first address in the stack_array, the last index of the array(but the last index will not be copied), the first index of the new array)
        copy(stack_array  , stack_array   + entry_count, stack_array_temp);
        copy(maximum_array, maximum_array + max_count  , maximum_array_temp);
        copy(minimum_array, minimum_array + min_count  , minimum_array_temp);
        // Once copied, delete the old array and release memory.
        delete [] stack_array;
        delete [] maximum_array;
        delete [] minimum_array;
        // once deleted, do the new memory allocation.
        stack_array   = new int[current_capacity] ;
        maximum_array = new int[current_capacity] ;
        minimum_array = new int[current_capacity] ;
        // copy the temp array to the new created array.
        copy(stack_array_temp    , stack_array   + entry_count, stack_array);
        copy(maximum_array_temp  , maximum_array + max_count  , maximum_array);
        copy(minimum_array_temp  , minimum_array + min_count  , minimum_array);
        delete [] stack_array_temp;
        delete [] maximum_array_temp;
        delete [] minimum_array_temp;
	}

	// Insert the obj to the array.
	stack_array[entry_count] = obj;
	entry_count++;
	// the first time push, insert the first element into max and min array too.
	if (entry_count == 1){
        // increment the maxcount and mincount too.
        maximum_array[max_count] = obj;
        max_count = max_count + 1 ;
        minimum_array[min_count] = obj;
        min_count = min_count + 1 ;
	}

	// every time pushed, check the new value with the max and min see if need to insert to the new array.
	if (obj >= maximum_array[max_count - 1] )
	{
	    maximum_array[max_count] =  obj;
	    max_count++;
	}
	if (obj <= minimum_array[min_count - 1] )
    {
        minimum_array[min_count] =  obj;
        min_count++;
    }


	return;
}

int Dynamic_range_stack::pop() {
	// Enter your implementation here.
	// If already empty, error.
	// instead of calling the empty() function, use the counter, which have higher efficiency.
	if(entry_count <= 0){
        underflow ex;
        throw ex;
    }
    if ( stack_array[entry_count - 1 ] = maximum_array[max_count-1])
        max_count--;
    if ( stack_array[entry_count - 1 ] = minimum_array[min_count-1])
        min_count--;

    entry_count--;
	// return the top value on the stack.
	return stack_array[entry_count];
}

void Dynamic_range_stack::clear() {
	// Enter your implementation here.
	delete [] stack_array   ;
	delete [] maximum_array ;
	delete [] minimum_array ;
	// reset all the counter to zero.
	current_capacity  = 0 ;
	entry_count       = 0 ;
	max_count         = 0 ;
	min_count         = 0 ;
	// memory allocation for the three stacks, set the size back to initial capacity.
	stack_array   = new int[initial_capacity];
	maximum_array = new int[initial_capacity];
    minimum_array = new int[initial_capacity];
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack ) {
	// Print out your stacks

}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
