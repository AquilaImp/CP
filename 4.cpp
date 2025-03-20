#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h> // Для управления кодировкой консоли

using namespace std;

// Абстрактный базовый класс Product
class Product {
public:
    virtual void displayInfo() const = 0;  // Чисто виртуальная функция для вывода информации о товаре
    virtual double getPrice() const = 0;   // Чисто виртуальная функция для получения цены
    virtual string getCategory() const = 0; // Метод для получения категории товара
    virtual ~Product() = default;  // Виртуальный деструктор
};

// Класс SaleItem, наследующий от Product
class SaleItem : public Product {
private:
    string storeName;      // Название магазина
    string address;        // Адрес магазина
    double discount;       // Процент скидки
    string productName;    // Название товара
    string category;       // Категория товара
    double originalPrice;  // Оригинальная цена товара
    double discountedPrice; // Цена после скидки

public:

    // Конструктор по умолчанию
    SaleItem() : storeName("Неизвестно"), address("Неизвестно"), discount(0),
                 productName("Неизвестно"), category("Неизвестно"),
                 originalPrice(0), discountedPrice(0) {}

    // Конструктор с параметрами
    SaleItem(const string& store, const string& addr, double disc, 
             const string& name, const string& cat, double price) 
        : storeName(store), address(addr), discount(disc), 
          productName(name), category(cat), originalPrice(price) {
        discountedPrice = originalPrice * (1 - discount / 100);  // Вычисление цены после скидки
    }

    // Переопределение виртуальных методов
    void displayInfo() const override {
        cout << "| " << setw(15) << productName << " | "
             << setw(15) << storeName << " | "
             << setw(15) << address << " | "
             << setw(10) << category << " | "
             << setw(15) << originalPrice << " | "
             << setw(18) << discountedPrice << " |" << endl;
    }

    double getPrice() const override {
        return discountedPrice;  // Возвращаем цену со скидкой
    }
    
    string getCategory() const override { return category; } // Возвращаем категорию товара

    // Геттеры
    string getStoreName() const { return storeName; }
    string getAddress() const { return address; }
    double getDiscount() const { return discount; }
    string getProductName() const { return productName; }
    double getOriginalPrice() const { return originalPrice; }
    double getDiscountedPrice() const { return discountedPrice; }

    // Сеттеры
    void setStoreName(const string& store) { storeName = store; }
    void setAddress(const string& addr) { address = addr; }
    void setDiscount(double disc) { discount = disc; discountedPrice = originalPrice * (1 - discount / 100); }
    void setProductName(const string& name) { productName = name; }
    void setCategory(const string& cat) { category = cat; }
    void setOriginalPrice(double price) { originalPrice = price; discountedPrice = price * (1 - discount / 100); }

    // Метод для изменения скидочной цены
    void setDiscountedPrice(double price) { discountedPrice = price; }

    // Операция сложения стоимости двух товаров (с учётом скидок)
    SaleItem operator+(const SaleItem& other) {
        double newPrice = discountedPrice + other.discountedPrice;
        double newOriginalPrice = originalPrice + other.originalPrice;
        return SaleItem(storeName, address, discount, productName, category, newOriginalPrice);
    }

    // Операция вычитания стоимости двух товаров (с учётом скидок)
    SaleItem operator-(const SaleItem& other) {
        double newPrice = discountedPrice - other.discountedPrice;
        double newOriginalPrice = originalPrice - other.originalPrice;
        return SaleItem(storeName, address, discount, productName, category, newOriginalPrice);
    }

    // Операция инкремента (увеличение скидки на 1%)
    SaleItem& operator++() {
        ++discount;
        discountedPrice = originalPrice * (1 - discount / 100);
        return *this;
    }

    // Операция декремента (уменьшение скидки на 1%)
    SaleItem& operator--() {
        --discount;
        discountedPrice = originalPrice * (1 - discount / 100);
        return *this;
    }

    // Операция сравнения (сравнение цен после скидки)
    bool operator<(const SaleItem& other) const {
        return discountedPrice < other.discountedPrice;
    }

    // Дружественная функция для изменения скидки товара
    friend void applyDiscount(SaleItem& item, double discount);
};

// Реализация дружественной функции
void applyDiscount(SaleItem& item, double discount) {
    item.setDiscount(discount);  // Изменяем скидку через метод
}

// Новый класс-наследник от SaleItem
class DiscountedSaleItem : public SaleItem {
private:
    string additionalInfo; // Дополнительная информация для товаров с большой скидкой

public:
    // Конструктор с параметрами
    DiscountedSaleItem(const string& store, const string& addr, double disc, 
                       const string& name, const string& cat, double price, const string& info)
        : SaleItem(store, addr, disc, name, cat, price), additionalInfo(info) {}

    void displayInfo() const override {
        // Выводим информацию о товаре с дополнительным описанием
        SaleItem::displayInfo();
        cout << "Дополнительная информация: " << additionalInfo << endl;
    }
};

// Класс Store
class Store {
private:
    static const int MAX_ITEMS = 100;  // Максимальное количество товаров
    Product* items[MAX_ITEMS];         // Массив для хранения товаров
    int count = 0;                     // Счётчик товаров
    void applyDiscount(SaleItem& item, double discount) {
        item.setDiscount(discount);  // Устанавливаем новый процент скидки
    }
    
public:
    // Метод для отображения меню
    void displayMenu() {
        int choice;
        do {
            cout << "\n1. Список товаров\n";
            cout << "2. Добавить товар\n";
            cout << "3. Удалить товар\n";
            cout << "4. Операции с товарами\n";
            cout << "5. Товары в категории Одежда\n";  // Новый пункт меню
            cout << "6. Выход\n";
            cout << "Введите выбор: ";
            cin >> choice;

            switch (choice) {
                case 1: listItems(); break;            // Показать список товаров
                case 2: addItem(); break;              // Добавить новый товар
                case 3: deleteItem(); break;           // Удалить товар
                case 4: performOperations(); break;    // Операции с товарами
                case 5: listClothesItems(); break;     // Показать товары в категории Одежда
                case 6: cout << "Выход из программы.\n"; break; // Завершение программы
                default: cout << "Некорректный ввод.\n"; break;
            }
        } while (choice != 6);  // Повторять, пока не выбран выход
    }

private:
    // Метод для отображения товаров в категории Одежда
    void listClothesItems() {
        bool found = false;
        if (count > 0) {
            cout << "Товары в категории Одежда:\n";
            printTableHeader(); // Печать заголовка таблицы
            for (int i = 0; i < count; i++) {
                // Приводим объект к типу SaleItem, чтобы использовать getCategory
                SaleItem* saleItem = dynamic_cast<SaleItem*>(items[i]);
                if (saleItem != nullptr && (saleItem->getCategory() == "Одежда" || saleItem->getCategory() == "Clothes")) {
                    saleItem->displayInfo();  // Вывод информации о товаре
                    found = true;
                }
            }
            if (!found) {
                cout << "Товары в категории 'Одежда' не найдены.\n";
            }
        } else {
            cout << "Список товаров пуст.\n";
        }
    }

    void listItems() {
        if (count > 0) {
            cout << "Список товаров:\n";
            printTableHeader(); // Печать заголовка таблицы
            for (int i = 0; i < count; i++) {
                items[i]->displayInfo(); // Вывод информации о товаре
            }
        } else {
            cout << "Список товаров пуст.\n";
        }
    }

    // Метод для вывода заголовка таблицы
    void printTableHeader() {
        cout << "| " << setw(15) << "Товар" << " | "
             << setw(15) << "Магазин" << " | "
             << setw(15) << "Адрес" << " | "
             << setw(10) << "Категория" << " | "
             << setw(15) << "Цена без скидки" << " | "
             << setw(18) << "Цена со скидкой" << " |" << endl;
        cout << "-----------------------------------------------------------------------------\n";
    }

    // Метод для добавления товара
    void addItem() {
        if (count < MAX_ITEMS) {
            string storeName, address, productName, category, additionalInfo;
            double discount, price;
            int itemType;
            cout << "Выберите тип товара (1 - обычный, 2 - со скидкой): ";
            cin >> itemType;
            cout << "Введите название магазина: ";
            cin >> storeName;
            cout << "Введите адрес магазина: ";
            cin >> address;
            cout << "Введите процент скидки: ";
            cin >> discount;
            cout << "Введите название товара: ";
            cin >> productName;
            cout << "Введите категорию товара: ";
            cin >> category;
            cout << "Введите цену товара: ";
            cin >> price;

            if (itemType == 1) {
                items[count++] = new SaleItem(storeName, address, discount, productName, category, price);
            } else if (itemType == 2) {
                cout << "Введите дополнительную информацию: ";
                cin.ignore(); // Чтобы убрать лишний символ новой строки из буфера
                getline(cin, additionalInfo);
                items[count++] = new DiscountedSaleItem(storeName, address, discount, productName, category, price, additionalInfo);
            } else {
                cout << "Некорректный выбор типа товара.\n";
            }
        } else {
            cout << "Превышено максимальное количество товаров.\n";
        }
    }

    // Метод для удаления товара
    void deleteItem() {
        int index;
        cout << "Введите индекс товара для удаления: ";
        cin >> index;
        index--;  // Снижаем на 1 для корректности индексации

        if (index >= 0 && index < count) {
            delete items[index];  // Удаление товара
            for (int i = index; i < count - 1; i++) {
                items[i] = items[i + 1];  // Сдвигаем оставшиеся товары
            }
            count--;  // Уменьшаем количество товаров
        } else {
            cout << "Некорректный индекс.\n";
        }
    }

    // Метод для выполнения операций с товарами
    void performOperations() {
        int choice;
        listItems(); // Автоматически выводим список товаров перед операциями
        cout << "\nВыберите операцию:\n";
        cout << "1. Сложить цену двух товаров\n";
        cout << "2. Вычесть цену двух товаров\n";
        cout << "3. Инкремент скидки на товар\n";
        cout << "4. Декремент скидки на товар\n";
        cout << "5. Сравнить цены товаров\n";
        cout << "Введите выбор: ";
        cin >> choice;

        switch (choice) {
            case 1: addPrice(); break;
            case 2: subtractPrice(); break;
            case 3: incrementDiscount(); break;
            case 4: decrementDiscount(); break;
            case 5: comparePrices(); break;
            default: cout << "Некорректный ввод.\n"; break;
        }
    }

    // Метод для сложения цен двух товаров
    void addPrice() {
        if (count >= 2) {
            int index1, index2;
            cout << "Введите индексы двух товаров для сложения: ";
            cin >> index1 >> index2;
            index1--; index2--;  // Снижаем на 1 для корректности индексации

            if (index1 >= 0 && index1 < count && index2 >= 0 && index2 < count) {
                SaleItem* item1 = dynamic_cast<SaleItem*>(items[index1]);
                SaleItem* item2 = dynamic_cast<SaleItem*>(items[index2]);

                cout << "Товар 1:\n";
                item1->displayInfo();
                cout << "Товар 2:\n";
                item2->displayInfo();

                double totalDiscountedPrice = item1->getDiscountedPrice() + item2->getDiscountedPrice();
                double totalOriginalPrice = item1->getOriginalPrice() + item2->getOriginalPrice();

                cout << "Результат сложения цен:\n";
                cout << "Со скидкой: " << totalDiscountedPrice << "\n";
                cout << "Без скидки: " << totalOriginalPrice << "\n";
            } else {
                cout << "Некорректные индексы.\n";
            }
        } else {
            cout << "Недостаточно товаров для выполнения операции.\n";
        }
    }

    // Метод для вычитания цен двух товаров
    void subtractPrice() {
        if (count >= 2) {
            int index1, index2;
            cout << "Введите индексы двух товаров для вычитания: ";
            cin >> index1 >> index2;
            index1--; index2--;  // Снижаем на 1 для корректности индексации

            if (index1 >= 0 && index1 < count && index2 >= 0 && index2 < count) {
                SaleItem* item1 = dynamic_cast<SaleItem*>(items[index1]);
                SaleItem* item2 = dynamic_cast<SaleItem*>(items[index2]);

                cout << "Товар 1:\n";
                item1->displayInfo();
                cout << "Товар 2:\n";
                item2->displayInfo();

                double totalDiscountedPrice = item1->getDiscountedPrice() - item2->getDiscountedPrice();
                double totalOriginalPrice = item1->getOriginalPrice() - item2->getOriginalPrice();

                cout << "Результат вычитания цен:\n";
                cout << "Со скидкой: " << totalDiscountedPrice << "\n";
                cout << "Без скидки: " << totalOriginalPrice << "\n";
            } else {
                cout << "Некорректные индексы.\n";
            }
        } else {
            cout << "Недостаточно товаров для выполнения операции.\n";
        }
    }

    // Метод для инкремента скидки
    void incrementDiscount() {
        int index;
        cout << "Введите индекс товара для увеличения скидки: ";
        cin >> index;
        index--;  // Снижаем на 1 для корректности индексации

        if (index >= 0 && index < count) {
            SaleItem* item = dynamic_cast<SaleItem*>(items[index]);
            if (item != nullptr) {
                ++(*item);  // Увеличиваем скидку на 1%
                cout << "Скидка увеличена на 1%.\n";
                item->displayInfo();
            }
        } else {
            cout << "Некорректный индекс.\n";
        }
    }

    // Метод для декремента скидки
    void decrementDiscount() {
        int index;
        cout << "Введите индекс товара для уменьшения скидки: ";
        cin >> index;
        index--;  // Снижаем на 1 для корректности индексации

        if (index >= 0 && index < count) {
            SaleItem* item = dynamic_cast<SaleItem*>(items[index]);
            if (item != nullptr) {
                --(*item);  // Уменьшаем скидку на 1%
                cout << "Скидка уменьшена на 1%.\n";
                item->displayInfo();
            }
        } else {
            cout << "Некорректный индекс.\n";
        }
    }

    // Метод для сравнения цен товаров
    void comparePrices() {
        if (count >= 2) {
            int index1, index2;
            cout << "Введите индексы двух товаров для сравнения: ";
            cin >> index1 >> index2;
            index1--; index2--;  // Снижаем на 1 для корректности индексации

            if (index1 >= 0 && index1 < count && index2 >= 0 && index2 < count) {
                SaleItem* item1 = dynamic_cast<SaleItem*>(items[index1]);
                SaleItem* item2 = dynamic_cast<SaleItem*>(items[index2]);

                cout << "Товар 1:\n";
                item1->displayInfo();
                cout << "Товар 2:\n";
                item2->displayInfo();

                if (*item1 < *item2) {
                    cout << "Товар 1 дешевле товара 2.\n";
                } else {
                    cout << "Товар 2 дешевле товара 1.\n";
                }
            } else {
                cout << "Некорректные индексы.\n";
            }
        } else {
            cout << "Недостаточно товаров для выполнения операции.\n";
        }
    }
};

// Точка входа
int main() {
    SetConsoleCP(65001);          //Кодировка Ру
    SetConsoleOutputCP(65001);    
    Store store;
    store.displayMenu();
    return 0;
}
