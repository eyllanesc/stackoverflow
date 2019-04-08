#ifndef BOOK_H
#define BOOK_H
#include <string>

using namespace std;

class book {
public:
  book();
  book(const string &, const string &, const string &);

  void setName(const string &);
  void setAuthor(const string &);
  void setUid(const string &);

  string getName();
  string getAuthor();
  string getUid();

private:
  string name, author, uid;
};

#endif // BOOK_H
