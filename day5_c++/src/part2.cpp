#include "part2.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

void Part2::readFile() {
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
        }
    }
}

long long Part2::countFresh() {
    long long count = 0;
    sort(ranges.begin(), ranges.end(), Range::compareRanges);
    
    // Remove ranges inside others
    for (int i = ranges.size() - 1; i > 0; i--) {
        if (ranges[i].getStart() >= ranges[i-1].getStart() && ranges[i].getEnd() <= ranges[i-1].getEnd()) {
            ranges.erase(ranges.begin() + i);
        }
    }

    // Merge overlaps
    for (int i = ranges.size() - 1; i > 0; i--) {
        if (ranges[i].getStart() <= ranges[i-1].getEnd()) {
            ranges[i-1].setRange(ranges[i-1].getStart(), ranges[i].getEnd());
            ranges.erase(ranges.begin() + i);
        }
    }

    for (Range r : ranges) {
        count += r.getEnd() - r.getStart() + 1;
    }

    return count;
}

int main() {
    Part2 p2;
    p2.readFile();
    long long fresh_count = p2.countFresh();

    cout << fresh_count << endl;
}