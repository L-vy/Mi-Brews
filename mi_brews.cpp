#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 15
#define MAX_TOPPINGS 4
#define MAX_ORDERS 50

#define HISTORY_FILE "order_history.txt"
#define GAME_FILE "game_data.txt"

// Struktur data untuk menu utama minuman
typedef struct {
    char name[30];
    int price;
} Item;

// Daftar menu minuman
Item items[MAX_ITEMS] = {
    // Minuman Berkafein
    {"Midnight Espresso", 15000}, 
    {"Caramel Cloud Macchiato", 20000}, 
    {"Hazelnut Latte", 18000},
    {"Mocha Java", 17000}, 
    {"Nitro Cold Brew", 22000}, 

    // Minuman non-kafein
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

// Struktur data untuk topping
typedef struct {
    char name[30];
    int price;
} addOn;

// Daftar menu topping
addOn toppings[MAX_TOPPINGS] = {
    {"Grass Jelly", 3500}, 
    {"Pearl", 4500}, 
    {"Pudding", 5000}, 
    {"Coconut Jelly", 5000}
};

// Variabel global untuk menyimpan data pesanan
int total = 0;                            // Harga total pesanan
int counter = 0;                          // Jumlah pesanan
float disc = 0;                           // Jumlah diskon yang didapatkan
int loyaltyPoints = 0;                    // Banyak loyalty points

int quantities[MAX_ITEMS] = {0};          // Kuantitas setiap minuman   
int itemTotals[MAX_ITEMS] = {0};          // Total harga untuk setiap minuman
int orderIndices[MAX_ORDERS] = {0};       // Indeks item dalam daftar pesanan


// Deklarasi Fungsi
void welcome();
void displayMenu(Item items[], addOn toppings[]);
int addTopping(addOn toppings[]);

void orderItem();
void updateOrder();
void deleteOrder();

void previewBill();
float dateDiscount();
void bill();

void processOrder();
void viewTransactionHistory();
void saveOrderHistory();

void introduction();
void rules();
void gameForUser();
void freeDrink();


int main() {
    welcome();            // Menampilkan halaman awal
    while (true) {        // Menampilkan halaman menu
        int menu;
        
        puts("");
        puts("============ Menu ============");
        puts("1. Start Ordering");
        puts("2. View History");
        puts("3. Redeem Free Drink");
        puts("   *if eligible");
        puts("4. Exit");
        printf(">> ");
        scanf("%d", &menu); getchar();
        
        switch(menu) {
            case 1:
                processOrder();
                saveOrderHistory();
                continue;
            case 2:
                viewTransactionHistory();
                continue;
            case 3:
            	gameForUser();
                continue;
            case 4:
                break;
            default: 
                puts("Pilihan ini tidak valid, silakan coba lagi.");
                break;
        }
        break;
    }

    puts("\nTerima kasih telah memesan di Mi Brews!");
    return 0;
}

// Menampilkan halaman awal
void welcome(){
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


	printf("\nEnter any key to start ordering...");
	getchar();
	system("cls");
}

// Menampilkan menu minuman dan topping
void displayMenu(Item items[], addOn toppings[]) {
    printf("\n=================== Menu Minuman ==================\n");
    printf("\n\t--------- Berkafein ---------\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %-30s \tRp %d\n", i + 1, items[i].name, items[i].price);
    }

    printf("\n\t--------- Non-Kafein ---------\n");
    for (int i = 5; i < 10; i++) {
        printf("%d. %-30s \tRp %d\n", i + 1, items[i].name, items[i].price);
    }

    printf("\n\t------- Minuman Spesial -------\n");
    for (int i = 10; i < 14; i++) {
        printf("%d. %-30s \tRp %d\n", i + 1, items[i].name, items[i].price);
    }

    printf("\n================== Menu Toppings ==================\n\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %-30s \tRp %d\n", i + 1, toppings[i].name, toppings[i].price);
    }
    printf("\n");
}

// Menambahkan topping ke pesanan
int addTopping(addOn toppings[]) {
    int toppingChoice, toppingTotal = 0;
    char addTop;
    do {
        printf("\nApakah Anda ingin menambahkan topping? (y/n): ");
        scanf("%c", &addTop); getchar();

        if (addTop == 'y') {
            do {
                puts("Silakan pilih nomor topping (1-4): ");
                printf(">> ");
                scanf("%d", &toppingChoice); getchar();

                if (toppingChoice < 1 || toppingChoice > 4) {
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

// Membuat pesanan baru
void orderItem() {
	displayMenu(items, toppings);
	char addMore;
	do{
		int choice, quantity;
	    do {
	        puts("\nSilakan pilih nomor minuman yang diinginkan^^");
	        printf(">> ");
	        scanf("%d", &choice); getchar();
	
	        if (choice < 1 || choice > 14) {
	            puts("\n!! Pilihan ini tidak valid. Silakan coba lagi. !!");
	            continue;
	        }
	    } while (choice < 1 || choice > 14);
	
	    do {
	        printf("\nBerapa jumlah minuman %s?\n", items[choice - 1].name);
	        printf(">> ");
	        scanf("%d", &quantity); getchar();
	
	        if (quantity < 1) {
	            puts("\n!! Minimal minuman yang dibeli adalah 1. Silakan coba lagi. !!");
	            continue;
	        }
	    } while (quantity < 1);
	
	    int itemTotal = items[choice - 1].price * quantity;
	    int toppingTotal = addTopping(toppings);
	
	    itemTotal += toppingTotal;
	    total += itemTotal;
	
	    quantities[choice - 1] += quantity; 
	    itemTotals[choice - 1] += itemTotal;
	    orderIndices[counter++] = choice - 1;
	    
	    // Melihat jika minuman yang di pesan merupakan minuman spesial (yang ada di index 10-14)
	    // Mendapatkan 1 poin untuk setiap minuman spesial yang dipesan. 
	    if (choice >= 10) {
	        loyaltyPoints += quantity; 
	        printf("Anda telah mendapatkan %d poin loyalitas!\n", quantity);
	    }
	
	    printf("Pesanan %s dengan total Rp %d berhasil ditambahkan.\n\n", items[choice - 1].name, itemTotal);	
	    
	    printf("Apakah ingin memesan lagi? (y/n): ");
		scanf("%c", &addMore); getchar();
	} while (addMore == 'y');
	
    system("cls");
	previewBill();
}

// Memperbarui jumlah minuman untuk pesanan yang sudah ada 
void updateOrder() {
    system("cls");
    previewBill();
    
    int num;
    puts("\nPilihlah nomor order untuk memperbaharui item");
    printf(">> ");
    scanf("%d", &num); getchar();

    if (num < 1 || num > counter) {
        puts("\n!! Pilihan tidak valid. Silakan coba lagi. !!");
        return;
    }

    int currentIndex = orderIndices[num - 1];
    total -= itemTotals[currentIndex];

    int quantity;
    do {
        printf("\nBerapa jumlah minuman %s?\n", items[currentIndex].name);
        printf(">> ");
        scanf("%d", &quantity); getchar();

        if (quantity < 1) {
            puts("\n!! Minimal minuman yang dibeli adalah 1. Silakan coba lagi. !!");
            continue;
        }
    } while (quantity < 1);

    int itemTotal = items[currentIndex].price * quantity;
    int toppingTotal = addTopping(toppings);

    itemTotal += toppingTotal;
    total += itemTotal;

    quantities[currentIndex] = quantity;
    itemTotals[currentIndex] = itemTotal;

    printf("Pesanan %s berhasil diperbarui dengan total Rp %d.\n\n", items[currentIndex].name, itemTotal);
    
    system("cls");
    previewBill();
}

// Menghapus salah satu pesanan
void deleteOrder() {
    system("cls");
    puts("\n\t\t============================ Order List ============================");
    for (int i = 0; i < counter; i++) {
        int index = orderIndices[i];
        printf("Order#%d : %-30s\t | Qty: %d\t | Price: Rp %d\t | Total: Rp %d\n",
               i + 1, items[index].name, quantities[index], items[index].price, itemTotals[index]);
    }
    
	int num;
	do{
	    puts("\nPilihlan nomor order untuk menghapus item");
	    printf(">> ");
	    scanf("%d", &num); getchar();
	
	    if (num < 1 || num > counter) {
	        printf("Pilihan ini invalid. Tidak ada perubahan.\n");
	        return;
	    }
	} while (num < 1 || num > counter);
    
    int deleteIndex = orderIndices[num - 1];
    total -= itemTotals[deleteIndex];
    quantities[deleteIndex] = 0;
    itemTotals[deleteIndex] = 0;

    for (int i = num - 1; i < counter - 1; i++) {
        orderIndices[i] = orderIndices[i + 1];
    }
    counter--;

    system("cls");
    previewBill();
}

// Menampilkan bill sebelum ditetapkan
void previewBill() {
    puts("\n\t\t============================ Preview Bill ============================");
    for (int i = 0; i < counter; i++) {
        int index = orderIndices[i];
        printf("Order#%d : %-30s\t | Qty: %d\t | Price: Rp %d\t | Total: Rp %d\n",
               i + 1, items[index].name, quantities[index], items[index].price, itemTotals[index]);
    }
}

// Mendapatkan diskon ketika tanggal hari dan bulan sama
// contoh : 11 November atau 12 Desember
float dateDiscount() {
    time_t t;
    time(&t);
    struct tm *timeInfo = localtime(&t);

    int year = timeInfo->tm_year + 1900; 
    int month = timeInfo->tm_mon + 1;   
    int day = timeInfo->tm_mday;       

    // Jika hari dan bulan memiliki tanggal yang sama, 
    // Pelanggan mendapat diskon sebesar 22%
    if (month == day) {
        puts("\nAnda mendapatkan diskon 22%!");
        return disc += 0.22; 
    } 

    return disc; 
}

// Menampilkan bill akhir dan melakukan pembayaran
void bill() {
    system("cls");
    previewBill();
    
    typedef struct {
    	char name[30];
	} payment;
	
    payment method[3] = {{"QRIS"}, {"Debit Card"}, {"Cash"}};
    
    int pay;
    do{
    	puts("\n============ Payment Method ============");
    	puts("1. QRIS");
    	puts("2. Debit Card");
    	puts("3. Cash");
    	printf(">> ");
    	scanf("%d", &pay); getchar();
	} while (pay < 1 || pay > 3);
	
	// Mendapatkan diskon untuk pembayaran tertentu
	switch (pay){
		case 1:
			disc = 0.1;
			puts("\nAnda mendapatkan diskon 10%% !");
			break;
		case 2:
			disc = 0.25;
			puts("\nAnda mendapatkan diskon 25%% !");
			break;
		default: 
			break;
	}
    
    disc = dateDiscount();
    
	getchar();
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

// Untuk memesan minuman 
void processOrder(){
	system("cls");
	orderItem();

	while (true){
		int option;
		// Navigasi jika ingin memperbahrui pesanan atau langsung pembayaran
	    puts("\n============ Navigation ============");
		puts("1. Add Item(s)");
	    puts("2. Update Item(s)");
	    puts("3. Delete Item(s)");
		puts("4. Finalize Bill");
		printf(">> ");
		scanf("%d", &option); getchar();
				
		switch (option) {
			case 1:
				system("cls");
				puts("Adding items . . .");
				orderItem();
				continue;
			case 2:
			    updateOrder();
			    continue;
			case 3:
			    deleteOrder();
				continue;
			case 4:
			    bill();
			    
			    printf("\nApakah Anda ingin memesan lagi? (y/n): ");
			    char again;
				scanf(" %c", &again); getchar();
					                
			    if (again == 'y' || again == 'Y') {
				    system("cls");
				    continue;
				} else break;
			default:
				puts("Pilihan ini tidak valid, silakan coba lagi.");
			break;
		}
	    break;
    }
    
    system("cls");
}

// Untuk menyimpan order history dalam "order_history.txt"
void saveOrderHistory() {
    FILE *file = fopen(HISTORY_FILE, "a");
    if (file != NULL) {
        fprintf(file, "======================== Order History ========================\n");
        for (int i = 0; i < counter; i++) {
            int index = orderIndices[i];
            int pointsEarned = (index >= 10) ? quantities[index] : 0;
            fprintf(file, "Order ID: %d\n", i + 1);
            fprintf(file, "\tItem: %s | ", items[index].name);
            fprintf(file, " Quantity: %d |", quantities[index]);
            fprintf(file, " Price: Rp %d\n", items[index].price);
            
            fprintf(file, "\tTotal Price: Rp %d\n", itemTotals[index]);
            fprintf(file, "\tLoyalty Points Earned: %d\n", pointsEarned);
            fprintf(file, "--------------------------------------------------------------\n");
        }
        fprintf(file, "===============================================================\n");
        fclose(file);
    }
}

// Untuk melihat order history di console
void viewTransactionHistory() {
	system("cls");
    FILE *file = fopen(HISTORY_FILE, "r");
    if (file == NULL) {
        puts("Tidak ada riwayat transaksi ditemukan.");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
    
    getchar();
    system("cls");
}

void introduction(){
	puts("Lucky Roll Showdown !!\n");
	puts("Dalam permainan ini, Anda akan melempar tiga dadu.");
	puts("  (i) Jika ketiga dadu menunjukkan angka yang sama, Anda akan mendapatkan diskon 100%.");
	puts(" (ii) Jika dua dadu menunjukkan angka yang sama, Anda akan mendapatkan diskon 50%.");
	puts("(iii) Namun, jika tidak ada dadu yang sama, Anda tidak mendapatkan diskon.");
	puts("");
	printf("Apakah Anda ingin bermain? (y/n): ");
}

void rules(){
	system("cls");
	puts("Pada awal permainan, tiga dadu akan dilempar secara acak dengan nilai antara 1 hingga 6.\n");
	
	puts("Anda memiliki kesempatan untuk melakukan maksimal 3 kali reroll.\n");
	
	puts("Pada setiap kesempatan, Anda dapat memilih untuk :");
	puts("\t1. melempar ulang satu dadu, ");
	puts("\t2. melempar ulang semua dadu,");
	puts("\t3. menyimpan satu dadu dan melempar ulang dua lainnya.");
	puts("\t4. memutuskan untuk berhenti\n");
	
	puts("Setelah batas reroll tercapai atau Anda memutuskan untuk berhenti, hasil akhir dadu akan ditampilkan.");
	puts("lalu, akan ditentukan apakah Anda mendapatkan diskon atau tidak.\n");

	puts("Selamat bermain dan semoga beruntung!");
	getchar();
	system("cls");
}

//Fungsi untuk permainnan
void gameForUser() {
    system("cls"); 
    char pilihan;
    int rerollCount = 0; 	// hitungan reroll
    int dice[3];         	// array untuk dice value
    int i;
    
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    char today[11];
    strftime(today, sizeof(today), "%Y-%m-%d", localTime);

    // Membaca kapan terakhir kali dimainkan dan jumlah poin
    char lastPlayDate[11] = "";
    int totalMinumanGratis = 0;

    FILE *file = fopen(GAME_FILE, "r");
    if (file) {
        fscanf(file, "%10s %d", lastPlayDate, &loyaltyPoints);
        fclose(file);
    }

    printf("Pilih salah satu opsi berikut:\n");
    printf("1. Bermain game \"Lucky Roll Showdown!!\"\n");
    printf("2. Lanjut cek poin loyalitas\n");
    printf("\nMasukkan pilihan Anda: ");
    scanf(" %c", &pilihan);

    if (pilihan == '2') {
        freeDrink();
        return;
    } else if (pilihan != '1') {
        printf("Pilihan tidak valid.\n");
        return;
    }

    // Mengecek apakah user sudah bermain hari ini
    if (strcmp(today, lastPlayDate) == 0) {
    	system("cls");
        printf("Anda sudah bermain hari ini. Silakan coba lagi besok.\n");
        getchar();
        system("cls");
        return; // Exit jika sudah bermain hari ini
    }

    system("cls"); 
	introduction();
    scanf(" %c", &pilihan); getchar();

    if (pilihan == 'n' || pilihan == 'N') {
        system("cls");
        return; // Jika user memilih n atau N maka akan kembali ke menu utama
    }
    
	rules();
    srand(time(0)); // Seed random number generator
    for (i = 0; i < 3; i++) {
        dice[i] = (rand() % 6) + 1; // Roll three dice
    }
	puts("Mulai!!!");
	
    do {
        printf("\nNilai dadu saat ini:\n");
        for (i = 0; i < 3; i++) {
            printf("Dadu %d: %d\n", i + 1, dice[i]);
        }

        printf("\nOpsi reroll:\n");
        printf("1. Reroll satu dadu\n");
        printf("2. Reroll semua dadu\n");
        printf("3. Simpan satu dadu, reroll dua lainnya\n");
        printf("4. Tidak melakukan reroll (selesai)\n");
        printf("Masukkan pilihan Anda: ");
        int opsi;
        scanf("%d", &opsi);

        switch (opsi) {
        case 1: {
            printf("Masukkan nomor dadu yang ingin di-reroll (1, 2, 3): ");
            int rerollDadu;
            scanf("%d", &rerollDadu);
            if (rerollDadu >= 1 && rerollDadu <= 3) {
                dice[rerollDadu - 1] = (rand() % 6) + 1;
                printf("Dadu %d di-reroll.\n", rerollDadu);
                rerollCount++;
            } else {
                printf("Nomor dadu tidak valid.\n");
            }
            break;
        }
        case 2:
            for (i = 0; i < 3; i++) {
                dice[i] = (rand() % 6) + 1;
            }
            printf("Semua dadu di-reroll.\n");
            rerollCount++;
            break;
        case 3:
            printf("Masukkan nomor dadu yang ingin disimpan (1, 2, 3): ");
            int keepDadu;
            scanf("%d", &keepDadu);
            for (i = 0; i < 3; i++) {
                if (i != keepDadu - 1) {
                    dice[i] = (rand() % 6) + 1;
                }
            }
            printf("Dadu %d disimpan, dua dadu lainnya di-reroll.\n", keepDadu);
            rerollCount++;
            break;
        case 4:
            printf("Reroll selesai.\n");
            break;
        default:
            printf("Pilihan tidak valid.\n");
            continue;
        }

        // Cek apakah user punya 3 dadu yang sama
        if (dice[0] == dice[1] && dice[1] == dice[2]) {
            printf("\nSelamat! Anda mendapatkan 1 poin loyalitas.\n");
            loyaltyPoints++; // Mendapatkan reward loyalty points
            break; 
        }

        // Jika tercapai limit reroll atau user memutuskan berhenti bermain
        if (rerollCount >= 3) {
            printf("Anda telah mencapai batas reroll.\n");
            break;
        }
    } while (1);

    // Save data sekarang tanggal dan juga poin
    file = fopen(GAME_FILE, "w");
    if (file) {
        fprintf(file, "%s %d", today, &loyaltyPoints);
        fclose(file);
    }
    freeDrink();
    system("cls");
}

// Mendapatkan minuman gratis (Minuman Spesial) untuk setiap 10 poin
void freeDrink() {
    system("cls");

    if (loyaltyPoints >= 10) {
        int freeChoice;
        char lastPlayDate[11];

        // Baca tanggal terakhir bermain dari file
        FILE *file = fopen(GAME_FILE, "r");
        if (file) {
            fscanf(file, "%10s %*d", lastPlayDate); // Hanya membaca tanggal
            fclose(file);
        } else {
            strcpy(lastPlayDate, ""); // Jika file tidak ditemukan, default kosong
        }

        puts("\nSelamat! Anda memiliki cukup poin untuk mendapatkan 1 minuman gratis.");
        puts("Pilih 1 minuman gratis dari menu:");
        puts("*tanpa topping");

        printf("\n\t------- Minuman Spesial -------\n");
        for (int i = 10; i < 15; i++) {
            printf("%d. %-30s \tRp %d\n", i + 1, items[i].name, items[i].price);
        }

        do {
            printf("Masukkan nomor minuman yang ingin Anda pilih: ");
            scanf("%d", &freeChoice);
            while (getchar() != '\n'); // Membersihkan buffer input

            if (freeChoice < 11 || freeChoice > 15) {
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                continue;
            }
            printf("Minuman %s gratis berhasil ditambahkan ke pesanan Anda.\n", items[freeChoice - 1].name);

            loyaltyPoints -= 10;

            // Perbarui file game_data 
            file = fopen(GAME_FILE, "w");
            if (file) {
                fprintf(file, "%s %d", lastPlayDate, loyaltyPoints); 
                fclose(file);
            }
            break;
        } while (1);
    } else {
        printf("Poin loyalitas Anda saat ini: %d\n", loyaltyPoints);
        printf("Poin loyalitas Anda belum cukup untuk mendapatkan minuman gratis.\n");
        getchar();
    }

    getchar();
    system("cls");
}
