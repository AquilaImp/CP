#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h> 

using namespace std;

class Product {
public:
    virtual void showDetails() const = 0;  // Абстрактная функция для вывода информации
    virtual ~Product() = default;
};

class SaleItem : public Product {
private:
    string storeName;
    string address;
    double discount;
    string productName;
    string category;
    double originalPrice;
    double discountedPrice;

public:
    SaleItem(const string& store, const string& addr, double disc, 
             const string& name, const string& cat, double price) 
        : storeName(store), address(addr), discount(disc), 
          productName(name), category(cat), originalPrice(price) {
        discountedPrice = originalPrice * (1 - discount / 100);
    }

    void showDetails() const override {
        cout << "Product: " << productName << ", Store: " << storeName 
             << ", Address: " << address << ", Category: " << category 
             << ", Price: " << originalPrice << ", Discounted Price: " << discountedPrice << endl;
    }

    // Другие методы для работы с товаром
    double getDiscountedPrice() const { return discountedPrice; }
    void setDiscount(double disc) {
        discount = disc;
        discountedPrice = originalPrice * (1 - discount / 100);
    }

    friend class Store;  // Дружеский класс Store
};

class DiscountedItem : public SaleItem {
private:
    double extraDiscount;

public:
    DiscountedItem(const string& store, const string& addr, double disc, 
                   const string& name, const string& cat, double price, double extraDisc)
        : SaleItem(store, addr, disc, name, cat, price), extraDiscount(extraDisc) {}

    void showDetails() const override {
        cout << "Discounted Item: ";
        SaleItem::showDetails();
        cout << "Extra Discount: " << extraDiscount << "%" << endl;
    }

    void applyExtraDiscount() {
        double newPrice = getDiscountedPrice() * (1 - extraDiscount / 100);
        cout << "Price after extra discount: " << newPrice << endl;
    }
};

class PremiumItem : public DiscountedItem {
private:
    string premiumFeature;

public:
    PremiumItem(const string& store, const string& addr, double disc, 
                const string& name, const string& cat, double price, double extraDisc, const string& feature)
        : DiscountedItem(store, addr, disc, name, cat, price, extraDisc), premiumFeature(feature) {}

    void showDetails() const override {
        cout << "Premium Item: ";
        DiscountedItem::showDetails();
        cout << "Premium Feature: " << premiumFeature << endl;
    }
};

// Класс Store, который является другом класса SaleItem
class Store {
private:
    static const int MAX_ITEMS = 100;
    Product* items[MAX_ITEMS];
    int count = 0;

public:
    Store() : count(0) {}

    // Добавить товар в магазин
    void addItem(Product* item) {
        if (count < MAX_ITEMS) {
            items[count++] = item;
        } else {
            cout << "Store is full.\n";
        }
    }

    // Вывод списка товаров
    void listItems() const {
        for (int i = 0; i < count; ++i) {
            items[i]->showDetails();
        }
    }

    // Дружественная функция для изменения скидки на товар
    void updateDiscount(SaleItem& item, double newDiscount) {
        item.setDiscount(newDiscount);
        cout << "Discount updated. New discounted price: " << item.getDiscountedPrice() << endl;
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Store store;

    // Создание объектов разных типов
    SaleItem* item1 = new SaleItem("Shop1", "Address1", 10, "Product1", "Category1", 100);
    DiscountedItem* item2 = new DiscountedItem("Shop2", "Address2", 20, "Product2", "Category2", 200, 5);
    PremiumItem* item3 = new PremiumItem("Shop3", "Address3", 15, "Product3", "Category3", 300, 10, "Free shipping");

    // Добавление товаров в магазин
    store.addItem(item1);
    store.addItem(item2);
    store.addItem(item3);

    // Список товаров в магазине
    store.listItems();

    // Обновление скидки через дружественную функцию
    store.updateDiscount(*item1, 25);

    // Выводим обновленный список
    cout << "\nUpdated Item Details:\n";
    store.listItems();

    // Очистка памяти
    delete item1;
    delete item2;
    delete item3;

    return 0;
}
