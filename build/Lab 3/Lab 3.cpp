#include <iostream>
#include <vector>
#include <array_list.h>

int main()
{
    std::cout << "Test 1: Iterator \n";
    ssuds::ArrayList<short> slist;
    slist.append(25);
    slist.append(90);
    slist.append(1000);
    slist.append(1001);
    ssuds::ArrayList<short>::ArrayListIterator sit = slist.begin();     // Output:
    while (sit != slist.end()) {                                        // 25
        std::cout << *sit << "\n";                                      // 90
        ++sit;                                                          // 1000
    }                                                                   // 1001

    std::cout << "Test 2: Iterator \n";                                 // Output:
    for (short s : slist) {                                             // 25
        std::cout << s << "\n";                                         // 90
    }                                                                   // 1000
    std::cout << "\n";                                                  // 1001

    std::cout << "Test 3: Copy Constructor \n";                         // Output:
    ssuds::ArrayList<short> slist2(slist);                              // 25
    for (short s : slist2) {                                            // 90
        std::cout << s << "\n";                                         // 1000
    }                                                                   // 1001
    std::cout << "\n";

    std::cout << "Test 4: Assignment Operator \n";                      // Output:
    ssuds::ArrayList<short> slist3 = slist;                             // 25
    for (short s : slist3) {                                            // 90
        std::cout << s << "\n";                                         // 1000
    }                                                                   // 1001

    std::cout << "\n";                                                  // Output:
    std::cout << "Test 5: Reverse Iterator \n";                         // 1.1
    ssuds::ArrayList<float> flist;                                      // 2.2
    flist.append(1.1f);                                                 // 3.3
    flist.append(2.2f);                                                 // 4.4
    flist.append(3.3f);
    flist.append(4.4f);
    ssuds::ArrayList<float>::ArrayListIterator fit = flist.begin();     // Reverse:
    while (fit != flist.end()) {                                        // 4.4
        float cur = *fit;                                               // 3.3
        std::cout << cur << "\n";                                       // 2.2
        ++fit;                                                          // 1.1
    }
    std::cout << "Reverse: \n";
    ssuds::ArrayList<float>::ArrayListIterator rit = flist.rbegin();
    while (rit != flist.rend()) {
        float cur = *rit;
        std::cout << cur << "\n";
        ++rit;                                                          // now backwards
    }

    std::cout << "Test 6: Initializer-list Constructor and String Type \n";     // Output:
    // abe
    ssuds::ArrayList<std::string> stlist = { "abe", "bob", "carl", "diana" };   // bob
    // carl
    for (unsigned int i = 0; i < stlist.size(); i++)                            // diana
        std::cout << stlist[i] << "\n";

    std::cout << "Test 7: Overload Method \n";                                  // Output:
    std::cout << stlist << "\n";                                                // [abe, bob, carl, diana]
} 