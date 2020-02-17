
#include <iostream>
#include <vector>

#include <algorithm>    
#include <random>       
#include <chrono>

#include <iomanip>

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

void printVector(const std::vector<int>* vect)
{
	int size = vect->size();
		
	for (int i = 0; i < size; i++) {
		std::cout << (*vect)[i] << " ";
	}
		
	std::cout << std::endl;
}

std::vector<int>* createRandomArray(int size) {

	std::vector<int>* newArray = new std::vector<int>(size);
	for (int i = 0; i < size; i++)
	{
		(*newArray)[i] = i;
	}

	// Shuffle the array
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle((*newArray).begin(), (*newArray).end(), std::default_random_engine(seed));

	return newArray;
}

void createAndSortVectSinglePivot(int size) {

	if (size <= 0) {
		return;
	}

	
	std::cout << "VECTOR OF SIZE " << size << " :" << std::endl;

	std::vector<int> *vect = createRandomArray(size);

	std::cout << "Sorting via Single Pivot Quick-Sort..." << std::endl;

	auto start = std::chrono::steady_clock::now();

	quickSortSinglePivot(vect, 0, size - 1);

	auto end = std::chrono::steady_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	std::cout << "Sort completed, execution time : " << duration.count() << " ms." << std::endl;

	std::cout << std::endl;
}

int main()
{
	std::cout << "--- SINGLE PIVOT QUICK-SORT ---" << std::endl << std::endl;

	// --- CREATE AND SORT THREE VECTOR WITH SINGLE PIVOT QUICK-SORT ---
	createAndSortVectSinglePivot(500);
	createAndSortVectSinglePivot(35000);
	createAndSortVectSinglePivot(1000000);
	// -----------------------------------------------------------------
	std::cout << "-------------------------------" << std::endl << std::endl;

	while (true) {

	}

	return 0;
}

