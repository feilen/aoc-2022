#include <iostream>
#include <fstream>
// Rock - 1X, Paper - 2Y, Scissors - 3Z
//         A           B              C
// Lose - 0,  Draw - 3, Win - 6

enum class opponent_plays: char {
    ROCK = 'A',
    PAPER = 'B',
    SCISSORS = 'C',
};
enum class we_play: char {
    LOSE = 'X',
    DRAW = 'Y',
    WIN = 'Z'
};


int main() {
    std::ifstream input_file("input");

    size_t total_score = 0;
    std::string input1, input2;
    while(input_file >> input1 >> input2) {
        switch (opponent_plays(input1[0])) {
            case opponent_plays::ROCK:
            switch(we_play(input2[0])) {
                //case we_play::ROCK: total_score += 1 + 3; continue;
                case we_play::DRAW: total_score += 1 + 3; continue;
                //case we_play::PAPER: total_score += 2 + 6; continue;
                case we_play::WIN: total_score += 2 + 6; continue;
                //case we_play::SCISSORS: total_score += 3 + 0; continue;
                case we_play::LOSE: total_score += 3 + 0; continue;
            }
            case opponent_plays::PAPER:
            switch(we_play(input2[0])) {
                case we_play::LOSE: total_score += 1 + 0; continue;
                case we_play::DRAW: total_score += 2 + 3; continue;
                case we_play::WIN: total_score += 3 + 6; continue;
            }
            case opponent_plays::SCISSORS:
            switch(we_play(input2[0])) {
                case we_play::WIN: total_score += 1 + 6; continue;
                case we_play::LOSE: total_score += 2 + 0; continue;
                case we_play::DRAW: total_score += 3 + 3; continue;
            }
        }
    }
    std::cout << total_score << std::endl;
}
