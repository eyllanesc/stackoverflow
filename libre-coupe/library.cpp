#include "library.h"

library::library()
{
    arr.resize(0);
}

void library :: addBook(book b)
{
    arr.resize(arr.size() + 1);

    arr[arr.size() - 1] = b;

    ++num;
}

book library :: getBook(int index)
{
    return this->arr[index];
}

int library :: numOfBooks()
{
    return this->num;
}
