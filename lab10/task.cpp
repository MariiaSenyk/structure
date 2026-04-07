#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
    vector<vector<int> > adjMatrix;
    int numVertices;

public:
    Graph(int vertices) : numVertices(vertices) {
        adjMatrix.resize(vertices, vector<int>(vertices, 0));
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    vector<vector<int> > getAdjacencyList() {
        vector<vector<int> > adjList(numVertices);
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                if (adjMatrix[i][j] != 0) {
                    adjList[i].push_back(j);
                }
            }
        }
        return adjList;
    }

    bool isComplete() {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                if (i != j && adjMatrix[i][j] == 0) {
                    return false;
                }
            }
        }
        return true;
    }

    double averagePathLength() {
        int totalDistance = 0;
        int count = 0;
        for (int i = 0; i < numVertices; ++i) {
            for (int j = i + 1; j < numVertices; ++j) {
                if (adjMatrix[i][j] != 0) {
                    totalDistance += adjMatrix[i][j];
                    count++;
                }
            }
        }
        return (count == 0) ? 0 : (double) totalDistance / count;
    }

    void checkIsolated() {
        for (int i = 0; i < numVertices; ++i) {
            int degree = 0;
            for (int j = 0; j < numVertices; ++j) {
                if (adjMatrix[i][j] != 0) {
                    degree++;
                }
            }
            if (degree == 1) {
                cout << "Isolated point: " << i + 1 << " with nearest distance: ";
                for (int j = 0; j < numVertices; ++j) {
                    if (adjMatrix[i][j] != 0) {
                        cout << adjMatrix[i][j] << endl;
                        break;
                    }
                }
            }
        }
    }

    int countIsolated() {
        int count = 0;
        for (int i = 0; i < numVertices; ++i) {
            int degree = 0;
            for (int j = 0; j < numVertices; ++j) {
                if (adjMatrix[i][j] != 0) {
                    degree++;
                }
            }
            if (degree == 1) {
                count++;
            }
        }
        return count;
    }

    void findLongestPath() {
        int maxLength = -1;
        pair<int, int> longestPath;
        for (int i = 0; i < numVertices; ++i) {
            for (int j = i + 1; j < numVertices; ++j) {
                if (adjMatrix[i][j] != 0) {
                    for (int k = j + 1; k < numVertices; ++k) {
                        if (adjMatrix[j][k] != 0 && adjMatrix[i][k] != 0) {
                            int totalLength = adjMatrix[i][j] + adjMatrix[j][k] + adjMatrix[i][k];
                            if (totalLength > maxLength) {
                                maxLength = totalLength;
                                longestPath = make_pair(i + 1, j + 1);
                            }
                        }
                    }
                }
            }
        }
        cout << "Longest path is between points: " << longestPath.first << " and " << longestPath.second << endl;
    }

    bool hasHamiltonianPath() {
        return false;
    }
};

int main() {
    Graph g(6);

    g.addEdge(0, 1, 6);
    g.addEdge(0, 2, 2);
    g.addEdge(0, 3, 9);
    g.addEdge(1, 4, 4);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 5, 7);

    vector<vector<int> > adjList = g.getAdjacencyList();
    cout << "Adjacency List:\n";
    for (int i = 0; i < adjList.size(); ++i) {
        cout << "Vertex " << i + 1 << ": ";
        for (int j: adjList[i]) {
            cout << j + 1 << " ";
        }
        cout << endl;
    }

    if (g.isComplete()) {
        cout << "Graph is complete.\n";
    } else {
        cout << "Graph is not complete.\n";
    }

    cout << "Average path length: " << g.averagePathLength() << endl;

    g.checkIsolated();

    cout << "Isolated points count: " << g.countIsolated() << endl;

    g.findLongestPath();

    if (g.hasHamiltonianPath()) {
        cout << "Graph has a Hamiltonian path.\n";
    } else {
        cout << "Graph does not have a Hamiltonian path.\n";
    }

    return 0;
}
