#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void introduction(){
	puts("Lucky Roll Showdown !!\n");
	puts("Dalam permainan ini, Anda akan melempar tiga dadu.");
	puts("  (i) Jika ketiga dadu menunjukkan angka yang sama, Anda akan mendapatkan diskon 100%.");
	puts(" (ii) Jika dua dadu menunjukkan angka yang sama, Anda akan mendapatkan diskon 50%.");
	puts("(iii) Namun, jika tidak ada dadu yang sama, Anda tidak mendapatkan diskon.");
	puts("");
}

void rules(){
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
}

int main() {
    char pilihan;
    int rerollCount = 0; 	// Menghitung jumlah reroll yang dilakukan
    int dice[3];         	// Array untuk menyimpan nilai tiga dadu

    int dadu_2_sama = 50;
    int dadu_3_sama = 100;

	introduction();
	
    // Menanyakan apakah ingin bermain pada awal program
    printf("Apakah Anda ingin bermain? (y/n): ");
    scanf(" %c", &pilihan);
    
    // Keluar jika pengguna memilih 'n'
    if (pilihan == 'n' || pilihan == 'N') {
        printf("Terima kasih.\n");
        return 0; 
    }
	system("cls");
	
	rules();
	printf("\nTekan tombol apa saja untuk memulai...");
	char key = getch();
	system("cls");
	
    // Inisialisasi generator angka acak
    srand(time(0));

    // Generate angka awal untuk semua dadu
    for (int i = 0; i < 3; i++) {
        dice[i] = (rand() % 6) + 1; // Angka acak dari 1 sampai 6
    }

    do {
        // Menampilkan nilai dadu saat ini
        printf("Nilai dadu saat ini:\n");
        for (int i = 0; i < 3; i++) {
            printf("Dadu %d: %d\n", i + 1, dice[i]);
        }

        // Menanyakan apakah ingin melakukan reroll
        printf("\nOpsi reroll:\n");
        printf("\t1. Reroll satu dadu\n");
        printf("\t2. Reroll semua dadu\n");
        printf("\t3. Simpan satu dadu, reroll dua lainnya\n");
        printf("\t4. Tidak melakukan reroll (selesai)\n");
        printf("Masukkan pilihan Anda: ");
        
        int opsi;
        scanf("%d", &opsi);
        switch (opsi) {
        case 1: {
            // Reroll satu dadu
            printf("Masukkan nomor dadu yang ingin di-reroll (1, 2, 3): ");
            int rerollDadu;
            scanf("%d", &rerollDadu);
            
            if (rerollDadu >= 1 && rerollDadu <= 3) {
                dice[rerollDadu - 1] = (rand() % 6) + 1;
                printf("Dadu %d di-reroll.\n", rerollDadu);
                rerollCount++;
            } 
			else {
                printf("Nomor dadu tidak valid.\n");
            }
            break;
        }
        
        case 2:
            // Reroll semua dadu
            for (int i = 0; i < 3; i++) {
                dice[i] = (rand() % 6) + 1;
            }
            printf("Semua dadu telah di-reroll.\n");
            rerollCount++;
            break;

        case 3: {
            // Simpan satu dadu, reroll dua lainnya
            printf("Masukkan nomor dadu yang ingin disimpan (1, 2, 3): ");
            int simpanDadu;
            scanf("%d", &simpanDadu);
            if (simpanDadu >= 1 && simpanDadu <= 3) {
                for (int i = 0; i < 3; i++) {
                    if (i != simpanDadu - 1) {
                        dice[i] = (rand() % 6) + 1;
                    }
                }
                printf("Dadu %d disimpan, dua dadu lainnya di-reroll.\n", simpanDadu);
                rerollCount++;
            } else {
                printf("Nomor dadu tidak valid.\n");
            }
            break;
        }

        case 4:
            // Tidak melakukan reroll, keluar dari loop
            printf("Tidak melakukan reroll. Permainan selesai.\n");
            rerollCount = 3; // Terpaksa keluar dan permainan selesai
            break;

        default:
            printf("Pilihan Anda tidak valid.\n");
        }

        // Cek batas reroll
        if (rerollCount >= 3) {
            printf("Anda telah mencapai batas maksimum reroll (3 kali).\n");
            break;
        }
		
		printf("\n");
    } while (rerollCount < 3);

    // Menampilkan hasil akhir
    printf("\nPermainan selesai. Hasil akhir nilai dadu:\n");
    for (int i = 0; i < 3; i++) {
        printf("\tDadu %d: %d\n", i + 1, dice[i]);
    }
	
	if (dice[0] == dice[1] && dice[1] == dice[2]) {
        printf("\nSelamat! Semua dadu sama. Anda mendapat diskon %d %%.\n", dadu_3_sama);
    } 
	else if (dice[0] == dice[1] || dice[0] == dice[2] || dice[1] == dice[2]) {
        printf("\nSelamat! Ada dua dadu yang sama. Anda mendapat diskon %d %%.\n", dadu_2_sama);
    } 
	else {
        printf("\nSayang sekali, Anda kurang beruntung...\n");
    }

    printf("Terima kasih telah bermain.\n");
    return 0;
}
