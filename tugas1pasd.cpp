#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 100
#define FILE_DB "netfilm_db.txt"

struct movie {
	char nama[100];
	float harga;
	int tahun;
	float rating;
};

struct movie films[max];
int total = 0;

void clearscreen() {
	system("cls");
}

void load_data() {
	FILE *fp = fopen(FILE_DB, "r");
	if (fp == NULL) {
		printf("Database belum ada.\n");
		return;
	}
		
		total = 0;
		while (fscanf(fp, "%[^;];%f;%d;%f\n",
			films[total].nama,
			&films[total].harga,
			&films[total].tahun,
			&films[total].rating) != EOF) {
			total++;	
		}
		
		fclose(fp);
		printf("Data loaded: %d film ditemukan.\n", total);
	}
	
void save_data() {
	FILE *fp= fopen(FILE_DB, "w");
	for (int i = 0; i < total; i++) {
		fprintf(fp, "%s;%.0f;%d;%.1f\n",
			films[i].nama,
			films[i].harga,
			films[i].tahun,
			films[i].rating);
		}
	fclose(fp);
	printf("Data tersimpan di %s\n", FILE_DB);
}

void bubsortjudul() {
	struct movie temp;
	for (int i = 0; i < total-1; i++) {
		for (int j = 0; j < total-i-1; j++) {
			if (strcmp(films[j].nama, films[j+1].nama) > 0) {
				temp = films[j];
				films[j] = films[j+1];
				films[j+1] = temp;
			}
		}
	}
}

void quickSort(struct movie arr[], int awal, int akhir) {
	int low = awal, high = akhir;
	float pivot = arr[(awal + akhir) / 2].rating;
	
	do {
		while (arr[low].rating > pivot)
		low++;
		
		while (arr[high].rating < pivot)
		high--;
		
		if (low <= high) {
			struct movie temp = arr [low];
			arr[low] = arr[high];
			arr[high] = temp;
			
			low++;
			high--;
		}
	} while (low <= high);
	
	if (awal < high) // rekursif utk bagian kiri & kanan
		quickSort(arr, awal, high);
	if (low < akhir)
		quickSort(arr, low, akhir);
}

void urutRating() {
	if (total > 0) {
		quickSort(films, 0, total-1);
	}
}

int linearsearch(char cari[]) {
	for (int i= 0; i < total; i++) {
		if (strcmp(films[i].nama, cari) == 0) {
			return i;
		}
	}
	return -1;
}

int binarysearch(char cari[]) {
	int kiri = 0, kanan = total-1;
	while (kiri <= kanan) {
		int tengah = (kiri + kanan) / 2;
		int hasil = strcmp(films[tengah].nama, cari);
		if (hasil == 0) return tengah;
		if (hasil < 0) kiri = tengah + 1;
		else kanan = tengah - 1;
	}
	return -1;
}

void tampilFilm() {
	if (total == 0) {
		printf("Belum ada film\n");
		return;
	}

	printf("\n+----+------------------------------+----------+-------+---------+\n");
	printf("| ID | JUDUL FILM                   | LISENSI  | TAHUN | RATING  |\n");
	printf("+----+------------------------------+----------+-------+---------+\n");

	for (int i = 0; i < total; i++) {
		printf("| %-2d | %-28s | Rp%-6.0f | %-5d | %-7.1f |\n",
				i+1, films[i].nama, films[i].harga, films[i].tahun, films[i].rating);
	}
	printf("+----+------------------------------+----------+-------+---------+\n");
}

void tambahFilm() {
	if (total >= max) {
		printf("Maaf, kapasitas penuh.\n");
		return;
	}

	printf("\n--- Tambah Film Baru ---\n");
	getchar();
	
	printf("Input Judul: ");
	fgets(films[total].nama, sizeof(films[total].nama), stdin);
	films[total].nama[strcspn(films[total].nama, "\n")] = '\0';
	
	printf("Input Harga: ");
	scanf("%f", &films[total].harga);

	printf("Input Tahun: ");
	scanf("%d", &films[total].tahun);

	printf("Input Rating: ");
	scanf("%f", &films[total].rating);

	total++;
	save_data();
	printf("[ SUCCESS ] Data berhasil disinkronkan ke netfilm_db.txt!\n");
	printf("[ SUCCESS ] Film ditambahkan");
}

int main() {
	int pilih;
	char cari[100];
	int index;
	
	// clearscreen();
	printf("=== NETFILM SYSTEM ===\n");
	load_data();
	
	do {
		clearscreen();
		
		printf("\n+--------------------------------+\n");
		printf("|   NETFILM SYSTEM - DASHBOARD   |\n");
		printf("+--------------------------------+\n");
		printf("| [1] Lihat Katalog Film         |\n");
		printf("| [2] Urut Rating (Quick Sort)   |\n");
		printf("| [3] Urut Abjad (Bubble Sort)   |\n");
		printf("| [4] Cari Film (Linear Search)  |\n");
		printf("| [5] Cari Film (Binary Search)  |\n");
		printf("| [6] Tambah Film                |\n");
		printf("| [0] Keluar & Simpan            |\n");
		printf("+--------------------------------+\n");
		printf("Pilih: ");
		scanf("%d", &pilih);

		switch(pilih) {
			case 1:
				printf("N E T F I L M   C O N T E N T   K A T A L O G");
				tampilFilm();
				break;
				
			case 2:
				printf("N E T F I L M   C O N T E N T   K A T A L O G");
				urutRating();
				tampilFilm();
				printf("[!] Katalog berhasil diurutkan berdasarkan Rating Tertinggi.\n");
				break;
				
			case 3:
				printf("N E T F I L M   C O N T E N T   K A T A L O G");
				bubsortjudul();
				tampilFilm();
				printf("[!] Katalog berhasil diurutkan berdasarkan Abjad (A-Z).\n");
				break;
				
			case 4:
				if (total == 0) {
					printf("Film kosong.\n");
					break;
				}
				getchar();
				printf("Keyword judul: ");
				fgets(cari, sizeof(cari), stdin);
				cari[strcspn(cari, "\n")] = '\0';
				
				index = linearsearch(cari);
				if (index != -1) {
					printf("[ FOUND ] %s (%d)\n", films[index].nama, films[index].tahun);
				} else {
					printf("Film '%s' tidak ditemukan!\n", cari);
				} break;
				
			case 5:
				if (total == 0) {
					printf("Film kosong.\n");
					break;
				}
				if (total < 30) {
					printf("Data < 30 sebaiknya pakai linear search.\n");
				}
				getchar();
				printf("Judul Lengkap (Exact): ");
				fgets(cari, sizeof(cari), stdin);
				cari[strcspn(cari, "\n")] = '\0';
				
				bubsortjudul();
				
				index = binarysearch(cari);
				if (index != -1) {
					printf("[ FOUND ] %s (%d)\n", films[index].nama, films[index].tahun);
				} else {
					printf("[!] Judul tidak ditemukan. Pastikan data sudah di-sort A-Z.\n");
				} break;
				
			case 6:
				tambahFilm();
				break;
			
			case 0:
				save_data();
				printf("[ SUCCESS ] Data berhasil disinkronkan ke netfilm_db.txt\n");
				printf("\nSistem Offline. Terimakasih!");
				break;
				
			default:
				printf("Pilihan salah! coba lagi.\n");
		}	
			
		if (pilih != 0) {
			printf("\nTekan enter untuk melanjutkan...");
			getchar();
			getchar();
		}
		
	} while (pilih != 0);

	return 0;
}
