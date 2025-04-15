#include <stdlib.h>
#include <iostream>
#include <exception>
#include <stdexcept>

template <class T>
class vector {
private:
    T *v; // dynamic array of elements type T
    int s; // size

public:
  //default constructor
    vector() {
        this->s = 0;
        this->v = NULL;
    }
//CC
    vector(const vector<T> &other) {
        this->s = other.s;
        this->v = new T[this->s];
        for (int i = 0; i < this->s; i++)
            this->v[i] = other.v[i];
    }
//AOO
    vector<T> &operator=(const vector<T> &other) {
        if (this != &other) {
            delete[] this->v;
            this->s = other.s;
            this->v = new T[this->s];
            for (int i = 0; i < this->s; i++)
                this->v[i] = other.v[i];
        }
        return *this;
    }
//destructor
    ~vector() {
        delete[] this->v;
    }
//size function
    int size() {
        return this->s;
    }
//add element to the end
    void push_back(T ele) {
        T *temp = new T[++this->s];
        for (int i = 0; i < this->s - 1; i++)
            temp[i] = this->v[i];

        delete[] this->v;
        this->v = temp;
        this->v[this->s - 1] = ele;
    }
//poins to array of elements 'index' type 'T', performs address arithmetic
    T operator[](int index) {
        return this->v[index];
    }
//checks if vector is within size
    T at(int index) {
        if (index >= 0 && index < this->s) {
            return this->v[index];
        } else {
            throw std::out_of_range("out of my vector bounds");
        }
    }
};
