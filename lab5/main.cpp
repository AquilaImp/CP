#include "Store.h"
#include <windows.h>

int main() {
    // Русифик
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Store store;
    store.displayMenu();
    
    return 0;
}
