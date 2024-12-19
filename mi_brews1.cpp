#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Items and Toppings
#define MAX_ITEMS 15
#define MAX_TOPPINGS 4
#define MAX_ORDERS 50

typedef struct {
    char name[30];
    int price;
} Item;

Item items[MAX_ITEMS] = {
	// Berkafein
    {"Midnight Espresso", 15000}, 
	{"Caramel Cloud Macchiato", 20000}, 
	{"Hazelnut Latte", 18000},
    {"Mocha Java", 17000}, 
	{"Nitro Cold Brew", 22000}, 
	
	// Non-kafein
	{"Tropical Twist Tea", 15000},
    {"Berry Bliss Smoothie", 20000}, 
	{"Matcha Magic", 22000}, 
	{"Ginger Elixir", 18000},
	
	// Minuman Spesial
    {"Coconut Dream", 15000}, 
	{"Unicorn Latte", 25000}, 
	{"Galaxy Smoothie", 25000},
    {"Cloud 9", 18000}, 
	{"Ocean Breeze", 20000}
};

int counter = 0;
int quantities[MAX_ITEMS] = {0};    
int itemTotals[MAX_ITEMS] = {0};   
int orderIndices[MAX_ORDERS] = {0}; 

typedef struct {
    char name[30];
    int price;
} addOn;

addOn toppings[MAX_TOPPINGS] = {
    {"Grass Jelly", 5000}, {"Pearl", 5000}, {"Pudding", 5000}, {"Coconut Jelly", 5000}
};

// Display Menu
void displayMenu(Item items[], int nItems, addOn toppings[], int nToppings) {
    printf("=================== Menu Minuman ==================\n");
    printf("\n\t--------- Berkafein ---------\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %-30s \tRp %d\n", i + 1, items[i].name, items[i].price);
    }

    printf("\n\t--------- Non-Kafein ---------\n");
    for (int i = 5; i < 10; i++) {
        printf("%d. %-30s \tRp %d\n", i + 1, items[i].name, items[i].price);
    }

    printf("\n\t------- Minuman Spesial -------\n");
    for (int i = 10; i < nItems; i++) {
        printf("%d. %-30s \tRp %d\n", i + 1, items[i].name, items[i].price);
    }

    printf("\n================== Menu Toppings ==================\n\n");
    for (int i = 0; i < nToppings; i++) {
        printf("%d. %-30s \tRp %d\n", i + 1, toppings[i].name, toppings[i].price);
    }
    printf("\n");
}

// Add Toppings
int addTopping(addOn toppings[], int nToppings) {
    int toppingChoice, toppingTotal = 0;
    char addTop;
    do {
        puts("");
        printf("Apakah Anda ingin menambahkan topping? (y/n): ");
        scanf("%c", &addTop); getchar();

        if (addTop == 'y') {
            do {
                puts("Silakan pilih nomor topping (1-4): ");
                printf(">> ");
                scanf("%d", &toppingChoice); getchar();

                if (toppingChoice < 1 || toppingChoice > nToppings) {
                    printf("Pilihan topping tidak valid. Coba lagi.\n");
                    continue;
                }

                toppingTotal += toppings[toppingChoice - 1].price;
                printf("Topping %s berhasil ditambahkan dengan harga Rp %d.\n",
                       toppings[toppingChoice - 1].name, toppings[toppingChoice - 1].price);
                break;
            } while (1);
        } else if (addTop != 'n') {
            printf("Pilihan ini tidak valid, silakan coba lagi.\n");
        }
    } while (addTop != 'n');

    return toppingTotal;
}

// Order Items
void orderItem(int *total) {
    int choice, quantity;
    do {
        puts("");
        puts("Silakan pilih nomor minuman yang diinginkan ^^");
        printf(">> ");
        scanf("%d", &choice); getchar();

        if (choice < 1 || choice > 14) {
            puts("\n!! Pilihan ini tidak valid. Silakan coba lagi. !!");
            continue;
        }
    } while (choice < 1 || choice > 14);

    do {
        puts("");
        printf("Berapa jumlah minuman %s?\n", items[choice - 1].name);
        printf(">> ");
        scanf("%d", &quantity); getchar();

        if (quantity < 1) {
            puts("\n!! Minimal minuman yang dibeli adalah 1. Silakan coba lagi. !!");
            continue;
        }
    } while (quantity < 1);

    int itemTotal = items[choice - 1].price * quantity;
    int toppingTotal = addTopping(toppings, MAX_TOPPINGS);

    itemTotal += toppingTotal;
    *total += itemTotal;

    quantities[choice - 1] += quantity; 
    itemTotals[choice - 1] += itemTotal;
    orderIndices[counter++] = choice - 1;

    printf("Pesanan %s dengan total Rp %d berhasil ditambahkan.\n\n", items[choice - 1].name, itemTotal);
}

// Preview Bill
void previewBill() {
    puts("\t\t============================ Preview Bill ============================");
    for (int i = 0; i < counter; i++) {
        int index = orderIndices[i];
        printf("Order#%d : %-30s\t | Qty: %d\t | Price: Rp %d\t | Total: Rp %d\n",
               i + 1, items[index].name, quantities[index], items[index].price, itemTotals[index]);
    }
}

// Update Order
void updateOrder(int *total) {
    system("cls");
    previewBill();
    
    int num;
    puts("");
    puts("Pilihlah nomor order untuk memperbaharui item");
    printf(">> ");
    scanf("%d", &num); getchar();

    if (num < 1 || num > counter) {
        puts("\n!! Pilihan tidak valid. Silakan coba lagi. !!");
        return;
    }

    int currentIndex = orderIndices[num - 1];
    *total -= itemTotals[currentIndex];

    int quantity;
    do {
        puts("");
        printf("Berapa jumlah minuman %s?\n", items[currentIndex].name);
        printf(">> ");
        scanf("%d", &quantity); getchar();

        if (quantity < 1) {
            puts("\n!! Minimal minuman yang dibeli adalah 1. Silakan coba lagi. !!");
            continue;
        }
    } while (quantity < 1);

    int itemTotal = items[currentIndex].price * quantity;
    int toppingTotal = addTopping(toppings, MAX_TOPPINGS);

    itemTotal += toppingTotal;
    *total += itemTotal;

    quantities[currentIndex] = quantity;
    itemTotals[currentIndex] = itemTotal;

    printf("Pesanan %s berhasil diperbarui dengan total Rp %d.\n\n", items[currentIndex].name, itemTotal);
    
    system("cls");
    previewBill();
}

// Delete Order
void deleteOrder(int *total) {
    system("cls");
    puts("\t\t============================ Order List ============================");
    for (int i = 0; i < counter; i++) {
        int index = orderIndices[i];
        printf("Order#%d : %-30s\t | Qty: %d\t | Price: Rp %d\t | Total: Rp %d\n",
               i + 1, items[index].name, quantities[index], items[index].price, itemTotals[index]);
    }
	int num;
	do{
	    puts("");
	    puts("Pilihlan nomor order untuk menghapus item");
	    printf(">> ");
	    scanf("%d", &num); getchar();
	
	    if (num < 1 || num > counter) {
	        printf("Pilihan ini invalid. Tidak ada perubahan.\n");
	        return;
	    }
	} while (num < 1 || num > counter);
    

    int deleteIndex = orderIndices[num - 1];
    *total -= itemTotals[deleteIndex];
    quantities[deleteIndex] = 0;
    itemTotals[deleteIndex] = 0;

    for (int i = num - 1; i < counter - 1; i++) {
        orderIndices[i] = orderIndices[i + 1];
    }
    counter--;

    system("cls");
    previewBill();
}

// Finalize Bill
void bill(int total) {
    system("cls");
    previewBill();
    
    typedef struct {
    	char name[30];
	} payment;
    payment method[3] = {{"QRIS"}, {"Debit Card"}, {"Cash"}};
    
    int pay;
    do{
    	puts("");
    	puts("============ Payment Method ============");
    	puts("1. QRIS");
    	puts("2. Debit Card");
    	puts("3. Cash");
    	printf(">> ");
    	scanf("%d", &pay); getchar();
	} while (pay < 1 || pay > 3);
	
	float disc;
	switch (pay){
		case 1:
			disc = 0.1;
			break;
		case 2:
			disc = 0.25;
			break;
		default: 
			break;
	}
    
    system("cls");
    puts("\t\t============================ Rincian Pesanan ============================");
    for (int i = 0; i < counter; i++) {
        int index = orderIndices[i];
        printf("Order#%d : %-30s\t | Qty: %d\t | Price: Rp %d\t | Total: Rp %d\n",
               i + 1, items[index].name, quantities[index], items[index].price, itemTotals[index]);
    }
    puts("");
    puts("==========================================================================================================");
    
    int discount = disc * total;
    
    printf("%-18s : \tRp %d\n", "Subtotal", total);
    printf("%-18s : \t%s\n\n", "Payment method", method[pay-1].name);
    printf("%-18s : \tRp %d\n", "Discount", discount);
    printf("%-18s : \tRp %d\n", "Total biaya", (total-discount));
    
}

int main() {
    int nItems = 14, nToppings = 4, total = 0;
    char addMore;

    // Welcoming
    
	puts(" __       __  __        _______ ");                                             
	puts("|  \\     /  \\|  \\      |       \\");                                           
	puts("| $$\\   /  $$ \\$$      | $$$$$$$\\  ______    ______   __   __   __   _______"); 
	puts("| $$$\\ /  $$$|  \\      | $$__/ $$ /      \\  /      \\ |  \\ |  \\ |  \\ /       \\");
	puts("| $$$$\\  $$$$| $$      | $$    $$|  $$$$$$\\|  $$$$$$\\| $$ | $$ | $$|  $$$$$$$");
	puts("| $$\\$$ $$ $$| $$      | $$$$$$$\\| $$   \\$$| $$    $$| $$ | $$ | $$ \\$$    \\");
	puts("| $$ \\$$$| $$| $$      | $$__/ $$| $$      | $$$$$$$$| $$_/ $$_/ $$ _\\$$$$$$\\");
	puts("| $$  \\$ | $$| $$      | $$    $$| $$       \\$$     \\ \\$$   $$   $$|       $$");
	puts(" \\$$      \\$$ \\$$       \\$$$$$$$  \\$$        \\$$$$$$$  \\$$$$$\\$$$$  \\$$$$$$$");
	
	printf("\n");
	                                                                                                               
	puts(",--.                ,----.                              ,--.   ,--.,--.                              ,---.     ,--.   ");
	puts("|  |-.,--. ,--.    '  .-./    ,--,--.,--,--,  ,---.     |   `.'   |`--',--.  ,--.,--.,--. ,---.     '.-.  \\   /    \\  ");
	puts("| .-. '\\  '  /     |  | .---.' ,-.  ||      \\| .-. |    |  |'.'|  |,--. \\  `'  / |  ||  || .-. :     .-' .'  |  ()  | ");
	puts("| `-' | \\   '      '  '--'  |\\ '-'  ||  ||  |' '-' '    |  |   |  ||  | /  /.  \\ '  ''  '\\   --.    /   '-.--.\\    /  ");
	puts(" `---'.-'  /        `------'  `--`--'`--''--'.`-  /     `--'   `--'`--''--'  '--' `----'  `----'    '-----'--' `--'   ");
	puts("      `---'                                  `---'                                                                    ");


	printf("\n");
    displayMenu(items, nItems, toppings, nToppings);
	
	// Order Items
    do {
        orderItem(&total);
        printf("Apakah ingin memesan lagi? (y/n): ");
        scanf("%c", &addMore); getchar();
    } while (addMore == 'y');

    system("cls");
    previewBill();

    int option;
    while (true) {
    	puts("");
        puts("============ Navigation ============");
        puts("1. Add Item(s)");
        puts("2. Update Item(s)");
        puts("3. Delete Item(s)");
        puts("4. Finalize Bill");
        printf(">> ");
        scanf("%d", &option); getchar();

        switch (option) {
            case 1:
            	system("cls");
            	puts("Adding order........");
				displayMenu(items, nItems, toppings, nToppings);
                orderItem(&total);
                puts("");
                
                system("cls");
                previewBill();
                continue;
            case 2:
            	puts("Updating order........");
                updateOrder(&total);
                continue;
            case 3:
            	puts("Deleting order........");
                deleteOrder(&total);
                continue;
            case 4:
                bill(total);
                break;
            default:
                break;
        }
        break;
    }

    puts("\nTerima kasih telah memesan di Mi Brews!");
    return 0;
}
