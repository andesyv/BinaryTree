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
        // search
        Node<T>* nodeToDelete{nullptr};
        Node<T>* nodeBefore{nullptr};

    }

    void intrav() {
        if (root != nullptr)
            root->intrav();
    }

    Node<T>* search(T data) {

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
