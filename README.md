# 📘 Library Book Management System – C++

A console-based Library Management System implemented in C++ to demonstrate mastery of:

* C++ fundamentals
* OOP concepts
* STL containers
* Exception handling
* Clean code practices
* Memory-safe programming using smart pointers

---

## 🚀 Features Implemented (Assignment Requirements)

### ✅ **1. Classes Implemented**

#### **Book**

* Attributes:

  * `Book ID`
  * `Title`
  * `Author`
  * `Quantity`
* Methods:

  * Getters for all attributes
  * `setQuantity()` to update quantity
  * `serialize()` for file persistence
  * `display()` for formatted output

#### **Library**

* Stores a collection of books
* Uses an `unordered_map<int, unique_ptr<Book>>` to map **Book ID → Book**
* Manages all operations on books

---

## 📚 Core Operations Implemented

| Requirement                | Status | Details                                   |
| -------------------------- | ------ | ----------------------------------------- |
| Add a new book (unique ID) | ✔️     | Checks for duplicate ID, throws exception |
| Search by ID               | ✔️     | Returns a `Book*` or `nullptr`            |
| Search by Title            | ✔️     | Supports **partial matching**             |
| Display all books          | ✔️     | Iterates and prints all stored books      |
| Update quantity            | ✔️     | Uses setter in `Book` class               |
| Delete a book              | ✔️     | Removes entry from `unordered_map`        |

---

## ⚙️ Technical Expectations

### ✔ **OOP Principles**

* **Encapsulation**: All data members are private
* **Constructors/Destructors**:

  * `Book` constructor initializes all attributes using **member initializer list**
  * `Library` constructor loads data from file
  * `Library` destructor automatically saves data before exit

### ✔ **STL Containers Used**

* `unordered_map<int, unique_ptr<Book>>` – fast lookup by ID
* `vector<Book*>` – used for returning search results

### ✔ **Exception Handling**

* Duplicate ID check
* Invalid ID when updating or deleting
* Proper `try–catch` blocks in menu loop

### ✔ **Memory Management**

* Uses `unique_ptr<Book>`
* Prevents memory leaks
* No manual `new`/`delete`
* C++ RAII used for file I/O and object lifetime

### ✔ **Clean Code Practices**

* Fully modular methods (`addBook`, `searchById`, `updateQuantity`, etc.)
* Meaningful method and variable names
* Organized comments
* Clear menu interface

---

## ⭐ Bonus Features Implemented

| Bonus Feature        | Status | Explanation                                         |
| -------------------- | ------ | --------------------------------------------------- |
| File Handling        | ✔️     | Books are automatically saved to `library_data.txt` |
| Partial Title Search | ✔️     | Using substring matching (`string::find`)           |
| Smart Pointers       | ✔️     | `unique_ptr<Book>` used for all storage             |
| Menu Interface       | ✔️     | Clear, text-based interactive UI                    |

---

## 🗂 File Persistence

Books are saved in the format:

```
ID|Title|Author|Quantity
```

Example:

```
101|Harry Potter|J.K. Rowling|5
```

Loaded automatically on startup and saved on exit.

---

## 🖥 How to Compile & Run

### **Linux / Mac / WSL**

```bash
g++ -std=c++17 library.cpp -o library
./library
```

### **Windows (MinGW)**

```bash
g++ -std=c++17 library.cpp -o library.exe
library.exe
```

---

## 📸 Menu Screenshot

```
---------------- Library Menu ----------------
1. Add Book
2. Search Book by ID
3. Search Book by Title (Partial)
4. Display All Books
5. Update Quantity
6. Delete Book by ID
7. Exit
Enter choice:
```

---

## 📦 Project Structure

```
/LibrarySystem
│
├── library.cpp    # Entire logic and implementation
├── library_data.txt (auto-created)
└── README.md
```

---

## 🧠 Concepts Demonstrated

* OOP design and separation of responsibilities
* STL containers & iterators
* Smart pointer memory safety
* File persistence design
* Custom exception handling
* Clean coding best practices

---

## 🏁 Final Notes

This project satisfies **all core requirements** and implements **all bonus features** hence delivering a complete, production-quality console application.