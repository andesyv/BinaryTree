#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <vector>

// A binary tree-node.

namespace DuckyTools {
template <class T>
class Node {

    template <class U>
    friend class BTree;

private:   
    // static unsigned int m_index;
    Node<T>* m_vSub{nullptr};
    Node<T>* m_hSub{nullptr};

    void addToVector(std::vector<T> &v) {
        if (m_vSub)
            m_vSub->addToVector(v);
        v.push_back(m_data);
        if (m_hSub) {
            m_hSub->addToVector(v);
        }
    }
public:
    T m_data{};
public:
    // Default constructor
    Node(T data = T{}) : m_data{data} {
        // m_index++;
    }
    ~Node() {
        // m_index--;
    }

//    int getIndex() {
//        return m_index;
//    }

    void insert(const T &data) {
        if (data < m_data) {
            if (m_vSub == nullptr) {
                m_vSub = new Node<T>{data};
            } else {
                m_vSub->insert(data);
            }
        } else {
            if (m_hSub == nullptr) {
                m_hSub = new Node<T>{data};
            } else {
                m_hSub->insert(data);
            }
        }
    }

    void intrav() {
        if (m_vSub)
            m_vSub->intrav();
        std::cout << m_data << std::endl;
        if (m_hSub) {
            m_hSub->intrav();
        }
    }
};
}

#endif // TREENODE_H
