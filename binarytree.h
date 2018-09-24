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
        }
    }

    void remove(T data) {
        // Search for the node you want to remove
        Node<T>* nodeToDelete{search(data)};
        if (nodeToDelete != nullptr) {

            // Find the nodes right, most left node. This will be the new tree-root.
            Node<T>* newBase{nullptr};
            if (nodeToDelete->m_hSub != nullptr) {
                newBase = nodeToDelete->m_hSub->findMostLeft();
                // Also find the parent of that node.
                Node<T>* baseParent = newBase->m_parent; /// Should'nt need to check for nullptr here, as this is down in the tree.

                // Set the parents left to the root-nodes right
                baseParent->m_vSub = newBase->m_hSub;
                if (baseParent->m_vSub != nullptr) {
                    baseParent->m_vSub->m_parent = baseParent;
                }

                // Set the left for the deleted node to be the left for the root-node.
                newBase->m_vSub = nodeToDelete->m_vSub;
                if (newBase->m_vSub != nullptr) {
                    newBase->m_vSub->m_parent = newBase;
                }

                // Set the right for the deleted node to be the right for the root-node.
                newBase->m_hSub = nodeToDelete->m_hSub;
                if (newBase->m_hSub != nullptr) {
                    newBase->m_hSub->m_parent = newBase;
                }

                if (nodeToDelete->m_parent != nullptr) {
                    newBase->m_parent = nodeToDelete->m_parent; /// Only if nodeToDelete->m_parent is not nullptr!
                } else {
                    newBase->m_parent = nullptr;
                }

                // Set the root, you idiot!
                root = newBase;
            } else if (nodeToDelete->m_vSub != nullptr) {
                // What happens if there are no nodes on the
                // right side of the node we want to delete?

                if (nodeToDelete->m_parent != nullptr) {
                    if (nodeToDelete->m_parent->m_data < nodeToDelete->m_vSub->m_data) {
                        nodeToDelete->m_parent->m_hSub = nodeToDelete->m_vSub;
                    } else {
                        nodeToDelete->m_parent->m_vSub = nodeToDelete->m_vSub;
                    }
                    nodeToDelete->m_vSub->m_parent = nodeToDelete->m_parent;
                } else {
                    root = nodeToDelete->m_vSub;
                    nodeToDelete->m_vSub->m_parent = nullptr;
                }
            } else {
                if (nodeToDelete->m_parent != nullptr) {
                    if (nodeToDelete->m_parent->m_vSub == nodeToDelete) {
                        nodeToDelete->m_parent->m_vSub = nullptr;
                    } else {
                        nodeToDelete->m_parent->m_hSub = nullptr;
                    }
                } else {
                    root = nullptr;
                }
            }

            delete nodeToDelete;

        } else {
            // cannot find the node to delete. Abort
        }


    }

    void intrav() {
        if (root != nullptr)
            root->intrav();
    }

    Node<T>* search(const T &data) {
        if (root != nullptr) {
            root->search(data);
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
