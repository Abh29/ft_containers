#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>
#include "src/ft_vector.hpp"

template <class T>
void print_vector(std::vector<T> &v) {
    typename std::vector<T>::iterator b = v.begin();
    typename std::vector<T>::iterator e = v.end();
    std::cout << "**********************" << std::endl;
    while (b != e)
        std::cout << **b++ << std::endl;
    std::cout << "**********************" << std::endl;
};

template <class T>
void print_vector_size(std::vector<T> &v) {
    std::cout << "size: " << v.size() << ", capacity: " << v.capacity() << std::endl;
}

int main() {
    std::vector<int*> v;
    ft::vector<int> fv;

    int ints[] = {1, 2, 3, 4, 77};

    v.push_back(ints);
    v.push_back(ints + 1);
    v.push_back(ints + 2);
    v.push_back(ints + 3);

    std::vector<int*> v2(v);

    *v.at(1) = 42;

    print_vector(v);

    print_vector_size(v);

    v.insert(v.end(), ints + 4);

    print_vector(v);
    
    print_vector_size(v);

    // v.assign(2000, ints);

    // print_vector_size(v);

    int a = 5;
    int b = 6;
    int d;

    d = a += b;

    std::cout << a << " " << b << " " << d << std::endl;

    std::is_integral<int> t;
    std::reverse_iterator<int> n;

}
   
