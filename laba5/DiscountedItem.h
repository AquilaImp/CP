#ifndef DISCOUNTEDITEM_H
#define DISCOUNTEDITEM_H

#include "SaleItem.h"

class DiscountedItem : public SaleItem {
private:
    double extraDiscount;

public:
    DiscountedItem(const std::string& store, const std::string& addr, double disc, 
                   const std::string& name, const std::string& cat, double price, double extraDisc);

    void showDetails() const override;
    void applyExtraDiscount();
};

#endif
