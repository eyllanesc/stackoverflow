#include "book.h"

book::book() { book("", "", ""); }

book ::book(const string &n, const string &a, const string &u)
    : name(n), author(a), uid(u) {}

void book ::setName(const string &n) { this->name = n; }

void book ::setAuthor(const string &a) { this->author = a; }

void book ::setUid(const string &u) { this->uid = u; }

string book ::getName() { return this->name; }

string book ::getAuthor() { return this->author; }

string book ::getUid() { return this->uid; }
