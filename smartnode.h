/** A node class that uses smartpointers
 * for use in the SmartBinaryTree-class.
 *
 * @author andesyv
 */

#ifndef SMARTNODE_H
#define SMARTNODE_H

#include <memory>
#include <iostream>
#include <algorithm>
#include <stdexcept>

namespace DuckyTools{

// Forward declare treeclass
template <class U>
class SmartBinaryTree;



template <class T>
class SmartNode {

    friend SmartBinaryTree<T>;

private:
    SmartNode<T> *m_parent{}; // Using a normal pointer here because of circular dependancy, and it's easier to assign.
    std::unique_ptr<SmartNode<T>> m_vSub{};
    std::unique_ptr<SmartNode<T>> m_hSub{};
    T m_data{};

    // Something to consider including:
    // bool deleted{false}; // A marker if the node is "deleted": physically in the tree, but not counted.
public:
    static const bool AUTOBALANCE{false}; // Automaticly balance the tree while inserting?

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
                if (AUTOBALANCE) {
                    balance(m_hSub);
                }
            } else {
                m_hSub = std::make_unique<SmartNode<T>>(data, this);
            }
        } else {
            if (m_vSub) {
                m_vSub->insert(data);
                if (AUTOBALANCE) {
                    balance(m_vSub);
                }
            } else {
                m_vSub = std::make_unique<SmartNode<T>>(data, this);
            }
        }
    }

    /** A balancing function that balances out
     * the tree from the specified node.
     *
     * @brief Balances out the tree
     * @param t The subtree to balance
     */
    static void balance(std::unique_ptr<SmartNode<T>> &t) {
        if (!t) {
            return;
        }

        if (t->m_vSub && t->m_hSub) {
            if (t->m_vSub->getDepth() - t->m_hSub->getDepth() > 1) {
                // Left subtree is 2 or more deeper than right
                if (t->m_vSub->m_vSub && t->m_vSub->m_hSub) {
                    if (t->m_vSub->m_vSub->getDepth() >= t->m_vSub->m_hSub->getDepth()) {
                        rotate(t, true);
                    } else {
                        doubleRotate(t, true);
                    }
                } else {
                    return;
                }
            } else if (t->m_hSub->getDepth() - t->m_vSub->getDepth() > 1) {
                // Right subtree is 2 or more deeper than left
                if (t->m_hSub->m_vSub && t->m_hSub->m_hSub) {
                    if (t->m_hSub->m_hSub->getDepth() >= t->m_hSub->m_vSub->getDepth()) {
                        rotate(t, false);
                    } else {
                        doubleRotate(t, false);
                    }
                } else {
                    return;
                }
            }
        } else {
            // leftsub and/or rightsub of node doesn't exist. Return.
            return;
        }
    }

    /** Rotates the subtree of the given node k2
     *
     * @param k2 The startnode of the subtree to rotate
     * @param clockwise Whether to rotate clockwise or
     * counter clockwise. Defaults to true
     */
    static void rotate(std::unique_ptr<SmartNode<T>> &k2, bool clockwise = true) {
        if (!k2) {
            return;
        }

        if (clockwise) {
            std::unique_ptr<SmartNode<T>> k1 = std::move(k2->m_vSub);

            if (!k1) {
                return;
            }

            k2->m_vSub = std::move(k1->m_hSub);
            k1->m_hSub = std::move(k2);

            k2 = std::move(k1);
        } else {
            std::unique_ptr<SmartNode<T>> k1 = std::move(k2->m_hSub);

            if (!k1) {
                return;
            }

            k2->m_hSub = std::move(k1->m_vSub);
            k1->m_vSub = std::move(k2);

            k2 = std::move(k1);
        }
    }

    /** Performs a double rotation of the subtree
     *
     * @param k3 The startnode of the subtree to rotate
     * @param clockwise Whether to rotate clockwise or
     * counter clockwise. Defaults to true
     */
    static void doubleRotate(std::unique_ptr<SmartNode<T>> &k3, bool clockwise = true) {
        if (!k3) {
            return;
        }

        if (clockwise) {
            rotate(k3->m_vSub, false);
            rotate(k3, true);
        } else {
            rotate(k3->m_hSub, true);
            rotate(k3, false);
        }
    }

    /**
     * Returns a pointer to the first occurence that matches data.
     *
     * @param data The data to search for
     * @return Pointer to the first occurrence. Nullptr if none found
     */
    SmartNode<T>* search(const T &data) {
        if (m_data == data) {
            return this;
        } else if (m_data < data) {
            if (m_hSub) {
                return m_hSub->search(data);
            } else {
                return nullptr;
            }
        } else {
            if (m_vSub) {
                return m_vSub->search(data);
            } else {
                return nullptr;
            }
        }
    }

    SmartNode<T>* findSmallest() {
        if (m_vSub) {
            return m_vSub->findSmallest();
        } else {
            return this;
        }
    }

    // Preorder traversal
    void preTrav() {
        std::cout << m_data << std::endl;

        if (m_vSub) {
            m_vSub.get()->preTrav();
        }

        if (m_hSub) {
            m_hSub.get()->preTrav();
        }
    }

    // Inorder traversal
    void inTrav() {
        if (m_vSub) {
            m_vSub.get()->inTrav();
        }

        std::cout << m_data << std::endl;

        if (m_hSub) {
            m_hSub.get()->inTrav();
        }
    }

    // Postorder traversal
    void postTrav() {
        if (m_vSub) {
            m_vSub.get()->postTrav();
        }

        if (m_hSub) {
            m_hSub.get()->postTrav();
        }

        std::cout << m_data << std::endl;
    }

    unsigned int countNodesInternal() {
        return ((m_vSub) ? m_vSub.get()->countNodesInternal() : 0)
            + ((m_hSub) ? m_hSub.get()->countNodesInternal() : 0)
            + 1;
    }

    unsigned int getDepth(unsigned int currentDepth = 0) {
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


    ~SmartNode() {
        std::cout << "Destructed!" << std::endl;
    }

private:
    // Don't want anyone but the tree class to be able to remove, or they might delete the root and cause errors.
    void remove(const T &data) {
        // Search for the node to use

        if (m_data == data) {
            // Should do the remove on the node before, not the node that shall be removed.
            // So if this is true, then this is the root.

            // Root deletion is handled by the tree, so this is definetively an error.
            throw std::runtime_error{"Root deletion activated on a node instead of on the tree"};
        }

        if (m_data < data) {
            if (m_hSub) {
                if (m_hSub->m_data == data) {
                    // Match found, continue deleting.
                    removeLeftOrRight(false);
                } else {
                    m_hSub->remove(data);
                }
            } else {
                // The data to search for isn't in the tree. Abort.
                return;
            }
        } else {
            if (m_vSub) {
                if (m_vSub->m_data == data) {
                    // Match found, continue deleting.
                    removeLeftOrRight(true);
                } else {
                    m_vSub->remove(data);
                }
            } else {
                // The data to search for isn't in the tree. Abort.
                return;
            }
        }
    }

    void removeLeftOrRight(bool left) {
        /* At this point the function should be running on the parent of the
         * node that is going to be deleted, and "left" has been set to
         * either true or false.
         */

        // Figure out what deletion method and do the deletion method:
        if ((left ? m_vSub : m_hSub)->m_vSub && (left ? m_vSub : m_hSub)->m_hSub) {
            // Node that is going to be deleted has two children:
            removeWithTwoChildren(left);
        } else if ((left ? m_vSub : m_hSub)->m_vSub || (left ? m_vSub : m_hSub)->m_hSub) {
            // Node that is going to be deleted has 1 children:
            removeWithOneChild(left);
        } else {
            // Node that is going to be deleted has no children:
            removeWithNoChildren(left);
        }
    }

    void removeWithNoChildren(bool left) {
        // Find out if it's the left or right child of the parent:

        (left ? m_vSub : m_hSub) = nullptr; /// Smart pointers baby!!

        /// (Wow, this was way easier than the last way of doing it)
    }

    void removeWithOneChild(bool left) {

        // Set parent (Not sure if I am going to need a parent pointer anymore)
        if (left) {
            if (!m_vSub) { /// Even some error handling! :o
                throw std::logic_error{"Dereferencing a nullpointer"};
            }

            if (m_vSub->m_vSub) {
                m_vSub->m_vSub->m_parent = m_vSub->m_parent;
            } else {
                m_vSub->m_hSub->m_parent = m_vSub->m_parent;
            }

            // Swap. This destroys the node that is up for deletion in the process.
            m_vSub = std::move((m_vSub->m_vSub) ? m_vSub->m_vSub : m_vSub->m_hSub);
        } else {
            if (!m_hSub) {
                throw std::logic_error{"Dereferencing a nullpointer"};
            }

            if (m_hSub->m_vSub) {
                m_hSub->m_vSub->m_parent = m_hSub->m_parent;
            } else {
                m_hSub->m_hSub->m_parent = m_hSub->m_parent;
            }

            // Swap. This destroys the node that is up for deletion in the process.
            m_hSub = std::move((m_hSub->m_vSub) ? m_hSub->m_vSub : m_hSub->m_hSub);
        }
    }

    void removeWithTwoChildren(bool left) {
        if (!m_vSub && !m_hSub) {
            throw std::logic_error{"removeWithTwoChildren() called on node without two children"};
        }

        SmartNode<T> *smallestRight{ (left ? m_vSub : m_hSub)->m_hSub->findSmallest() };

        // Swap the two nodes' values
        std::swap((left ? m_vSub : m_hSub)->m_data, smallestRight->m_data);

        // Remove the now switched node using one of the old deletion methods. (Because it will only have 1 child)
        smallestRight->m_parent->removeLeftOrRight(smallestRight->m_parent->m_vSub.get() == smallestRight); // I did get to use the parent pointer afterall.
    }


};
}

#endif // SMARTNODE_H
