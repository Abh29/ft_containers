#include <iostream>
#include <vector>
#include "src/ft_vector.hpp"

// template <class T>
// void print_vector(std::vector<T> &v) {
//     typename std::vector<T>::iterator b = v.begin();
//     typename std::vector<T>::iterator e = v.end();
//     std::cout << "**********************" << std::endl;
//     while (b != e)
//         std::cout << **b++ << std::endl;
//     std::cout << "**********************" << std::endl;
// };

// template <class T>
// void print_vector_size(std::vector<T> &v) {
//     std::cout << "size: " << v.size() << ", capacity: " << v.capacity() << std::endl;
// }

// int main2() {
//     std::vector<int*> v;
//     ft::vector<int> fv;

//     int ints[] = {1, 2, 3, 4, 77};

//     v.push_back(ints);
//     v.push_back(ints + 1);
//     v.push_back(ints + 2);
//     v.push_back(ints + 3);

//     std::vector<int*> v2(v);

//     *v.at(1) = 42;

//     print_vector(v);

//     print_vector_size(v);

//     v.insert(v.end(), ints + 4);

//     print_vector(v);
    
//     print_vector_size(v);

//     // v.assign(2000, ints);

//     // print_vector_size(v);

//     int a = 5;
//     int b = 6;
//     int d;

//     d = a += b;

//     std::cout << a << " " << b << " " << d << std::endl;

//     std::is_integral<int> t;

// };


#include <iostream>
#include <string>
#include "src/ft_vector.hpp"
#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

int main(int argc, char** argv) {

	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::vector<Buffer> vector_buffer;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	std::cout << std::endl;
	return (0);

}
