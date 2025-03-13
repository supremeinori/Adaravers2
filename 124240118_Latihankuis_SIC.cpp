#include <iostream>
#include <cstring> // Untuk strcmp
#include <cstdio>  // Untuk fopen, fread, fwrite, fclose
using namespace std;

struct Mahasiswa {
    char nama[50];
    int nim;
    char jurusan[20];
    int tahunMasuk;
    float ipk;
};

void tambahMahasiswa();
void tampilkanMahasiswa();
void cariMahasiswaByNIM();
void cariMahasiswaByJurusan();
void perbaruiIPK();
void hapusMahasiswa();
void simpanKeFile();
void bacaDariFile();
void bubbleSort();
int binarySearch(int key);
void quickSort(int low, int high);
int partition(int low, int high);

const int MAX_MAHASISWA = 100;
Mahasiswa *mhs[MAX_MAHASISWA]; // Array of pointers untuk mahasiswa
int jumlahMahasiswa = 0;

int main() {
    bacaDariFile(); // Membaca data dari file saat program dimulai

    int pilihan;
    do {
        cout << "\n=== SmartCampus++ ===" << endl;
        cout << "1. Tambah Mahasiswa Baru" << endl;
        cout << "2. Tampilkan Seluruh Mahasiswa" << endl;
        cout << "3. Cari Mahasiswa Berdasarkan NIM" << endl;
        cout << "4. Cari Mahasiswa Berdasarkan Jurusan" << endl;
        cout << "5. Perbarui IPK Mahasiswa" << endl;
        cout << "6. Hapus Mahasiswa" << endl;
        cout << "7. Keluar" << endl;
        cout << "Pilih menu: "; cin >> pilihan;

        switch (pilihan) {
            case 1: tambahMahasiswa(); break;
            case 2: tampilkanMahasiswa(); break;
            case 3: cariMahasiswaByNIM(); break;
            case 4: cariMahasiswaByJurusan(); break;
            case 5: perbaruiIPK(); break;
            case 6: hapusMahasiswa(); break;
            case 7:
                cout << "Terima kasih telah menggunakan SmartCampus++! Semoga sukses dalam studi Anda!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan pilih 1-7." << endl;
        }
    } while (pilihan != 7);

    // Simpan data ke file sebelum keluar
    simpanKeFile();

    // Bebaskan memori yang dialokasikan
    for (int i = 0; i < jumlahMahasiswa; i++) {
        delete mhs[i];
    }

    return 0;
}

// Fungsi untuk menambahkan mahasiswa baru
void tambahMahasiswa() {
    if (jumlahMahasiswa >= MAX_MAHASISWA) {
        cout << "Database penuh! Tidak bisa menambahkan mahasiswa baru." << endl;
        return;
    }

    mhs[jumlahMahasiswa] = new Mahasiswa(); // Alokasi memori dinamis

    cout << "\nMasukkan data mahasiswa baru:" << endl;
    cin.ignore();
    cout << "Nama: "; cin.getline(mhs[jumlahMahasiswa]->nama, 50);
    cout << "NIM: "; cin >> mhs[jumlahMahasiswa]->nim; cin.ignore();
    cout << "Jurusan: "; cin.getline(mhs[jumlahMahasiswa]->jurusan, 20);
    cout << "Tahun Masuk: "; cin >> mhs[jumlahMahasiswa]->tahunMasuk; cin.ignore();
    mhs[jumlahMahasiswa]->ipk = 0.0; // IPK awal = 0.0

    jumlahMahasiswa++;
    cout << "Mahasiswa berhasil ditambahkan!" << endl;
}

// Fungsi untuk menampilkan seluruh mahasiswa (dengan sorting)
void tampilkanMahasiswa() {
    if (jumlahMahasiswa == 0) {
        cout << "Database mahasiswa kosong." << endl;
        return;
    }

    bubbleSort(); // Urutkan data sebelum menampilkan

    cout << "\nData Mahasiswa:" << endl;
    for (int i = 0; i < jumlahMahasiswa; i++) {
        cout << "NIM: " << mhs[i]->nim << endl;
        cout << "Nama: " << mhs[i]->nama << endl;
        cout << "Jurusan: " << mhs[i]->jurusan << endl;
        cout << "Tahun Masuk: " << mhs[i]->tahunMasuk << endl;
        cout << "IPK: " << mhs[i]->ipk << endl;
        cout << "-------------------------" << endl;
    }
}

// Fungsi untuk mencari mahasiswa berdasarkan NIM (Binary Search + Quick Sort)
void cariMahasiswaByNIM() {
    if (jumlahMahasiswa == 0) {
        cout << "Database mahasiswa kosong." << endl;
        return;
    }

    int nim;
    cout << "Masukkan NIM yang dicari: "; cin >> nim;

    quickSort(0, jumlahMahasiswa - 1); // Urutkan data sebelum mencari
    int index = binarySearch(nim);

    if (index != -1) {
        cout << "\nMahasiswa ditemukan!" << endl;
        cout << "NIM: " << mhs[index]->nim << endl;
        cout << "Nama: " << mhs[index]->nama << endl;
        cout << "Jurusan: " << mhs[index]->jurusan << endl;
        cout << "Tahun Masuk: " << mhs[index]->tahunMasuk << endl;
        cout << "IPK: " << mhs[index]->ipk << endl;
    } else {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan!" << endl;
    }
}

// Fungsi untuk mencari mahasiswa berdasarkan jurusan (Sequential Search)
void cariMahasiswaByJurusan() {
    if (jumlahMahasiswa == 0) {
        cout << "Database mahasiswa kosong." << endl;
        return;
    }

    char jurusan[20];
    cout << "Masukkan jurusan yang dicari: "; cin.ignore(); cin.getline(jurusan, 20);

    bool ditemukan = false;
    for (int i = 0; i < jumlahMahasiswa; i++) {
        if (strcmp(mhs[i]->jurusan, jurusan) == 0) {
            cout << "\nMahasiswa ditemukan!" << endl;
            cout << "NIM: " << mhs[i]->nim << endl;
            cout << "Nama: " << mhs[i]->nama << endl;
            cout << "Jurusan: " << mhs[i]->jurusan << endl;
            cout << "Tahun Masuk: " << mhs[i]->tahunMasuk << endl;
            cout << "IPK: " << mhs[i]->ipk << endl;
            cout << "-------------------------" << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Mahasiswa dengan jurusan " << jurusan << " tidak ditemukan!" << endl;
    }
}

// Fungsi untuk memperbarui IPK mahasiswa
void perbaruiIPK() {
    if (jumlahMahasiswa == 0) {
        cout << "Database mahasiswa kosong." << endl;
        return;
    }

    int nim;
    cout << "Masukkan NIM mahasiswa yang ingin diperbarui IPK-nya: "; cin >> nim;

    for (int i = 0; i < jumlahMahasiswa; i++) {
        if (mhs[i]->nim == nim) {
            float ipkBaru;
            cout << "Masukkan IPK baru (0.0 - 4.0): "; cin >> ipkBaru;

            if (ipkBaru >= 0.0 && ipkBaru <= 4.0) {
                mhs[i]->ipk = ipkBaru;
                cout << "IPK mahasiswa dengan NIM " << nim << " berhasil diperbarui!" << endl;
            } else {
                cout << "IPK tidak valid. Harus dalam rentang 0.0 - 4.0." << endl;
            }
            return;
        }
    }

    cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan!" << endl;
}

// Fungsi untuk menghapus mahasiswa
void hapusMahasiswa() {
    if (jumlahMahasiswa == 0) {
        cout << "Database mahasiswa kosong." << endl;
        return;
    }

    int nim;
    cout << "Masukkan NIM mahasiswa yang ingin dihapus: "; cin >> nim;

    for (int i = 0; i < jumlahMahasiswa; i++) {
        if (mhs[i]->nim == nim) {
            delete mhs[i]; // Hapus memori dinamis
            for (int j = i; j < jumlahMahasiswa - 1; j++) {
                mhs[j] = mhs[j + 1]; // Geser elemen array
            }
            jumlahMahasiswa--;
            cout << "Mahasiswa dengan NIM " << nim << " berhasil dihapus!" << endl;
            return;
        }
    }

    cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan!" << endl;
}

// Fungsi untuk menyimpan data ke file
void simpanKeFile() {
    FILE *file = fopen("MahasiswaData.dat", "wb");
    if (file) {
        fwrite(&jumlahMahasiswa, sizeof(int), 1, file); // Simpan jumlah mahasiswa
        for (int i = 0; i < jumlahMahasiswa; i++) {
            fwrite(mhs[i], sizeof(Mahasiswa), 1, file); // Simpan data mahasiswa
        }
        fclose(file);
    } else {
        cout << "Gagal membuka file untuk penyimpanan!" << endl;
    }
}

// Fungsi untuk membaca data dari file
void bacaDariFile() {
    FILE *file = fopen("MahasiswaData.dat", "rb");
    if (file) {
        fread(&jumlahMahasiswa, sizeof(int), 1, file); // Baca jumlah mahasiswa
        for (int i = 0; i < jumlahMahasiswa; i++) {
            mhs[i] = new Mahasiswa(); // Alokasi memori dinamis
            fread(mhs[i], sizeof(Mahasiswa), 1, file); // Baca data mahasiswa
        }
        fclose(file);
    } else {
        cout << "File tidak ditemukan atau gagal dibuka!" << endl;
    }
}

// Fungsi untuk sorting dengan Bubble Sort
void bubbleSort() {
    for (int i = 0; i < jumlahMahasiswa - 1; i++) {
        for (int j = 0; j < jumlahMahasiswa - i - 1; j++) {
            if (mhs[j]->nim > mhs[j + 1]->nim) {
                swap(mhs[j], mhs[j + 1]);
            }
        }
    }
}

// Fungsi untuk Binary Search
int binarySearch(int key) {
    int low = 0, high = jumlahMahasiswa - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (mhs[mid]->nim == key) {
            return mid;
        } else if (mhs[mid]->nim < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Fungsi untuk Quick Sort
void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

// Fungsi untuk partisi dalam Quick Sort
int partition(int low, int high) {
    int pivot = mhs[high]->nim;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (mhs[j]->nim < pivot) {
            i++;
            swap(mhs[i], mhs[j]);
        }
    }
    swap(mhs[i + 1], mhs[high]);
    return i + 1;
}
