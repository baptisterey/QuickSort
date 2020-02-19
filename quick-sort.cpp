
#include <iostream>
#include <vector>

#include <algorithm>    
#include <random>       
#include <chrono>
#include <tuple>

#include <cassert>

#include <iomanip>

void swap(int* a, int* b);
int partitionSinglePivot(std::vector<int> *vect, int low, int high);
void quickSortSinglePivot(std::vector<int> *vect, int low, int high);
std::tuple<int, int> partitionDoublePivot(std::vector<int> *vect, int low, int high);
void quickSortDoublePivot(std::vector<int> *vect, int low, int high);
void printVector(const std::vector<int>* vect, int low, int high);
void printFullVector(const std::vector<int>* vect);
std::vector<int>* createRandomArray(int size);
void createAndSortVect(int size);

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partitionSinglePivot(std::vector<int> *vect, int low, int high)
{
	int pivot = (*vect)[high]; // We choose the highest element as the pivot
	int i = (low - 1); 

	for (int j = low; j <= high - 1; j++)
	{
		if ((*vect)[j] < pivot)
		{
			i++;
			swap(&(*vect)[i], &(*vect)[j]);
			
		}
	}
	swap(&(*vect)[i + 1], &(*vect)[high]);
	return (i + 1);
}

void quickSortSinglePivot(std::vector<int> *vect, int low, int high)
{
	if (low < high)
	{

		int pivot = partitionSinglePivot(vect, low, high);

		// Divide the sort by cutting the array in half and solve it via reccursion.
		quickSortSinglePivot(vect, pivot + 1, high);
		quickSortSinglePivot(vect, low, pivot - 1);
	}
}

std::tuple<int, int> partitionDoublePivot(std::vector<int> *vect, int low, int high)
{
	if ((*vect)[low] > (*vect)[high]) // 1st pivot must have the lowest value of the two. If not, swap the two pivots.
	{
		swap(&(*vect)[low], &(*vect)[high]);
	}

	int pivot1 = (*vect)[low]; // We choose the lowest element as the 1st pivot
	int pivot2 = (*vect)[high]; // We choose the highest element as the 2nd pivot

	int i = low + 1; // cursor for 1st pivot
	int j = high - 1; // cursor for 2nd pivot

	for (int k = i; k <= j; k++)
	{
		if ((*vect)[k] < pivot1) // If element is lower than 1st pivot, swap it in the 1st section
		{
			swap(&(*vect)[k], &(*vect)[i]);
			i++;
		}
		else if ((*vect)[k] >= pivot2)
		{
			// If element is greater than 2nd pivot, search for the first element to the left that is not greater than the pivot, and swap our element with this one
			while ((*vect)[j] > pivot2 && k < j)
				j--;
			swap(&(*vect)[k], &(*vect)[j]);
			j--;

			// Then, if the element we just swapped appends to be lower than the 1st pivot, we swap it aswell
			if ((*vect)[k] < pivot1)
			{
				swap(&(*vect)[k], &(*vect)[i]);
				i++;
			}
		}
	}
	i--;
	j++;

	swap(&(*vect)[i], &(*vect)[low]);
	swap(&(*vect)[j], &(*vect)[high]);
	return {i, j};
}

void quickSortDoublePivot(std::vector<int> *vect, int low, int high)
{	
	if (low < high)
	{
		auto pivot = partitionDoublePivot(vect, low, high);
		int pivot1 = std::get<0>(pivot);
		int pivot2 = std::get<1>(pivot);

		// Divide the sort by cutting the array in half and solve it via reccursion.
		quickSortDoublePivot(vect, low, pivot1 - 1);
		quickSortDoublePivot(vect, pivot1 + 1, pivot2 - 1);
		quickSortDoublePivot(vect, pivot2 + 1, high);
	}
}

void printVector(const std::vector<int>* vect, int low, int high)
{
	low = std::max(0, low);
	high = std::min(static_cast<int>(vect->size()), high);
		
	for (int i = low; i < high; i++) {
		std::cout << (*vect)[i] << " ";
	}
		
	std::cout << std::endl;
}

void printFullVector(const std::vector<int>* vect)
{
	int size = static_cast<int>(vect->size());
	printVector(vect, 0, size);
}

std::vector<int>* createRandomArray(int size)
{
	std::vector<int>* newArray = new std::vector<int>(size);
	for (int i = 0; i < size; i++)
	{
		(*newArray)[i] = i;
	}

	// Shuffle the array
	unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
	shuffle((*newArray).begin(), (*newArray).end(), std::default_random_engine(seed));

	return newArray;
}

void createAndSortVect(int size)
{
	if (size <= 0) {
		return;
	}

	std::cout << "VECTOR OF SIZE " << size << " :" << std::endl;

	std::vector<int> *vect = createRandomArray(size);

	{

		std::vector<int> tmp(*vect);

		std::cout << "Sorting via Single Pivot Quick-Sort..." << std::endl;

		auto start = std::chrono::steady_clock::now();

		quickSortSinglePivot(&tmp, 0, size - 1);

		auto end = std::chrono::steady_clock::now();

		assert(std::is_sorted(tmp.begin(), tmp.end()));

		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		std::cout << "Sort completed, execution time : " << duration.count() << " ms." << std::endl;
	}
	
	{
		
		std::vector<int> tmp(*vect);

		std::cout << "Sorting via Double Pivot Quick-Sort..." << std::endl;

		auto start = std::chrono::steady_clock::now();

		quickSortDoublePivot(&tmp, 0, size - 1);

		auto end = std::chrono::steady_clock::now();
		
		assert(std::is_sorted(tmp.begin(), tmp.end()));

		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		std::cout << "Sort completed, execution time : " << duration.count() << " ms." << std::endl;
	}

	std::cout << "-------------------------------" << std::endl << std::endl;

	delete vect;
}

int main()
{
	// --- CREATE AND SORT THREE VECTOR WITH QUICK-SORT ---
	createAndSortVect(1000);
	createAndSortVect(100000);
	createAndSortVect(10000000);
	createAndSortVect(1000000000);
	// ----------------------------------------------------

	return 0;
}

