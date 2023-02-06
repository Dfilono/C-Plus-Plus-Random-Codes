#include <iostream>
#include <math.h>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

struct solution{
    double rank;
    double x;
    double y;
    double z;

    void fitness(){
        double ans = (6 * x + -y + pow(z, 200)) - 25;

        if (ans == 0){
            rank  = 9999;
        }
        else{
            rank = abs(1/ans);
        }
    }
};


int main(){
    // Create intial rnadom solutions
    random_device device;
    uniform_real_distribution<double> unif(-10000, 10000);
    vector<solution> solutions;

    const int NUM = 100000;
    for (int i = 0; i < NUM; i++){
        solutions.push_back(solution{0, unif(device), unif(device), unif(device)});
    }
    int gens = 100;
    while (gens > 0){
        // Run fitness function
        for (auto& s : solutions) {s.fitness(); }

        // Sort solutions by rank
        sort(solutions.begin(), 
            solutions.end(), 
            [](const auto& lhs, const auto& rhs){
                return lhs.rank > rhs.rank;
        });

        // Print top 10 solutions
        for_each(
            solutions.begin(),
            solutions.begin() + 10,
            [](const auto& s){
                cout << fixed << "Rank " << static_cast<int>(s.rank) << "\n x:"
                << s.x << " y:" << s.y << " z:" << s.z << " \n";
            }
        );
        // Take the top 1000 solutions
        const int SAMPLE_SIZE = 1000;
        vector<solution> sample;
        copy(solutions.begin(), 
        solutions.begin() + SAMPLE_SIZE,
        back_inserter(sample));
        solutions.clear();

        // Mutate the top soltions by %
        uniform_real_distribution<double> m(0.95, 1.05);
        for_each(
            sample.begin(),
            sample.end(),
            [&](auto& s){
                s.x *= m(device);
                s.y *= m(device);
                s.z *= m(device);
            }
        );
        
        // Cross over
        uniform_int_distribution<int> cross(0, SAMPLE_SIZE - 1);
        for (int i = 0; i < NUM; i++){
            solutions.push_back(solution{
                0,
                sample[cross(device)].x,
                sample[cross(device)].y,
                sample[cross(device)].z,
            });
        }
        sample.clear();
        gens -= 1;
    }

    
    return 0;
}
