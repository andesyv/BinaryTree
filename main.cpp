#include <iostream>
#include "binarytree.h"
#include "smartbinarytree.h"
#include <vector>
#include <stack>
#include <cmath>

using namespace DuckyTools;

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

//    DuckyTools::BTree<char> tree{};
//    for (auto item : "alfabetet") {
//        tree.insert(item);
//    }
    /*
    tree.insert(7);
    tree.insert(2);
    tree.insert(1);
    tree.insert(4);
    tree.insert(14);
    tree.insert(8);
    tree.insert(9);
    tree.insert(12);*/

    /*
    for (auto item : tree.toVector()) {
        std::cout << item << std::endl;
    }
    */

//    std::stack<std::unique_ptr<SmartNode<int>>> workingStack{};
//    int nodesLeft = 10;
//    while (nodesLeft > 0) {
//        int nodesInCurrentRow = getLastQuantityInGeometricSeries(nodesLeft);
//        for (int i{0}; i < nodesInCurrentRow; i++) {
//            auto newNode = new SmartNode<int>();
//            if (!workingStack.empty()) {
//                newNode->m_vSub = std::move(workingStack.top());
//                workingStack.pop();
//            }
//            if (!workingStack.empty()) {
//                newNode->m_hSub = std::move(workingStack.top());
//                workingStack.pop();
//            }
//            workingStack.push(std::unique_ptr<SmartNode<int>>{newNode});
//        }
//        nodesLeft -= nodesInCurrentRow;
//    }
//    std::unique_ptr<SmartNode<int>> root{};
//    if (!workingStack.empty()) {
//        root = std::move(workingStack.top());
//    }
//    std::cout << "Hello, this is message!" << std::endl;
//    root = nullptr;
//    std::cout << "Hello, this is another message!" << std::endl;
    // SmartBinaryTree<int> tree{};
    // tree.buildFromGround(10);
    SmartBinaryTree<int> tree{7, 5, 6, 12, 3, 9, 1, 2};

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
    // tree.inTrav();



    tree.printDepth();
    std::cout << "There are " << tree.countNodes() << " nodes in the tree." << std::endl;
    std::cout << "There is " << tree.freeSpace() << " free space(s) in the tree!" << std::endl;

    tree.inTrav();
    std::cout << "And then...  " << std::endl;
    tree.inTrav();

    tree.root = nullptr;
    std::cout << "See! Another message!" << std::endl;
    tree.print();
    std::cout << "There are " << tree.countNodes() << " nodes in the tree." << std::endl;

    return 0;
}
