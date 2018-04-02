#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <QMetaType>

using namespace std;

class book
{
public:
    book();
    book(string, string, string);

    void setName(string);
    void setAuthor(string);
    void setUid(string);

    string getName();
    string getAuthor();
    string getUid();

    ~book() { }
private:
    string name, author, uid;
};

Q_DECLARE_METATYPE(book);


#endif // BOOK_H
