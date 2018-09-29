#ifndef SMARTBINARYTREE_H
#define SMARTBINARYTREE_H

#include "smartnode.h"
#include <stack>
#include <cmath>

namespace DuckyTools{
template <class T>
class SmartBinaryTree {
public:
    std::unique_ptr<SmartNode<T>> root{};

public:
    SmartBinaryTree() {}
    /*SmartBinaryTree(const T &data)
        : root{std::make_unique<SmartNode<T>>(data)} {
    }*/

    void buildFromGround(int totalNodes) {
        std::stack<std::unique_ptr<SmartNode<int>>> workingStack{};
        while (totalNodes > 0) {
            int nodesInCurrentRow = getLastQuantityInGeometricSeries(totalNodes);
            for (int i{0}; i < nodesInCurrentRow; i++) {
                auto newNode = new SmartNode<int>();
                if (!workingStack.empty()) {
                    newNode->m_vSub = std::move(workingStack.top());
                    workingStack.pop();
                }
                if (!workingStack.empty()) {
                    newNode->m_hSub = std::move(workingStack.top());
                    workingStack.pop();
                }
                workingStack.push(std::unique_ptr<SmartNode<int>>{newNode});
            }
            totalNodes -= nodesInCurrentRow;
        }
        if (!workingStack.empty()) {
            root = std::move(workingStack.top());
            workingStack.pop(); // just to keep the code clean.
        }
    }

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
};
}

#endif // SMARTBINARYTREE_H
