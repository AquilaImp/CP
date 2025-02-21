#include "Store.h"
#include <iostream>

using namespace std;

Store::Store() : count(0) {}

void Store::addItem(Product* item) {
    if (count < MAX_ITEMS) {
        items[count++] = item;
    } else {
        cout << "Store is full.\n";
    }
}

void Store::listItems() const {
    for (int i = 0; i < count; ++i) {
        items[i]->showDetails();
    }
}

void Store::updateDiscount(SaleItem& item, double newDiscount) {
    item.setDiscount(newDiscount);
    cout << "Discount updated. New discounted price: " << item.getDiscountedPrice() << endl;
}
