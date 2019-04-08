#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"

#include <vector>

class Library {
public:
  Library();
  void addBook(const Book &book);
  Book getBook(int index);
  int numOfBooks();

private:
  std::vector<Book> books;
};

#endif // LIBRARY_H
