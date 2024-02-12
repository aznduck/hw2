// mydatastore.cpp
#include "mydatastore.h"
#include "util.h"
#include "product.h"
#include "user.h"
#include <queue>
#include <iostream>
#include <iterator>

using namespace std;

MyDataStore::MyDataStore(){
  // for(Product* p : products) {
  //       std::set<std::string> productKeywords = p->keywords();
  //       std::set<std::string>::iterator it;
  //       for (it = productKeywords.begin(); it != productKeywords.end(); ++it) {
  //           keywordIndex[*it].insert(p);
  //       }
  //   }

  //   for(User* u : users) {
  //       carts[u->getName()] = std::vector<Product*>();
  //   }
}

MyDataStore::~MyDataStore() {
   for(Product* p: products)
   {
    delete p;
   }

  for(User* u: users)
  {
    delete u;
  }
}


void MyDataStore::addProduct(Product* p) {
    products.push_back(p);
    std::set<std::string> productKeywords = p->keywords();
    for (std::set<std::string>::iterator it = productKeywords.begin(); it != productKeywords.end(); ++it) {
        keywordIndex[*it].insert(p);
    }
}

void MyDataStore::addUser(User* u) {
    users.push_back(u);
    //carts[u->getName()] = std::vector<Product*>();
    carts[u->getName()];
  }

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    
    std::set<Product*> resultSet;
    if (type == 0) {
        // AND search
        for(std::string& term: terms)
        {
          //cout<<term<<endl;
          std::unordered_map<std::string, std::set<Product*>>::iterator it = keywordIndex.find(term);
          if(it != keywordIndex.end())
          {
            if(resultSet.empty())
            {
              resultSet = it -> second;
            }
            else
            {
              resultSet = setIntersection(resultSet, it -> second);
            }
          }
          else
          {
            resultSet.clear();
            break;
          }
        }
    } 
    else if (type == 1) {
        // OR search
        for (std::string& term: terms)
        {
          std::unordered_map<std::string, std::set<Product*>>::iterator it = keywordIndex.find(term);
          if(it != keywordIndex.end())
          {
            resultSet = setUnion(resultSet, it -> second);
          }
        }
    }
    std::vector<Product*> result(resultSet.begin(), resultSet.end());
    return result;
}

void MyDataStore::addToCart(std::string u, Product* p)
{
  if(carts.find(u) == carts.end())
  {
    cout << "Invalid request" << endl;
    return;
  }
  carts[u].push_back(p);
}

void MyDataStore::viewCart(std::string u)
{
  if(carts.find(u) == carts.end())
  {
    cout << "Invalid username";
    return;
  }
  
  std::vector<Product*>& temp = carts[u];

  for(size_t i = 0; i < temp.size(); i++)
  {
    cout << "Item " << i+1 << endl;
    cout << temp[i] -> displayString() << endl;
    cout << endl;
  }
  
}

void MyDataStore::buyCart(std::string u)
{
    User* uObj = nullptr;

    for (User* u_ : users) {
        if (convToLower(u_->getName()) == convToLower(u)) {
            uObj = u_;
            break;
        }
    }

    if (carts.find(u) == carts.end()) {
        cout << "Invalid username";
        return;
    }

    std::vector<Product*>& userCart = carts[u];

    std::vector<Product*>::iterator it = userCart.begin();

    // Loop through the vector
    while (it != userCart.end()) {
        Product* product = *it;

        if (product->getQty() > 0 && uObj->getBalance() >= product->getPrice()) {
            product->subtractQty(1);
            uObj->deductAmount(product->getPrice());

            cout << "Product bought: " << product->displayString() << endl;

            it = userCart.erase(it);
        } else {
            cout << "Unable to buy: " << product->displayString() << endl;
            ++it; // Move to the next element in the vector
        }
    }
}


void MyDataStore::dump(std::ostream& ofile) {
  ofile << "<products>" << endl;
    for (Product* p : products) {
        if (p != nullptr) {
            p->dump(ofile);
        }
    }
ofile << "</products>" << endl;
ofile << "<users>" << endl;
    for (User* u : users) {
        if (u != nullptr) {
            u->dump(ofile);
        }
    }
ofile << "</users>" << endl;
}

