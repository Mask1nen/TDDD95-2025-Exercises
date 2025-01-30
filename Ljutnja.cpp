#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int main() {
    unsigned long long M, N, currentChildWants;
    cin >> M >> N;
    unsigned long long sumAnger = 0;
    unsigned long long candiesWanted = 0;
    vector<unsigned long long> children;

    for (int i = 0; i < N; i++) {
        cin >> currentChildWants;
        candiesWanted += currentChildWants;
        if(currentChildWants > 0) {
            children.push_back(currentChildWants);
        }
    }

    if (M > candiesWanted) {
        cout << 0;
        return 0;
    }

    stable_sort(children.begin(), children.end()); //sort children vector in ascending order

    unsigned long long candiesLeft = candiesWanted - M; //candies that cannot be handed out, the point is to distribute this evenly among the children

    for (int i = 0; i < children.size(); i++) {
        if(candiesLeft == 0) {
            break;
        }
        int childrenLeft = children.size() - i; //children that havent gotten candy yet
        unsigned long long equalDivide = floor(candiesLeft / childrenLeft); //how many candies the child would not recieve if split evenly with the remaining children
        unsigned long long candiesNotRecieved = min(children[i], equalDivide); //how many candies the child will not recieve, this uses the ascending order of the children vector to scew the distribution of candies to the children who want more candies
        sumAnger += candiesNotRecieved * candiesNotRecieved; //how angry the child is by not recieving these candies
        candiesLeft -= candiesNotRecieved; //how many candies are left to "not recieve"
    } 

    cout << sumAnger;
    return 0;
}
