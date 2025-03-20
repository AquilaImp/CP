#include "Store.h"
#include <iostream>
#include <iomanip>

using namespace std;
// Деструктор
Store::~Store() {
    for (int i = 0; i < count; i++) {
        delete items[i];
    }
}

void Store::displayMenu() {
    int choice;
    do {
        cout << "\n1. Список товаров\n";
        cout << "2. Добавить товар\n";
        cout << "3. Удалить товар\n";
        cout << "4. Операции с товарами\n";
        cout << "5. Товары в категории Одежда\n";
        cout << "6. Выход\n";
        cout << "Введите выбор: ";
        cin >> choice;

        switch (choice) {
            case 1: listItems(); break;
            case 2: addItem(); break;
            case 3: deleteItem(); break;
            case 4: performOperations(); break;
            case 5: listClothesItems(); break;
            case 6: cout << "Выход из программы.\n"; break;
            default: cout << "Некорректный ввод.\n"; break;
        }
    } while (choice != 6);
}
// Отоюражение товаров Одежда
void Store::listClothesItems() {
    bool found = false;
    if (count > 0) {
        cout << "Товары в категории Одежда:\n";
        printTableHeader(); //Заголовок
        for (int i = 0; i < count; i++) {
            SaleItem* saleItem = dynamic_cast<SaleItem*>(items[i]);
            if (saleItem != nullptr && (saleItem->getCategory() == "Одежда" || saleItem->getCategory() == "Clothes" || saleItem->getCategory() == "clothes")) {
                saleItem->displayInfo(); // О товаре
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
// Отоброжение полного списка 
void Store::listItems() {
    if (count > 0) {
        cout << "Список товаров:\n";
        printTableHeader();
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". ";  // Добавляем номер товара
            items[i]->displayInfo();
        }
    } else {
        cout << "Список товаров пуст.\n";
    }
}
// Заголовок
void Store::printTableHeader() {
    cout << string(95, '-') << endl;
    cout << "| " << setw(15) << "Название" << " | "
         << setw(15) << "Магазин" << " | "
         << setw(15) << "Адрес" << " | "
         << setw(10) << "Категория" << " | "
         << setw(15) << "Цена" << " | "
         << setw(18) << "Цена со скидкой" << " |" << endl;
    cout << string(95, '-') << endl;
}
// + Товар
void Store::addItem() {
    if (count >= MAX_ITEMS) {
        cout << "Достигнуто максимальное количество товаров.\n";
        return;
    }
    // Данные о товаре
    string storeName, address, productName, category, additionalInfo;
    double price, discount;
    char isDiscounted;

    cout << "Введите название магазина: ";
    cin.ignore();
    getline(cin, storeName);
    cout << "Введите адрес магазина: ";
    getline(cin, address);
    cout << "Введите название товара: ";
    getline(cin, productName);
    cout << "Введите категорию товара: ";
    getline(cin, category);
    cout << "Введите цену: ";
    cin >> price;
    cout << "Введите процент скидки: ";
    cin >> discount;
    // Доп инфа -> добавление объекта если y
    cout << "Товар имеет дополнительную информацию? (y/n): ";
    cin >> isDiscounted;
    
    if (isDiscounted == 'y' || isDiscounted == 'Y') {
        cout << "Введите дополнительную информацию: ";
        cin.ignore();
        getline(cin, additionalInfo);
        items[count] = new DiscountedSaleItem(storeName, address, discount, 
                                            productName, category, price, additionalInfo);
    } else {
        items[count] = new SaleItem(storeName, address, discount, 
                                  productName, category, price);
    }
    count++;
    cout << "Товар успешно добавлен.\n";
}
// удаление товара
void Store::deleteItem() {
    if (count == 0) {
        cout << "Список товаров пуст.\n";
        return;
    }

    cout << "Текущие товары:\n";
    listItems();

    int index;
    cout << "Введите номер товара для удаления (1-" << count << "): ";
    cin >> index;

    if (index < 1 || index > count) {
        cout << "Некорректный номер товара.\n";
        return;
    }

    delete items[index - 1];
    for (int i = index - 1; i < count - 1; i++) {
        items[i] = items[i + 1]; // Сдвиг массива
    }
    count--;
    cout << "Товар успешно удален.\n";
}
// Для друга
void Store::applyDiscount(SaleItem& item, double discount) {
    item.setDiscount(discount);  // Устанавливаем новый процент скидки
}
// Доп операции(4)
void Store::performOperations() {
    if (count < 2) {
        cout << "Недостаточно товаров для выполнения операций.\n";
        return;
    }

    listItems(); // Показываем список товаров
    cout << "\nВыберите операцию:\n";
    cout << "1. Сложить цену двух товаров\n";
    cout << "2. Вычесть цену двух товаров\n";
    cout << "3. Инкремент скидки на товар\n";
    cout << "4. Декремент скидки на товар\n";
    cout << "5. Сравнить цены товаров\n";
    cout << "Введите выбор: ";
    
    int choice;
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

// Сложить цену
void Store::addPrice() {
    if (count < 2) {
        cout << "Недостаточно товаров для выполнения операции.\n";
        return;
    }

    int index1, index2;
    cout << "Введите Номера двух товаров для сложения: ";
    cin >> index1 >> index2;
    index1--; index2--;  // Корректируем Номера

    if (index1 >= 0 && index1 < count && index2 >= 0 && index2 < count) {
        SaleItem* item1 = dynamic_cast<SaleItem*>(items[index1]);
        SaleItem* item2 = dynamic_cast<SaleItem*>(items[index2]);

        if (item1 && item2) {
            cout << "Товар 1:\n";
            item1->displayInfo();
            cout << "Товар 2:\n";
            item2->displayInfo();

            double totalDiscountedPrice = item1->getDiscountedPrice() + item2->getDiscountedPrice();
            double totalOriginalPrice = item1->getOriginalPrice() + item2->getOriginalPrice();

            cout << "Результат сложения цен:\n";
            cout << "Со скидкой: " << totalDiscountedPrice << "\n";
            cout << "Без скидки: " << totalOriginalPrice << "\n";
        }
    } else {
        cout << "Некорректные Номера.\n";
    }
}
// - цена
void Store::subtractPrice() {
    if (count < 2) {
        cout << "Недостаточно товаров для выполнения операции.\n";
        return;
    }

    int index1, index2;
    cout << "Введите Номера двух товаров для вычитания: ";
    cin >> index1 >> index2;
    index1--; index2--;  // Корректируем Номера

    if (index1 >= 0 && index1 < count && index2 >= 0 && index2 < count) {
        SaleItem* item1 = dynamic_cast<SaleItem*>(items[index1]);
        SaleItem* item2 = dynamic_cast<SaleItem*>(items[index2]);

        if (item1 && item2) {
            cout << "Товар 1:\n";
            item1->displayInfo();
            cout << "Товар 2:\n";
            item2->displayInfo();

            double totalDiscountedPrice = item1->getDiscountedPrice() - item2->getDiscountedPrice();
            double totalOriginalPrice = item1->getOriginalPrice() - item2->getOriginalPrice();

            cout << "Результат вычитания цен:\n";
            cout << "Со скидкой: " << totalDiscountedPrice << "\n";
            cout << "Без скидки: " << totalOriginalPrice << "\n";
        }
    } else {
        cout << "Некорректные Номера.\n";
    }
}
// Инкремент реализован через друга applyDiscount
void Store::incrementDiscount() {
    int index;
    cout << "Введите Номер товара для инкремента скидки: ";
    cin >> index;
    index--;  // Корректируем номер

    if (index >= 0 && index < count) {
        SaleItem* item = dynamic_cast<SaleItem*>(items[index]);
        if (item) {
            cout << "До инкремента скидки:\n";
            item->displayInfo();
            applyDiscount(*item, item->getDiscount() + 1);  // Увеличиваем скидку
            cout << "После инкремента скидки:\n";
            item->displayInfo();
        }
    } else {
        cout << "Некорректный Номер.\n";
    }
}
// Декремент реализован через друга applyDiscount
void Store::decrementDiscount() {
    int index;
    cout << "Введите Номер товара для декремента скидки: ";
    cin >> index;
    index--;  // Корректируем номер

    if (index >= 0 && index < count) {
        SaleItem* item = dynamic_cast<SaleItem*>(items[index]);
        if (item) {
            cout << "До декремента скидки:\n";
            item->displayInfo();
            applyDiscount(*item, item->getDiscount() - 1);  // Уменьшаем скидку
            cout << "После декремента скидки:\n";
            item->displayInfo();
        }
    } else {
        cout << "Некорректный Номер.\n";
    }
}

// Сравнение <
void Store::comparePrices() {
    if (count < 2) {
        cout << "Недостаточно товаров для выполнения операции.\n";
        return;
    }

    int index1, index2;
    cout << "Введите Номера товаров для сравнения: ";
    cin >> index1 >> index2;
    index1--; index2--;  // Корректируем Номера

    if (index1 >= 0 && index1 < count && index2 >= 0 && index2 < count) {
        SaleItem* item1 = dynamic_cast<SaleItem*>(items[index1]);
        SaleItem* item2 = dynamic_cast<SaleItem*>(items[index2]);

        if (item1 && item2) {
            cout << "Товар 1:\n";
            item1->displayInfo();
            cout << "Товар 2:\n";
            item2->displayInfo();

            if (*item1 < *item2) {
                cout << "Первый товар дешевле второго.\n";
            } else {
                cout << "Первый товар дороже или равен по цене второму.\n";
            }
        }
    } else {
        cout << "Некорректные Номера.\n";
    }
}
