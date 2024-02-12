#include "clothing.h"
#include "product.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) : 
Product(category, name, price, qty)
{
  size_ = size;
  brand_ = brand;
}

Clothing::~Clothing()
{
  
}

std::set<std::string> Clothing::keywords() const
{
  std::set<std::string> words = parseStringToWords(name_);
  std::set<std::string> brandTerms = parseStringToWords(brand_);
  std::set<std::string>::iterator it;
  for(it = brandTerms.begin(); it != brandTerms.end(); ++it)
  {
    words.insert(*it);
  }
  return words;
}

std::string Clothing::displayString() const
{
  string s; 
  s += name_;
  s += "\nSize: ";
  s += size_;
  s += " Brand: ";
  s += brand_; 
  s += "\n";
  string price = to_string(price_);
  string roundPrice = price.substr(0, price.find(".") + 3);
  s += roundPrice;
  s += " ";
  s += to_string(qty_);
  s += " left.";
  return s;
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}



