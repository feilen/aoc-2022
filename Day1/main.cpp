#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

int main(int argc, char** argv) {
    std::ifstream input_file("input");

    std::string input;
    std::vector<size_t> heap;
    size_t running_total = 0;
    while(getline(input_file, input))
    {
        if (input.size() != 0)
        {
            running_total += std::stoi(input);
        }
        else
        {
            heap.push_back(running_total);
            std::push_heap(heap.begin(), heap.end());
            running_total = 0;
        }
    }
    heap.push_back(running_total);
    std::push_heap(heap.begin(), heap.end());

    size_t max_total = 0;
    for (size_t i = 0; i < 3; i++)
    {
        std::pop_heap(heap.begin(), heap.end());
        max_total += heap.back();
        heap.pop_back();
    }
    std::cout << max_total << std::endl;
}
