#pragma once
template <typename T> class Vector {
public:
    T* arr;
    Vector();
    void push(T data);
    void push(T data, int index);
    const T get(int index) const;
    const T get() const;
    T pop();
    void pop(int index);
    const int getLength() const;
    const int getSize() const;
    const void print() const;
    T operator [](int i) const;
    void operator=(T data);
private:
    int max_length;
    int cur_length;
};

template <typename T>
Vector<T>::Vector() {
    arr = new T[1];
    max_length = 1;
    cur_length = 0;
}

template <typename T>
void Vector<T>::push(T data) {
    if (cur_length == max_length) {
        T* temp = new T[2 * max_length];
        for (int i = 0; i < max_length; i++) {
            temp[i] = arr[i];

        }

        delete[] arr;
        max_length *= 2;
        arr = temp;

    }
    arr[cur_length] = data;
    cur_length++;

}

template <typename T>
void Vector<T>::push(T data, int index) {
    if (index == max_length) {
        push(data);

    }
    else {
        arr[index] = data;

    }
}

template <typename T>
T Vector<T>::pop() {
    cur_length--;
    return arr[cur_length];
}

template <typename T>
void Vector<T>::pop(int index) {
    if ((index < 0) || (index >= cur_length)) {
        throw "pop: Index out of range";
    }
    for (int i = index; i < cur_length - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    --cur_length;
}

template <typename T>
const T Vector<T>::get() const {
    return arr[cur_length - 1];
}

template <typename T>
const T Vector<T>::get(int index) const {
    if (index < cur_length) {
        return arr[index];

    }
}

template <typename T>
const int Vector<T>::getLength() const {
    return cur_length;
}

template <typename T>
const int Vector<T>::getSize() const {
    return max_length;
}
template <typename T>
const void Vector<T>::print() const {
    for (int i = 0; i < cur_length; i++) {
        printf("%p", arr[i]);
    }
}

template <typename T>
T Vector<T>::operator [](int i) const {
    return arr[i];
}

template <typename T>
void Vector<T>::operator=(T data) {
    this->push(data);
}
