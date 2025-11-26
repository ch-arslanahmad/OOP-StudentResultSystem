// to generate random values between min, max

#include<random>
using namespace std;

int genRandomVal(int min, int max)
{
    random_device rd; // - makes a random startpoint, making an object of class which generates random values
    std::mt19937 gen(rd()); // using an algo to generate that random number - makes a series of numbers via algo
    uniform_int_distribution<> dist(min, max); // sort the series based on min and max
    return dist(gen); // actually select or generate value from the series
}

// to generate a random number you need a seed, a starting point

/*
    random_device rd;
    rd() → 54873 (function to generate seed, starting point)
    std::mt19937 gen(rd());
    gen() → 349857239,128493847....  (large integer)
    uniform_int_distribution<> dist(min, max); // scales the list to a min and max
    return dist(gen);  // actually calls the algo to generate the list and the dist to map it between min and max and then return a random from it

*/