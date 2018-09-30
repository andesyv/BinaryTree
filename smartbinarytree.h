#ifndef SMARTBINARYTREE_H
#define SMARTBINARYTREE_H

#include "smartnode.h"
#include <stack>
#include <cmath>
#include <limits>

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

    unsigned int countNodes() {
        if (root) {
            return root.get()->countNodesInternal();
        } else {
            return 0;
        }
    }

    void printDepth() {
        if (root) {
            root.get()->printDepth(0);
        }
    }

    void print() {
        if (root) {
            root.get()->print();
        }
    }

    void buildFromGround(int totalNodes) {
        int index{0}; // Just to diffentiate the different nodes.
        std::stack<std::unique_ptr<SmartNode<int>>> workingStack{};
        while (totalNodes > 0) {
            int nodesInCurrentRow = getLastQuantityInGeometricSeries(totalNodes, 1, 2);
            std::stack<std::unique_ptr<SmartNode<int>>> newNodes{};

            // Add new nodes on current layer.
            for (int i{0}; i < nodesInCurrentRow; i++) {
                auto newNode = new SmartNode<int>(++index);
                if (!workingStack.empty()) {
                    newNode->m_vSub = std::move(workingStack.top());
                    workingStack.pop();
                }
                if (!workingStack.empty()) {
                    newNode->m_hSub = std::move(workingStack.top());
                    workingStack.pop();
                }
                newNodes.push(std::unique_ptr<SmartNode<int>>{newNode});
            }

            // Cleanup
            workingStack = std::move(newNodes);
            totalNodes -= nodesInCurrentRow;
        }
        if (!workingStack.empty()) {
            root = std::move(workingStack.top());
            workingStack.pop(); // just to keep the code clean.
        }
    }

    /// Calculates how many nodes there are going to be on the last step relative to how many nodes there are in total
    static int getLastQuantityInGeometricSeries(int sum, float a1, float k) {
        /* Function to figure out how many nodes there are going to be on
         * each step relative to how many nodes there are in total.
         * Uses the formula of a geometric series
         * (a_n = a1 * k^(n - 1)),
         * the formula of the sum of a geometric series
         * (S_n = a1 * ((k^n - 1) / (k - 1)))
         * and std::ceil to figure this out.
         */

        // Sum of a geometric series is not valid for k == 1, so just return 1.
        if (k < (1 + std::numeric_limits<float>::epsilon()) && k > (1 - std::numeric_limits<float>::epsilon())) {
            return 1;
        }

        float n_0 = (std::log(std::abs(sum * (k - 1) + a1)) - std::log(std::abs(a1)))/(std::log(std::abs(k)));
        int S_n = static_cast<int>(a1 * ((std::pow(k, std::ceil(n_0)) - 1)/(k - 1)));
        double a_n = static_cast<double>(a1 * std::pow(k, (std::ceil(n_0) - 1)));
        int diff = S_n - sum;
        return std::lround(a_n) - diff;
    }
};
}

#endif // SMARTBINARYTREE_H
