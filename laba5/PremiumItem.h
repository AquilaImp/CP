#ifndef PREMIUMITEM_H
#define PREMIUMITEM_H

#include "DiscountedItem.h"

class PremiumItem : public DiscountedItem {
private:
    std::string premiumFeature;

public:
    PremiumItem(const std::string& store, const std::string& addr, double disc, 
                const std::string& name, const std::string& cat, double price, 
                double extraDisc, const std::string& feature);

    void showDetails() const override;
};

#endif
