#ifndef SALEITEM_H
#define SALEITEM_H

#include "Product.h"
#include <string>

class Store;

class SaleItem : public Product {
private:
    std::string storeName;
    std::string address;
    double discount;
    std::string productName;
    std::string category;
    double originalPrice;
    double discountedPrice;

public:
    SaleItem(const std::string& store, const std::string& addr, double disc, 
             const std::string& name, const std::string& cat, double price);
    virtual ~SaleItem() {}

    void showDetails() const override;
    double getDiscountedPrice() const;
    void setDiscount(double disc);

    friend class Store;
};

#endif
