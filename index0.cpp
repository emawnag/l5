#include <iostream>
#include <vector>
using namespace std;

void printCombination(const vector<char>& combination) {
    for (size_t i = 0; i < combination.size(); i++) {
        cout << combination[i];
        if (i < combination.size() - 1) {
            cout << "*";
        }
    }
}

int main() {
    string elements = "abcdef";
    int n = elements.size();

    bool first = true;
int cc = 0;
    // Use bitmasking to generate all combinations
    for (int mask = 1; mask < (1 << n); ++mask) {  // Skip mask 0 (empty set)
        vector<char> combination;
        
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                combination.push_back(elements[i]);
            }
        }

        if (!first) {
            cout << "+cc["<<cc<<"]*";cc++;
        }
        first = false;

        printCombination(combination);
    }

    cout << endl;
    return 0;
}
