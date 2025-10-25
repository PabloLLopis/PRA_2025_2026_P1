#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T value;
    Node<T>* next;
    explicit Node(const T& v, Node<T>* n = nullptr) : value(v), next(n) {}
};

#endif // NODE_H


