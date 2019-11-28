//
// Created by Grayson on 10/16/19.
//

#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <string>
#include <queue>

template <class T>
class bounded_buffer {
public:
    explicit bounded_buffer(int size);
    void add_to_buffer(T t);
    T copy_first_item_from_buffer();
    void remove_first_item_from_buffer();
    bool isEmpty();
    bool isFull();
private:
    int size;
    std::queue<T> q;
};

template<class T>
void bounded_buffer<T>::add_to_buffer(T t) {
    if (q.size() == size) {
        throw "Buffer is full.";
    }
    q.push(t);
}

template<class T>
T bounded_buffer<T>::copy_first_item_from_buffer() {
    T copy = q.front();
    return copy;
}

template<class T>
void bounded_buffer<T>::remove_first_item_from_buffer() {
    q.pop();
}

template<class T>
bounded_buffer<T>::bounded_buffer(int size):size(size) {}

template<class T>
bool bounded_buffer<T>::isEmpty() {
    return q.empty();
}

template<class T>
bool bounded_buffer<T>::isFull() {
    return q.size() == size;
}


#endif //BOUNDED_BUFFER_H
