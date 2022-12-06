#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

static const size_t NUM_STACKS = 9;

int main(int argc, char** argv) {
    std::ifstream input_file("input");

    std::regex word_regex("(\\w+)");
    std::string input;
    std::vector<std::vector<char>> stacks(NUM_STACKS);
    // initial setup
    while(getline(input_file, input))
    {
        if(input == "") {
            break;
        }
        if(input[1] == '1') {
            continue;
        }
        for(size_t i = 0; i < NUM_STACKS; i++)
        {
            // [N] [Q] [W]                 [R] [B]
            auto selected_char = input[1 + (i * 4)];
            if(selected_char != ' ') {
                stacks[i].insert(stacks[i].begin(), selected_char);
            }
        }
    }
    // movements
    while(getline(input_file, input))
    {
        // move 1 from 8 to 4
        auto words_begin = std::sregex_iterator(input.begin(), input.end(), word_regex);
        auto words_end = std::sregex_iterator();
        std::vector<std::string> words;
        for(auto r_itr = words_begin; r_itr != words_end; ++r_itr)
        {
            words.push_back(r_itr->str());
        }
        for(size_t i = 0; i < std::stoi(words[1]); i++) {
            auto from = std::stoi(words[3]), to = std::stoi(words[5]);
            stacks[to - 1].push_back(stacks[from - 1].back());
            stacks[from - 1].pop_back();
        }
    }
    for(const auto& stack: stacks)
    {
        std::cout << stack.back();
    }
    std::cout << std::endl;
}
