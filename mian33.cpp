#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <chrono> //년도 함수

using namespace std;

//책 추가 제거 조회
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
    //책 추가 함수
    void addBook(const Book& book)//const 를 사용하여 Book값을 함수내에서 변경 불가하게 해서 book값을 참조로 받겠다는 것.
    {
       books.push_back(book);//백터에 새로운 책 추가.
       cout << "책이 추가되었습니다.\n";//출력
        
    }

    //다 백터값으로 받고 저장하고 가져오는거여서 
    //책 목록 함수,bc,d
    void  listBooks() const //const아래로 받는값은 변경안하겠다.
    {
        if (books.empty()) //목록이 없으면 실행
        {
            cout << "책이 없습니다.\n";//출력
            return;//if 함수를 다시 실행하는 리턴값
        }
        for (const auto& book : books)// for로 (const auto& book : books) 책 목록 반복 찾기
        {
            cout << "제목:" << book.title
                << " 저자:" << book.author
                << " 출판년도:" << book.year << endl;//출력
        }
    }
    //책 제거 함수
    void removeBook(const string& title)
    {
        auto it = books.begin();
        while (it != books.end())
        {
            if (it->title == title) 
            {
                books.erase(it);
                cout << title << "책이 제거되었습니다.\n";
                return;
            }
            ++it;
        }
        cout << title << "책이 없습니다.\n";
    }
    //책 검색 함수
    void searchBook(const string& title) const
    {  
        for (const auto& book : books)
        {
            if (book.title == title)
            {
                cout << "제목: " << book.title
                    << "저자: " << book.author
                    << "출판년도: " << book.year << endl;
                return;
            }
        }
        cout << title << "책이 없습니다.\n";
    }
    //메뉴 함수
    void li()
    {
        while(true)
        {
            cout << "1. 책 추가\n2. 책 목록\n3. 책 제거\n4. 책 검색\n0. 종료\n";
            
            int choice;           
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                
            string title, author;
            int year;

           if (choice == 0)
            {
                cout << "프로그램을 종료합니다.\n";
                break;
            }
           else if (choice == 1)
            {
                cout << "책 제목을 입력하세요.\n";
                getline(cin, title);
                cout << "저자를 입력하세요.\n";
                getline(cin, author);
                cout << "출판년도를 입력하세요.\n";
                cin >> year;
                
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "\n다시 입력하세요.\n";               
                    continue;
                }
                cin.ignore();

                addBook(Book(title, author, year));
            }
            else if (choice == 2)
            {
               cout << "- 책 목록 -\n";
               listBooks();
            }
            else if (choice == 3)
            {
                cout << "제거할 책 제목을 입력하세요.\n";
                cin.clear();
                getline(cin, title);
                removeBook(title);
            }
            else if (choice == 4)
            {
                cout << "검색할 책 제목을 입력하세요.\n";
                cin.clear();
                getline(cin, title);
                searchBook(title);
            }
            else
            {
                cout << "다시 입력하세요.\n";
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
