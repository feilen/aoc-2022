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
    std::vector<char> current_sack;
    size_t current_count = 0;
    while(input_file >> input) {
        current_count ++;
        if(current_count == 1)
        {
            current_sack = std::vector<char>(input.begin(), input.end());
        } else {
            std::set<char> our_sack(current_sack.begin(), current_sack.end());
            std::set<char> incoming_sack(input.begin(), input.end());
            current_sack.clear();
            std::set_intersection<>(our_sack.begin(), our_sack.end(),
                                  incoming_sack.begin(), incoming_sack.end(),
                                  std::back_inserter(current_sack));
            if(current_count == 3)
            {
                current_count = 0;
                for(const auto& current_sack_item: current_sack) {
                    if (current_sack_item >= 'a') {
                        total_score += static_cast<int>(current_sack_item - 'a') + 1;
                    } else {
                        total_score += static_cast<int>(current_sack_item - 'A') + 27;
                    }
                }
            }
        }
    }
    std::cout << total_score << std::endl;
}
