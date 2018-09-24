#include <iostream>
#include "binarytree.h"
#include <vector>

int main()
{
//    int randomArray[10];
//    for (unsigned int i{0}; i < sizeof(randomArray)/sizeof(randomArray[0]); i++) {
//        std::cout << "index " << i << " is: " << randomArray[i] << std::endl;
//    }
//    DuckyTools::BTree<char> tree{};
//    /*for (int i{10}; i > 0; --i) {
//        tree.insert(i);
//    }*/

    DuckyTools::BTree<char> tree{};
    for (auto item : "alfabetet") {
        tree.insert(item);
    }
    /*
    tree.insert(7);
    tree.insert(2);
    tree.insert(1);
    tree.insert(4);
    tree.insert(14);
    tree.insert(8);
    tree.insert(9);
    tree.insert(12);*/

    tree.intrav();
    std::cout << std::endl;

    tree.remove('a');
    tree.remove('a');

    tree.intrav();
    /*
    for (auto item : tree.toVector()) {
        std::cout << item << std::endl;
    }
    */

    return 0;
}
