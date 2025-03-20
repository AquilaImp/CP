
#include "Product.h"
#include "SaleItem.h"
#include "DiscountedSaleItem.h"

class Store {
private:
    static const int MAX_ITEMS = 100;  // Кол-во товаров
    Product* items[MAX_ITEMS];         // Массив хранения
    int count = 0;                     // Счётчик товаров

    void listClothesItems();           // Вывод Одежда
    void listItems();                  // Вывод
    void printTableHeader();           // Заголовок
    void addItem();                    // Добавить
    void deleteItem();                 // Удалить
    void performOperations();          // Операции
    
    //Операции (4)
    void addPrice();                   // +
    void subtractPrice();              // -
    void incrementDiscount();          // Скидка+
    void decrementDiscount();          // Скидка-
    void comparePrices();              // <>

public:
    Store() = default;
    ~Store();
    void displayMenu();                // Метод для отображения меню
};
