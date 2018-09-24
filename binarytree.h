#ifndef BINARYTREE_H
#define BINARYTREE_H

namespace DuckyTools {
template <class T>
class BTree;
}

#include "treenode.h"
#include <vector>

namespace DuckyTools {
template <class T>
class BTree {
private:
    unsigned int count{0};
public:
    Node<T>* root{nullptr};
    BTree() {

    }

    void insert(const T &data) {
        if (root == nullptr) {
            root = new Node<T>{data};
            count++;
        } else {
            root->insert(data);
            /*
            if (data < root->m_data) {
                if (root->m_vSub == nullptr) {
                    root->m_vSub = new Node<T>{data};
                    count++;
                } else {
                    root->m_vSub->insert(data);
                }
            } else {
                if (root->m_hSub == nullptr) {
                    root->m_hSub = new Node<T>{data};
                    count++;
                } else {
                    root->m_hSub->insert(data);
                }
            }
            */
        }
    }

    void remove(T data) {
        // 1. Search for the node before the one you want to remove
        Node<T>* nodeToDelete{nullptr};

        // Find the node to delete
        nodeToDelete = find(data);
        // Find the nodes right, most left node. This will be the new tree-root.
        Node<T>* newBase = nodeToDelete->m_hSub->findMostLeft();
        // Also find the parent of that node.
        Node<T>* overBase = newBase->parent;

        // Set the parents left to the root-nodes right
        overBase->m_vSub = newBase->m_hSub;
        // Set the left for the deleted node to be the left for the root-node.
        newBase->m_vSub = nodeToDelete->m_vSub;
        // Set the right for the deleted node to be the right for the root-node.
        newBase->m_hSub = nodeToDelete->m_hSub;

    }

    void intrav() {
        if (root != nullptr)
            root->intrav();
    }

    Node<T>* search(const T &data, Node<T>* &parent) {
        if (root != nullptr) {
            root->search(data, parent);
        }
    }

    std::vector<T> toVector() {
        std::vector<T> v{};
        if (root != nullptr)
            root->addToVector(v);
        return v;
    }
};
}

#endif // BINARYTREE_H
