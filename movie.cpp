#include "movie.h"
#include "util.h"
#include <sstream>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : 
Product(category, name, price, qty)
{
  genre_ = genre;
  rating_ = rating;
}

Movie::~Movie()
{
  
}

std::set<std::string> Movie::keywords() const
{
  std::set<std::string> words = parseStringToWords(name_);
  std::set<std::string> genreTerms = parseStringToWords(genre_);
  std::set<std::string>::iterator it;
  for(it = genreTerms.begin(); it != genreTerms.end(); ++it)
  {
    words.insert(*it);
  }
  return words;
}

std::string Movie::displayString() const
{
  string s; 
  s += name_;
  s += "\nGenre: ";
  s += genre_;
  s += " Rating: ";
  s += rating_;
  s += "\n";
  string price = to_string(price_);
  string roundPrice = price.substr(0, price.find(".") + 3);
  s += roundPrice;
  s += " ";
  s += to_string(qty_);
  s += " left.";
  return s;
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}




