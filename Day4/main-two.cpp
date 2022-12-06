#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <vector>
#include <iterator>
#include <bitset>

const size_t MAX_BITSET_SIZE = 1024;

int main() {
    std::ifstream input_file("input");

    size_t total_count = 0;
    std::string input;
    while(input_file >> input) {
        auto range1 = std::string(input.begin(), input.begin() + input.find(','));
        auto range2 = std::string(input.begin() + input.find(',') + 1, input.end());
        std::bitset<MAX_BITSET_SIZE> r1, r2;
        int r1_s = std::stoi(range1.substr(0, range1.find('-'))),
            r1_e = std::stoi(range1.substr(range1.find('-') + 1)),
            r2_s = std::stoi(range2.substr(0, range2.find('-'))),
            r2_e = std::stoi(range2.substr(range2.find('-') + 1));
        for(auto i = r1_s; i <= r1_e; i++) {
            r1.set(i);
        }
        for(auto i = r2_s; i <= r2_e; i++) {
            r2.set(i);
        }
        auto overlap = r1 & r2;
        if(overlap.any()) {
            total_count++;
            std::cout << range1 << " " << range2 << std::endl;
        }
    }
    std::cout << total_count << std::endl;
}
