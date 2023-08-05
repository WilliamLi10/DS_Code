#include<string>
#include<list>
#include<fstream>

int main()
{
	std::ifstream istr("my_information.txt");
 std::string s;
 std::list<std::string> data;
 while (istr >> s) { data.push_back(s); }
 std::list<std::string>::iterator password = data.begin() + 1;
}