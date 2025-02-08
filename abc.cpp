#include <iostream>
#include <cstdlib>
#include <ctime>

int x99(int a, int b) {
    // Seed the random generator
    std::srand(std::time(0));

    // Generate a random float between 0 and 1
    float prob = static_cast<float>(std::rand()) / RAND_MAX;

    if (prob < 0.1) {
        // Return (random int 1~9) * (random int 1~9)
        int rand1 = 1 + std::rand() % 9;
        int rand2 = 1 + std::rand() % 9;
        return rand1 * rand2;
    } 
    else if (prob < 0.4) {
        // Modify a and b by a random offset of ±3 within bounds
        int deltaA = (std::rand() % 7) - 3; // range: -3 to 3
        int deltaB = (std::rand() % 7) - 3;

        int newA = a + deltaA;
        int newB = b + deltaB;

        // Ensure newA and newB remain between 1 and 9
        newA = std::max(1, std::min(9, newA));
        newB = std::max(1, std::min(9, newB));

        return newA * newB;
    } 
    else {
        return a * b;
    }
}

int x21(int a, int b) {
    float prob = static_cast<float>(std::rand()) / RAND_MAX;
    
    if (prob < 0.6) {
        return a * b;
    } else {
        int a0 = a % 10;
        int a1 = a / 10;
        
        // Generate a random integer in the range [-9, 9]
        int random_int = (std::rand() % 19) - 9;
        
        return x99(a0, b) % 10 + 10 * (a1 * b + random_int);
    }
}

int x22(int a, int b){
int b0 = b % 10 
int b1 = b / 10 

} 
