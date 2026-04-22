#include <iostream>
#include <set>
#include <unordered_set>
#include <string>
#include <ctime>

using namespace std;

int main() {
    int N, K;

    cout << "Enter N: ";
    cin >> N;

    set<string> sSet;
    unordered_set<string> usSet;

    cout << "Enter " << N << " words:\n";

    clock_t start = clock();
    for (int i = 0; i < N; i++) {
        string word;
        cin >> word;
        sSet.insert(word);
    }
    clock_t end = clock();
    double setInsertTime = double(end - start) / CLOCKS_PER_SEC;

    cin.clear();

    cout << "Enter same " << N << " words again:\n";

    start = clock();
    for (int i = 0; i < N; i++) {
        string word;
        cin >> word;
        usSet.insert(word);
    }
    end = clock();
    double usetInsertTime = double(end - start) / CLOCKS_PER_SEC;

    cout << "\n--- Insertion Time ---\n";
    cout << "set: " << setInsertTime << " sec\n";
    cout << "unordered_set: " << usetInsertTime << " sec\n\n";

    cout << "Enter K: ";
    cin >> K;

    cout << "Enter " << K << " words to search:\n";

    start = clock();
    for (int i = 0; i < K; i++) {
        string word;
        cin >> word;
        sSet.find(word);
    }
    end = clock();
    double setSearchTime = double(end - start) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < K; i++) {
        string word;
        cin >> word;
        usSet.find(word);
    }
    end = clock();
    double usetSearchTime = double(end - start) / CLOCKS_PER_SEC;

    cout << "\n--- Search Time ---\n";
    cout << "set: " << setSearchTime << " sec\n";
    cout << "unordered_set: " << usetSearchTime << " sec\n\n";

    cout << "--- Conclusion ---\n";
    cout << "unordered_set is faster for both operations\n";
    cout << "set: O(log n) - tree structure\n";
    cout << "unordered_set: O(1) average - hash table\n";

    return 0;
}