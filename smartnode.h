#ifndef SMARTNODE_H
#define SMARTNODE_H

#include <memory>
#include <iostream>
#include <algorithm>

namespace DuckyTools{
template <class T>
class SmartNode {
private:
    SmartNode<T> *m_parent{}; // Using a normal pointer here because of circular dependancy, and it's easier to assign.

public:
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
    SmartNode(const T &data, SmartNode<T> *parent) : m_data{data}, m_parent{parent} {
        std::cout << "Constructed!" << std::endl;
    }

    void insert (const T &data) {
        if (m_data <= data) {
            if (m_hSub) {
                m_hSub->insert(data);
            } else {
                m_hSub = std::make_unique<SmartNode<T>>(data, this);
            }
        } else {
            if (m_vSub) {
                m_vSub->insert(data);
            } else {
                m_vSub = std::make_unique<SmartNode<T>>(data, this);
            }
        }
    }

    void preIntrav() {
        std::cout << m_data << std::endl;

        if (m_vSub) {
            m_vSub.get()->preIntrav();
        }
        if (m_hSub) {
            m_hSub.get()->preIntrav();
        }
    }

    void postIntrav() {
        if (m_vSub) {
            m_vSub.get()->postIntrav();
        }
        if (m_hSub) {
            m_hSub.get()->postIntrav();
        }

        std::cout << m_data << std::endl;
    }

    unsigned int countNodesInternal() {
        return ((m_vSub) ? m_vSub.get()->countNodesInternal() : 0)
            + ((m_hSub) ? m_hSub.get()->countNodesInternal() : 0)
            + 1;
    }

    unsigned int getDepth(unsigned int currentDepth) {
        return std::max(
                    (m_vSub) ? m_vSub.get()->getDepth(currentDepth + 1) : currentDepth,
                    (m_hSub) ? m_hSub.get()->getDepth(currentDepth + 1) : currentDepth
                        );
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
