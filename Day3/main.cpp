#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <vector>
#include <iterator>

int main() {
    std::ifstream input_file("input");


    size_t total_score = 0;
    std::string input;
    while(input_file >> input) {
        size_t middle = input.size()/2;
        // overkill but w/e
        std::set<char> sack_one(input.begin(), input.begin() + middle);
        std::set<char> sack_two(input.begin() + middle, input.end());
        std::vector<char> common;
        std::set_intersection<>(sack_one.begin(), sack_one.end(),
                              sack_two.begin(), sack_two.end(),
                              std::back_inserter(common));
        for(const auto& common_item: common) {
            if (common_item >= 'a') {
                total_score += static_cast<int>(common_item - 'a') + 1;
            } else {
                total_score += static_cast<int>(common_item - 'A') + 27;
            }
        }
    }
    std::cout << total_score << std::endl;
}
