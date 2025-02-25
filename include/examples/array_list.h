#pragma once
#include <string>
#include <stdexcept>
#include <ostream>

// Note: in C++, a general tempate (like this one) must be defined inline
// entirely in the .h file (no .cpp files).  

namespace ssuds
{
	/// An ArrayList is an array-based data structure. 
	template <class T>
	class ArrayList
	{
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ ATTRIBUTES                              @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	protected:
		/// The default (and minimum) capacity of an ArrayList
		static const int msMinCapacity = 5;

		/// The current number of "slots" AVAILABLE in my_array (i.e. the array size)
		unsigned int array_capacity;

		/// How many slots are we USING?  This will always be less than or equal to array_capacity
		unsigned int array_size;

		/// The array of data we're currently holding.  Note: an alternative would've been T* my_array
		/// but I'm attempting to use raw bytes here so we don't have to have a default constructor
		/// for templated types.
		unsigned char* my_array;



		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ CONSTRUCTORS / DESTRUCTORS              @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:
		/// Default constructor
		ArrayList() : array_size(0), array_capacity(0), my_array(nullptr)
		{
			// intentionally empty
		};



		/// Destructor
		~ArrayList()
		{
			// Note that I used to worry about my_array being null, but the delete operator
			// already has an internal check to avoid freeing a null pointer, so adding our own
			// would be redundance, so I'm commenting this line.
			// if (my_array)
			delete[] my_array;
		}


		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ OTHER METHODS (alphabetical)            @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:
		/// <summary>
		///  Inserts a new element at the end of the array
		/// </summary>
		/// <param name="val">the new value to add</param>
		void append(const T& val)
		{
			// check to see if we need to increase our capacity
			grow();

			// Stick our new element in the last slot and (sneakily) increase our size in the process
			// ... This is what I had originally...
			//(T&)(my_array[array_size * sizeof(T)]) = val;
			// ... but I switched to this.  Person seemed to be a problem (in particular the strings)
			//     Memcpy would side-step any = operators.  I'm not 100% sure why this fixed the problem
			memcpy(&my_array[array_size * sizeof(T)], &val, sizeof(T));
			//T temp = (T&)(my_array[array_size * sizeof(T)]);     // <- seeing if I could read out what i put in just now
			array_size++;
		}


		/// <summary>
		/// Returns a reference to the item at the given index.  Since it is a reference, this
		/// type of operation is allowed:
		///		my_float_array.at(5) = 17.3f;
		///		my_int_array.at(3)++;
		/// This method will raise a std::out_of_range exception if an invalid index is given.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		T& at(const unsigned int index) const
		{
			if (index >= array_size)
				throw std::out_of_range("Invalid index (" + std::to_string(index) + ")");
			return (T&)(my_array[index * sizeof(T)]);
		}


		/// <summary>
		/// Returns the current capacity of the ArrayList (this is always
		/// greater than or equal to the size)
		/// </summary>
		/// <returns>the capacity of the internal array in the ArrayList</returns>
		unsigned int capacity() const
		{
			return array_capacity;
		}

		/// <summary>
		/// Clears the array back to its original state
		/// </summary>
		void clear()
		{
			if (my_array)
				delete[] my_array;
			my_array = nullptr;
			array_size = 0;
			array_capacity = 0;
		}

		/// <summary>
		/// Finds the index of the first occurrence of the given value
		/// </summary>
		/// <param name="val">the value to search for</param>
		/// <param name="start_index">the index to start searching at</param>
		/// <returns></returns>
		int find(const T& val, const unsigned int start_index = 0) const
		{
			if (start_index >= array_size)
				throw std::out_of_range("Invalid index: " + std::to_string(start_index));

			for (unsigned int i = start_index; i < array_size; i++)
			{
				T temp = at(i);
				if (temp == val)
					return i;
			}

			// We didn't find it
			return -1;
		}



		/// <summary>
		/// Inserts a new data item at a given index
		/// </summary>
		/// <param name="val">the new value to insert</param>
		/// <param name="index">the index at which to insert (must be >= 0 and <= size) </param>
		void insert(const T& val, unsigned int index)
		{
			if (index > array_size)
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			else if (index == array_size)
				append(val);
			else
			{
				// check to see if we need to increase capacity first
				grow();

				// Move all the elements that come *after* index up one spot
				memcpy(&my_array[sizeof(T) * (index + 1)], &my_array[index * sizeof(T)], (array_size - index) * sizeof(T));

				// Put our new elements in spot index and increase our size
				//(T&)(my_array[index * sizeof(T)]) = val;
				memcpy(&my_array[index * sizeof(T)], &val, sizeof(T));
				array_size++;
			}
		}


		/// <summary>
		/// Outputs the ArrayList to the given output stream
		/// </summary>
		/// <param name="os">an ostream object (ofstream, stringstream, cout, etc.) </param>
		void output(std::ostream& os) const
		{
			os << "[";
			for (unsigned int i = 0; i < size(); i++)
			{
				os << at(i);
				if (i < size() - 1)
					os << ", ";
			}
			os << "]";
		}

		/// <summary>
		/// Removes a data item at the given index
		/// </summary>
		/// <param name="index">the index of the thing to remove (will return a std::out_of_bounds exception if invalid (<0 or >= size)</param>
		/// <param name="resize_if_necessary">if true, the array will be resized if it is now below half capacity</param>
		/// <returns>the data item that was just removed</returns>
		T remove(unsigned int index, bool resize_if_necessary = true)
		{
			if (index >= array_size || index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(index));

			// Get the value we'll return at the end (the element removed)
			T result = (T&)(my_array[index * sizeof(T)]);

			// Move all elements that come after index down one spot
			memcpy(&my_array[index * sizeof(T)], &my_array[(index + 1) * sizeof(T)], (array_size - index - 1) * sizeof(T));

			// Decrement our size
			array_size--;

			// Shrink, if applicable and requested
			if (resize_if_necessary)
				shrink();

			// Return the result
			return result;
		}

		/// <summary>
		/// Removes all occurrences of a given value.  Uses find and remove internally to do the removal
		/// </summary>
		/// <param name="val">the value to remove</param>
		/// <param name="resize_if_necessary">if true, the array will be resized if it is now below half capacity</param>
		/// <returns>the number of occurrences of that data item that were removed</returns>
		int remove_all(const T val, bool resize_if_necessary = true)
		{
			int cur_index = 0;
			unsigned int num_removed = 0;
			while (cur_index >= 0 && (unsigned int)cur_index < array_size)
			{
				// Find the next occurrence of val, starting at the current position
				cur_index = find(val, cur_index);
				if (cur_index >= 0)
				{
					// We found one!
					remove(cur_index, false);
					num_removed++;
				}
			}

			if (resize_if_necessary)
				shrink();

			return num_removed;
		}


		/// <summary>
		/// Ensures the internal array has at least this capacity.  This is useful if
		/// the user knows how many items they will add and don't want to take the performance
		/// penalty of the grow operation happening in-between.  If the capacity is already higher or
		/// equal to the given value, there will be no effect.
		/// </summary>
		/// <param name="desired_capacity">The capacity will be set to at least this value</param>
		void reserve(unsigned int desired_capacity)
		{
			if (desired_capacity > array_capacity)
			{
				// Make the larger array
				unsigned char* temp_array = new unsigned char[desired_capacity * sizeof(T)];
				memset(temp_array, 0, sizeof(T) * desired_capacity);

				// Copy data from the existing array
				memcpy(temp_array, my_array, array_size * sizeof(T));

				// Free the old array
				delete[] my_array;

				// Make my_array point to the larger array
				my_array = temp_array;
				array_capacity = desired_capacity;
			}
		}

		/// <summary>
		/// Returns the size of the internal array (i.e.) how many things are being stored in the ArrayList
		/// </summary>
		/// <returns>the size of the ArrayList</returns>
		unsigned int size() const
		{
			return array_size;
		}





	protected:
		/// <summary>
		/// An internal method to resize the array if we are currently at capacity (if we are not, nothing is done)
		/// </summary>
		void grow()
		{
			if (array_size == array_capacity)
			{
				// Allocate what will become the new array
				unsigned char* new_array = nullptr;
				if (array_capacity == 0)
				{
					new_array = new unsigned char[msMinCapacity * sizeof(T)];
					memset(new_array, 0, msMinCapacity * sizeof(T));
				}
				else
				{
					new_array = new unsigned char[(array_capacity * 2) * sizeof(T)];
					memset(new_array, 0, (array_capacity * 2) * sizeof(T));
				}

				// Copy over data from the old array (if any)
				if (my_array != nullptr)
				{
					memcpy(new_array, my_array, sizeof(T) * array_size);

					// Destroy the old array
					delete[] my_array;
				}

				// Make the new array *the* array
				my_array = new_array;

				// Note that our capacity is now double what it used to be
				if (array_capacity == 0)
					array_capacity = msMinCapacity;
				else
					array_capacity *= 2;
			}
		}


		/// <summary>
		/// An internal method to see if the array can be shrunk (capacity reduced by half, down to msMinCapacity)
		/// </summary>
		void shrink()
		{
			if (array_size < array_capacity / 4 && array_capacity > msMinCapacity)
			{
				// Allocate what will become the new array
				unsigned char* new_array = new unsigned char[(array_capacity / 2) * sizeof(T)];
				memset(new_array, 0, (array_capacity / 2) * sizeof(T));

				// Copy over data from the old array (if any)
				memcpy(new_array, my_array, array_size * sizeof(T));

				// Destroy the old array
				delete[] my_array;

				// Make the new array *the* array
				my_array = new_array;

				// Note that our capacity is now double what it used to be
				array_capacity /= 2;
			}
		}




		class ArrayListIterator {

		private:
			ArrayList* list_ptr;
			int index;
			bool reverse;

		public:
			ArrayListIterator() {
				list_ptr = nullptr;
				index = 0;
				reverse = false;
			}

			ArrayListIterator(ArrayList* ptr, int idx, bool rev) {
				list_ptr = ptr;
				index = idx;
				reverse = rev;
			}

			const T& operator*() {
				return list_ptr->at(index);
			}

			ArrayListIterator operator++() {
				if (reverse) {
					index--;
					if (index < 0) {
						list_ptr = nullptr;
					}
				}
				else {
					index++;
					if (index > list_ptr->array_size - 1) {
						list_ptr = nullptr;
					}
				}
				return *this;
			}

			bool operator!=(const ArrayListIterator& other) {
				if (list_ptr != other.list_ptr || index != other.index || reverse != other.reverse)
					return true;
				return false;
			}

		};

		ArrayListIterator begin() {
			ArrayListIterator temp(this, 0, false);
			return temp;
		}

		ArrayListIterator end() {
			ArrayListIterator temp(nullptr, array_size, false);
			return temp;
		}

		ArrayListIterator rbegin() {
			ArrayListIterator temp(this, array_size - 1, true);
			return temp;
		}

		ArrayListIterator rend() {
			ArrayListIterator temp(nullptr, -1, true);
			return temp;
		}

		ArrayList(ArrayList&& other) {
			my_array = other->my_array;
			array_size = other->array_size;
			array_capacity = other->array_capacity;

			other->my_array = nullptr;
		}

		ArrayList(const std::initializer_list<T>& init_list) {
			my_array = nullptr;
			array_size = 0;
			array_capacity = 10;

			for (T cur_val : init_list) {
				append(cur_val);
			}
		}

		ArrayList(const ArrayList& other) {
			my_array = new T(other.array_capacity);
			array_size = other.array_size;
			for (unsigned int i = 0; i < array_size; i++) {
				my_array[i] = other.my_array[i];
			}
		}

		friend std::ostream& operator<<(std::ostream& os, const ArrayList& A) {
			A.output(os);
			return os;
		}

		T& operator[](unsigned int index) {
			return my_array[index];
		}

		ArrayList& operator=(const ArrayList& other) {
			delete[] my_array;

			my_array = new T(other.array_capacity);
			array_size = other.array_size;
			for (unsigned int i = 0; i < array_size; i++) {
				my_array[i] = other.my_array[i];
			}
			return *this;
		}
	};
}