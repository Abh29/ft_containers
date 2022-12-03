#include <iostream>
#include <vector>
#include "src/ft_vector.hpp"
#include "src/ft_map.hpp"

template <class T>
void print_vector(T &v, const std::string& s = "") {
    typename T::iterator b = v.begin();
    typename T::iterator e = v.end();
    std::cout << "begin " << s << " **********************" << std::endl;
    while (b != e)
        std::cout << *b++ << ", ";
    std::cout << "\nend " << s << " **********************" << std::endl;
};

template <class T>
void print_vector_size(T &v) {
    std::cout << "size: " << v.size() << ", capacity: " << v.capacity() << std::endl;
}

template <class T, class T2>
void info_vectors(T &v1, T2 &v2, const std::string& s1 = "", const std::string &s2 = ""){
	print_vector(v1, s1);
	print_vector_size(v1);
	print_vector(v2, s2);
	print_vector_size(v2);
}

template<class T>
bool vect_equal(std::vector<T>& vs, ft::vector<T>& vf){
	if (vs.size() != vf.size())
		return false;
	if (vs.capacity() != vf.capacity())
		return false;
	
	typename ft::vector<T>::iterator itf = vf.begin();
	typename std::vector<T>::iterator its = vs.begin();

	while (its != vs.end() && itf != vf.end())
		if (*its++ != *itf++)
			return false;
	if (its != vs.end() || itf != vf.end())
		return false;
	return true;
}


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


 template <class Vector>
    bool Ok(Vector v)
    {   // type corresponding to elements of Vector
        typedef typename Vector::value_type Scalar;
		(void)v;

        bool ok = true;             // initialize testing flag

        Vector x;                   // use the default constructor
        ok &= (x.size() == 0);      // test size for an empty vector
        Vector y(2);                // use the sizing constructor
        ok &= (y.size() == 2);      // size for an vector with elements

        // non-const access to the elements of y
        size_t i;
        for(i = 0; i < 2; i++)
            y[i] = Scalar(i);

        const Vector z(y);          // copy constructor
        x.resize(2);                // resize
        x = z;                      // vector assignment

        // use the const access to the elements of x
        // and test the values of elements of x, y, z
        for(i = 0; i < 2; i++)
        {   ok &= (x[i] == Scalar(i));
            ok &= (y[i] == Scalar(i));
            ok &= (z[i] == Scalar(i));
        }
        return ok;
}

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

int main2(int argc, char** argv) {

	std::vector<int> sv;

	sv.push_back(1);
	sv.push_back(2);
	sv.push_back(3);
	sv.push_back(4);
	sv.push_back(5);

	ft::vector<int> fv;
	
	fv.push_back(1);
	fv.push_back(2);
	fv.push_back(3);
	fv.push_back(4);
	fv.push_back(5);

	std::cout << vect_equal(sv, fv) << std::endl;
	
	std::vector<int> sv2;
	ft::vector<int> fv2;

	sv2.insert(sv2.begin(), sv.begin(), sv.end());
	fv2.insert(fv2.begin(), fv.begin(), fv.end());

	std::cout << vect_equal(sv2, fv2) << std::endl;

	// info_vectors(sv2, fv2, "sv2", "fv2");

	sv2.insert(sv2.begin(), 4, -5);
	fv2.insert(fv2.begin(), 4, -5);

	std::cout << vect_equal(sv2, fv2) << std::endl;

	sv2.insert(sv2.begin() + 3, 4, -3);
	fv2.insert(fv2.begin() + 3, 4, -3);

	std::cout << vect_equal(sv2, fv2) << std::endl;

	sv2.insert(sv2.end(), 4, 13);
	fv2.insert(fv2.end(), 4, 13);

	std::cout << vect_equal(sv2, fv2) << std::endl;

	sv2.insert(sv2.end() - 1, 4, -4);
	fv2.insert(fv2.end() - 1, 4, -4);

	std::cout << vect_equal(sv2, fv2) << std::endl;

	info_vectors(sv2, fv2);

	sv2.resize(5, 13);
	fv2.resize(5, 13);

	// info_vectors(sv2, fv2, "sv2 resized", "fv2 resized");

	sv2.resize(8, 13);
	fv2.resize(8, 13);

	sv2.resize(7, 13);
	fv2.resize(7, 13);

	// info_vectors(sv2, fv2, "sv2 downsized", "fv2 downsized");

	// sv2.resize(11, 13);
	// fv2.resize(11, 13);

	// info_vectors(sv2, fv2, "sv2 resized", "fv2 resized");

	std::cout << Ok(fv) << std::endl;

	std::cout << (sv2 == sv2) << std::endl;
	std::cout << (sv2 == sv) << std::endl;

	// if (argc != 2)
	// {
	// 	std::cerr << "Usage: ./test seed" << std::endl;
	// 	std::cerr << "Provide a seed please" << std::endl;
	// 	std::cerr << "Count value:" << COUNT << std::endl;
	// 	return 1;
	// }

	// const int seed = 13;
	// srand(seed);

	// ft::vector<std::string> vector_str;
	// ft::vector<int> vector_int;
	// ft::vector<Buffer> vector_buffer;

	// for (int i = 0; i < COUNT; i++)
	// {
	// 	vector_buffer.push_back(Buffer());
	// }

	// for (int i = 0; i < COUNT; i++)
	// {
	// 	const int idx = rand() % COUNT;
	// 	vector_buffer[idx].idx = 5;
	// }
	// ft::vector<Buffer>().swap(vector_buffer);

	// try
	// {
	// 	for (int i = 0; i < COUNT; i++)
	// 	{
	// 		const int idx = rand() % COUNT;
	// 		vector_buffer.at(idx);
	// 		std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
	// 	}
	// }
	// catch(const std::exception& e)
	// {
	// 	//NORMAL ! :P
	// 	std::cout << "normal" << std::endl;
	// }
	
	// std::cout << std::endl;
	return (0);

}


// typedef struct Buffer
// {
// 	int idx;
// 	char buff[1000];
// }	t_buff;

// int main() {
	
// 	ft::vector<int> v;

// 	v.push_back(1);
// 	v.push_back(2);
// 	v.push_back(3);


// 	for(ft::vector<int>::iterator i = v.begin(); i != v.end(); i++)
// 		std::cout << *i << std::endl;



// 	return 0;
// }


int main() {

	ft::Red_Black_Tree<int> t1;
	
	ft::Red_Black_Tree<int>::iterator b, e;


	b = t1.begin();
	e = t1.end();

	std::cout << (b == e) << std::endl;


}



