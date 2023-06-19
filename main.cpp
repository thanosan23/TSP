#include <algorithm>
#include <ios>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

#define N 20
#define TEST false
vector< vector< pair<int, int> > > graph(N);

vector<int> generate_hamiltonian_cycle(int n) {
    vector<int> a(n);
    for(int i = 0; i < n; i++) a[i] = i;
    next_permutation(a.begin(), a.end());
    return a;
}

double cost(const vector<int> &cycle) {
    double ret = 0;
    for(int i = 1; i < cycle.size(); i++) {
        for(pair<int, int> &node : graph[cycle[i-1]]) {
            if(node.first == cycle[i]) {
                ret += node.second;
                break;
            } else {
                return 1e3;
            }
        }
    }
    return ret;
}

void add_bidirectional(int u, int v, int weight) {
    graph[u].push_back(make_pair(v, weight));
    graph[u].push_back(make_pair(u, weight));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    // set up the data using an adjacency list
    if(!TEST) {
        cout << "Enter the number of cities: \n";
        cin >> n;

        int number_of_connections;
        cout << "Enter number of roads: \n";
        cin >> number_of_connections;
        for(int i = 0; i < number_of_connections; i++) {
            int x, y, w;
            cout << "Enter city 1:\n";
            cin >> x;
            cout << "Enter city 2:\n";
            cin >> y;
            cout << "Enter the weight of the city:\n";
            cin >> w;
            add_bidirectional(x, y, w);
        }
    } else {
        // for testing purposes
        n = 3;
        add_bidirectional(0, 1, 4);
        add_bidirectional(1, 2, 1);
        add_bidirectional(2, 0, 1);
    }
    // generate a random hamiltonian cycle
    vector<int> cycle = generate_hamiltonian_cycle(n);
    // run simulated annealing on the hamiltonian cycle
    double temperature = 100;
    double best = cost(cycle);
    srand(time(NULL));
    for(int x = 0; x < 1000; x++) {
        temperature *= 0.99;
        for(int i = 0; i < 500; i++) {
            int idx1 = rand() % n;
            int idx2 = rand() % n;
            vector<int> neighbour(cycle);
            swap(neighbour[idx1], neighbour[idx2]);
            if(cost(neighbour) < best) {
                best = cost(neighbour);
                cycle.assign(neighbour.begin(), neighbour.end());
            } else {
                if(exp(cost(neighbour)-cost(cycle)/temperature) < (rand()%1000)/1000.0f) {
                    best = cost(neighbour);
                    cycle.assign(neighbour.begin(), neighbour.end());
                 }
            }
        }
    }
    for(int &i : cycle) cout << i << ' ';
    cout << '\n' << cost(cycle) << '\n';
}
