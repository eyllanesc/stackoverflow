#include "library.h"

library::library() { arr.resize(0); }

void library ::addBook(const book &b) { arr.push_back(b); }

book library ::getBook(int index) { return this->arr[index]; }

int library ::numOfBooks() { return this->arr.size(); }
