#include <set>
#include "tester.hpp"
#include "../src/set.hpp"

template <class Ta>
std::string equalContent(
	const std::set<Ta> & stl_set,
	const ft::set<Ta> & ft_set
)
{
	typename ft::set<Ta>::const_iterator ft_it;
	typename std::set<Ta>::const_iterator stl_it;
	if (ft_set.size() != stl_set.size())
		return ("✘");
	stl_it = stl_set.begin();
	for(ft_it = ft_set.begin(); ft_it != ft_set.end(); ft_it++)
	{
		if (*ft_it != *stl_it)
			return ("✘");
		stl_it++;
	}
	return ("✔");
}

template <class Ta>
bool printsetAttributes(
	std::fstream& fs,
	std::set<Ta>& stl_set,
	ft::set<Ta>& ft_set
)
{
	/* STL Values */
	std::string stl_empty = ((stl_set.empty() == 1) ? "true" : "false");
	size_t stl_size = stl_set.size();
	size_t stl_max_size = stl_set.max_size();

	/* FT Values */
	std::string ft_empty = ((ft_set.empty() == 1) ? "true" : "false");
	size_t ft_size = ft_set.size();
	size_t ft_max_size = ft_set.max_size();

	/* FT Result compare values */
	bool empty = equalbool(ft_empty, stl_empty);
	bool size = equalbool(ft_size, stl_size);
	bool max_size = equalbool(ft_max_size, stl_max_size);
	std::string content = equalContent(stl_set, ft_set);
	
	fs << "\n══════════════════════════════════════════════════════════════\n";
	fs << "sets attributes : \n";
	fs << "STL : \n";
	fs << "Empty       : " << stl_empty  << std::endl;
	fs << "Size        : " << stl_size  << std::endl;
	fs << "Max size    : " << stl_max_size  << std::endl;
	fs << "Content     : [";
	
	typename std::set<Ta>::const_iterator stl_it;
	for (stl_it = stl_set.begin();  stl_it != stl_set.end(); stl_it++)
	{
		fs << "[";
		fs << *stl_it;
		fs << "]";
		fs << ", ";
	}
	fs << "]\n";

	fs << std::endl;

	fs << "FT : \n";
	fs << "Empty    [" << equal(ft_empty, stl_empty) << "]: " << ft_empty  << std::endl;
	fs << "Size     [" << equal(ft_size, stl_size) << "]: " << ft_size  << std::endl;
	fs << "Max size [" << equal(ft_max_size, stl_max_size) << "]: " << ft_max_size  << std::endl;

	fs << "Content  [" << content << "]: [";

	typename ft::set<Ta>::const_iterator ft_it;
	for(ft_it = ft_set.begin(); ft_it != ft_set.end(); ft_it++)
	{
		fs << "[";
		fs << *ft_it;
		fs << "]";
		fs << ", ";
	}
	fs << "]\n";

	fs << "══════════════════════════════════════════════════════════════\n";

	/* Error case */
	if (empty == false)
		return (false);
	else if (size == false)
		return (false);
	else if (max_size == false)
		return (false);
	else if (content == "✘")
		return (false);
	return (true);
}

void test_set()
{

	std::cout << UNDERLINE << "set :\n" << NORMAL ;

	mkdir("./tester/sets_output", 0777);
	
	std::fstream fs;

	/* Constructors */
	std::cout << "Constructors : ";

	/* Default constructor */
	{
		std::set<int> stl_default_set;
		ft::set<int> ft_default_set;

		fs.open("./tester/sets_output/constructor_default", std::fstream::in | std::fstream::out | std::fstream::trunc);
		std::cout << ((printsetAttributes(fs, stl_default_set, ft_default_set) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::set<int> ft_default_set;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::set<int> stl_default_set;\n";
		fs.close();     
	}

	/* Range constrcutor */
	{
		const int range_int[] = {-652, -4, 98, 54, -210};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/constructor_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printsetAttributes(fs, stl_set, ft_set);

		std::set<int> stl_set_copy(stl_set.begin(), stl_set.end());
		ft::set<int> ft_set_copy(ft_set.begin(), ft_set.end());

		std::cout << ((printsetAttributes(fs, stl_set_copy, ft_set_copy) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-652, -4, 98, 54, -210};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int> ft_set_copy(ft_set.begin(), ft_set.end());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-652, -4, 98, 54, -210};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int> stl_set_copy(stl_set.begin(), stl_set.end());\n";
		fs.close();
	}

	/* Copy constructor */
	{
		const int range_int[] = {842, 695, -98, -2, -4};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/constructor_copy", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printsetAttributes(fs, stl_set, ft_set);

		std::set<int> stl_set_copy(stl_set);
		ft::set<int> ft_set_copy(ft_set);

		std::cout << ((printsetAttributes(fs, stl_set_copy, ft_set_copy) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, 695, -98, -2, -4};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int> ft_set_copy(ft_set);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, 695, -98, -2, -4};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int> stl_set_copy(stl_set);\n";
		fs.close();
	}

	/* Assign operator */
	{
		const int range_int[] = {478, 952, 12, -96, -9};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/operator_assign", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printsetAttributes(fs, stl_set, ft_set);

		std::set<int> stl_set_copy = stl_set;
		ft::set<int> ft_set_copy = ft_set;

		std::cout << ((printsetAttributes(fs, stl_set_copy, ft_set_copy) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {478, 952, 12, -96, -9};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int> ft_set_copy = ft_set;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {478, 952, 12, -96, -9};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int> stl_set_copy = stl_set;\n";
		fs.close();
	}

	std::cout << std::endl;
	std::cout << "Iterators : ";

	/* Begin */
	{
		const int range_int[] = {1485, 5, 89, 652, -94};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printsetAttributes(fs, stl_set, ft_set);
		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_set.begin()), (*ft_set.begin())) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1485, 5, 89, 652, -94};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1485, 5, 89, 652, -94};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs.close(); 
	}

	/* Const begin */
	{
		const int range_int[] = {48, 9, 12, 63, 99};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/begin_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::set<int>::const_iterator stl_it = stl_set.begin();
		ft::set<int>::const_iterator ft_it = ft_set.begin();

		printsetAttributes(fs, stl_set, ft_set);
		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it), (*ft_it)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {48, 9, 12, 63, 99};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::const_iterator ft_it = ft_set.begin();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {48, 9, 12, 63, 99};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::const_iterator stl_it = stl_set.begin();\n";
		fs.close(); 
	}

	/* End */
	{
		const int range_int[] = {-99, 584, 965, 366, 77};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/end", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::set<int>::iterator stl_it = stl_set.end();
		ft::set<int>::iterator ft_it = ft_set.end();

		printsetAttributes(fs, stl_set, ft_set);

		--stl_it;
		--ft_it;

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it), (*ft_it)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-99, 584, 965, 366, 77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::iterator ft_it = ft_set.end();\n";
		fs << "--ft_it;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-99, 584, 965, 366, 77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::iterator stl_it = stl_set.end();\n";
		fs << "--stl_it;\n";
		fs.close(); 
	}

	/* Const end */
	{
		const int range_int[] = {154, 966, 3, -84, 75};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/end_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::set<int>::const_iterator stl_it = stl_set.end();
		ft::set<int>::const_iterator ft_it = ft_set.end();

		printsetAttributes(fs, stl_set, ft_set);

		--stl_it;
		--ft_it;

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it), (*ft_it)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {154, 966, 3, -84, 75};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::const_iterator ft_it = ft_set.end();\n";
		fs << "--ft_it;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {154, 966, 3, -84, 75};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::const_iterator stl_it = stl_set.end();\n";
		fs << "--stl_it;\n";
		fs.close();
	}

	/* Reverse begin */
	{
		const int range_int[] = {1458, -985, 58, 632, 65};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/reverse_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::set<int>::reverse_iterator stl_it = stl_set.rbegin();
		ft::set<int>::reverse_iterator ft_it = ft_set.rbegin();

		printsetAttributes(fs, stl_set, ft_set);

		++stl_it;
		++ft_it;

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it), (*ft_it)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1458, -985, 58, 632, 65};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::reverse_iterator ft_it = ft_set.rbegin();\n";
		fs << "++ft_it;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1458, -985, 58, 632, 65};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::reverse_iterator stl_it = stl_set.rbegin();\n";
		fs << "++stl_it;\n";
		fs.close();
	}

	/* Const reverse begin */
	{
		const int range_int[] = {859, 99, -325, -65, -98};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/reverse_begin_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::set<int>::const_reverse_iterator stl_it = stl_set.rbegin();
		ft::set<int>::const_reverse_iterator ft_it = ft_set.rbegin();

		printsetAttributes(fs, stl_set, ft_set);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it), (*ft_it)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {859, 99, -325, -65, -98};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::const_reverse_iterator ft_it = ft_set.rbegin();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {859, 99, -325, -65, -98};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::const_reverse_iterator stl_it = stl_set.rbegin();\n";
		fs.close();
	}

	/* Reverse end */
	{
		const int range_int[] = {325, -657, -942, -8, 66};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/reverse_end", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::set<int>::reverse_iterator stl_it = stl_set.rend();
		ft::set<int>::reverse_iterator ft_it = ft_set.rend();

		printsetAttributes(fs, stl_set, ft_set);

		--stl_it;
		--ft_it;

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it), (*ft_it)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {325, -657, -942, -8, 66};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::reverse_iterator ft_it = ft_set.rend();\n";
		fs << "--ft_it;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {325, -657, -942, -8, 66};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::reverse_iterator stl_it = stl_set.rend();\n";
		fs << "--stl_it;\n";
		fs.close();
	}


	/* Const reverse end */
	{
		const int range_int[] = {-99, 584, 965, 366, 77};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/reverse_end_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::set<int>::const_reverse_iterator stl_it = stl_set.rend();
		ft::set<int>::const_reverse_iterator ft_it = ft_set.rend();

		printsetAttributes(fs, stl_set, ft_set);

		--(--stl_it);
		--(--ft_it);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it), (*ft_it)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-99, 584, 965, 366, 77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::const_reverse_iterator ft_it = ft_set.rend();\n";
		fs << "--(--ft_it);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-99, 584, 965, 366, 77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::const_reverse_iterator stl_it = stl_set.rend();\n";
		fs << "--(--stl_it);\n";
		fs.close(); 
	}

	std::cout << std::endl;
	std::cout << "Capacity : ";

	/* Empty true */
	{
		std::set<int> stl_default_set;
		ft::set<int> ft_default_set;

		fs.open("./tester/sets_output/empty_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printsetAttributes(fs, stl_default_set, ft_default_set);
		std::cout << ((printBoolResult(fs, stl_default_set.empty(), ft_default_set.empty()) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::set<int> ft_default_set;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::set<int> stl_default_set;\n";
		fs.close();  
	}

	/* Empty false */
	{
		const int range_int[] = {1452, 3651, -98, 84, 899};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/empty_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printsetAttributes(fs, stl_set, ft_set);
		std::cout << ((printBoolResult(fs, stl_set.empty(), ft_set.empty()) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1452, 3651, -98, 84, 899};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1452, 3651, -98, 84, 899};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs.close(); 
	}

	/* Size */
	{
		const int range_int[] = {9, -84, -45, -67, -9};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/size", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printsetAttributes(fs, stl_set, ft_set);
		std::cout << "[";
		std::cout << ((printSingleValue(fs, stl_set.size(), ft_set.size()) == true) ? "[OK]" : "[NOP]");

		stl_set.insert(42);
		ft_set.insert(42);

		std::cout << ((printSingleValue(fs, stl_set.size(), ft_set.size()) == true) ? "[OK]" : "[NOP]");

		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {9, -84, -45, -67, -9};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "Sending output...\n";
		fs << "ft_set.insert(42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {9, -84, -45, -67, -9};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "Sending output...\n";
		fs << "stl_set.insert(42));\n";
		fs.close(); 
	}

	/* Maximum size */
	{
		std::set<int> stl_default_set;
		ft::set<int> ft_default_set;

		fs.open("./tester/sets_output/max_size", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printsetAttributes(fs, stl_default_set, ft_default_set);
		std::cout << ((printSingleValue(fs, stl_default_set.max_size(), ft_default_set.max_size()) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::set<int> ft_default_set;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::set<int> stl_default_set;\n";
		fs.close();  
	}

	std::cout << std::endl;
	std::cout << "Modifier : ";

	/* Insert single */
	{
		std::set<int> stl_set;
		ft::set<int> ft_set;

		stl_set.insert(42);
		ft_set.insert(42);

		fs.open("./tester/sets_output/insert_single", std::fstream::in | std::fstream::out | std::fstream::trunc);
		std::cout << ((printsetAttributes(fs, stl_set, ft_set) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "ft_set.insert(42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::set<int> stl_set;\n";
		fs << "stl_set.insert(42);\n";
		fs.close();  
	}

	/* Insert hint */
	{
		const int range_int[] = {584, 96, 21, -54, 36};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/insert_hint", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printsetAttributes(fs, stl_set, ft_set);
		
		stl_set.insert(++(stl_set.begin()), 42);
		ft_set.insert(++(ft_set.begin()), 42);

		std::cout << ((printsetAttributes(fs, stl_set, ft_set) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {584, 96, 21, -54, 36};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft_set.insert(++(ft_set.begin()), 42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {584, 96, 21, -54, 36};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "stl_set.insert(++(stl_set.begin()), 42);\n";
		fs.close(); 
	}

	/* Insert Range */
	{
		const int range_int[] = {754, -985, 58, 999, 5};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set_one;
		ft::set<int> ft_set_one;
		std::set<int> stl_set_two;
		ft::set<int> ft_set_two;

		for (int i = 0; i < 5; i++)
		{
			stl_set_one.insert(range_int[i]);
			ft_set_one.insert(range_int[i]);
			stl_set_two.insert(range_int[i] + 266);
			ft_set_two.insert(range_int[i] + 266);
		}

		fs.open("./tester/sets_output/insert_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printsetAttributes(fs, stl_set_one, ft_set_one);
		printsetAttributes(fs, stl_set_two, ft_set_two);
		
		stl_set_one.insert(stl_set_two.begin(), stl_set_two.end());
		ft_set_one.insert(ft_set_two.begin(), ft_set_two.end());

		std::cout << ((printsetAttributes(fs, stl_set_one, ft_set_one) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {754, -985, 58, 999, 5};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set_one;\n";
		fs << "ft::set<int> ft_set_two;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "	ft_set_one.insert(range_int[i]);\n";
		fs << "	ft_set_two.insert(ange_int[i] + 266));\n";
		fs << "}\n";
		fs << "Sending output...\n";
		fs << "ft_set_one.insert(ft_set_two.begin(), ft_set_two.end());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {754, -985, 58, 999, 5};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set_one;\n";
		fs << "std::set<int> stl_set_two;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "	stl_set_one.insert(range_str[i);\n";
		fs << "	stl_set_two.insert(range_int[i] + 266+ \"_two\"));\n";
		fs << "}\n";
		fs << "Sending output...\n";
		fs << "stl_set_one.insert(stl_set_two.begin(), stl_set_two.end());\n";
		fs.close(); 

	}

	/* Erase single */
	{
		const int range_int[] = {-9, -84, -77, 24, 56};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/erase_single", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printsetAttributes(fs, stl_set, ft_set);
		
		stl_set.erase(stl_set.begin());
		ft_set.erase(ft_set.begin());

		std::cout << ((printsetAttributes(fs, stl_set, ft_set) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-9, -84, -77, 24, 56};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft_set.erase(ft_set.begin());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-9, -84, -77, 24, 56};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "stl_set.erase(stl_set.begin());\n";
		fs.close(); 
	}

	/* Erase key */
	{
		const int range_int[] = {1452, 3651, -98, 84, 899};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/erase_key", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printsetAttributes(fs, stl_set, ft_set);
		
		stl_set.erase(-98);
		ft_set.erase(-98);

		std::cout << ((printsetAttributes(fs, stl_set, ft_set) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1452, 3651, -98, 84, 899};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft_set.erase(-98);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1452, 3651, -98, 84, 899};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "stl_set.erase(-98);\n";
		fs.close(); 
	}

	/* Erase range */
	{
        const int range_int[] = {-854, 1, 965, -9, 755};
        const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

        for (int i = 0; i < 5; i++)
        {
            stl_set.insert(range_int[i]);
            ft_set.insert(range_int[i]);
        }

		fs.open("./tester/sets_output/erase_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printsetAttributes(fs, stl_set, ft_set);
	    
		std::set<int>::iterator stl_it_beg = stl_set.begin();
		ft::set<int>::iterator ft_it_beg = ft_set.begin();
		std::set<int>::iterator stl_it_end = stl_set.end();
		ft::set<int>::iterator ft_it_end = ft_set.end();

		for (int i = 0; i < 2; i++)
		{
			stl_it_beg++;
			ft_it_beg++;
		}
		stl_it_end--;
		ft_it_end--;

        stl_set.erase(stl_it_beg, stl_it_end);
        ft_set.erase(ft_it_beg, ft_it_end);

        std::cout << ((printsetAttributes(fs, stl_set, ft_set) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "const int range_int[] = {-854, 1, 965, -9, 755};\n";
        fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::iterator ft_it_beg = ft_set.begin();\n";
		fs << "ft::set<int>::iterator ft_it_end = ft_set.end();\n";
		fs << "for (int i = 0; i < 2; i++)\n";
		fs << "	ft_it_beg++;\n";
		fs << "ft_it_end--;\n";
        fs << "ft_set.erase(ft_it_beg, ft_it_end);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "const int range_int[] = {-854, 1, 965, -9, 755};\n";
        fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::iterator stl_it_beg = stl_set.begin();\n";
		fs << "std::set<int>::iterator stl_it_end = stl_set.end();\n";
		fs << "for (int i = 0; i < 2; i++)\n";
		fs << "	stl_it_beg++;\n";
		fs << "stl_it_end--;\n";
        fs << "stl_set.erase(stl_it_beg, stl_it_end);\n";
		fs.close(); 
	}

	/* Swap */
	{
		const int range_int[] = {489, 851, 32, -98, 8};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set_one;
		ft::set<int> ft_set_one;
		std::set<int> stl_set_two;
		ft::set<int> ft_set_two;

		for (int i = 0; i < 5; i++)
		{
			stl_set_one.insert(range_int[i]);
			ft_set_one.insert(range_int[i]);
			stl_set_two.insert(range_int[i] + 120);
			ft_set_two.insert(range_int[i] + 120);
		}

		fs.open("./tester/sets_output/swap", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printsetAttributes(fs, stl_set_one, ft_set_one);
		printsetAttributes(fs, stl_set_two, ft_set_two);
		
		stl_set_one.swap(stl_set_two);
		ft_set_one.swap(ft_set_two);

		std::cout << ((printsetAttributes(fs, stl_set_one, ft_set_one) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printsetAttributes(fs, stl_set_two, ft_set_two) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {489, 851, 32, -98, 8};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set_one;\n";
		fs << "ft::set<int> ft_set_two;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "		ft_set_one.insert(range_int[i]);\n";
		fs << "		ft_set_two.insert(ange_int[i] + 120);\n";
		fs << "}\n";
		fs << "Sending Output...\n";
		fs << "ft_set_one.swap(ft_set_two);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {489, 851, 32, -98, 8};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set_one;\n";
		fs << "std::set<int> stl_set_two;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "		stl_set_one.insert(range_str[i);\n";
		fs << "		stl_set_two.insert(range_int[i] + 120);\n";
		fs << "}\n";
		fs << "Sending Output...\n";
		fs << "stl_set_one.swap(stl_set_two);\n";
		fs.close();
	}

	/* Clear */
	{
		const int range_int[] = {148, 9874, -987, 52, 96};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/clear", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printsetAttributes(fs, stl_set, ft_set);
		
		stl_set.clear();
		ft_set.clear();

		std::cout << ((printsetAttributes(fs, stl_set, ft_set) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {148, 9874, -987, 52, 96};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft_set.clear()\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {148, 9874, -987, 52, 96};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "stl_set.clear()\n";
		fs.close();
	}

	std::cout << std::endl;
	std::cout << "Observers : ";

	/* Key comp */
	{
		std::set<int>::key_compare stl_key = std::set<int>().key_comp();
		ft::set<int>::key_compare ft_key = ft::set<int>().key_comp();

		bool stl_res = stl_key(42, 99);
		bool ft_res = ft_key(42, 99);

		fs.open("./tester/sets_output/key_comp", std::fstream::in | std::fstream::out | std::fstream::trunc);
		std::cout << ((printBoolResult(fs, stl_res, ft_res) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::set<int>::key_compare ft_key = ft::set<int>().key_comp();\n";
		fs << "bool ft_res = ft_key(42, 99);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::set<int>::key_compare stl_key = std::set<int>().key_comp();\n";
		fs << "bool stl_res = stl_key(42, 99);\n";
		fs.close();  
	}

	/* Value comp */
	{
		std::set<int>::value_compare stl_key = std::set<int>().value_comp();
		ft::set<int>::value_compare ft_key = ft::set<int>().value_comp();

		bool stl_res = stl_key(99, 42);
		bool ft_res = ft_key(99, 42);

		fs.open("./tester/sets_output/value_comp", std::fstream::in | std::fstream::out | std::fstream::trunc);
		std::cout << ((printBoolResult(fs, stl_res, ft_res) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::set<int>::value_compare ft_key = ft::set<int>().value_comp();\n";
		fs << "bool ft_res = ft_key(99, 42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::set<int>::value_compare stl_key = std::set<int>().value_comp();\n";
		fs << "bool stl_res = stl_key(99, 42);\n";
		fs.close();  
	}

	std::cout << std::endl;
	std::cout << "Operations : ";

	/* Find exist */
	{
		const int range_int[] = {954, 12, -965, 42, 1000};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/find_exist", std::fstream::in | std::fstream::out | std::fstream::trunc);

		std::set<int>::iterator stl_it = stl_set.find(42);
		ft::set<int>::iterator ft_it = ft_set.find(42);
		
		printsetAttributes(fs, stl_set, ft_set);
		
		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it), (*ft_it)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {954, 12, -965, 42, 1000};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::iterator ft_it = ft_set.find(42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {954, 12, -965, 42, 1000};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::iterator stl_it = stl_set.find(42);\n";
		fs.close(); 
	}

	/* Find not exist*/
	{
		const int range_int[] = {14, 985, 578, -23, 47};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/find_not_exist", std::fstream::in | std::fstream::out | std::fstream::trunc);

		std::set<int>::iterator stl_it = stl_set.find(42);
		ft::set<int>::iterator ft_it = ft_set.find(42);
		
		printsetAttributes(fs, stl_set, ft_set);
		
		std::cout << ((printBoolResult(fs, (stl_it == stl_set.end()), (ft_it == ft_set.end())) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {14, 985, 578, -23, 47};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::iterator ft_it = ft_set.find(42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {14, 985, 578, -23, 47};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::iterator stl_it = stl_set.find(42);\n";
		fs.close(); 
	}

	/* Const it Find */
	{
		const int range_int[] = {842, -965, 99, 52, 65};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/find_const_exist", std::fstream::in | std::fstream::out | std::fstream::trunc);

		std::set<int>::const_iterator stl_it = stl_set.find(99);
		ft::set<int>::const_iterator ft_it = ft_set.find(99);
		
		printsetAttributes(fs, stl_set, ft_set);
		
		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it), (*ft_it)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, -965, 99, 52, 65};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::const_iterator ft_it = ft_set.find(99);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, -965, 99, 52, 65};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::const_iterator stl_it = stl_set.find(99);\n";
		fs.close();
	}

	/* Count */
	{
		const int range_int[] = {842, 654, 95, -98, -8};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/count", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printsetAttributes(fs, stl_set, ft_set);

		std::cout << "[";
		std::cout << ((printBoolResult(fs, (stl_set.count(-98) > 0), (ft_set.count(-98) > 0)) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printBoolResult(fs, (stl_set.count(42) > 0), (ft_set.count(42) > 0)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, 654, 95, -98, -8};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "Search for -98 & 42\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, 654, 95, -98, -8};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "Search for -98 & 42\n";
		fs.close(); 
	}

	/* Lower bound */
	{
		const int range_int[] = {351, -999, 5, 76, 61};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/lower_bound", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printsetAttributes(fs, stl_set, ft_set);

		std::set<int>::iterator stl_it = stl_set.lower_bound(80);
		ft::set<int>::iterator ft_it = ft_set.lower_bound(80);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it), (*ft_it)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {351, -999, 5, 76, 61};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::iterator ft_it = ft_set.lower_bound(80);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {351, -999, 5, 76, 61};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::iterator stl_it = stl_set.lower_bound(80);\n";
		fs.close(); 
	}
	
	/* Const it Lower bound */
	{
		const int range_int[] = {554, 62, 345, 98, -77};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/lower_bound_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printsetAttributes(fs, stl_set, ft_set);

		std::set<int>::const_iterator stl_it = stl_set.lower_bound(80);
		ft::set<int>::const_iterator ft_it = ft_set.lower_bound(80);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it), (*ft_it)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {554, 62, 345, 98, -77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::const_iterator ft_it = ft_set.lower_bound(80);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {554, 62, 345, 98, -77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::const_iterator stl_it = stl_set.lower_bound(80);\n";
		fs.close(); 
	}

	/* Upper bound */
	{
		const int range_int[] = {45, -84, 957, 966, 3};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/upper_bound", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printsetAttributes(fs, stl_set, ft_set);

		std::set<int>::iterator stl_it = stl_set.upper_bound(950);
		ft::set<int>::iterator ft_it = ft_set.upper_bound(950);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it), (*ft_it)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {45, -84, 957, 966, 3};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::iterator ft_it = ft_set.upper_bound(950);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {45, -84, 957, 966, 3};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::iterator stl_it = stl_set.upper_bound(950);\n";
		fs.close(); 
	}

	/* Const it Upper bound */
	{
		const int range_int[] = {963, 654, 789, -9, 85};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/upper_bound_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printsetAttributes(fs, stl_set, ft_set);

		std::set<int>::const_iterator stl_it = stl_set.upper_bound(950);
		ft::set<int>::const_iterator ft_it = ft_set.upper_bound(950);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it), (*ft_it)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {963, 654, 789, -9, 85};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "ft::set<int>::const_iterator ft_it = ft_set.upper_bound(950);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {963, 654, 789, -9, 85};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs << "std::set<int>::const_iterator stl_it = stl_set.upper_bound(950);\n";
		fs.close();
	}

	/* Equal range */
	{
		const int range_int[] = {-741, 520, 65, -84, -1};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::set<int> stl_set;
		ft::set<int> ft_set;

		for (int i = 0; i < 5; i++)
		{
			stl_set.insert(range_int[i]);
			ft_set.insert(range_int[i]);
		}

		fs.open("./tester/sets_output/equal_range_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printsetAttributes(fs, stl_set, ft_set);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*(stl_set.equal_range(65).first)), (*(ft_set.equal_range(65).first))) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*(stl_set.equal_range(65).second)), (*(ft_set.equal_range(65).second))) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-741, 520, 65, -84, -1};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::set<int> ft_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_set.insert(range_int[i]);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-741, 520, 65, -84, -1};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::set<int> stl_set;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_set.insert(range_str[i);\n";
		fs.close();
	}

	std::cout << "\n";
}