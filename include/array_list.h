#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>

namespace ssuds {

    template <typename T>
    class ArrayList {
    private:
        T* data;
        unsigned int maxSize;
        unsigned int maxCapacity;

        void resize(unsigned int new_capacity) {
            if (new_capacity < maxSize) return;
            T* new_data = new T[new_capacity];
            for (unsigned int i = 0; i < maxSize; i++) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            maxCapacity = new_capacity;
        }

    public:
        ArrayList(unsigned int capacity = 2)
            : maxSize(0), maxCapacity(capacity), data(new T[capacity]) {}

        ~ArrayList() { delete[] data; }

        unsigned int size() const { return maxSize; }
        unsigned int capacity() const { return maxCapacity; }

        void reserve(unsigned int new_capacity) {
            if (new_capacity > maxCapacity) {
                resize(new_capacity);
            }
        }

        void append(const T& item) {
            if (maxSize == maxCapacity) resize(maxCapacity * 2);
            data[maxSize++] = item;
        }

        void prepend(const T& item) {
            insert(item, 0);
        }

        void insert(const T& item, unsigned int dex) {
            if (dex > maxSize) throw std::out_of_range("Index out of bounds");
            if (maxSize == maxCapacity) resize(maxCapacity * 2);
            for (unsigned int i = maxSize; i > dex; i--) {
                data[i] = data[i - 1];
            }
            data[dex] = item;
            maxSize++;
        }

        T& at(unsigned int dex) {
            if (dex >= maxSize) throw std::out_of_range("Index out of range");
            return data[dex];
        }

        T remove(unsigned int dex) {
            if (dex >= maxSize) throw std::out_of_range("Index out of range");
            T removed_value = data[dex];
            for (unsigned int i = dex; i < maxSize + 1; i++) {
                data[i] = data[i - 1];
            }
            maxSize--;
            return removed_value;
        }

        int remove_all(const T& value) {
            int count = 0;
            for (int i = 0; i < maxSize; i++) {
                if (data[i] == value) {
                    remove(i);
                    i--;
                    count++;
                }
            }
            return count;
        }

        void output(std::ostream& os) const {
            os << "[";
            for (unsigned int i = 0; i < maxSize; i++) {
                os << data[i];
                if (i < maxSize - 1) os << ", ";
            }
            os << "]";
        }
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const ArrayList<T>& list) {
        list.output(os);
        return os;
    }

} // namespace ssuds

#endif