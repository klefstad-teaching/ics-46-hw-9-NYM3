#include "dijkstras.h"
struct Node {
    int vertex;
    int distance;
    Node(int v, int dist) : vertex(v), distance(dist) {}
};

struct CompareNode {
    bool operator()(const Node& a, const Node& b) {
        return a.distance > b.distance; // min-heap
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);

    distance[source] = 0;
    previous.resize(n, -1);

    priority_queue<Node, vector<Node>, CompareNode> pq;
    pq.push(Node(source, 0));

    while (!pq.empty()) {
        Node top = pq.top();
        pq.pop();

        int u = top.vertex;
        if (visited[u]) continue;

        visited[u] = true;

        for (auto &edge : G[u]) {
            int v = edge.dst;
            int w = edge.weight;

            if (!visited[v] && distance[u] != INF && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances,
                                  const vector<int>& previous,
                                  int destination)
{
    vector<int> path;
    if (destination < 0 || destination >= (int)distances.size() ||
        distances[destination] == INF) {
        return path;
    }
    int current = destination;
    while (current != -1) {
        path.push_back(current);
        current = previous[current];
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    for (int i = 0; i < (int)path.size(); i++) {
        cout << path[i];
        if (i < (int)path.size() - 1) cout << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}
