#include <array_list_utility.h>
#include <fstream>
#include <chrono>

std::chrono::steady_clock::time_point start, end;

int main(int args, char** argv)
{
	std::ofstream fp("..\\..\\media\\results.csv");
	fp << "array size, create time, shuffle time, copy time, quicksort time, bubblesort time\n";

	for (int sample_size = 1000; sample_size < 10000; sample_size += 5000)
	{
		fp << sample_size << ", ";

		start = std::chrono::steady_clock::now();
		//create array (do operation)
		end = std::chrono::steady_clock::now();
		std::chrono::milliseconds elapsed;
		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		unsigned long int time_create = elapsed.count();
		//fp << time_create << ",  ";
		fp << "\n";

	}

	fp.close();
}