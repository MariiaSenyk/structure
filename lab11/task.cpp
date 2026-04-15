#include <iostream>
#include <vector>
using namespace std;

static void showGraph(const vector<vector<int> > &matrix)
{
    for (const auto &row: matrix) {
        for (const auto col: row) {
            cout << col << " ";
        }
        cout << endl;
    }
}

static void createConnectList(vector<vector<int> > &matrix, vector<vector<int> > &list, bool showList) {
    for (int i = 0; i < matrix.size(); i++) {
        list.push_back({});
        if (showList) {
            cout << "Vertex " << i + 1 << ": ";
        }
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] != 0) {
                list[i].push_back(j + 1);
                if (showList) {
                    cout << j + 1 << " ";
                }
            }
        }
        if (showList) {
            cout << endl;
        }
    }
}

int countEdges(const vector<vector<int> > &matrix) {
    int edges = 0;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] != 0) {
                edges++;
            }
        }
    }
    return edges / 2;
}

void calculatePowOfVertex(vector<vector<int> > &matrix, int &max, int &min) {
    vector<vector<int> > listOfConnect;
    createConnectList(matrix, listOfConnect, false);

    for (auto row: listOfConnect) {
        if (row.size() > max) {
            max = row.size();
        } else if (row.size() < min) {
            min = row.size();
        }
    }
    cout << "Maximum number of vertices: " << max << endl;
    cout << "Minimum number of vertices: " << min << endl;
}

void haveSimilarPow(vector<vector<int> > &matrix) {
    vector<vector<int> > listOfConnect;
    createConnectList(matrix, listOfConnect, false);
    for (int i = 0; i < listOfConnect.size(); i++) {
        for (int j = i; j < listOfConnect.size(); j++) {
            if (listOfConnect[i].size() == listOfConnect[j].size() && i != j) {
                cout << "Vertex " << i + 1 << " with " << j + 1 << endl;
            }
        }
    }
}

int findLongestPath(vector<vector<int> > &matrix, int &firstVertex, int &secondVertex) {
    int longest = 0;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] > longest) {
                longest = matrix[i][j];
                firstVertex = i;
                secondVertex = j;
            }
        }
    }
    return longest;
}

static void showVector(const vector<int> v) {
    for (auto i: v) {
        cout << i << " ";
    }
}

static bool containsValue(const vector<int> &list, const int value) {
    for (const int i: list) {
        if (i == value) {
            return true;
        }
    }
    return false;
}

static void testFunction(const vector<vector<int> > &matrix,
                         int currentVertex,
                         vector<int> visitedVertex,
                         int needEdge,
                         int currentSum,
                         int &minSum,
                         vector<int> &lastVariant,
                         bool show) {
    visitedVertex.push_back(currentVertex);
    if (visitedVertex.size() - 1 == needEdge && minSum > currentSum) {
        minSum = currentSum;
        lastVariant = visitedVertex;
    }


    for (int j = 0; j < matrix.size(); j++) {
        if (!containsValue(visitedVertex, j) && matrix[currentVertex][j] != 0) {
            currentSum += matrix[currentVertex][j];
            if (show) { cout << j << " " << currentSum << endl; }


            testFunction(
                matrix,
                j,
                visitedVertex,
                needEdge,
                currentSum,
                minSum,
                lastVariant,
                show);
            if (show) { cout << "reverse" << endl; }
            currentSum -= matrix[currentVertex][j];
        }
    }
}

static void findShortestRout(const vector<vector<int> > &matrix, int edges, bool show) {
    if (edges > matrix.size() - 1) {
        cout << "Incorrect number of edges" << endl;
        return;
    }
    vector<int> lastVariant = {};
    int minSum = 1000000000;
    vector<int> v = {};


    for (int i = 0; i < matrix.size(); i++) {
        if (show) { cout << "next Vertex: " << i << endl; }
        testFunction(
            matrix,
            i,
            v,
            edges,
            0,
            minSum,
            lastVariant,
            show);
    }
    cout << "Minimal sum = " << minSum << endl;
    cout << "Vector: ";
    showVector(lastVariant);
    cout << endl;
}

int main()
{
    vector<vector<int> > listOfConnect = {};

    vector<vector<int> > matrix = {
        {0, 0, 3, 0, 0, 0, 10},
        {0, 0, 6, 1, 0, 0, 0},
        {3, 6, 0, 5, 2, 8, 0},
        {0, 1, 5, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0, 0},
        {0, 0, 8, 0, 0, 0, 11},
        {10, 0, 0, 0, 0, 11, 0},
    };
    cout << "-----Adjacency matrix-----" << endl;
    showGraph(matrix);
    cout << "---------Vertices---------" << endl;
    createConnectList(matrix, listOfConnect, true);
    cout << "--------------------------" << endl;
    cout << "Edges in graph: " << countEdges(matrix) << endl;
    cout << "--------------------------" << endl;
    int maxPow = 0;
    int minPow = matrix.size();
    calculatePowOfVertex(matrix, maxPow, minPow);
    cout << "--------------------------" << endl;
    cout << "Similar pow:\n";
    haveSimilarPow(matrix);
    cout << "---------------------------------------" << endl;
    int firstVertex = -1;
    int secondVertex = -1;
    int longest = findLongestPath(matrix, firstVertex, secondVertex);
    cout << "Longest Path: " << longest << " | With vertex: " << firstVertex + 1 << " and " << secondVertex + 1 <<
            endl;
    cout << "---------------------------------------" << endl;
    findShortestRout(matrix, 2, false);

    return 0;
}
