#include <iostream>
#include <fstream>
#include <set>

int main() {
    std::ifstream input_file("input");

    std::string input;
    while(input_file >> input) {
        for(size_t i = 0; i < input.size() - 14; i++)
        {
            auto current_set = std::set<char>(
                    input.begin() + i,
                    input.begin() + i + 14);
            std::cout << std::string(current_set.begin(), current_set.end()) << std::endl;
            if (current_set.size() == 14) {
                std::cout << i + 14 << std::endl;
                break;
            }
        }
    }
}
