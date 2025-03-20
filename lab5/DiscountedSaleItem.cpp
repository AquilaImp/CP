#include "DiscountedSaleItem.h"
#include <iostream>

DiscountedSaleItem::DiscountedSaleItem(const std::string& store, const std::string& addr, 
                                     double disc, const std::string& name, const std::string& cat, 
                                     double price, const std::string& info)
    : SaleItem(store, addr, disc, name, cat, price), additionalInfo(info) {}

void DiscountedSaleItem::displayInfo() const {
    SaleItem::displayInfo();
    std::cout << "Дополнительная информация: " << additionalInfo << std::endl;
}
