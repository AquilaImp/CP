#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
public:
    virtual void showDetails() const = 0;
    virtual ~Product() {}
};

#endif
