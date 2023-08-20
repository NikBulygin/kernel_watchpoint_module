#include <stdio.h>
    
    int* getAddressOfVariable() {
        static int myVariable = 10; // используем static, чтобы переменная не разрушалась после завершения функции
        return &myVariable;
    }
    
    int main() {
        int* address = getAddressOfVariable();
        printf("Адрес переменной: %p\n", address);
        printf("Значение по этому адресу: %d\n", *address);
        return 0;
    }
