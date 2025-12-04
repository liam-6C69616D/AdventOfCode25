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
    vector<int> highest_stack = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    
    for (int i = 0; i < batteries.size(); i++) {
        int offset_from_end = batteries.size() - i; // last digit will be 1

        int start_index = max(0, 12 - offset_from_end);

        for (int j = start_index; j < 12; j++) {
            if (batteries[i] > highest_stack[j]) {
                highest_stack[j] = batteries[i];
                for (int k = j + 1; k < 12; k++) {
                    highest_stack[k] = -1;
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