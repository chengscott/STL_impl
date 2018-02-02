#include<iostream>
#include"header/I2P_test.h"
using namespace std;
using namespace I2P_test_util;

int main()
{
	check_hierarchy();
	check_iterator_type();
#ifdef TEST_LIST
	cout<<"check list\n";
	check_list();
#endif
#ifdef TEST_SET
	cout<<"check set\n";
	check_set();
#endif
#ifdef TEST_VECTOR
	cout<<"check vector\n";
	check_vec();
#endif
	cout<<"done\n";
}