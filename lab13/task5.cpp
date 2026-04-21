#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;
using Clock = chrono::high_resolution_clock;
using Ms = chrono::duration<double, milli>;

string makeKey(int i) {
    return "key_" + to_string(i);
}

double benchInsertMap(int n) {
    map<string, int> m;
    auto t0 = Clock::now();
    for (int i = 0; i < n; ++i) m[makeKey(i)] = i;
    return Ms(Clock::now() - t0).count();
}

double benchDeleteMap(int n, int del) {
    map<string, int> m;
    for (int i = 0; i < n; ++i) m[makeKey(i)] = i;
    mt19937 rng(42);
    uniform_int_distribution<int> dist(0, n - 1);
    auto t0 = Clock::now();
    for (int i = 0; i < del; ++i) m.erase(makeKey(dist(rng)));
    return Ms(Clock::now() - t0).count();
}

double benchSearchMap(int n, int k) {
    map<string, int> m;
    for (int i = 0; i < n; ++i) m[makeKey(i)] = i;
    mt19937 rng(99);
    uniform_int_distribution<int> dist(0, n - 1);
    volatile int sink = 0;
    auto t0 = Clock::now();
    for (int i = 0; i < k; ++i) {
        auto it = m.find(makeKey(dist(rng)));
        if (it != m.end()) sink += it->second;
    }
    return Ms(Clock::now() - t0).count();
}

double benchInsertUMap(int n) {
    unordered_map<string, int> m;
    m.reserve(n);
    auto t0 = Clock::now();
    for (int i = 0; i < n; ++i) m[makeKey(i)] = i;
    return Ms(Clock::now() - t0).count();
}

double benchDeleteUMap(int n, int del) {
    unordered_map<string, int> m;
    m.reserve(n);
    for (int i = 0; i < n; ++i) m[makeKey(i)] = i;
    mt19937 rng(42);
    uniform_int_distribution<int> dist(0, n - 1);
    auto t0 = Clock::now();
    for (int i = 0; i < del; ++i) m.erase(makeKey(dist(rng)));
    return Ms(Clock::now() - t0).count();
}

double benchSearchUMap(int n, int k) {
    unordered_map<string, int> m;
    m.reserve(n);
    for (int i = 0; i < n; ++i) m[makeKey(i)] = i;
    mt19937 rng(99);
    uniform_int_distribution<int> dist(0, n - 1);
    volatile int sink = 0;
    auto t0 = Clock::now();
    for (int i = 0; i < k; ++i) {
        auto it = m.find(makeKey(dist(rng)));
        if (it != m.end()) sink += it->second;
    }
    return Ms(Clock::now() - t0).count();
}

void printRow(const string &op, double mapMs, double umapMs) {
    cout << left << setw(22) << op
            << right << setw(14) << fixed << setprecision(3) << mapMs
            << setw(20) << umapMs
            << setw(12) << setprecision(2) << (mapMs / umapMs) << "x\n";
}

int main() {
    int N, M, K;
    cout << "Number of elements to insert  N: ";
    cin >> N;
    cout << "Number of elements to delete  M: ";
    cin >> M;
    cout << "Number of elements to search  K: ";
    cin >> K;

    if (M > N) {
        cerr << "M cannot be greater than N.\n";
        return 1;
    }

    cout << "\nRunning benchmarks...\n\n";

    double t_ins_map = benchInsertMap(N);
    double t_del_map = benchDeleteMap(N, M);
    double t_sea_map = benchSearchMap(N, K);

    double t_ins_umap = benchInsertUMap(N);
    double t_del_umap = benchDeleteUMap(N, M);
    double t_sea_umap = benchSearchUMap(N, K);

    cout << string(68, '-') << "\n";
    cout << left << setw(22) << "Operation"
            << right << setw(14) << "map (ms)"
            << setw(20) << "unordered_map (ms)"
            << setw(12) << "Speedup" << "\n";
    cout << string(68, '-') << "\n";

    printRow("Insert (" + to_string(N) + ")", t_ins_map, t_ins_umap);
    printRow("Delete (" + to_string(M) + ")", t_del_map, t_del_umap);
    printRow("Search (" + to_string(K) + ")", t_sea_map, t_sea_umap);

    cout << string(68, '-') << "\n";
    cout << "\nConclusion:\n"
            << "  map           - ordered, O(log n) for all operations.\n"
            << "  unordered_map - unordered, O(1) average case.\n"
            << "  For large N, unordered_map is typically 3-10x faster.\n";

    return 0;
}
