#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to;
    int weight;
};

struct Node {
    int city;
    int distance;
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

class TravelPlanner {
    private:
        int numCities;
        vector<vector<Edge>> adjList;

    public:
    
}