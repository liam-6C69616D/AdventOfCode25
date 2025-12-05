#pragma once
#include <vector>
#include <set>

using namespace std;

class Range {
    private:
        long long start;
        long long end;

    public:
        void setRange(long long s, long long e) {start = s; end = e;};
        long long getStart() {return start;};
        long long getEnd() {return end;};
        static bool compareRanges(Range& lhs, Range& rhs) {return lhs.getStart() < rhs.getStart();}
};

class Part2 {
    private:
        vector<Range> ranges;
    
    public:
        void readFile();
        long long countFresh();
};