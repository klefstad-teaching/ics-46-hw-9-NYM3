#include "dijkstras.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <graphfile.txt>" << endl;
        return 1;
    }

    Graph G;
    try {
        file_to_graph(argv[1], G);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }

    vector<int> previous;
    vector<int> dist = dijkstra_shortest_path(G, 0, previous);

    for (int v = 0; v < G.numVertices; v++) {
        vector<int> path = extract_shortest_path(dist, previous, v);

        if (!path.empty()) {
for (int i = 0; i < (int)path.size(); i++) {
    cout << path[i];
    if (i < (int)path.size() - 1) {
        cout << " ";
    }
}
cout << endl;
         cout << "Total cost is " << dist[v] << endl;
        } else {
            cout << v << " is unreachable from 0." << endl;
        }
    }

    return 0;
}
