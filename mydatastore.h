// mydatastore.h
#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <vector>
#include <unordered_map>
#include <queue>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void addToCart(std::string u, Product* p);
    void viewCart(std::string u);
    void buyCart(std::string u);
    void quit(std::ostream& ofile);
    void dump(std::ostream& ofile);

private:
    std::vector<Product*> products;
    std::vector<User*> users;
    std::unordered_map<std::string, std::set<Product*>> keywordIndex;
    std::unordered_map<std::string, std::vector<Product*>> carts;
};

#endif
