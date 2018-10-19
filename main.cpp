#include <iostream>
#include "binarytree.h"
#include "smartbinarytree.h"
#include <vector>
#include <stack>
#include <cmath>

using namespace DuckyTools;

int main()
{
    SmartBinaryTree<int> tree{7, 5, 5, 6, 12, 3, 9, 1, 2, 15, 1, 18, 8, 22, 13, -2};
    // SmartBinaryTree<int> tree{};

    // tree.buildFromGround(10);

    /*
    tree.insert(7);
    tree.insert(5);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(3);
    tree.insert(9);
    tree.insert(1);
    tree.insert(2);
    //*/

    std::cout << "See! A message!" << std::endl;
    tree.printDepth();
    std::cout << "There are " << tree.countNodes() << " nodes in the tree." << std::endl;
    std::cout << "There is " << tree.freeSpace() << " free space(s) in the tree!" << std::endl;

    tree.visualDepthPrint();

    /*
    tree.remove(5);

    tree.printDepth();
    std::cout << "There are " << tree.countNodes() << " nodes in the tree." << std::endl;
    std::cout << "There is " << tree.freeSpace() << " free space(s) in the tree!" << std::endl;

    tree.inTrav();
    std::cout << "And then...  " << std::endl;
    tree.inTrav();

    // tree.root = nullptr;
    std::cout << "See! Another message!" << std::endl;
    tree.print();
    std::cout << "There are " << tree.countNodes() << " nodes in the tree." << std::endl;
    //*/
    return 0;
}
