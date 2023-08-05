#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <set>


// defined in performance.cpp
void usage();


template <class Key> 
void map_sort(std::map<Key,int>& mp, std::istream& istr, std::ostream& ostr, int& output_count, int& input_count)
{

    Key read;
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
    for (typename std::map<Key, int>::iterator i = mp.begin(); i != mp.end(); ++i)
    {
        for (int j = 0; j != i->second; ++j)
        {
            ostr << i->first << "\n";
            ++output_count;
        }
    }
}

template <class Key>
void map_remove_duplicates(std::map<Key,int>& mp, std::istream& istr, std::ostream& ostr, int& output_count, int& input_count)
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
void map_first_sorted(std::map<Key,int>& mp, std::istream& istr, std::ostream& ostr, int& output_count,int optional_arg, int& input_count)
{
    output_count = 0;
    Key read;
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
    assert(optional_arg >= 1);
    assert(input_count >= optional_arg);
    typename std::map<Key, int>::iterator i = mp.begin();
    for (int j = 0; j  != optional_arg; ++j)
    {
        for (int x = 0; x != i->second; ++x)
        {
            ostr << i->first << "\n";
            ++output_count;
            if (output_count >= optional_arg)
                return;
        }
        ++i;
    }
}

template <class Key>
void map_mode(std::map<Key, int>& mp, std::ostream& ostr, int& output_count, int& input_count)
{
   
    int maxcount = 0;
    Key Max;
    for (typename std::map<Key, int>::iterator i = mp.begin(); i != mp.end(); ++i)
    {
        if (i->second > maxcount)
        {
            maxcount = i->second;
            Max = i->first;
        }
    }
    ostr << Max << "\n";
}
void map_longest_substring(std::map<std::string, int>& mp, std::ostream& ostr, int& output_count, int& input_count)
{
    std::string LongestSubstr = "";
    for (std::map<std::string,int>::iterator i = mp.begin(); i != mp.end(); ++i)
    {
        for (std::map<std::string,int>::iterator j = std::next(i); j != mp.end(); ++j)
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

void map_closest_pair(std::map<int, int>& mp, std::ostream& ostr, int& output_count, int& input_count)
{
    assert(mp.size() >= 2);
    // use the list sort algorithm
    output_count = 2;
    int best;
    std::map<int,int>::iterator best_index = mp.begin();
    // the two elements with closest value must be next to each other in sorted order
    for (std::map<int,int>::iterator i = std::next(mp.begin()); i != std::prev(mp.end()); i++) {
        std::map<int,int>::iterator check = std::next(i);
        int diff = check->first - i->first;
        if (best_index == mp.begin() || diff < best) {
            best = diff;
            best_index = i;
        }
    }
    // print the two elements
    output_count = 2;
    ostr << best_index->first << "\n";
    ostr << (++best_index)->first << "\n";
}
void bst_test(const std::string& operation, const std::string& type,
    std::istream& istr, std::ostream& ostr,
    int& input_count, int& output_count, int optional_arg) {

    if (type == "string") {

        std::map<std::string, int> mp;
        if (operation == "sort" || operation == "remove_duplicates" || operation == "first_sorted")
        {
            if (operation == "sort") { map_sort(mp, istr, ostr, output_count, input_count); }
            else if (operation == "remove_duplicates") { map_remove_duplicates(mp, istr, ostr, output_count, input_count); }
            else if (operation == "first_sorted") { map_first_sorted(mp, istr, ostr, output_count, optional_arg, input_count); }
        }
        else
        {
            std::map<std::string, int> mp;
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

            if (operation == "mode") { map_mode(mp, ostr, output_count, input_count); }
            // "closest_pair" not available for strings
            else if (operation == "longest_substring") { map_longest_substring(mp, ostr, output_count, input_count); }
            else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
        }
        // load the data into a map of strings
    }

    else
    {
        assert(type == "integer");
        std::map<int, int> mp;
        int read;
        input_count = 0;
        // load the data into a map of integers
        if (operation == "sort" || operation == "remove_duplicates" || operation == "first_sorted")
        {
            if (operation == "sort") { map_sort(mp, istr, ostr, output_count, input_count); }
            else if (operation == "remove_duplicates") { map_remove_duplicates(mp, istr, ostr, output_count, input_count); }
            else if (operation == "first_sorted") { map_first_sorted(mp, istr, ostr, output_count, optional_arg, input_count); }
        }
        else
        {
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
            if (operation == "mode") { map_mode(mp, ostr, output_count, input_count); }
            else if (operation == "closest_pair") { map_closest_pair(mp, ostr, output_count, input_count); }
            // "longest_substring" not available for integers
            else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
        }
    }
}
