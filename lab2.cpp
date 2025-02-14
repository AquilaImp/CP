#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>  //Русиф

using namespace std;

class SaleItem {
private:
    string storeName;      // Название магазина
    string address;        // Адрес магазина
    double discount;       // Процент скидки
    string productName;    // Наименование товара
    string category;       // Категория товара (например, "Одежда")
    double originalPrice;  // Оригинальная цена товара
    double discountedPrice; // Цена после скидки

public:
    //Конструктор по умолчанию
    SaleItem() : storeName("Неизвестно"), address("Неизвестно"), discount(0), 
                 productName("Неизвестно"), category("Неизвестно"), 
                 originalPrice(0), discountedPrice(0) {}

    //Конструктор с параметрами (с тремя параметрами: название магазина, адрес и товар)
    SaleItem(const string& store, const string& addr, double disc, 
             const string& name, const string& cat, double price) 
        : storeName(store), address(addr), discount(disc), 
          productName(name), category(cat), originalPrice(price) {
        discountedPrice = originalPrice * (1 - discount / 100);  //Вычисление цены после скидки
    }

    //Конструктор копирования
    SaleItem(const SaleItem& other) 
        : storeName(other.storeName), address(other.address), discount(other.discount),
          productName(other.productName), category(other.category), 
          originalPrice(other.originalPrice), discountedPrice(other.discountedPrice) {}

    //Геттеры
    string getStoreName() const { return storeName; }
    string getAddress() const { return address; }
    double getDiscount() const { return discount; }
    string getProductName() const { return productName; }
    string getCategory() const { return category; }
    double getOriginalPrice() const { return originalPrice; }
    double getDiscountedPrice() const { return discountedPrice; }

    //Сеттеры
    void setStoreName(const string& store) { storeName = store; }
    void setAddress(const string& addr) { address = addr; }
    void setDiscount(double disc) { discount = disc; }
    void setProductName(const string& name) { productName = name; }
    void setCategory(const string& cat) { category = cat; }
    void setOriginalPrice(double price) { originalPrice = price; discountedPrice = price * (1 - discount / 100); }
};

//Класс для работы с магазином
class Store {
private:
    static const int MAX_ITEMS = 100;  //Максимальное количество товаров
    SaleItem items[MAX_ITEMS];         //Массив для хранения
    int count = 0;                     //Счётчик 

public:
    //Метод для отображения меню
    void displayMenu() {
        int choice;
        do {
            cout << "\n1. Список товаров на распродаже\n";
            cout << "2. Добавить товар\n";
            cout << "3. Удалить товар\n";
            cout << "4. Товары в категории 'Одежда'\n";
            cout << "5. Выход\n";
            cout << "Введите выбор: ";
            cin >> choice;

            switch (choice) {
                case 1: listItems(); break;            // Показать список товаров
                case 2: addItem(); break;              // Добавить новый товар
                case 3: deleteItem(); break;           // Удалить товар
                case 4: listItemsInCategory("Одежда"); break; // Показать товары категории 'Одежда'
                case 5: cout << "Выход из программы.\n"; break; // Завершение программы
                default: cout << "Некорректный ввод.\n"; break;
            }
        } while (choice != 5); 
    }

private:
    // Метод для отображения всех товаров на распродаже
    void listItems() {
        if (count > 0) {
            cout << "Список товаров на распродаже:\n";
            printTableHeader(); 
            for (int i = 0; i < count; i++) {
                printTableRow(i, items[i]); 
            }
        } else {
            cout << "Список товаров пуст.\n";
        }
    }

    //Метод для добавления нового товара
    void addItem() {
        if (count < MAX_ITEMS) {
            string storeName, address, productName, category;
            double discount, originalPrice;

            cout << "Введите название магазина: ";
            cin.ignore();  //Очистка буфера ввода
            getline(cin, storeName);

            cout << "Введите адрес магазина: ";
            getline(cin, address);

            cout << "Введите наименование товара: ";
            getline(cin, productName);

            cout << "Введите категорию товара: ";
            getline(cin, category);

            cout << "Введите оригинальную цену товара: ";
            cin >> originalPrice;

            cout << "Введите процент скидки: ";
            cin >> discount;

           
            items[count] = SaleItem(storeName, address, discount, productName, category, originalPrice);
            count++;
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
            //Удаление сдвиг
            for (int i = index; i < count - 1; i++) {
                items[i] = items[i + 1];
            }
            count--;  // Уменьшаем счётчик товаров
            cout << "Товар удалён.\n";
        } else {
            cout << "Неверный номер.\n";
        }
    }

    // Метод для отображения товаров в категории 'Одежда'
    void listItemsInCategory(const string& category) {
        cout << "Товары в категории '" << category << "':\n";
        bool found = false; // Флаг для отслеживания наличия товаров в категории
        printTableHeader();  // Печать заголовка таблицы
        for (int i = 0; i < count; i++) {
            if (items[i].getCategory() == category) {
                printTableRow(i, items[i]);  // Печать найденного товара
                found = true;
            }
        }
        if (!found) {
            cout << "Нет товаров в категории '" << category << "'.\n";
        }
    }

    //Заголовок
    void printTableHeader() {
        cout << left << setw(5) << "№"
             << setw(25) << "Магазин"
             << setw(25) << "Адрес"
             << setw(40) << "Наименование товара"
             << setw(40) << "Категория"
             << setw(40) << "Оригинальная цена"
             << setw(40) << "Цена со скидкой" << endl;
        cout << string(140, '-') << endl;
    }

    //Строки
    void printTableRow(int index, const SaleItem& item) {
        cout << left << setw(5) << index + 1
             << setw(20) << item.getStoreName()
             << setw(15) << item.getAddress()
             << setw(15) << item.getProductName()
             << setw(45) << item.getCategory()
             << setw(30) << fixed << setprecision(2) << item.getOriginalPrice()
             << setw(30) << fixed << setprecision(2) << item.getDiscountedPrice() << endl;
    }
};

int main() {
    SetConsoleCP(65001);          //Кодировка Ру
    SetConsoleOutputCP(65001);    

    Store store;     // Создание объекта класса Store
    store.displayMenu(); // Вызов метода для отображения меню
    return 0;
}
