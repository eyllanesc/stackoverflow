#include "library.h"

Library::Library() {}

void Library::addBook(const Book &book) { books.push_back(book); }

Book Library::getBook(int index) { return books[index]; }

int Library::numOfBooks() { return books.size(); }
