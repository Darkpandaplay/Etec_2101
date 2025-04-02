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
    
    template <typename T>
    std::pair<int, int> partition(ArrayList<T>& listo, int left_index, int right_index, sort_order order) {
        int mid_index = (left_index + right_index) / 2;
        T pivot_value = listo[mid_index];
        std::swap(listo[mid_index], listo[right_index]);
        int num_swap = 1;
        int swap_index = left_index;

        auto compare = [&](const T& a, const T& b) {
            if (order == sort_order::ASCENDING) return a <= b;
            if (order == sort_order::DESCENDING) return a >= b;
            throw std::runtime_error("Invalid sort order");
            };

        for (int i = left_index; i <= right_index; ++i) {
            if (compare(listo[i], pivot_value)) {
                std::swap(listo[i], listo[swap_index]);
                num_swap++;
                swap_index++;
            }
        }
        return { swap_index - 1, num_swap };
    }

    template <typename T>
    int quick_sort(ArrayList<T>& my_list, int left_index, int right_index, sort_order order)
    {
        int num_swap = 0;
        if (left_index >= right_index)
        {
            return num_swap;
        }

        std::pair temp = std::make_pair(0, 0);
        temp = partition<T>(my_list, left_index, right_index, order);
        int pivot_index = temp.first;
        num_swap += temp.second;
        num_swap += quick_sort<T>(my_list, left_index, pivot_index - 1, order);
        num_swap += quick_sort<T>(my_list, pivot_index + 1, right_index, order);
    }


}
