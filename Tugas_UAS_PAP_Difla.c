#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Union untuk tempat dan tanggal lahir
typedef union {
    char tempat[50];
    char tanggal[20];
} TempatTanggalLahir;

// Struct untuk menyimpan data siswa
typedef struct {
    char nama[50];
    char kelas[10];
    int umur;
    TempatTanggalLahir ttl;
    char prestasi[100];
    char pengalaman[100];
    float nilaiRaport;  // Menambahkan nilai rapor
    int isBaru;  // Menandakan apakah anggota OSIS baru atau lama (0 = lama, 1 = baru)
} Siswa;

// Fungsi untuk menampilkan judul program
void tampilkanJudul() {
    printf("Pendaftaran Anggota OSIS SMA Negeri 1 Medan\n");
    printf("==========================================\n\n");
}

// Fungsi untuk mendaftarkan anggota OSIS
Siswa *daftarAnggota() {
    Siswa *siswa = (Siswa *)malloc(sizeof(Siswa));
    if (siswa == NULL) {
        printf("Memori tidak cukup!\n");
        exit(1);
    }

    printf("Masukkan nama: ");
    fgets(siswa->nama, 50, stdin);
    strtok(siswa->nama, "\n"); // Menghapus newline

    printf("Masukkan kelas: ");
    fgets(siswa->kelas, 10, stdin);
    strtok(siswa->kelas, "\n");

    printf("Masukkan umur: ");
    scanf("%d", &siswa->umur);
    getchar(); // Membersihkan newline di buffer

    printf("Masukkan tempat lahir: ");
    fgets(siswa->ttl.tempat, 50, stdin);
    strtok(siswa->ttl.tempat, "\n");

    printf("Masukkan tanggal lahir (format DD-MM-YYYY): ");
    fgets(siswa->ttl.tanggal, 20, stdin);
    strtok(siswa->ttl.tanggal, "\n");

    printf("Masukkan prestasi: ");
    fgets(siswa->prestasi, 100, stdin);
    strtok(siswa->prestasi, "\n");

    printf("Masukkan pengalaman organisasi: ");
    fgets(siswa->pengalaman, 100, stdin);
    strtok(siswa->pengalaman, "\n");

    // Menambahkan input nilai rapor
    printf("Masukkan nilai rapor (0-10): ");
    scanf("%f", &siswa->nilaiRaport);
    getchar(); // Membersihkan newline di buffer

    // Mengecek apakah siswa diterima
    if (siswa->nilaiRaport >= 8.0) {
        printf("Selamat, Anda diterima sebagai anggota OSIS baru!\n");
        siswa->isBaru = 1;  // Anggota baru
    } else {
        printf("Maaf, Anda tidak diterima menjadi anggota OSIS.\n");
        free(siswa);  // Membebaskan memori jika tidak diterima
        return NULL;
    }

    return siswa;
}

// Fungsi untuk menampilkan data anggota OSIS
void tampilkanAnggota(Siswa *siswa) {
    printf("\n--- Data Anggota OSIS ---\n");
    printf("Nama: %s\n", siswa->nama);
    printf("Kelas: %s\n", siswa->kelas);
    printf("Umur: %d\n", siswa->umur);
    printf("Tempat Lahir: %s\n", siswa->ttl.tempat);
    printf("Tanggal Lahir: %s\n", siswa->ttl.tanggal);
    printf("Prestasi: %s\n", siswa->prestasi);
    printf("Pengalaman Organisasi: %s\n", siswa->pengalaman);
    printf("Nilai Raport: %.2f\n", siswa->nilaiRaport);
    if (siswa->isBaru) {
        printf("Status: Anggota OSIS Baru\n");
    } else {
        printf("Status: Anggota OSIS Lama\n");
    }
}

// Fungsi untuk menambahkan anggota ke dalam daftar
Siswa **tambahAnggota(Siswa **daftar, int *jumlah) {
    (*jumlah)++;
    daftar = (Siswa **)realloc(daftar, (*jumlah) * sizeof(Siswa *));  // Perbaiki dengan casting
    if (daftar == NULL) {
        printf("Memori tidak cukup!\n");
        exit(1);
    }
    printf("\nPendaftaran Anggota %d\n", *jumlah);
    Siswa *siswa = daftarAnggota();
    if (siswa != NULL) {
        daftar[*jumlah - 1] = siswa;  // Menyimpan siswa yang diterima
    } else {
        (*jumlah)--;  // Tidak menambah anggota jika siswa tidak diterima
    }
    return daftar;
}

// Fungsi untuk menghapus anggota berdasarkan indeks
Siswa **hapusAnggota(Siswa **daftar, int *jumlah, int indeks) {
    if (indeks < 0 || indeks >= *jumlah) {
        printf("Indeks tidak valid!\n");
        return daftar;
    }
    free(daftar[indeks]);
    for (int i = indeks; i < *jumlah - 1; i++) {
        daftar[i] = daftar[i + 1];
    }
    (*jumlah)--;
    daftar = (Siswa **)realloc(daftar, (*jumlah) * sizeof(Siswa *));  // Perbaiki dengan casting
    if (*jumlah > 0 && daftar == NULL) {
        printf("Memori tidak cukup!\n");
        exit(1);
    }
    printf("Anggota ke-%d berhasil dihapus.\n", indeks + 1);
    return daftar;
}

// Fungsi untuk menampilkan semua anggota OSIS
void tampilkanSemuaAnggota(Siswa **daftar, int jumlah) {
    printf("\nData Semua Anggota OSIS:\n");
    for (int i = 0; i < jumlah; i++) {
        printf("\nAnggota ke-%d:\n", i + 1);
        tampilkanAnggota(daftar[i]);
    }
}

int main() {
    int jumlah = 0;
    Siswa **daftar = NULL;
    int pilihan;

    // Menampilkan judul
    tampilkanJudul();

    do {
        printf("\nMenu:\n");
        printf("1. Tambah Anggota\n");
        printf("2. Lihat Semua Anggota\n");
        printf("3. Hapus Anggota\n");
        printf("4. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar(); // Membersihkan newline di buffer

        switch (pilihan) {
        case 1:
            daftar = tambahAnggota(daftar, &jumlah);
            break;
        case 2:
            if (jumlah == 0) {
                printf("Tidak ada anggota yang terdaftar.\n");
            } else {
                tampilkanSemuaAnggota(daftar, jumlah);
            }
            break;
        case 3:
            if (jumlah == 0) {
                printf("Tidak ada anggota yang bisa dihapus.\n");
            } else {
                int indeks;
                printf("Masukkan indeks anggota yang akan dihapus (1-%d): ", jumlah);
                scanf("%d", &indeks);
                getchar(); // Membersihkan newline di buffer
                daftar = hapusAnggota(daftar, &jumlah, indeks - 1);
            }
            break;
        case 4:
            printf("Keluar dari program.\n");
            break;
        default:
            printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 4);

    for (int i = 0; i < jumlah; i++) {
        free(daftar[i]);
    }
    free(daftar);

    return 0;
}