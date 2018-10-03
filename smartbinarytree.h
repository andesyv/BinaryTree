#ifndef SMARTBINARYTREE_H
#define SMARTBINARYTREE_H

#include "smartnode.h"
#include <stack>
#include <cmath>
#include <limits>
#include <queue>

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

    void insert(const T &data) {
        if (!root) {
            root = std::make_unique<SmartNode<T>>(data);
        } else {
            root->insert(data);
        }
    }

    void remove(T data) {
        if (root) {
            if (root->m_data == data) {
                removeRoot();
            } else {
                root->remove(data);
            }
        }
    }

    // Preorder traversal
    void preTrav() {
        if (root) {
            root.get()->preTrav();
        }
    }

    // Inorder traversal
    void inTrav() {
        if (root) {
            root.get()->inTrav();
        }
    }

    // Postorder traversal
    void postTrav() {
        if (root) {
            root.get()->postTrav();
        }
    }

    unsigned int countNodes() {
        if (root) {
            return root.get()->countNodesInternal();
        } else {
            return 0;
        }
    }

    unsigned int getDepth() {
        if (root) {
            return root.get()->getDepth(1);
        } else {
            return 0;
        }
    }

    int capacity() {
        /* This uses the function for the sum of a
         * geometric series to calculate capacity.
         */
        return std::pow(2, getDepth()) - 1;
    }

    int freeSpace() {
        return capacity() - countNodes();
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

    // Builds the tree from the ground up but with
    void buildFromGround(int totalNodes) {
        int index{0}; // Just to diffentiate the different nodes.
        std::queue<std::unique_ptr<SmartNode<int>>> workingStack{};
        while (totalNodes > 0) {
            int nodesInCurrentRow = getLastQuantityInGeometricSeries(totalNodes, 1, 2);
            std::queue<std::unique_ptr<SmartNode<int>>> newNodes{};

            // Add new nodes on current layer.
            for (int i{0}; i < nodesInCurrentRow; i++) {
                auto newNode = new SmartNode<int>(++index);
                if (!workingStack.empty()) {
                    newNode->m_vSub = std::move(workingStack.front());
                    workingStack.pop();
                }
                if (!workingStack.empty()) {
                    newNode->m_hSub = std::move(workingStack.front());
                    workingStack.pop();
                }
                newNodes.push(std::unique_ptr<SmartNode<int>>{newNode});
            }

            // Cleanup
            workingStack = std::move(newNodes);
            totalNodes -= nodesInCurrentRow;
        }
        if (!workingStack.empty()) {
            root = std::move(workingStack.front());
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
        if (std::abs(k) < (1 + std::numeric_limits<float>::epsilon())) {
            return 1;
        }

        float n_0 = (std::log(std::abs(sum * (k - 1) + a1)) - std::log(std::abs(a1)))/(std::log(std::abs(k)));
        int S_n = static_cast<int>(a1 * ((std::pow(k, std::ceil(n_0)) - 1)/(k - 1)));
        double a_n = static_cast<double>(a1 * std::pow(k, (std::ceil(n_0) - 1)));
        int diff = S_n - sum;
        return std::lround(a_n) - diff;
    }

private:
    void removeRoot() {
        /* Run only when deleting the root node.
         *
         * I need to duplicate this code because when deleting
         * a node the removal function runs on the node above,
         * but if I delete the root the function needs to run
         * on the tree instead. Most probably a better way to
         * solve this, but atleast my node removal function
         * is pretty straightforward and somewhat efficient.
         *
         * (Could also place the functions in the tree class
         * and instantiate them on the individual nodes)
         */
        if (root->m_vSub && root->m_hSub) {
            removeRootTwoChildren();
        } else if (root->m_vSub || root->m_hSub) {
            removeRootOneChild();
        } else {
            removeRootNoChildren();
        }
    }

    void removeRootNoChildren() {
        root = nullptr;
    }

    void removeRootOneChild() {
        if (root->m_vSub) {
            root->m_vSub->m_parent = nullptr; // Set parent
            root = std::move(root->m_vSub);
        } else {
            root->m_hSub->m_parent = nullptr; // Set parent
            root = std::move(root->m_hSub);
        }
    }

    void removeRootTwoChildren() {
        if (!root->m_vSub && !root->m_hSub) {
            throw std::logic_error{"removeRootTwoChildren called but root doesn't have two children."};
        }

        SmartNode<T> *smallestRight{ root->m_hSub->findSmallest() };

        // Swap the two nodes' values
        std::swap(root->m_data, smallestRight->m_data);

        // Remove the now switched node using one of the old deletion methods. (Because it will only have 1 or 0 children)
        smallestRight->m_parent->removeLeftOrRight(smallestRight->m_parent->m_vSub.get() == smallestRight); // I did get to use the parent pointer afterall.
    }
};
}

#endif // SMARTBINARYTREE_H
