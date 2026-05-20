#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Activity {
    int start, end, index;
};

int main() {
    int n;
    cout << "Enter the number of classes: ";
    cin >> n;

    vector<Activity> a(n);

    cout << "Enter the start and end times for each class:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Class " << i + 1 << " (start end): ";
        cin >> a[i].start >> a[i].end;

        if (a[i].start >= a[i].end) {
            cout << "Error: Start time must be less than end time!" << endl;
            return 1;
        }

        a[i].index = i + 1;
    }

    sort(a.begin(), a.end(), [](const Activity &x, const Activity &y) {
        if (x.end == y.end)
            return x.start < y.start;
        return x.end < y.end;
    });

    cout << "\nSelected classes:" << endl;
    cout << "Index\tStart\tEnd" << endl;
    cout << "-----------------------------" << endl;

    int count = 0;
    int lastEnd = -1;

    for (const auto &act: a) {
        if (act.start >= lastEnd) {
            cout << act.index << "\t\t" << act.start << "\t\t" << act.end << endl;
            lastEnd = act.end;
            count++;
        }
    }

    cout << "-----------------------------" << endl;
    cout << "The maximum number of non-overlapping classes: " << count << endl;

    return 0;
}
