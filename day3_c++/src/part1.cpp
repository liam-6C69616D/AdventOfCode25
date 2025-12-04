#include "part1.hpp"
#include <fstream>
#include <string>
#include <iostream>

int Bank::highestJoltage() {
    int highest_found = 0;
    for (int i = 0; i < batteries.size(); i++) {
        for (int j = i + 1; j < batteries.size(); j++) {
            char first = batteries[i] + '0';
            char second = batteries[j] + '0';

            string result_string(1, first);
            result_string += second;

            int as_number = stoi(result_string);

            if (as_number > highest_found) {
                highest_found = as_number;
            }
        }
    }

    return highest_found;
}

void Part1::readFile() {
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

vector<Bank> Part1::getBanks() {
    return banks;
}

int main() {
    Part1 p1;
    p1.readFile();
    vector<Bank> banks = p1.getBanks();

    vector<int> values;
    for (Bank b : banks) {
        int highest_value = b.highestJoltage();
        values.push_back(highest_value);
    }

    int total = 0;
    for (int val : values) {
        total += val;
    }

    cout << total << endl;
}