#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>


// defined in performance.cpp
void usage();

template <class T>
void priority_queue_sort(std::priority_queue<T, std::vector<T>, std::greater<T>>& pq, std::ostream& ostr, int& output_count)
{
    while (!pq.empty()) {
        ostr << pq.top() << "\n";
        pq.pop();
        ++output_count;
    }
}
template <class T>
void priority_queue_first_sorted(std::priority_queue<T, std::vector<T>, std::greater<T>>& pq, std::ostream& ostr, int& output_count,int optional_arg)
{
    assert(optional_arg >= 1);
    assert((int)pq.size() >= optional_arg);
    output_count = 0;
    while (optional_arg >output_count) {
        ostr << pq.top() << "\n";
        pq.pop();
        ++output_count;
    }
}
template <class T>
void priority_queue_mode(std::priority_queue<T, std::vector<T>, std::greater<T>>& pq, std::ostream& ostr, int& output_count)
{
    T Mode;
    int CurCount = 0;
    int MaxCount = 0;
    T Prev = pq.top();
    while (!pq.empty())
    {
        if (Prev == pq.top())
        {
            ++CurCount;
            if (CurCount > MaxCount)
            {
                Mode = pq.top();
                MaxCount = CurCount;
            }
        }
        else
        {
            CurCount = 0;
        }
        Prev = pq.top();
        pq.pop();
    }
    output_count = 1;
    ostr << Mode << "\n";
}
void priority_queue_closest_pair(std::priority_queue<int, std::vector<int>, std::greater<int>>& pq, std::ostream& ostr, int& output_count)
{
    assert(pq.size() >= 2);
    int pair1 = pq.top();
    pq.pop();
    int pair2 = pq.top();
    int prev = pq.top();
    pq.pop();
    int mindiff = pair2 - pair1;
        while (!pq.empty())
        {
            int CurDiff = pq.top() - prev;
            if (CurDiff < mindiff)
            {
                pair1 = prev;
                pair2 = pq.top();
            }
            prev = pq.top();
            pq.pop();
        }
        output_count = 2;
        ostr << pair1 << "\n";
        ostr << pair2 << "\n";
}
void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your priority_queue like this:

  // std::priority_queue<std::string,std::priority_queue<std::string> > pq;
  // (this will make a "max" priority queue, with big values at the top)

  // OR
  
  // std::priority_queue<std::string,std::priority_queue<std::string>, std::greater<std::string> > pq;
  // (this will make a "min" priority queue, with big values at the bottom)

   if (type == "string") {
        // load the data into a priority_queue of strings
        std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> pq;
        std::string s;
        input_count = 0;
        while (istr >> s) {
            pq.push(s);
            input_count++;
        }
        if (operation == "sort") { priority_queue_sort(pq, ostr, output_count); }
        else if (operation == "mode") { priority_queue_mode(pq, ostr, output_count); }
        // "closest_pair" not available for strings
        else if (operation == "first_sorted") { priority_queue_first_sorted(pq, ostr, output_count, optional_arg); }
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }

    else {
        assert(type == "integer");
        // load the data into a priority_queue of integers
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        int v;
        input_count = 0;
        while (istr >> v) {
            pq.push(v);
            input_count++;
        }
        if (operation == "sort") { priority_queue_sort(pq, ostr, output_count); }
        else if (operation == "mode") { priority_queue_mode(pq, ostr, output_count); }
        else if (operation == "closest_pair") { priority_queue_closest_pair(pq, ostr, output_count); }
        else if (operation == "first_sorted") { priority_queue_first_sorted(pq, ostr, output_count, optional_arg); }
        // "longest_substring" not available for integers
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
}
