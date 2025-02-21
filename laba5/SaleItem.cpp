#include "SaleItem.h"
#include <iostream>

using namespace std;

SaleItem::SaleItem(const string& store, const string& addr, double disc, 
                   const string& name, const string& cat, double price)
    : storeName(store), address(addr), discount(disc), 
      productName(name), category(cat), originalPrice(price) {
    discountedPrice = originalPrice * (1 - discount / 100);
}

void SaleItem::showDetails() const {
    cout << "Product: " << productName << ", Store: " << storeName 
         << ", Address: " << address << ", Category: " << category 
         << ", Price: " << originalPrice << ", Discounted Price: " << discountedPrice << endl;
}

double SaleItem::getDiscountedPrice() const {
    return discountedPrice;
}

void SaleItem::setDiscount(double disc) {
    discount = disc;
    discountedPrice = originalPrice * (1 - discount / 100);
}
