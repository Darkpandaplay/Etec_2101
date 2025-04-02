#pragma once
#include <array_list.h>
#include <random>

enum class sort_order { ASCENDING, DESCENDING };

template <typename T>
void sorto_bubble(ArrayList<T>& listo, sort_order order)
{
	int n = listo.size();
	bool sorted;
	if (order == sort_order::ASCENDING)
	{
		for (int i = 0; i < n - 1; i++)
		{
            if (order == sort_order::ASCENDING) {
                for (int i = 0; i < n - 1; ++i) {
                    bool sorted = true;
                    for (int j = 0; j < n - 1 - i; ++j) { 
                        if (listo[j] > listo[j + 1]) {
                            std::swap(listo[j], listo[j + 1]); 
                            sorted = false;
                        }
                    }
                    if (sorted) break;
                }
            }
		}
	}
    else if (order == sort_order::DESCENDING)
    {
        if (order == sort_order::DESCENDING) {
            for (int i = 0; i < n - 1; ++i) {
                bool sorted = true;
                for (int j = 0; j < n - 1 - i; ++j) {
                    if (listo[j] < listo[j + 1]) {
                        std::swap(listo[j], listo[j + 1]);
                        sorted = false;
                    }
                }
                if (sorted) break;
            }
        }
    }
};