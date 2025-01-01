// Requirement 8: Search for Books
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void searchBooks() {
    ifstream inFile("books.txt"); // File containing book details
    if (!inFile) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    string searchTerm, line, bookName, genre;
    int copies;
    bool found = false;

    cout << "Enter the book name or genre to search: ";
    cin.ignore();
    getline(cin, searchTerm);

    cout << "Search results:\n";
    while (getline(inFile, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find_last_of(",");

        if (pos1 != string::npos && pos2 != string::npos) {
            bookName = line.substr(0, pos1);
            genre = line.substr(pos1 + 1, pos2 - pos1 - 1);

            if (bookName.find(searchTerm) != string::npos || genre.find(searchTerm) != string::npos) {
                cout << "Book: " << bookName << " | Genre: " << genre << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No books found for '" << searchTerm << "'." << endl;
    }

    inFile.close();
}

int main() {
    searchBooks();
    return 0;
}



// Requirement 9: Borrow a Book
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void borrowBook() {
    ifstream inFile("books.txt");
    ofstream tempFile("temp_books.txt");

    if (!inFile || !tempFile) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    string bookNameToBorrow, line, bookName, genre;
    int copies;
    bool found = false;

    cout << "Enter the name of the book to borrow: ";
    cin.ignore();
    getline(cin, bookNameToBorrow);

    while (getline(inFile, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find_last_of(",");

        if (pos1 != string::npos && pos2 != string::npos) {
            bookName = line.substr(0, pos1);
            genre = line.substr(pos1 + 1, pos2 - pos1 - 1);
            copies = stoi(line.substr(pos2 + 1));

            if (bookName == bookNameToBorrow && copies > 0) {
                copies--;
                found = true;
                cout << "You have successfully borrowed '" << bookName << "'.\n";
            }
        }
        tempFile << bookName << "," << genre << "," << copies << endl;
    }

    if (!found) {
        cout << "Book '" << bookNameToBorrow << "' is not available.\n";
    }

    inFile.close();
    tempFile.close();

    remove("books.txt");
    rename("temp_books.txt", "books.txt");
}

int main() {
    borrowBook();
    return 0;
}


// Requirement 10: Return a Borrowed Book
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void returnBook() {
    ifstream inFile("books.txt");
    ofstream tempFile("temp_books.txt");

    if (!inFile || !tempFile) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    string bookNameToReturn, line, bookName, genre;
    int copies;
    bool found = false;

    cout << "Enter the name of the book to return: ";
    cin.ignore();
    getline(cin, bookNameToReturn);

    while (getline(inFile, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find_last_of(",");

        if (pos1 != string::npos && pos2 != string::npos) {
            bookName = line.substr(0, pos1);
            genre = line.substr(pos1 + 1, pos2 - pos1 - 1);
            copies = stoi(line.substr(pos2 + 1));

            if (bookName == bookNameToReturn) {
                copies++;
                found = true;
                cout << "Book '" << bookName << "' returned successfully.\n";
            }
        }
        tempFile << bookName << "," << genre << "," << copies << endl;
    }

    if (!found) {
        cout << "Book '" << bookNameToReturn << "' not found.\n";
    }

    inFile.close();
    tempFile.close();

    remove("books.txt");
    rename("temp_books.txt", "books.txt");
}

int main() {
    returnBook();
    return 0;
}


// Requirement 11: View Borrowed Books
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void viewBorrowedBooks(string username) {
    ifstream inFile("borrowed_books.txt");
    if (!inFile) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    string line, borrower, bookName;
    bool found = false;

    cout << "Borrowed books for user '" << username << "':\n";
    while (getline(inFile, line)) {
        size_t pos = line.find(",");
        if (pos != string::npos) {
            borrower = line.substr(0, pos);
            bookName = line.substr(pos + 1);

            if (borrower == username) {
                cout << "- " << bookName << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No borrowed books found for user '" << username << "'.\n";
    }

    inFile.close();
}

int main() {
    string username;
    cout << "Enter your username: ";
    cin >> username;

    viewBorrowedBooks(username);
    return 0;
}


// Requirement 12: Extend Borrowed Books Deadline
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void extendDeadline() {
    ifstream inFile("borrowed_books.txt");
    ofstream tempFile("temp_borrowed_books.txt");

    if (!inFile || !tempFile) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    string username, bookName, line, borrower, borrowedBook;
    int days, currentDays;
    bool found = false;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter the name of the book to extend the deadline: ";
    cin.ignore();
    getline(cin, bookName);
    cout << "Enter the additional number of days: ";
    cin >> days;

    while (getline(inFile, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find_last_of(",");

        if (pos1 != string::npos && pos2 != string::npos) {
            borrower = line.substr(0, pos1);
            borrowedBook = line.substr(pos1 + 1, pos2 - pos1 - 1);
            currentDays = stoi(line.substr(pos2 + 1));

            if (borrower == username && borrowedBook == bookName) {
                currentDays += days;
                found = true;
                cout << "Deadline extended by " << days << " days.\n";
            }
            tempFile << borrower << "," << borrowedBook << "," << currentDays << endl;
        }
    }

    if (!found) {
        cout << "No record found for the book '" << bookName << "' borrowed by '" << username << "'.\n";
    }

    inFile.close();
    tempFile.close();

    remove("borrowed_books.txt");
    rename("temp_borrowed_books.txt", "borrowed_books.txt");
}

int main() {
    extendDeadline();
    return 0;
}


// Requirement 13: Generate Overdue Books Report
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void generateOverdueReport() {
    ifstream inFile("borrowed_books.txt");
    if (!inFile) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    string line, borrower, bookName;
    int days;
    bool found = false;

    cout << "Overdue Books Report:\n";
    while (getline(inFile, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find_last_of(",");

        if (pos1 != string::npos && pos2 != string::npos) {
            borrower = line.substr(0, pos1);
            bookName = line.substr(pos1 + 1, pos2 - pos1 - 1);
            days = stoi(line.substr(pos2 + 1));

            if (days < 0) { // Assuming negative days mean overdue
                cout << "User: " << borrower << " | Book: " << bookName << " | Overdue by " << -days << " days\n";
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No overdue books found.\n";
    }

    inFile.close();
}

int main() {
    generateOverdueReport();
    return 0;
}


// Requirement 14: Enable Book Reviews and Ratings
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void leaveReview() {
    ofstream outFile("reviews.txt", ios::app); // Append reviews to file
    if (!outFile) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    string bookName, review;
    int rating;

    cout << "Enter the name of the book to review: ";
    cin.ignore();
    getline(cin, bookName);

    cout << "Enter your review: ";
    getline(cin, review);

    cout << "Rate the book (1-5): ";
    cin >> rating;

    if (rating < 1 || rating > 5) {
        cout << "Invalid rating. Please rate between 1 and 5.\n";
        return;
    }

    outFile << bookName << "," << review << "," << rating << endl;
    cout << "Review submitted successfully!\n";

    outFile.close();
}

int main() {
    leaveReview();
    return 0;
}


// Requirement 15: View Book Reviews and Ratings
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void viewReviews() {
    ifstream inFile("reviews.txt");
    if (!inFile) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    string bookName, searchBook, line, review;
    int rating;
    bool found = false;

    cout << "Enter the name of the book to view reviews: ";
    cin.ignore();
    getline(cin, searchBook);

    cout << "Reviews for '" << searchBook << "':\n";
    while (getline(inFile, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find_last_of(",");

        if (pos1 != string::npos && pos2 != string::npos) {
            bookName = line.substr(0, pos1);
            review = line.substr(pos1 + 1, pos2 - pos1 - 1);
            rating = stoi(line.substr(pos2 + 1));

            if (bookName == searchBook) {
                cout << "Review: " << review << " | Rating: " << rating << "/5\n";
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No reviews found for '" << searchBook << "'.\n";
    }

    inFile.close();
}

int main() {
    viewReviews();
    return 0;
}
