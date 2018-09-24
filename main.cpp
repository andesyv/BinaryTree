#include <iostream>
#include "binarytree.h"
#include <vector>

int main()
{
    int randomArray[10];
    for (unsigned int i{0}; i < sizeof(randomArray)/sizeof(randomArray[0]); i++) {
        std::cout << "index " << i << " is: " << randomArray[i] << std::endl;
    }
    DuckyTools::BTree<char> tree{};
    /*for (int i{10}; i > 0; --i) {
        tree.insert(i);
    }*/
    for (auto item : "randomArray") {
        tree.insert(item);
    }

    // tree.intrav();

    for (auto item : tree.toVector()) {
        std::cout << item << std::endl;
    }

    return 0;
}
