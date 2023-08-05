#include <cassert>
#include <cstdlib>
//#include <algorithm>
#include <iostream>
#include <string>
#include <list>


// defined in performance.cpp
void usage();

template <class T>
void list_sort(std::list<T>& lst, std::ostream& ostr, int& output_count) {
    // use the list sort algorithm
    lst.sort();
    output_count = lst.size();
    for (typename std::list<T>::iterator i = lst.begin(); i != lst.end(); ++i)
    {
        ostr << *i << "\n";
    }
}

template <class T>
void list_remove_duplicates(const std::list<T>& lst, std::ostream& ostr, int& output_count) {
    // don't reorder the elements, just do all pairwise comparisons
    output_count = 0;
    for (typename std::list<T>::const_iterator i = lst.begin(); i != lst.end(); i++) {
        bool dup = false;
        for (typename std::list<T>::const_iterator j = lst.begin(); j != i; j++) {
            if (*i == *j) {
                dup = true;
                break;
            }
        }
        // if it has not already been added to the output list
        if (!dup) {
            ostr << *i << "\n";
            output_count++;
        }
    }
}


template <class T>
void list_mode(std::list<T>& lst, std::ostream& ostr, int& output_count) {
    // use the list sort algorithm
    lst.sort();
    int current_count = 1;
    T mode;
    int mode_count = 0;
    // keep track of two iterators into the structure
    typename std::list<T>::iterator current = lst.begin();
    ++current;
    typename std::list<T>::iterator previous = lst.begin();
    for (; current != lst.end(); ++current, ++previous) {
        if (*current == *previous) {
            // if they are the same element increment the count
            current_count++;
        }
        else if (current_count >= mode_count) {
            // found a new mode!
            mode = *previous;
            mode_count = current_count;
            current_count = 1;
        }
        else {
            current_count = 1;
        }
    }
    if (current_count >= mode_count) {
        // last entry is a new mode!
        mode = *previous;
        mode_count = current_count;
    }
    // save the mode to the output list
    output_count = 1;
    ostr << mode << "\n";
}


// note: closest_pair is only available for integer data (not string data)
void list_closest_pair(std::list<int>& lst, std::ostream& ostr, int& output_count) {
    assert(lst.size() >= 2);
    // use the list sort algorithm
    lst.sort();
    output_count = 2;
    int best;
    std::list<int>::iterator best_index = lst.begin();
    // the two elements with closest value must be next to each other in sorted order
    for ( std::list<int>::iterator i = std::next(lst.begin()); i != std::prev(lst.end()); i++) {
        std::list<int>::iterator check = std::next(i);
        int diff = *check - *i;
        if (best_index == lst.begin() || diff < best) {
            best = diff;
            best_index = i;
        }
    }
    // print the two elements
    output_count = 2;
    ostr << *best_index << "\n";
    ostr << *(++best_index) << "\n";
}


template <class T>
void list_first_sorted(std::list<T>& lst, std::ostream& ostr, int& output_count, int optional_arg) {
    assert(optional_arg >= 1);
    assert((int)lst.size() >= optional_arg);
    // use the list sort algorithm
    lst.sort();
    output_count = optional_arg;
    typename std::list<T>::iterator it = lst.begin();
    for (int i = 0; i < output_count; i++) {
        ostr << *it << "\n";
        ++it;
    }
}


// note: longest_substring is only available for string data (not integer data)
void list_longest_substring(std::list<std::string>& lst, std::ostream& ostr, int& output_count) {

    //
    // ASSIGNMENT: YOU NEED TO COMPLETE THIS FUNCTION
    //
    std::string LongestSubstr = "";
    for (std::list<std::string>::iterator i = lst.begin(); i != lst.end(); ++i)
    {
        for (std::list<std::string>::iterator j = std::next(i); j != lst.end(); ++j)
        {
            std::string CLSubstr = "";
            for (int c = 0; c != i->size(); ++c)
            {
                std::string window = "";
                for (int x = 0; x < j->size(); ++x)
                {
                    int count = 0;
                    while (count + c != i->size() && x != j->size() && (*i)[c + count] == (*j)[x])
                    {
                        //std::cout << window << std::endl;
                        window += (*j)[x];
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
    ostr << LongestSubstr << std::endl;

}
void list_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your list like this:
  // std::list<std::string> lst;

    if (type == "string") {
        // load the data into a list of strings
        std::list<std::string> lst;
        std::string s;
        input_count = 0;
        while (istr >> s) {
            lst.push_back(s);
            input_count++;
        }
        if (operation == "sort") { list_sort(lst, ostr, output_count); }
        else if (operation == "remove_duplicates") { list_remove_duplicates(lst, ostr, output_count); }
        else if (operation == "mode") { list_mode(lst, ostr, output_count); }
        // "closest_pair" not available for strings
        else if (operation == "first_sorted") { list_first_sorted(lst, ostr, output_count, optional_arg); }
        else if (operation == "longest_substring") { list_longest_substring(lst, ostr, output_count); }
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }

    else {
        assert(type == "integer");
        // load the data into a list of integers
        std::list<int> lst;
        int v;
        input_count = 0;
        while (istr >> v) {
            lst.push_back(v);
            input_count++;
        }
        if (operation == "sort") { list_sort(lst, ostr, output_count); }
        else if (operation == "remove_duplicates") { list_remove_duplicates(lst, ostr, output_count); }
        else if (operation == "mode") { list_mode(lst, ostr, output_count); }
        else if (operation == "closest_pair") { list_closest_pair(lst, ostr, output_count); }
        else if (operation == "first_sorted") { list_first_sorted(lst, ostr, output_count, optional_arg); }
        // "longest_substring" not available for integers
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
}
