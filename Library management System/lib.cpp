#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Book
{
private:
    int bookID;
    string title;
    string author;
    bool issued;

public:
    void addBook()
    {
        cout << "\nEnter Book ID: ";

        while (!(cin >> bookID))
        {
            cout << "Invalid Book ID! Enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        issued = false;

        cout << "\nBook Added Successfully!\n";
    }

    void displayBook()
    {
        cout << "\n-----------------------------\n";
        cout << "Book ID : " << bookID << endl;
        cout << "Title   : " << title << endl;
        cout << "Author  : " << author << endl;

        if (issued)
            cout << "Status  : Issued\n";
        else
            cout << "Status  : Available\n";

        cout << "-----------------------------\n";
    }

    string getTitle()
    {
        return title;
    }

    string getAuthor()
    {
        return author;
    }

    int getBookID()
    {
        return bookID;
    }

    bool isIssued()
    {
        return issued;
    }

    void issueBook()
    {
        issued = true;
    }

    void returnBook()
    {
        issued = false;
    }
};

int main()
{
    Book books[100];

    int bookCount = 0;
    int choice;
    int id;
    string search;
    bool found;

    do
    {
        cout << "\n=====================================\n";
        cout << "     LIBRARY MANAGEMENT SYSTEM\n";
        cout << "=====================================\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "=====================================\n";
        cout << "Enter Your Choice: ";

        while (!(cin >> choice))
        {
            cout << "Invalid Choice! Enter a number: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice)
        {
        case 1:
            if (bookCount < 100)
            {
                books[bookCount].addBook();
                bookCount++;
            }
            else
            {
                cout << "\nLibrary is Full!\n";
            }
            break;

        case 2:
            if (bookCount == 0)
            {
                cout << "\nNo Books Available!\n";
            }
            else
            {
                for (int i = 0; i < bookCount; i++)
                {
                    books[i].displayBook();
                }
            }
            break;

        case 3:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nEnter Book Title or Author Name: ";
            getline(cin, search);

            found = false;

            for (int i = 0; i < bookCount; i++)
            {
                if (books[i].getTitle() == search ||
                    books[i].getAuthor() == search)
                {
                    cout << "\nBook Found!\n";
                    books[i].displayBook();
                    found = true;
                }
            }

            if (!found)
            {
                cout << "\nBook Not Found!\n";
            }

            break;

        case 4:
            cout << "\nEnter Book ID to Issue: ";

            while (!(cin >> id))
            {
                cout << "Invalid Book ID! Enter a number: ";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            found = false;

            for (int i = 0; i < bookCount; i++)
            {
                if (books[i].getBookID() == id)
                {
                    found = true;

                    if (books[i].isIssued())
                    {
                        cout << "\nBook is Already Issued!\n";
                    }
                    else
                    {
                        books[i].issueBook();
                        cout << "\nBook Issued Successfully!\n";
                    }

                    break;
                }
            }

            if (!found)
            {
                cout << "\nBook Not Found!\n";
            }

            break;

        case 5:
            cout << "\nEnter Book ID to Return: ";

            while (!(cin >> id))
            {
                cout << "Invalid Book ID! Enter a number: ";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            found = false;

            for (int i = 0; i < bookCount; i++)
            {
                if (books[i].getBookID() == id)
                {
                    found = true;

                    if (!books[i].isIssued())
                    {
                        cout << "\nBook is Already Available!\n";
                    }
                    else
                    {
                        books[i].returnBook();
                        cout << "\nBook Returned Successfully!\n";
                    }

                    break;
                }
            }

            if (!found)
            {
                cout << "\nBook Not Found!\n";
            }

            break;

        case 6:
            cout << "\nExiting Library Management System...\n";
            break;

        default:
            cout << "\nInvalid Choice! Please Enter 1 to 6.\n";
        }

    } while (choice != 6);

    return 0;
}
