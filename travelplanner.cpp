#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>

using namespace std;

const double INF = 1e9;

struct City {
    string name;
    int x, y;
};
struct Edge {
    int to;
    double weight;
};

struct Node {
    int cityID;
    double distance;
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

class TravelPlanner {
    private:
        vector<City> cities;
        vector<vector<Edge>> adjList;

    public:
        void addCity() {
            string name;
            int x, y;
            cout << endl << "Enter city name: ";
            cin >> name;
            cout << endl << "Enter X coordinate: ";
            cin >> x;
            cout << endl << "Enter Y coordinate: ";
            cin >> y;

            cities.push_back({name, x, y});
            adjList.push_back({});

            cout << endl << "City added successfully with ID: " << cities.size() - 1 << endl;
        }

        void addRoute() {
            if (cities.size() < 2) {
                cout << endl << "At least two cities are required to add a route." << endl;
                return;
            }

            int from, to;
            cout << endl << "Enter start city ID: ";
            cin >> from;
            cout << endl << "Enter destination city ID: ";
            cin >> to;

            if (from >= 0 && from < cities.size() && to >= 0 && to < cities.size()) {
                double weight = sqrt(pow(cities[from].x - cities[to].x, 2) + pow(cities[from].y - cities[to].y, 2));
                adjList[from].push_back({to, weight});
                adjList[to].push_back({from, weight});
                cout << endl << "Route added successfully with distance: " << weight << endl;
            } else {
                cout << endl << "Invalid city IDs." << endl;
            }
        }

        void displayCities() {
            cout << endl << "Cities:" << endl;
            for (size_t i = 0; i < cities.size(); i++) {
                cout << "ID: [" << i << "], Name: " << cities[i].name << ", Coordinates: (" << cities[i].x << ", " << cities[i].y << ")" << endl;
            }
        }

        void displayRoutes() {
            cout << endl << "Routes:" << endl;
            for (size_t i = 0; i < adjList.size(); i++) {
                cout << "City ID [" << i << "] routes:" << endl;
                for (const auto& edge : adjList[i]) {
                    cout << "  To City ID [" << edge.to << "], Distance: " << edge.weight << endl;
                }
            }
        }

        void findShortestPath() {
            if (cities.size() < 2) {
                cout << endl << "At least two cities are required to find a path." << endl;
                return;
            }

            int start, end;
            displayCities();
            cout << endl << "Enter start city ID: ";
            cin >> start;
            cout << endl << "Enter destination city ID: ";
            cin >> end;

            if (start >= 0 && start < cities.size() && end >= 0 && end < cities.size()) {
                vector<double> dist(cities.size(), INF);
                vector<int> prev(cities.size(), -1);
                priority_queue<Node, vector<Node>, greater<Node>> pq;

                dist[start] = 0;
                pq.push({start, 0.0});

                while (!pq.empty()) {
                    Node current = pq.top();
                    pq.pop();

                    if (current.distance > dist[current.cityID]) continue;
                    if (current.cityID == end) break;

                    for (const auto& edge : adjList[current.cityID]) {
                        double newDist = current.distance + edge.weight;
                        if (newDist < dist[edge.to]) {
                            dist[edge.to] = newDist;
                            prev[edge.to] = current.cityID;
                            pq.push({edge.to, newDist});
                        }
                    }
                }

                if (dist[end] == INF) {
                    cout << endl << "No path found between the selected cities." << endl;
                } else {
                    cout << endl << "Shortest distance: " << dist[end] << endl;
                    
                    stack<int> path;
                    for (int at = end; at != -1; at = prev[at]) {
                        path.push(at);
                    }
                    cout << "Path: ";
                    while (!path.empty()) {
                        cout << cities[path.top()].name;
                        path.pop();
                        if (!path.empty()) cout << " -> ";
                    }
                    cout << endl;
                }
            } else {
                cout << endl << "Invalid city IDs." << endl;
            }
        }

        void displayMenu() {
            int choice = 0;
            while (choice != 5) {
                cout << endl << "Travel Planner Menu:" << endl;
                cout << "1. Add City" << endl;
                cout << "2. Add Route" << endl;
                cout << "3. Display Cities and Routes" << endl;
                cout << "4. Find Shortest Path" << endl;
                cout << "5. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        addCity();
                        break;
                    case 2:
                        addRoute();
                        break;
                    case 3:
                        displayCities();
                        displayRoutes();
                        break;
                    case 4:
                        findShortestPath();
                        break;
                    case 5:
                        cout << endl << "Exiting Travel Planner." << endl;
                        break;
                    default:
                        cout << endl << "Invalid choice. Please try again." << endl;
                }
            }
        }         
};

int main() {
    TravelPlanner planner;
    planner.displayMenu();
    return 0;
}
