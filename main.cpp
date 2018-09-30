#include <iostream>
#include "binarytree.h"
#include "smartbinarytree.h"
#include <vector>
#include <stack>
#include <cmath>

using namespace DuckyTools;

int getLastQuantityInGeometricSeries(int sum/*, int a_k, int k*/) { // Only works with a_k = 1 and k = 2. Could be rewritten to work with anything.

    /* Function to figure out how many nodes there are going to be on
     * each step relative to how many nodes there are in total.
     * Uses the formula of a geometric series
     * (a_n = a1 * k^(n - 1)),
     * the formula of the sum of a geometric series
     * (S_n = a1 * ((k^n - 1) / (k - 1)))
     * and std::ceil to figure this out.
     */
    int S_n = static_cast<int>(std::pow(2, std::ceil(std::log(std::abs(sum + 1)) / std::log(double{2}))) - 1);
    double a_n = static_cast<double>(std::pow(2.f, ((std::log(std::abs(S_n + 1))/std::log(static_cast<double>(2))) - 1)));
    int diff = S_n - sum;
    return std::lround(a_n) - diff;
}

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
    auto tree = std::make_unique<SmartBinaryTree<int>>();
    tree->buildFromGround(10);
    std::cout << "See! A message!" << std::endl;
    tree.get()->printDepth();
    std::cout << "There are " << tree.get()->countNodes() << " nodes in the tree." << std::endl;
    tree->root = nullptr;
    std::cout << "See! Another message!" << std::endl;
    tree.get()->print();
    std::cout << "There are " << tree.get()->countNodes() << " nodes in the tree." << std::endl;

    return 0;
}
