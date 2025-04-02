#pragma once
#include <array_list.h>
#include <random>


namespace ssuds
{
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
    
    template <typename T>
    
    void shuffle(ArrayList<T>& listo, bool derrangement)
    {
        std::random_device device;
        int n = listo.size();
        for (int i = n - 1; i > 0; i--)
        {
            std::random_device device;
            std::mt19937 generator(device());
            std::uniform_int_distribution<int> distribution(0, derrangement ? (i - 1) : i);
            int j = distribution(generator);
            std::swap(listo[j], listo[i]);
        }
    }

    template <typename T>
    int binary_search(ArrayList<T>& listo, T value, sort_order order)
    {
        if (order == sort_order::ASCENDING) { // the list is in ascending order
            int left = 0;
            int right = listo.size() - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (listo[mid] == value) {
                    return mid;
                }
                else if (listo[mid] > value) {
                    right = mid - 1;
                }
                else { // listo[mid] < value
                    left = mid + 1;
                }
            }
            return -1; // Value Not found
        }
        else if (order == sort_order::DESCENDING) { // the list is in descending order
            int left = 0;
            int right = listo.size() - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2; // More robust mid calculation
                if (listo[mid] == value) {
                    return mid;
                }
                else if (listo[mid] < value) {
                    right = mid - 1;
                }
                else { // listo[mid] > value
                    left = mid + 1;
                }
            }
            return -1; // Value Not found
        }
        else {
            throw std::runtime_error("List must be in ascending or descending order");
        }
    }
}
