#include <iostream>
#include <iomanip> 
#include <string>
#include <locale>

using namespace std;

// Структура для хранения информации о товаре в магазине
struct SaleItem 
{
    string storeName;      // Название магазина
    string address;        // Адрес магазина
    double discount;       // Процент скидки
    string productName;    // Наименование товара
    string category;       // Категория товара (например, "Одежда")
    double originalPrice;  // Оригинальная цена товара
    double discountedPrice; // Цена после скидки
};

SaleItem saleItems[100]; // Массив для хранения
int count = 0;           // Счётчик товаров

// Функция для вывода заголовка таблицы
void printTableHeader() 
{
    cout << left << setw(5) << "№"
         << setw(25) << "Магазин"
         << setw(25) << "Адрес"
         << setw(40) << "Наименование товара"
         << setw(40) << "Категория"
         << setw(40) << "Оригинальная цена"
         << setw(40) << "Цена со скидкой" << endl;
    cout << string(140, '-') << endl;
}

// Функция для вывода строки таблицы с информацией о товаре
void printTableRow(int index, const SaleItem& item) 
{
    cout << left << setw(5) << index + 1
         << setw(20) << item.storeName
         << setw(15) << item.address
         << setw(15) << item.productName
         << setw(45) << item.category
         << setw(30) << fixed << setprecision(2) << item.originalPrice
         << setw(30) << fixed << setprecision(2) << item.discountedPrice << endl;
}

int main() 
{
    //Устанавливаем кодировку на русский
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int choice;

    do 
    {
        // Вывод меню
        cout << "\n1. Список товаров на распродаже\n";
        cout << "2. Добавить товар на распродажу\n";
        cout << "3. Удалить товар\n";
        cout << "4. Товары в категории 'Одежда'\n";
        cout << "0. Выход\n";
        cout << "Введите выбор: ";
        cin >> choice; 

        if (choice == 1) 
        {
            if (count > 0) // Проверка, есть ли хотя бы один товар
            {
                cout << "Список товаров на распродаже:\n";
                printTableHeader(); // Вывод заголовка таблицы
                for (int i = 0; i < count; i++) 
                {
                    printTableRow(i, saleItems[i]); // Вывод данных о товаре в виде строки таблицы
                }
            } 
            else 
            {
                cout << "Список товаров пуст.\n"; 
            }
        }
        else if (choice == 2)
        {
            if (count < 100) // проверка лимита массива 
            {
                // Ввод данных о товаре
                cout << "Введите название магазина: ";
                cin.ignore(); // Очистка буфера ввода
                getline(cin, saleItems[count].storeName);
                cout << "Введите адрес магазина: ";
                getline(cin, saleItems[count].address);
                cout << "Введите наименование товара: ";
                getline(cin, saleItems[count].productName);
                cout << "Введите категорию товара: ";
                getline(cin, saleItems[count].category);
                cout << "Введите оригинальную цену товара: ";
                cin >> saleItems[count].originalPrice;
                cout << "Введите процент скидки: ";
                cin >> saleItems[count].discount;

                // Вычисление цены после скидки
                saleItems[count].discountedPrice = saleItems[count].originalPrice * (1 - saleItems[count].discount / 100);

                count++; 
            } 
            else 
            {
                cout << "Невозможно добавить больше товаров.\n"; 
            }
        }
        else if (choice == 3) 
        {
            int index;
            cout << "Введите номер товара для удаления: ";
            cin >> index;
            index--; // Уменьшение индекса на 1, так как массив начинается с 0

            if (index >= 0 && index < count) 
            {
                // Сдвиг элементов массива влево для удаления элемента
                for (int i = index; i < count - 1; i++) 
                {
                    saleItems[i] = saleItems[i + 1];
                }
                count--; 
            } 
            else 
            {
                cout << "Неверный номер.\n"; 
            }
        }
        else if (choice == 4) 
        {
            cout << "Товары в категории 'Одежда':\n";
            bool found = false; // Флаг для отслеживания наличия товаров в категории 'Одежда'
            printTableHeader(); // Вывод заголовка таблицы
            for (int i = 0; i < count; i++) 
            {
                if (saleItems[i].category == "Одежда") 
                {
                    printTableRow(i, saleItems[i]); // Вывод данных о найденном товаре
                    found = true;
                }
            }
            if (!found) 
            {
                cout << "Нет товаров в категории 'Одежда'.\n"; 
            }
        }
    } while (choice != 0); // Выход при выборе 0

    return 0;
}
