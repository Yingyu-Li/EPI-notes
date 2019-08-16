#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>

using namespace std;

template<typename D> // DistanceType
class V { // GraphVertex
public:
    vector<pair<V<D>*, D>> edges; // (V*, distance) pair
    int id; // id of this vertex

    pair<D, int> distance; // (distance, #edges) pair
    V* pred; // predecessor in the shortest path
    bool visited;

    V(void) :
        distance(numeric_limits<D>::max(), 0),
        pred(nullptr),
        visited(false){}
};

template <typename D>
class Comp { // of V<D>* for the
public:
};

template <typename D>
void Dijkstra_shortest_path(unordered_map<int, V<double>> &G, V<D>* s, V<D>* t) {

}



int main() {
    // construct a graph
    unordered_map<int, V<double>> G;
    G[1].id = 1;
    G[1].edges.emplace_back(G[2], 3.0);
    G[1].edges.emplace_back(G[3], 5.0);
    G[2].id = 2;
    G[2].edges.emplace_back(G[3], 1.0);
    G[3].id = 3;
    Dijkstra_shortest_path<double>(G, &G[1], &G[3]);



    return 0;
}