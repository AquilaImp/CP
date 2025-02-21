#include <iostream>
#include "Store.h"
#include "SaleItem.h"
#include "DiscountedItem.h"
#include "PremiumItem.h"

using namespace std;

int main() {
    Store store;

    SaleItem* item1 = new SaleItem("Shop1", "Address1", 10, "Product1", "Category1", 100);
    DiscountedItem* item2 = new DiscountedItem("Shop2", "Address2", 20, "Product2", "Category2", 200, 5);
    PremiumItem* item3 = new PremiumItem("Shop3", "Address3", 15, "Product3", "Category3", 300, 10, "Free shipping");

    store.addItem(item1);
    store.addItem(item2);
    store.addItem(item3);

    store.listItems();

    store.updateDiscount(*item1, 25);

    cout << "\nUpdated Item Details:\n";
    store.listItems();

    delete item1;
    delete item2;
    delete item3;

    return 0;
}
