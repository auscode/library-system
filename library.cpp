#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include <stdexcept>
using namespace std;

// -------------------- Book Class --------------------
class Book {
private:
    int bookId;
    string title;
    string author;
    int quantity;

public:
    Book(int id, const string& t, const string& a, int q)
        : bookId(id), title(t), author(a), quantity(q) {}

    // Getters
    int getId() const { return bookId; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getQuantity() const { return quantity; }

    // Update quantity
    void setQuantity(int q) { quantity = q; }

    // Serialize for file storage
    string serialize() const {
        return to_string(bookId) + "|" + title + "|" + author + "|" + to_string(quantity);
    }

    // Pretty print
    void display() const {
        cout << "Book ID: " << bookId
             << " | Title: " << title
             << " | Author: " << author
             << " | Quantity: " << quantity << "\n";
    }
};


// -------------------- Library Class --------------------
class Library {
private:
    //map of ID -> Book
    unordered_map<int, unique_ptr<Book>> books;
    const string filename = "library_data.txt";

public:
    Library() {
        loadFromFile();
    }

    ~Library() {
        saveToFile();
    }

    // ---------------- Add Book ----------------
    void addBook(int id, const string& title, const string& author, int qty) {
        if (books.count(id)) {
            throw runtime_error("Book ID already exists.");
        }
        books[id] = make_unique<Book>(id, title, author, qty);
        cout << "Book added successfully.\n";
    }

    // ---------------- Search by ID ----------------
    Book* searchById(int id) {
        if (!books.count(id)) return nullptr;
        return books[id].get();
    }

    // ---------------- Search by Title (partial/complete) ----------------
    vector<Book*> searchByTitle(const string& key) {
        vector<Book*> results;
        for (auto& [id, book] : books) {
            string t = book->getTitle();
            if (t.find(key) != string::npos) {
                results.push_back(book.get());
            }
        }
        return results;
    }

    // ---------------- Display All Books ----------------
    void displayAll() {
        if (books.empty()) {
            cout << "No books available.\n";
            return;
        }
        for (auto& [id, book] : books) {
            book->display();
        }
    }

    // ---------------- Update Quantity ----------------
    void updateQuantity(int id, int newQty) {
        Book* book = searchById(id);
        if (!book) throw runtime_error("Book ID not found.");
        book->setQuantity(newQty);
        cout << "Quantity updated successfully.\n";
    }

    // ---------------- Delete Book ----------------
    void deleteBook(int id) {
        if (!books.count(id)) throw runtime_error("Book ID not found.");
        books.erase(id);
        cout << "Book deleted successfully.\n";
    }

    // ---------------- File Persistence ----------------
    void saveToFile() {
        ofstream fout(filename);
        for (auto& [id, book] : books) {
            fout << book->serialize() << "\n";
        }
    }

    void loadFromFile() {
        ifstream fin(filename);
        if (!fin.is_open()) return;

        string line;
        while (getline(fin, line)) {
            int id, qty;
            string title, author;

            size_t p1 = line.find("|");
            size_t p2 = line.find("|", p1 + 1);
            size_t p3 = line.find("|", p2 + 1);

            id = stoi(line.substr(0, p1));
            title = line.substr(p1 + 1, p2 - p1 - 1);
            author = line.substr(p2 + 1, p3 - p2 - 1);
            qty = stoi(line.substr(p3 + 1));

            books[id] = make_unique<Book>(id, title, author, qty);
        }
    }
};


// -------------------- Menu Interface --------------------
void showMenu() {
    cout << "\n---------------- Library Menu ----------------\n";
    cout << "1. Add Book\n";
    cout << "2. Search Book by ID\n";
    cout << "3. Search Book by Title (Partial)\n";
    cout << "4. Display All Books\n";
    cout << "5. Update Quantity\n";
    cout << "6. Delete Book by ID\n";
    cout << "7. Exit\n";
    cout << "Enter choice: ";
}


// -------------------- Main --------------------
int main() {
    Library lib;
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        try {
            if (choice == 1) {
                int id, qty;
                string title, author;
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Title: ";
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                cout << "Enter Quantity: ";
                cin >> qty;

                lib.addBook(id, title, author, qty);
            }

            else if (choice == 2) {
                int id;
                cout << "Enter Book ID: ";
                cin >> id;
                Book* book = lib.searchById(id);
                if (!book) cout << "Book not found.\n";
                else book->display();
            }

            else if (choice == 3) {
                string key;
                cin.ignore();
                cout << "Enter title keyword: ";
                getline(cin, key);

                auto results = lib.searchByTitle(key);
                if (results.empty()) cout << "No matching books.\n";
                else
                    for (Book* b : results) b->display();
            }

            else if (choice == 4) {
                lib.displayAll();
            }

            else if (choice == 5) {
                int id, qty;
                cout << "Enter Book ID: ";
                cin >> id;
                cout << "Enter new quantity: ";
                cin >> qty;
                lib.updateQuantity(id, qty);
            }

            else if (choice == 6) {
                int id;
                cout << "Enter Book ID to delete: ";
                cin >> id;
                lib.deleteBook(id);
            }

            else if (choice == 7) {
                cout << "Exiting...\n";
                break;
            }

            else {
                cout << "Invalid choice.\n";
            }

        } catch (const exception& ex) {
            cout << "Error: " << ex.what() << "\n";
        }
    }

    return 0;
}
