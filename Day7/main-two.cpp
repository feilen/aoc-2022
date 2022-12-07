#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

struct fs_file {
    std::string name = "";
    size_t bytes = 0;
};

struct fs_dir {
    fs_dir* parent = nullptr;
    std::string name = "";
    std::vector<fs_dir> children;
    std::vector<fs_file> files;
    size_t bytes = 0;
};

const size_t TOTAL_DISK = 70000000;
const size_t UNUSED_NEEDED = 30000000;

int main(int argc, char** argv) {
    std::ifstream input_file("input");

    std::regex word_regex("([^[:space:]]+)");
    std::string input;
    fs_dir directory_tree;
    fs_dir* current_directory;
    // initial setup
    while(getline(input_file, input))
    {
        if(input == "") {
            break;
        }
        auto words_begin = std::sregex_iterator(input.begin(), input.end(), word_regex);
        auto words_end = std::sregex_iterator();
        std::vector<std::string> words;

        for(auto r_itr = words_begin; r_itr != words_end; ++r_itr)
        {
            words.push_back(r_itr->str());
        }
        if(words[0] == "$")
        {
            if(words[1] == "cd") {
                if (words[2] == "..") {
                    current_directory = current_directory->parent;
                } else if (words[2] == "/") {
                    current_directory = &directory_tree;
                } else {
                    auto found_child = std::find_if(current_directory->children.begin(),
                                               current_directory->children.end(),
                                               [words] (const fs_dir& cur_child) {
                                                   return cur_child.name == words[2];
                                               });
                    if (found_child != current_directory->children.end()) {
                        current_directory = &(*found_child);
                    } else {
                        throw std::runtime_error("");
                        //currentdirectory->children.push_back(fs_dir());
                        //currentdirectory->children.back().name = words[2];
                        //currentdirectory->children.back().parent = current_directory;
                        //currentdirectory = &current_directory->children.back();
                    }
                }
            }
            else if (words[1] == "ls")
            {
                // nada
            }
        } else if (words[0] == "dir") {
            auto found_child = std::find_if(current_directory->children.begin(),
                                       current_directory->children.end(),
                                       [words] (const fs_dir& cur_child) {
                                           return cur_child.name == words[1];
                                       });
            if (found_child == current_directory->children.end()) {
                current_directory->children.push_back(fs_dir());
                current_directory->children.back().name = words[1];
                current_directory->children.back().parent = current_directory;
            } else {
                throw std::runtime_error("");
            }
        } else {
            current_directory->files.push_back(fs_file());
            current_directory->files.back().bytes = std::stoi(words[0]);
            fs_dir* cur_parent = current_directory;
            while(cur_parent != nullptr) {
                cur_parent->bytes += std::stoi(words[0]);
                cur_parent = cur_parent->parent;
            }
            current_directory->files.back().name = words[1];
        }
    }
    // summing logic
    fs_dir* cur_search = nullptr;
    std::vector<fs_dir*> next_nodes;
    size_t sum_dirs_under_100k = 0;
    next_nodes.push_back(&directory_tree);
    std::vector<size_t> sizes;
    while(!next_nodes.empty()) {
        cur_search = next_nodes.back();
        next_nodes.pop_back();
        for(auto& child: cur_search->children) {
            next_nodes.push_back(&child);
        }
        if (cur_search->bytes <= 100000) {
            sum_dirs_under_100k += cur_search->bytes;
        }
        sizes.push_back(cur_search->bytes);
    }
    auto needed_space = UNUSED_NEEDED - (TOTAL_DISK - directory_tree.bytes);
    std::sort(sizes.begin(), sizes.end());
    auto found_val = std::upper_bound(sizes.begin(), sizes.end(), needed_space);
    std::cout << *found_val << std::endl;
    //std::cout << sum_dirs_under_100k << std::endl;
}
