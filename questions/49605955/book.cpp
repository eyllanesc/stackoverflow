#include "book.h"

Book::Book() { Book("", "", ""); }

Book::Book(const std::string &author, const std::string &name,
           const std::string &uuid)
    : mAuthor(author), mName(name), mUuid(uuid) {}

std::string Book::getAuthor() const { return mAuthor; }

void Book::setAuthor(const std::string &author) { mAuthor = author; }

std::string Book::getName() const { return mName; }

void Book::setName(const std::string &name) { mName = name; }

std::string Book::getUid() const { return mUuid; }

void Book::setUid(const std::string &uuid) { mUuid = uuid; }
