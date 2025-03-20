#pragma once
#include "Product.h"
#include <string>

class SaleItem : public Product {
private:
    std::string storeName;      // Название магазина
    std::string address;        // Адрес магазина
    double discount;       // Процент скидки
    std::string productName;    // Название товара
    std::string category;       // Категория товара
    double originalPrice;  // Оригинальная цена товара
    double discountedPrice; // Цена после скидки

public:
    SaleItem();
    SaleItem(const std::string& store, const std::string& addr, double disc, 
             const std::string& name, const std::string& cat, double price);

    void displayInfo() const override;
    double getPrice() const override;
    std::string getCategory() const override;

    // Геттеры
    std::string getStoreName() const;
    std::string getAddress() const;
    double getDiscount() const;
    std::string getProductName() const;
    double getOriginalPrice() const;
    double getDiscountedPrice() const;

    // Сеттеры
    void setStoreName(const std::string& store);
    void setAddress(const std::string& addr);
    void setDiscount(double disc);
    void setProductName(const std::string& name);
    void setCategory(const std::string& cat);
    void setOriginalPrice(double price);
    void setDiscountedPrice(double price);

    // Операторы
    SaleItem operator+(const SaleItem& other);
    SaleItem operator-(const SaleItem& other);
    SaleItem& operator++();
    SaleItem& operator--();
    bool operator<(const SaleItem& other) const;

    friend void applyDiscount(SaleItem& item, double discount);
};
