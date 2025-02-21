#include "DiscountedItem.h"
#include <iostream>

using namespace std;

DiscountedItem::DiscountedItem(const string& store, const string& addr, double disc, 
                              const string& name, const string& cat, double price, double extraDisc)
    : SaleItem(store, addr, disc, name, cat, price), extraDiscount(extraDisc) {}

void DiscountedItem::showDetails() const {
    cout << "Discounted Item: ";
    SaleItem::showDetails();
    cout << "Extra Discount: " << extraDiscount << "%" << endl;
}

void DiscountedItem::applyExtraDiscount() {
    double newPrice = getDiscountedPrice() * (1 - extraDiscount / 100);
    cout << "Price after extra discount: " << newPrice << endl;
}
