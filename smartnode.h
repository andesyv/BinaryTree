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

    }

    ~SmartNode() {
        std::cout << "Destructed!" << std::endl;
    }
};
}

#endif // SMARTNODE_H
