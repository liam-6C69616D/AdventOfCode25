#include "part1.hpp"
#include <fstream>
#include <string>
#include <iostream>

bool Range::inRange(long long value) {
    return value >= start && value <= end;
}

void Part1::readFile() {
    ifstream file("../src/input.txt");
    string line;

    bool reading_ranges = true;
    while (getline(file, line)) {
        if (line == "") {
            reading_ranges = false;
            continue;
        }

        if (reading_ranges) {
            Range r;
            int delim_pos = line.find("-");
            int len = line.length();

            r.setRange(stoll(line.substr(0, delim_pos)), stoll(line.substr(delim_pos + 1, len)));
            ranges.push_back(r);
        } else {
            ids.push_back(stoll(line));
        }
    }
}

int Part1::countFresh() {
    int count = 0;

    for (long long id : ids) {
        bool is_fresh = false;
        for (Range r : ranges) {
            if (r.inRange(id)) {
                is_fresh = true;
                break;
            }
        }

        if (is_fresh) {
            count++;
        }
    }

    return count;
}

int main() {
    Part1 p1;
    p1.readFile();
    int fresh_count = p1.countFresh();

    cout << fresh_count << endl;
}