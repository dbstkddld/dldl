#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <chrono> //�⵵ �Լ�

using namespace std;

//å �߰� ���� ��ȸ
#include <vector>
class Book
{
    public:
     string title;
     string author;
     int year;

     Book(string t, string a, int y) : title(t), author(a), year(y) {};
};

class Library
{
private:
    vector<Book> books;

public:
    //å �߰� �Լ�
    void addBook(const Book& book)//const �� ����Ͽ� Book���� �Լ������� ���� �Ұ��ϰ� �ؼ� book���� ������ �ްڴٴ� ��.
    {
       books.push_back(book);//���Ϳ� ���ο� å �߰�.
       cout << "å�� �߰��Ǿ����ϴ�.\n";//���
        
    }

    //�� ���Ͱ����� �ް� �����ϰ� �������°ſ��� 
    //å ��� �Լ�,bc,d
    void  listBooks() const //const�Ʒ��� �޴°��� ������ϰڴ�.
    {
        if (books.empty()) //����� ������ ����
        {
            cout << "å�� �����ϴ�.\n";//���
            return;//if �Լ��� �ٽ� �����ϴ� ���ϰ�
        }
        for (const auto& book : books)// for�� (const auto& book : books) å ��� �ݺ� ã��
        {
            cout << "����:" << book.title
                << " ����:" << book.author
                << " ���ǳ⵵:" << book.year << endl;//���
        }
    }
    //å ���� �Լ�
    void removeBook(const string& title)
    {
        auto it = books.begin();
        while (it != books.end())
        {
            if (it->title == title) 
            {
                books.erase(it);
                cout << title << "å�� ���ŵǾ����ϴ�.\n";
                return;
            }
            ++it;
        }
        cout << title << "å�� �����ϴ�.\n";
    }
    //å �˻� �Լ�
    void searchBook(const string& title) const
    {  
        for (const auto& book : books)
        {
            if (book.title == title)
            {
                cout << "����: " << book.title
                    << "����: " << book.author
                    << "���ǳ⵵: " << book.year << endl;
                return;
            }
        }
        cout << title << "å�� �����ϴ�.\n";
    }
    //�޴� �Լ�
    void li()
    {
        while(true)
        {
            cout << "1. å �߰�\n2. å ���\n3. å ����\n4. å �˻�\n0. ����\n";
            
            int choice;           
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                
            string title, author;
            int year;

           if (choice == 0)
            {
                cout << "���α׷��� �����մϴ�.\n";
                break;
            }
           else if (choice == 1)
            {
                cout << "å ������ �Է��ϼ���.\n";
                getline(cin, title);
                cout << "���ڸ� �Է��ϼ���.\n";
                getline(cin, author);
                cout << "���ǳ⵵�� �Է��ϼ���.\n";
                cin >> year;
                
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "\n�ٽ� �Է��ϼ���.\n";               
                    continue;
                }
                cin.ignore();

                addBook(Book(title, author, year));
            }
            else if (choice == 2)
            {
               cout << "- å ��� -\n";
               listBooks();
            }
            else if (choice == 3)
            {
                cout << "������ å ������ �Է��ϼ���.\n";
                cin.clear();
                getline(cin, title);
                removeBook(title);
            }
            else if (choice == 4)
            {
                cout << "�˻��� å ������ �Է��ϼ���.\n";
                cin.clear();
                getline(cin, title);
                searchBook(title);
            }
            else
            {
                cout << "�ٽ� �Է��ϼ���.\n";
            }
        }
    }
};



int main()
{
    Library lib;
    lib.li();

    return 0;
}
