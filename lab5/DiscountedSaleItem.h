
#include "SaleItem.h"
#include <string>

class DiscountedSaleItem : public SaleItem {
private:
    std::string additionalInfo; // Дополнительная информация для товаров с большой скидкой

public:
    DiscountedSaleItem(const std::string& store, const std::string& addr, double disc, 
                       const std::string& name, const std::string& cat, double price, 
                       const std::string& info);

    void displayInfo() const override;
};
