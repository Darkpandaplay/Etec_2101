#include <array_list_utility.h>
#include <fstream>
#include <chrono>

std::chrono::steady_clock::time_point start, end;

int main(int args, char** argv) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1000.0f, 1000.0f);

    std::ofstream fp("../../media/results.csv");
    fp << "array size, create-time(ns), shuffle-time(ns), copy-time(ns), save-time(ns), quicksort-time(ms), bubblesort-time(ms), binarysearch-time(ms), linearsearch-time(ms)\n";

    for (int sample_size = 1000; sample_size < 20000; sample_size += 5000) {
        fp << sample_size << ", ";

        // CREATE
        auto start = std::chrono::steady_clock::now();
        std::vector<float> flist(sample_size + 1);
        std::generate(flist.begin(), flist.end(), [&]() { return dist(gen); });
        auto end = std::chrono::steady_clock::now();
        fp << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << ", ";

        // SHUFFLE
        start = std::chrono::steady_clock::now();
        std::shuffle(flist.begin(), flist.end(), gen);
        end = std::chrono::steady_clock::now();
        fp << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << ", ";

        // COPY
        start = std::chrono::steady_clock::now();
        std::vector<float> flist2 = flist;
        end = std::chrono::steady_clock::now();
        fp << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << ", ";

        // SAVE 1000 VALUES
        start = std::chrono::steady_clock::now();
        std::vector<float> savedValues(flist.begin(), flist.begin() + 1001);
        end = std::chrono::steady_clock::now();
        fp << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << ", ";

        // QUICKSORT
        start = std::chrono::steady_clock::now();
        std::sort(flist.begin(), flist.end()); // Using std::sort for quicksort-like performance
        end = std::chrono::steady_clock::now();
        fp << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << ", ";

        // BUBBLESORT
        if (sample_size <= 300000) {
            start = std::chrono::steady_clock::now();
            std::vector<float> flist3 = flist2; // Need a fresh copy for bubblesort
            for (size_t i = 0; i < flist3.size() - 1; ++i)
                for (size_t j = 0; j < flist3.size() - i - 1; ++j)
                    if (flist3[j] > flist3[j + 1])
                        std::swap(flist3[j], flist3[j + 1]);
            end = std::chrono::steady_clock::now();
            fp << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << ", ";
        }
        else {
            fp << "N/A, ";
        }

        // BINARY SEARCH
        start = std::chrono::steady_clock::now();
        for (float value : savedValues) {
            std::binary_search(flist.begin(), flist.end(), value);
        }
        end = std::chrono::steady_clock::now();
        fp << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << ", ";

        // LINEAR SEARCH (FIND)
        start = std::chrono::steady_clock::now();
        for (float value : savedValues) {
            std::find(flist.begin(), flist.end(), value);
        }
        end = std::chrono::steady_clock::now();
        fp << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << ", ";

        fp << "\n";
    }

    fp.close();
}