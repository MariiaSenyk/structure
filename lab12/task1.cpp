#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

struct Book {
    string title;
    string author;
    string genre;
    double price;
    int popularity; // number of sales
    string date; // arrival date "YYYY-MM-DD"
    int stock;
};

void printHeader() {
    cout << "\n"
            << left
            << setw(28) << "Title"
            << setw(20) << "Author"
            << setw(14) << "Genre"
            << setw(8) << "Price"
            << setw(12) << "Popularity"
            << setw(12) << "Arrived"
            << setw(6) << "Stock"
            << "\n"
            << string(100, '-') << "\n";
}

void printBook(const Book &b) {
    cout << left
            << setw(28) << b.title
            << setw(20) << b.author
            << setw(14) << b.genre
            << setw(8) << fixed << setprecision(2) << b.price
            << setw(12) << b.popularity
            << setw(12) << b.date
            << setw(6) << b.stock
            << "\n";
}

void printAll(const vector<Book> &books) {
    if (books.empty()) {
        cout << "No books found.\n";
        return;
    }
    printHeader();
    for (const auto &b: books) printBook(b);
    cout << "Total: " << books.size() << " book(s)\n";
}

void addBook(vector<Book> &books) {
    Book b;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Title: ";
    getline(cin, b.title);
    cout << "Author: ";
    getline(cin, b.author);
    cout << "Genre: ";
    getline(cin, b.genre);
    cout << "Price: ";
    cin >> b.price;
    cout << "Popularity: ";
    cin >> b.popularity;
    cout << "Stock: ";
    cin >> b.stock;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Arrival date (YYYY-MM-DD): ";
    getline(cin, b.date);
    books.push_back(b);
    cout << "Book added.\n";
}

void removeSoldOut(vector<Book> &books) {
    int before = books.size();
    books.erase(
        remove_if(books.begin(), books.end(),
                  [](const Book &b) { return b.stock == 0; }),
        books.end()
    );
    cout << (before - (int) books.size()) << " sold-out book(s) removed.\n";
}


void sortByPrice(vector<Book> &books, bool ascending = true) {
    sort(books.begin(), books.end(), [ascending](const Book &a, const Book &b) {
        return ascending ? a.price < b.price : a.price > b.price;
    });
    cout << "Sorted by price (" << (ascending ? "asc" : "desc") << ").\n";
}

void sortByPopularity(vector<Book> &books) {
    sort(books.begin(), books.end(), [](const Book &a, const Book &b) {
        return a.popularity > b.popularity;
    });
    cout << "Sorted by popularity (desc).\n";
}

void sortByDate(vector<Book> &books) {
    sort(books.begin(), books.end(), [](const Book &a, const Book &b) {
        return a.date > b.date; // newest first
    });
    cout << "Sorted by arrival date (newest first).\n";
}


void filterByGenre(const vector<Book> &books) {
    string genre;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Genre: ";
    getline(cin, genre);

    vector<Book> result;
    copy_if(books.begin(), books.end(), back_inserter(result),
            [&genre](const Book &b) {
                return b.genre == genre;
            });
    printAll(result);
}

void filterByPrice(const vector<Book> &books) {
    double lo, hi;
    cout << "Min price: ";
    cin >> lo;
    cout << "Max price: ";
    cin >> hi;

    vector<Book> result;
    copy_if(books.begin(), books.end(), back_inserter(result),
            [lo, hi](const Book &b) {
                return b.price >= lo && b.price <= hi;
            });
    printAll(result);
}


void searchBooks(const vector<Book> &books) {
    string query;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Search (title or author): ";
    getline(cin, query);

    string lq = query;
    transform(lq.begin(), lq.end(), lq.begin(),
              [](unsigned char c) { return tolower(c); });

    vector<Book> result;
    copy_if(books.begin(), books.end(), back_inserter(result),
            [&lq](const Book &b) {
                string lt = b.title, la = b.author;
                transform(lt.begin(), lt.end(), lt.begin(),
                          [](unsigned char c) { return tolower(c); });
                transform(la.begin(), la.end(), la.begin(),
                          [](unsigned char c) { return tolower(c); });
                return lt.find(lq) != string::npos ||
                       la.find(lq) != string::npos;
            });
    printAll(result);
}

void showMenu() {
    cout << "\n=== Bookstore Manager ===\n"
            << "1.  Show all books\n"
            << "2.  Add book\n"
            << "3.  Remove sold-out books\n"
            << "4.  Sort by price (ascending)\n"
            << "5.  Sort by price (descending)\n"
            << "6.  Sort by popularity\n"
            << "7.  Sort by arrival date\n"
            << "8.  Filter by genre\n"
            << "9.  Filter by price range\n"
            << "10. Search by title / author\n"
            << "0.  Exit\n"
            << "Your choice: ";
}

// ── Sample data ───────────────────────────────────────────────────────────────

void loadSampleData(vector<Book> &books) {
    books = {
        {"The Pragmatic Programmer", "D. Thomas", "Tech", 45.99, 320, "2023-03-15", 12},
        {"Clean Code", "R. Martin", "Tech", 39.99, 480, "2022-11-01", 5},
        {"Dune", "F. Herbert", "Sci-Fi", 19.99, 750, "2023-07-20", 20},
        {"1984", "G. Orwell", "Fiction", 12.99, 910, "2021-06-10", 8},
        {"The Hobbit", "J.R.R. Tolkien", "Fantasy", 14.99, 670, "2023-01-05", 15},
        {"Atomic Habits", "J. Clear", "Self-Help", 24.99, 1200, "2023-09-18", 30},
        {"Sapiens", "Y.N. Harari", "History", 22.50, 540, "2022-04-22", 0},
        {"The Alchemist", "P. Coelho", "Fiction", 11.99, 430, "2023-05-30", 0},
        {"Neuromancer", "W. Gibson", "Sci-Fi", 16.99, 290, "2023-08-14", 7},
        {"Design Patterns", "Gang of Four", "Tech", 55.00, 360, "2022-12-01", 3},
    };
}

int main() {
    vector<Book> books;
    loadSampleData(books);

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: printAll(books);
                break;
            case 2: addBook(books);
                break;
            case 3: removeSoldOut(books);
                break;
            case 4: sortByPrice(books, true);
                break;
            case 5: sortByPrice(books, false);
                break;
            case 6: sortByPopularity(books);
                break;
            case 7: sortByDate(books);
                break;
            case 8: filterByGenre(books);
                break;
            case 9: filterByPrice(books);
                break;
            case 10: searchBooks(books);
                break;
            case 0: cout << "Goodbye!\n";
                break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
