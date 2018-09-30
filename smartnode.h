#ifndef SMARTNODE_H
#define SMARTNODE_H

#include <memory>
#include <iostream>

namespace DuckyTools{
template <class T>
class SmartNode {
public:
    std::weak_ptr<SmartNode<T>> m_parent{};
    std::unique_ptr<SmartNode<T>> m_vSub{};
    std::unique_ptr<SmartNode<T>> m_hSub{};
    T m_data{};

public:
    SmartNode() {
        std::cout << "Constructed!" << std::endl;
    }
    SmartNode(const T &data) : m_data{data} {
        std::cout << "Constructed!" << std::endl;
    }

    unsigned int countNodesInternal() {
        return ((m_vSub) ? m_vSub.get()->countNodesInternal() : 0)
            + ((m_hSub) ? m_hSub.get()->countNodesInternal() : 0)
            + 1;
    }

    void printDepth(int depth) {
        std::cout << std::string{""}.append(static_cast<unsigned int >(4 * depth), ' ')
                  << m_data << std::endl;
        if (m_vSub) {
            m_vSub.get()->printDepth(depth + 1);
        }
        if (m_hSub) {
            m_hSub.get()->printDepth(depth + 1);
        }
    }

    void print() {
        if (m_vSub) {
            m_vSub.get()->print();
        }
        if (m_hSub) {
            m_hSub.get()->print();
        }
        std::cout << m_data << std::endl;
    }


    ~SmartNode() {
        std::cout << "Destructed!" << std::endl;
    }
};
}

#endif // SMARTNODE_H
