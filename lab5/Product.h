#pragma once
#include <string>

class Product {
public:
    virtual void displayInfo() const = 0;  // Виртуалка для вывода информации о товаре
    virtual double getPrice() const = 0;   // Виртуалка для получения цены
    virtual std::string getCategory() const = 0; // Метод для получения категории товара
    virtual ~Product() = default;  // Виртуальный деструктор
};
