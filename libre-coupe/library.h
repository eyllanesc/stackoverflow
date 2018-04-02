#ifndef LIBRARY_H
#define LIBRARY_H
#include <vector>
#include <QString>
#include "book.h"

using namespace std;

class library
{
public:
    library();

    void addBook(const book & b);
    book getBook(int index);
    int numOfBooks();

private:
    vector<book> arr;
};

#endif // LIBRARY_H
