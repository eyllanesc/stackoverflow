#include "book.h"

book::book()
{
    name = "";
    author = "";
    uid = "";
}

book :: book(string n, string a, string u)
{
    this->name = n;
    this->author = a;
    this->uid = u;
}

void book :: setName(string n)
{
    this->name = n;
}

void book :: setAuthor(string a)
{
    this->author = a;
}

void book :: setUid(string u)
{
    this->uid = u;
}

string book :: getName()
{
    return this->name;
}

string book :: getAuthor()
{
    return this->author;
}

string book :: getUid()
{
    return this->uid;
}
