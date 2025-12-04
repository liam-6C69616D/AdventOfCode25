#pragma once
#include <vector>

using namespace std;

class Bank {
    public:
        vector<int> batteries;
        int highestJoltage();
};

class Part1 {
    private:
        vector<Bank> banks;

    public:
        void readFile();
        vector<Bank> getBanks();
        int totalJoltage();
};