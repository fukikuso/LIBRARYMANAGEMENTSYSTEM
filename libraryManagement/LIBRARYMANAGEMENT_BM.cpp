#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>//for clear screen and pause screen  
using namespace std;

//TAKE NOTE: Choose exit to save the data!!

//structure to store book information 
struct Book {
    string title;
    string author;
    int isbn;
    bool isAvailable;
};

//structure to store user information 
struct User {
    string name;
    string borrowedBook;
    int id;
};

//Dynamic array to store books and users
vector<Book> books;
vector<User> users;

//function declaration 
void clearScreen();
void pauseScreen();
void loadData();
void saveData();
void addBook();
void removeBook();
void addUser();
void removeUser();
void showBooks();
void showUsers();
void borrowBook();
void returnBook();

//Main menu options 
void showMainMenu() {
    cout << "======================================= "<<endl;
    cout << "        LIBRARY MANAGEMENT SYSTEM       "<<endl;
    cout << "======================================= "<<endl;
    cout << "1. Add Book "<<endl;
    cout << "2. Remove Book "<<endl;
    cout << "3. Add User "<<endl;
    cout << "4. Remove User "<<endl;
    cout << "5. Show Books "<<endl;
    cout << "6. Show Users "<<endl;
    cout << "7. Borrow Book "<<endl;
    cout << "8. Return Book "<<endl;
    cout << "9. Exit "<<endl;
    cout << "======================================= "<<endl;
    cout << "Enter your choice: ";
}

//Main program loop
int main() {
    loadData();//load existing data from files
    int choice;
    
    //keep running until the user choose exit
    while (true) {
        clearScreen();
        showMainMenu();
        cin >> choice;
        cin.ignore();
        clearScreen();

        //users menu choice 
        switch (choice) {
            case 1: 
                addBook(); 
                pauseScreen();
                break;
            case 2: 
                removeBook(); 
                pauseScreen();
                break;
            case 3: 
                addUser(); 
                pauseScreen();
                break;
            case 4: 
                removeUser(); 
                pauseScreen();
                break;
            case 5: 
                showBooks(); 
                pauseScreen();
                break;
            case 6: 
                showUsers(); 
                pauseScreen();
                break;
            case 7: 
                borrowBook(); 
                pauseScreen();
                break;
            case 8: 
                returnBook(); 
                pauseScreen();
                break;
            case 9: 
                saveData(); //Save data before exiting 
                clearScreen();
                cout << "======================================= "<<endl;
                cout << "         Data successfully saved...     "<<endl;
                cout << "                                        "<<endl;
                cout << "   Thank you for using Library System!  "<<endl;
                cout << "            Goodbye! "<<endl;
                cout << "======================================= "<<endl;
                return 0;
            default: 
                cout << "Invalid choice! Please try again. "<<endl;
                pauseScreen();
        }
    }
}

//clear the screen base on OS
void clearScreen() {
    #ifdef _WIN32
        system("cls"); 
    #else
        system("clear");
    #endif
}

//Wait for user to press enter before continue 
void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.get();//Wait for Enter key press
}

//load books and users data from text files
void loadData() {
    ifstream file;
    string line;
    
    //load books from books.txt file
    file.open("books.txt");
    while (getline(file, line)) {
        Book book;
        book.title = line;
        getline(file, book.author);
        getline(file, line);
        
        getline(file, line);
        book.isAvailable = (line == "1"); // All loaded books are available 
        books.push_back(book); //Add book to end of vector 
    }
    file.close();
    
    //load users from users.txt file 
    file.open("users.txt");
    string name, id, borrowedBook;
    while (getline(file, name) && getline(file, id) && getline(file, borrowedBook)) {
        User user;
        user.name = name;               
            
        user.borrowedBook = (borrowedBook == "NONE") ? "" : borrowedBook;
        users.push_back(user); // Add user to end of vector 
    }
    file.close();
}


//Save current books and users data to text files
void saveData() {
   // Save books to books.txt
   ofstream bookFile("books.txt");
   if (bookFile.is_open()) {
       for (int i = 0; i < books.size(); i++) {
           bookFile << books[i].title << endl;
           bookFile << books[i].author << endl;
           bookFile << books[i].isbn << endl;
           bookFile << (books[i].isAvailable ? "1" : "0") <<endl;
       }
       bookFile.close();
   }

   // Save users to users.txt
   ofstream userFile("users.txt");
   if (userFile.is_open()) {
       for (int i = 0; i < users.size(); i++) {
           userFile << users[i].name << endl;      
           userFile << users[i].id << endl;       
           if (users[i].borrowedBook.empty()) {
               userFile << "NONE" << endl;
           } else {
               userFile << users[i].borrowedBook << endl;
           }
       }
       userFile.close();
   }
}


//Add new book to the library 
void addBook() {
   cout << "=======================================\n";
   cout << "              ADD BOOK\n";
   cout << "=======================================\n";
   
   Book book;
   cout << "Enter book title: ";
   getline(cin, book.title);
   cout << "Enter book author: ";
   getline(cin, book.author);
   cout << "Enter ISBN: ";
   cin >> book.isbn;
   cin.ignore();
   
   //Check if book with ISBN already exists
   for (int i = 0; i < books.size(); i++) {
       if (books[i].isbn == book.isbn) {
           cout << "Book with this ISBN already exists!\n";
           return;
       }
   }
   
   book.isAvailable = true;//New book is available 
   books.push_back(book); //Add new book to end of vector 
   cout << "Book added successfully!\n";
}

//Remove Book from the library 
void removeBook() {
   cout << "=======================================\n";
   cout << "              REMOVE BOOK\n";
   cout << "=======================================\n";
   
   // Check if there are any books to remove
   if (books.empty()) {
       cout << "No books available to remove!\n";
       return;
   }
   
   int isbn;
   cout << "Enter ISBN to remove: ";
   cin >> isbn;
   cin.ignore(); // Clear input buffer
   
   // Search for book by ISBN and remove it
   for (int i = 0; i < books.size(); i++) {
       if (books[i].isbn == isbn) {
           // Check if book is currently borrowed
           if (!books[i].isAvailable) {
               cout << "Cannot remove book - it is currently borrowed!\n";
               return;
           }
           books.erase(books.begin() + i); // Remove book from vector
           cout << "Book removed successfully!\n";
           return;
       }
   }
   cout << "Book not found!\n";
}


//Add a new user to the systm
void addUser() {
    cout << "=======================================\n";
    cout << "              ADD USER\n";
    cout << "=======================================\n";
    User user;
    cout << "Enter user name: ";
    getline(cin, user.name);
    cout << "Enter id number: ";
    cin >> user.id;
    cin.ignore();
    user.borrowedBook = "";//no borrowed book initially 
    users.push_back(user); //Add new user to end of vector 
    cout << "User added successfully!\n";
}

//Remove a user from the system
void removeUser() {
    cout << "=======================================\n";
    cout << "              REMOVE USER\n";
    cout << "=======================================\n";
    
    int id;
    cout << "Enter id to remove: ";
    cin >> id;
    cin.ignore();
    
    //Search for user by ID
    for (int i = 0; i < users.size(); i++) {
        if ( users[i].id == id) {
        //If user has borrowed a book
            if (!users[i].borrowedBook.empty()) {
                cout << "User has borrowed a book. Return the book first!\n";
                return;
            }
            //User remove from the system 
            users.erase(users.begin() + i);
            cout << "User removed successfully!\n";
            return;
        }
    }
    //If user is not found
    cout << "User not found!\n";
}

//Display books including each information 
void showBooks() {
    cout << "=======================================\n";
    cout << "              SHOW BOOKS\n";
    cout << "=======================================\n";
    
    //Check if there are any books
    if (books.empty()) {
        cout << "No Books Available" << endl;
        return;
    }
    //Display each book information 
   for (int i = 0; i < books.size(); i++) {
   cout << "Title: " << books[i].title << endl;
   cout << "Author: " << books[i].author << endl;
   cout << "ISBN: " << books[i].isbn << endl;
   cout << "Status: " << (books[i].isAvailable ? "Available" : "Not Available") << endl;
   cout << "--------------------------------------"<< endl;
}
}

// Display all users in the system
void showUsers() {
   cout << "=======================================\n";
   cout << "              SHOW USERS\n";
   cout << "=======================================\n";
   
   // Check if there are any users
   if (users.empty()) {
       cout << "No users found.\n";
       return;
   }
   
   // Display each user's information 
   for (int i = 0; i < users.size(); i++) { 
       cout << "Name: " << users[i].name << endl;
       cout << "ID: " << users[i].id << endl;
       
       // Check if the user borrowed a book or not
       if (!users[i].borrowedBook.empty()) {
           cout << "Borrowed Book: " << users[i].borrowedBook << endl;
       } else {
           cout << "No borrowed book\n"; 
       }
       cout << "---------------------------------------\n";  
   }
}

//Allow a user to borrow a book
void borrowBook() {
   cout << "=======================================\n";
   cout << "              BORROW BOOK\n";
   cout << "=======================================\n";
   string name;
   string title;
   cout << "Enter user name: ";
   getline(cin, name);
   cout << "Enter book title: ";
   getline(cin, title);


   //Find the user by name
   for (int i = 0; i < users.size(); i++) {
       if (users[i].name == name) {
       //Check if the user has already borrowed a book
           if (!users[i].borrowedBook.empty()) {
               cout << "User has already borrowed a book!\n";
               return;
           }
           //Find the requested book
           for (int j = 0; j < books.size(); j++) {
               if (books[j].title == title) {
               //check if book is available 
                   if (!books[j].isAvailable) {
                       cout << "Book is not available!\n";
                       return;
                   }
                   //Proccess the borrowing 
                   users[i].borrowedBook = title;
                   books[j].isAvailable = false;
                   cout << "Book borrowed successfully!\n";
                   return;
               }
           }
           cout << "Book not found!\n";
           return;
       }
   }
   cout << "User not found!\n";
}
//Allow a user to return a borrow book
void returnBook() {
   cout << "=======================================\n";
   cout << "              RETURN BOOK\n";
   cout << "=======================================\n";
   string name;
   cout << "Enter user name: ";
   getline(cin, name);

   //Find the user by name
   for (int i = 0; i < users.size(); i++) {
       if (users[i].name == name) {
          // Check if user has borrowed book
           if (users[i].borrowedBook.empty()) {
               cout << "User has not borrowed any book!\n";
               return;
           }
           //Find the borrowed book and make it available 
           for (int j = 0; j < books.size(); j++) {
               if (books[j].title == users[i].borrowedBook) {
                   books[j].isAvailable = true;
                   users[i].borrowedBook = ""; //Clear borrow book
                   cout << "Book returned successfully!\n";
                   return;
               }
           }
       }
   }
   cout << "User not found!\n";
}

