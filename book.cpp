#include "book.h"
#include "product.h"
#include "util.h"
#include <sstream>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) : 
Product(category, name, price, qty)
{
  isbn_ = isbn;
  author_ = author;
}

Book::~Book()
{
  
}

std::set<std::string> Book::keywords() const
{
  std::set<std::string> words = parseStringToWords(name_);
  words.insert(isbn_);
  std::set<std::string> authorTerms = parseStringToWords(author_);
  std::set<std::string>::iterator it;
  for(it = authorTerms.begin(); it != authorTerms.end(); ++it)
  {
    words.insert(*it);
  }
  return words;
}

std::string Book::displayString() const
{
  string s; 
  s += name_;
  s += "\nAuthor: ";
  s += author_;
  s += " ISBN: ";
  s += isbn_;
  s += "\n";
  string price = to_string(price_);
  string roundPrice = price.substr(0, price.find(".") + 3);
  s += roundPrice;
  s += " ";
  s += to_string(qty_);
  s += " left.";
  return s;
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}



