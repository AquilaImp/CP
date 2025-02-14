#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h> // Для управления кодировкой консоли

using namespace std;

class SaleItem {
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

    // Конструктор с тремя параметрами
    SaleItem(const string& store, const string& addr, double disc, 
             const string& name, const string& cat, double price) 
        : storeName(store), address(addr), discount(disc), 
          productName(name), category(cat), originalPrice(price) {
        discountedPrice = originalPrice * (1 - discount / 100);  // Вычисление цены после скидки
    }

    // Конструктор копирования
    SaleItem(const SaleItem& other) 
        : storeName(other.storeName), address(other.address), discount(other.discount),
          productName(other.productName), category(other.category), 
          originalPrice(other.originalPrice), discountedPrice(other.discountedPrice) {}

    // Геттеры
    string getStoreName() const { return storeName; }
    string getAddress() const { return address; }
    double getDiscount() const { return discount; }
    string getProductName() const { return productName; }
    string getCategory() const { return category; }
    double getOriginalPrice() const { return originalPrice; }
    double getDiscountedPrice() const { return discountedPrice; }

    // Сеттеры
    void setStoreName(const string& store) { storeName = store; }
    void setAddress(const string& addr) { address = addr; }
    void setDiscount(double disc) { discount = disc; discountedPrice = originalPrice * (1 - discount / 100); }
    void setProductName(const string& name) { productName = name; }
    void setCategory(const string& cat) { category = cat; }
    void setOriginalPrice(double price) { originalPrice = price; discountedPrice = price * (1 - discount / 100); }

    // Операция сложения стоимости двух товаров (с учётом скидок)
    SaleItem operator+(const SaleItem& other) {
        double newPrice = discountedPrice + other.discountedPrice;
        return SaleItem(storeName, address, discount, productName, category, newPrice);
    }

    // Операция вычитания стоимости двух товаров (с учётом скидок)
    SaleItem operator-(const SaleItem& other) {
        double newPrice = discountedPrice - other.discountedPrice;
        return SaleItem(storeName, address, discount, productName, category, newPrice);
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
};

class Store {
private:
    static const int MAX_ITEMS = 100;  // Максимальное количество товаров
    SaleItem items[MAX_ITEMS];         // Массив для хранения товаров
    int count = 0;                     // Счётчик товаров

public:
    // Метод для отображения меню
    void displayMenu() {
        int choice;
        do {
            cout << "\n1. Список товаров\n";
            cout << "2. Добавить товар\n";
            cout << "3. Удалить товар\n";
            cout << "4. Операции с товарами\n";
            cout << "5. Выход\n";
            cout << "Введите выбор: ";
            cin >> choice;

            switch (choice) {
                case 1: listItems(); break;            // Показать список товаров
                case 2: addItem(); break;              // Добавить новый товар
                case 3: deleteItem(); break;           // Удалить товар
                case 4: performOperations(); break;    // Операции с товарами
                case 5: cout << "Выход из программы.\n"; break; // Завершение программы
                default: cout << "Некорректный ввод.\n"; break;
            }
        } while (choice != 5);  // Повторять, пока не выбран выход
    }

private:
    // Метод для выполнения операций с товарами
    void performOperations() {
        int choice;
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
        int index1, index2;
        cout << "Введите номер первого товара: ";
        cin >> index1;
        cout << "Введите номер второго товара: ";
        cin >> index2;

        if (index1 > 0 && index1 <= count && index2 > 0 && index2 <= count) {
            SaleItem result = items[index1 - 1] + items[index2 - 1];
            cout << "Результат сложения цен: " << result.getDiscountedPrice() << endl;
        } else {
            cout << "Неверный номер товара.\n";
        }
    }

    // Метод для вычитания цен двух товаров
    void subtractPrice() {
        int index1, index2;
        cout << "Введите номер первого товара: ";
        cin >> index1;
        cout << "Введите номер второго товара: ";
        cin >> index2;

        if (index1 > 0 && index1 <= count && index2 > 0 && index2 <= count) {
            SaleItem result = items[index1 - 1] - items[index2 - 1];
            cout << "Результат вычитания цен: " << result.getDiscountedPrice() << endl;
        } else {
            cout << "Неверный номер товара.\n";
        }
    }

    // Метод для инкремента скидки
    void incrementDiscount() {
        int index;
        cout << "Введите номер товара для увеличения скидки: ";
        cin >> index;

        if (index > 0 && index <= count) {
            ++items[index - 1];  // Инкремент скидки
            cout << "Новая цена с учётом скидки: " << items[index - 1].getDiscountedPrice() << endl;
        } else {
            cout << "Неверный номер товара.\n";
        }
    }

    // Метод для декремента скидки
    void decrementDiscount() {
        int index;
        cout << "Введите номер товара для уменьшения скидки: ";
        cin >> index;

        if (index > 0 && index <= count) {
            --items[index - 1];  // Декремент скидки
            cout << "Новая цена с учётом скидки: " << items[index - 1].getDiscountedPrice() << endl;
        } else {
            cout << "Неверный номер товара.\n";
        }
    }

    // Метод для сравнения цен товаров
    void comparePrices() {
        int index1, index2;
        cout << "Введите номер первого товара: ";
        cin >> index1;
        cout << "Введите номер второго товара: ";
        cin >> index2;

        if (index1 > 0 && index1 <= count && index2 > 0 && index2 <= count) {
            const SaleItem& item1 = items[index1 - 1];
            const SaleItem& item2 = items[index2 - 1];

            if (item1.getDiscountedPrice() < item2.getDiscountedPrice()) {
                cout << "Второй товар дешевле первого.\n";
            } else if (item1.getDiscountedPrice() > item2.getDiscountedPrice()) {
                cout << "Первый товар дешевле второго.\n";
            } else {
                cout << "Товары равны по цене.\n";
            }
        } else {
            cout << "Неверный номер товара.\n";
        }
    }

    // Метод для отображения всех товаров
    void listItems() {
        if (count > 0) {
            cout << "Список товаров:\n";
            printTableHeader(); // Печать заголовка таблицы
            for (int i = 0; i < count; i++) {
                printTableRow(i, items[i]); // Печать каждой строки таблицы
            }
        } else {
            cout << "Список товаров пуст.\n";
        }
    }

    // Метод для добавления нового товара
    void addItem() {
        if (count < MAX_ITEMS) {
            string store, address, productName, category;
            double discount, price;
            cout << "Введите название магазина: ";
            cin >> store;
            cout << "Введите адрес магазина: ";
            cin >> address;
            cout << "Введите Название товара: ";
            cin >> productName;
            cout << "Введите категорию товара: ";
            cin >> category;
            cout << "Введите процент скидки: ";
            cin >> discount;
            cout << "Введите оригинальную цену: ";
            cin >> price;

            items[count] = SaleItem(store, address, discount, productName, category, price);
            count++; // Увеличиваем счётчик товаров
        } else {
            cout << "Невозможно добавить больше товаров.\n";
        }
    }

    // Метод для удаления товара
    void deleteItem() {
        int index;
        cout << "Введите номер товара для удаления: ";
        cin >> index;
        index--;

        if (index >= 0 && index < count) {
            for (int i = index; i < count - 1; i++) {
                items[i] = items[i + 1];
            }
            count--;
            cout << "Товар удалён.\n";
        } else {
            cout << "Неверный номер.\n";
        }
    }

    // Метод для печати заголовка таблицы
    void printTableHeader() {
        cout << left << setw(5) << "№"
             << setw(25) << "Магазин"
             << setw(25) << "Адрес"
             << setw(40) << "Название"
             << setw(40) << "Категория"
             << setw(40) << "Цена без скидки"
             << setw(40) << "Цена со скидкой" << endl;
        cout << string(140, '-') << endl;
    }

    // Метод для печати строки таблицы
    void printTableRow(int index, const SaleItem& item) {
        cout << left << setw(5) << index + 1
             << setw(20) << item.getStoreName()
             << setw(15) << item.getAddress()
             << setw(15) << item.getProductName()
             << setw(45) << item.getCategory()
             << setw(30) << item.getOriginalPrice()
             << setw(30) << item.getDiscountedPrice() << endl;
    }
};

int main() {
    // Устанавливаем кодировку UTF-8 для ввода/вывода
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    Store store;
    store.displayMenu();
    return 0;
}
