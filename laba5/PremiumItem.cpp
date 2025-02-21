#include "PremiumItem.h"
#include <iostream>

using namespace std;

PremiumItem::PremiumItem(const string& store, const string& addr, double disc, 
                        const string& name, const string& cat, double price, 
                        double extraDisc, const string& feature)
    : DiscountedItem(store, addr, disc, name, cat, price, extraDisc), 
      premiumFeature(feature) {}

void PremiumItem::showDetails() const {
    cout << "Premium Item: ";
    DiscountedItem::showDetails();
    cout << "Premium Feature: " << premiumFeature << endl;
}
