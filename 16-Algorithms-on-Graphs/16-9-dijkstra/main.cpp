#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include <set>

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
void output_shortest_path(V<D>* t) {
    if (t) {
        output_shortest_path(t->pred);
    }
    else {
        cout << "shortest path: \n";
        return;
    }
    cout << t->id << " ";
}

template <typename D>
class Comp { // of V<D>* for the node_set
public:
    const bool operator() (const V<D>* lhs, const V<D>* rhs) const {
        return lhs->distance.first < rhs->distance.first ||
                (lhs->distance.first == rhs->distance.first
                && lhs->distance.second < rhs->distance.second);
    }
};

template <typename D>
void Dijkstra_shortest_path(unordered_map<int, V<D>> &G, V<D>* s, V<D>* t) {
    s->distance = {0, 0};
    set<V<D>*, Comp<D>> node_set;
    node_set.emplace(s);

    while (! t->visited) {
        V<D>* u = nullptr;
        while (! node_set.empty()) {
            u = *node_set.cbegin();
            node_set.erase(node_set.cbegin());
            if (! u->visited) {
                break;
            }
        }
        if (u) {
            u->visited = true;
            for (const pair<V<D>*, D> &v : u->edges) { // (neighbor_node*, distance_between_uv) pair
                D v_distance = u->distance.first + v.second;
                int v_num_edges = u->distance.second + 1;
                if (v.first->distance.first > v_distance ||
                        (v.first->distance.first == v_distance &&
                        v.first->distance.second > v_num_edges)) { // update
                    node_set.erase(v.first);
                    v.first->pred = u;
                    v.first->distance = {v_distance, v_num_edges};
                    node_set.emplace(v.first);
                }
            }
        }
        else {
            cout << "u is not valid.\n";
            break;
        }
    }
    output_shortest_path(t);
}



int main() {
    // construct a graph
    unordered_map<int, V<double>> G;
    G[1].id = 1;
    G[1].edges.emplace_back(&G[2], 3);
    G[1].edges.emplace_back(&G[3], 5);
    G[2].id = 2;
    G[2].edges.emplace_back(&G[3], 1);
    G[3].id = 3;
    Dijkstra_shortest_path<double>(G, &G[1], &G[3]);



    return 0;
}