#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
public:
  Book();
  Book(const std::string &author, const std::string &name,
       const std::string &uuid);

  std::string getAuthor() const;
  void setAuthor(const std::string &author);

  std::string getName() const;
  void setName(const std::string &name);

  std::string getUid() const;
  void setUid(const std::string &uuid);

private:
  std::string mAuthor;
  std::string mName;
  std::string mUuid;
};

#endif // BOOK_H
