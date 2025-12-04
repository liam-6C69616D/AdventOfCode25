#include "part2.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

vector<int> slice(const vector<int>& vec, size_t start, size_t end) {
    if (start >= vec.size() || end > vec.size() || start > end) {
        throw out_of_range("Invalid slice indices");
    }
    return vector<int>(vec.begin() + start, vec.begin() + end + 1);
}

long long Bank::highestJoltage() {
    /*
        For this block, we start with an array length 12, and work through the batteries to find the highest number we can make with a chronological
        series of the numbers per line

        Say out first value is 7, then there is an 8, we can replace the 7 with the 8 in that position for a higher number, so long as we clear
        the array after this point, since future digits need to follow the 8.

        If we are nearing the end of the line, there is no use replacing the beginning of our 12 character array, since there will not be enough
        characters after it to fill the requirement for a length of 12. Here we use start_index to work out if we are within 12 of the end of the array,
        and if so we only compare and replace the last x digits of our array, so we still get 12 characters when done
    */

    vector<int> highest_stack = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    
    // For each battery in the bank
    for (int i = 0; i < batteries.size(); i++) {
        int offset_from_end = batteries.size() - i; // distance from the end of the bank, last digit will be 1

        int start_index = max(0, 12 - offset_from_end); // Comparison index (if we are 3 from the end of the bank, only allow to replace last 3 digits of our highest number stack)

        // Loop through current highest values (within range using start_index so we still end with 12 digits)
        for (int j = start_index; j < 12; j++) {
            if (batteries[i] > highest_stack[j]) {
                highest_stack[j] = batteries[i]; // Replace value, ours is higher
                for (int k = j + 1; k < 12; k++) {
                    highest_stack[k] = -1; // Clear stack after, since future digits need to come later in the line
                }
                break;
            }
        }
    }

    string result_string = "";
    for (int v : highest_stack) {
        char to_char = v + '0';
        result_string += to_char;
    }

    long long as_number = stoll(result_string);

    return as_number;
}

void Part2::readFile() {
    ifstream file("../src/input.txt");
    string line;
    while (getline(file, line)) {
        Bank bank;
        for (char c : line) {
            int value = c - '0';
            bank.batteries.push_back(value);
        }
        banks.push_back(bank);
    }
}

vector<Bank> Part2::getBanks() {
    return banks;
}

int main() {
    Part2 p2;
    p2.readFile();
    vector<Bank> banks = p2.getBanks();

    vector<long long> values;
    for (Bank b : banks) {
        long long highest_value = b.highestJoltage();
        values.push_back(highest_value);
    }

    long long total = 0;
    for (long long val : values) {
        total += val;
    }

    cout << total << endl;
}