#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>


// defined in performance.cpp
void usage();



template <class Key>
void unordered_map_remove_duplicates(std::unordered_map<Key, int>& mp, std::istream& istr, std::ostream& ostr, int& output_count, int& input_count)
{
    Key read;
    input_count = 0;
    int count = 0;
    while (istr >> read)
    {
        if (mp.find(read) == mp.end())
        {
            mp[read] = count;
            ++count;
            ostr << read << "\n";
        }
        ++input_count;
    }
}



template <class Key>
void unordered_map_mode(std::unordered_map<Key, int>& mp, std::ostream& ostr, int& output_count, int& input_count)
{

    int maxcount = 0;
    Key Max;
    for (typename std::unordered_map<Key, int>::iterator i = mp.begin(); i != mp.end(); ++i)
    {
        
        if (i->second > maxcount)
        {
            maxcount = i->second;
            Max = i->first;
        }
    }
    ostr << Max << "\n";
}
void unordered_map_longest_substring(std::unordered_map<std::string, int>& mp, std::ostream& ostr, int& output_count, int& input_count)
{
    std::string LongestSubstr = "";
    for (std::unordered_map<std::string, int>::iterator i = mp.begin(); i != mp.end(); ++i)
    {
        for (std::unordered_map<std::string, int>::iterator j = std::next(i); j != mp.end(); ++j)
        {
            std::string CLSubstr = "";
            for (int c = 0; c != i->first.size(); ++c)
            {
                std::string window = "";
                for (int x = 0; x < j->first.size(); ++x)
                {
                    int count = 0;
                    while (count + c != i->first.size() && x != j->first.size() && (i->first)[c + count] == (j->first)[x])
                    {
                        //std::cout << window << std::endl;
                        window += (j->first)[x];
                        ++count;
                        ++x;
                    }
                    if (window.size() > CLSubstr.size())
                        CLSubstr = window;

                }
                //std::cout << lst[i] << " " <<CLSubstr << std::endl;
            }
            if (CLSubstr.size() > LongestSubstr.size())
                LongestSubstr = CLSubstr;

        }

    }
    ostr << LongestSubstr << "\n";
}

    void hash_table_test(const std::string & operation, const std::string & type,
        std::istream & istr, std::ostream & ostr,
        int& input_count, int& output_count, int optional_arg) {

        // HINT: For the string element type, declare your hash table like this:
        // std::unordered_set<std::string> ht;
        // OR 
        // std::unordered_map<std::string,int> ht;

        if (type == "string") {

            std::unordered_map<std::string, int> mp;
            if (operation == "remove_duplicates")
            {
                unordered_map_remove_duplicates(mp, istr, ostr, output_count, input_count);
            }
            else
            {
                std::unordered_map<std::string, int> mp;
                std::string read;
                input_count = 0;
                while (istr >> read)
                {
                    if (mp.find(read) == mp.end())
                    {
                        mp[read] = 1;
                    }
                    else
                    {
                        ++mp[read];
                    }
                    ++input_count;
                }

                if (operation == "mode") { unordered_map_mode(mp, ostr, output_count, input_count); }
                // "closest_pair" not available for strings
                else if (operation == "longest_substring") { unordered_map_longest_substring(mp, ostr, output_count, input_count); }
                else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
            }
            // load the data into a map of strings
        }

        else
        {
            assert(type == "integer");
            std::unordered_map<int, int> mp;
            int read;
            input_count = 0;
            // load the data into a map of integers
            if (operation == "remove_duplicates")
            {
                unordered_map_remove_duplicates(mp, istr, ostr, output_count, input_count);
            }
            else
            {
                while (istr >> read)
                {
                    //ostr << input_count << "\n";
                    ++input_count;
                    auto it = mp.find(read);

                    if (it == mp.end())
                    {

                        mp[read] = 1;

                    }
                    else
                    {
                        ++mp[read];
                    }


                }
                if (operation == "mode") { unordered_map_mode(mp, ostr, output_count, input_count); }
                // "longest_substring" not available for integers
                else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
            }
        }
    }
