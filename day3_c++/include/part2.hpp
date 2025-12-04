#pragma once
#include <vector>

using namespace std;

class Bank {
    public:
        vector<int> batteries;
        long long highestJoltage();
};

class Part2 {
    private:
        vector<Bank> banks;

    public:
        void readFile();
        vector<Bank> getBanks();
        int totalJoltage();
};