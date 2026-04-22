#include <iostream>
#include <set>
#include <unordered_set>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

int main() {
    int N, K;
    cout << "Enter N: ";
    cin >> N;

    set<string> s;
    unordered_set<string> us;
    string word;

    cout << "Enter " << N << " words for set:\n";
    auto start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        cin >> word;
        s.insert(word);
    }
    auto end = high_resolution_clock::now();
    auto set_insert = duration_cast<microseconds>(end - start);

    cout << "Enter " << N << " words for unordered_set:\n";
    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        cin >> word;
        us.insert(word);
    }
    end = high_resolution_clock::now();
    auto uset_insert = duration_cast<microseconds>(end - start);

    cout << "\nInsertion (microseconds):\n";
    cout << "set: " << set_insert.count() << "\n";
    cout << "unordered_set: " << uset_insert.count() << "\n";

    cout << "\nEnter K: ";
    cin >> K;

    cout << "Enter " << K << " words to search in set:\n";
    start = high_resolution_clock::now();
    for (int i = 0; i < K; i++) {
        cin >> word;
        s.find(word);
    }
    end = high_resolution_clock::now();
    auto set_search = duration_cast<microseconds>(end - start);

    cout << "Enter " << K << " words to search in unordered_set:\n";
    start = high_resolution_clock::now();
    for (int i = 0; i < K; i++) {
        cin >> word;
        us.find(word);
    }
    end = high_resolution_clock::now();
    auto uset_search = duration_cast<microseconds>(end - start);

    cout << "\nSearch (microseconds):\n";
    cout << "set: " << set_search.count() << "\n";
    cout << "unordered_set: " << uset_search.count() << "\n";

    cout << "\nConclusion: unordered_set is faster (hash table O(1) vs tree O(log n))\n";

    return 0;
}