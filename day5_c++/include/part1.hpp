#pragma once
#include <vector>

using namespace std;

class Range {
    private:
        long long start;
        long long end;

    public:
        void setRange(long long s, long long e) {start = s; end = e;};
        bool inRange(long long value);
};

class Part1 {
    private:
        vector<Range> ranges;
        vector<long long> ids;
    
    public:
        void readFile();
        int countFresh();
};