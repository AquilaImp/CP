#include "SaleItem.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Конструктор без параметров, просто ставим дефолтные значения
SaleItem::SaleItem() : storeName("Неизвестно"), address("Неизвестно"), discount(0),
                       productName("Неизвестно"), category("Неизвестно"),
                       originalPrice(0), discountedPrice(0) {}

// Конструктор с параметрами, тут передаём данные и сразу считаем цену со скидкой
SaleItem::SaleItem(const string& store, const string& addr, double disc, 
                   const string& name, const string& cat, double price) 
    : storeName(store), address(addr), discount(disc), 
      productName(name), category(cat), originalPrice(price) {
    discountedPrice = originalPrice * (1 - discount / 100); // Применяем скидку
}

// Метод для вывода инфы о товаре в табличном виде (чтобы красиво было)
void SaleItem::displayInfo() const {
    cout << "| " << setw(15) << productName << " | "
         << setw(15) << storeName << " | "
         << setw(15) << address << " | "
         << setw(10) << category << " | "
         << setw(15) << originalPrice << " | "
         << setw(18) << discountedPrice << " |" << endl;
}

// Возвращает цену со скидкой
double SaleItem::getPrice() const {
    return discountedPrice;
}

// Возвращает категорию товара
string SaleItem::getCategory() const {
    return category;
}

// --- Геттеры 
string SaleItem::getStoreName() const { return storeName; }
string SaleItem::getAddress() const { return address; }
double SaleItem::getDiscount() const { return discount; }
string SaleItem::getProductName() const { return productName; }
double SaleItem::getOriginalPrice() const { return originalPrice; }
double SaleItem::getDiscountedPrice() const { return discountedPrice; }

// --- Сеттеры
void SaleItem::setStoreName(const string& store) { storeName = store; }
void SaleItem::setAddress(const string& addr) { address = addr; }
void SaleItem::setDiscount(double disc) { 
    discount = disc; 
    discountedPrice = originalPrice * (1 - discount / 100); // Обновляем цену
}
void SaleItem::setProductName(const string& name) { productName = name; }
void SaleItem::setCategory(const string& cat) { category = cat; }
void SaleItem::setOriginalPrice(double price) { 
    originalPrice = price; 
    discountedPrice = price * (1 - discount / 100); // Обновляем цену со скидкой
}
void SaleItem::setDiscountedPrice(double price) { discountedPrice = price; }



//  складывает цены двух товаров и делает новый объект
SaleItem SaleItem::operator+(const SaleItem& other) {
    double newOriginalPrice = originalPrice + other.originalPrice;
    return SaleItem(storeName, address, discount, productName, category, newOriginalPrice);
}

// разница в ценах двух товаров
SaleItem SaleItem::operator-(const SaleItem& other) {
    double newOriginalPrice = originalPrice - other.originalPrice;
    return SaleItem(storeName, address, discount, productName, category, newOriginalPrice);
}

// Инкримент: увеличивает скидку (типа акция)
SaleItem& SaleItem::operator++() {
    ++discount;
    discountedPrice = originalPrice * (1 - discount / 100); // Обновляем цену
    return *this;
}

// ДИКРИМЕНТ: уменьшает скидку (если вдруг передумали делать акцию)
SaleItem& SaleItem::operator--() {
    --discount;
    discountedPrice = originalPrice * (1 - discount / 100); // Обновляем цену
    return *this;
}

// Оператор < для сравнения 
bool SaleItem::operator<(const SaleItem& other) const {
    return discountedPrice < other.discountedPrice;
}