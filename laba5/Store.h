#ifndef STORE_H
#define STORE_H

#include "Product.h"
#include "SaleItem.h"

class Store {
private:
    static const int MAX_ITEMS = 100;
    Product* items[MAX_ITEMS];
    int count;

public:
    Store();
    void addItem(Product* item);
    void listItems() const;
    void updateDiscount(SaleItem& item, double newDiscount);
};

#endif
