#include <iostream>
using namespace std;

// Struktur data untuk pesanan
struct Pesanan {
    string nama;
    string jenisRoti;
    double totalHarga;
    int nomorAntrean;
    Pesanan* next;
};

// Pointer untuk antrean (queue)
Pesanan* front = NULL;
Pesanan* rear = NULL;

// Pointer untuk riwayat (stack)
Pesanan* top = NULL;

// Counter untuk nomor antrean
int counter = 1;

// Fungsi untuk menambah pesanan ke antrean (enqueue)
void ambilAntrean() {
    Pesanan* newPesanan = new Pesanan();
    
    cout << "\n=== TAMBAH PESANAN ===" << endl;
    cout << "Nama Pembeli: ";
    cin.ignore();
    getline(cin, newPesanan->nama);
    cout << "Jenis Roti: ";
    getline(cin, newPesanan->jenisRoti);
    cout << "Total Harga: ";
    cin >> newPesanan->totalHarga;
    
    newPesanan->nomorAntrean = counter++;
    newPesanan->next = NULL;
    
    if (rear == NULL) {
        front = rear = newPesanan;
    } else {
        rear->next = newPesanan;
        rear = newPesanan;
    }
    
    cout << "Pesanan berhasil ditambahkan! Nomor antrean: " << newPesanan->nomorAntrean << endl;
}
void hapusSemuaPesanan() {
    while (front != NULL) {
        Pesanan* temp = front;
        front = front->next;
        delete temp;
    }
    while (top != NULL) {
        Pesanan* temp = top;
        top = top->next;
        delete temp;
    }
}

// Fungsi untuk melayani pesanan (dequeue dan push ke stack)
void layaniPembeli() {
    if (front == NULL) {
        cout << "Tidak ada pesanan dalam antrean!" << endl;
        return;
    }
    
    Pesanan* temp = front;
    front = front->next;
    
    if (front == NULL) {
        rear = NULL;
    }
    
    // Masukkan ke riwayat (stack)
    temp->next = top;
    top = temp;
    
    cout << "Pesanan no." << temp->nomorAntrean << " atas nama " << temp->nama << " telah dilayani." << endl;
}

// Fungsi untuk menampilkan antrean
void tampilkanPesanan() {
    if (front == NULL) {
        cout << "Tidak ada pesanan dalam antrean!" << endl;
        return;
    }
    
    Pesanan* current = front;
    cout << "\n=== DAFTAR ANTREAN PESANAN ===" << endl;
    while (current != NULL) {
        cout << "No. " << current->nomorAntrean << " | Nama: " << current->nama 
             << " | Roti: " << current->jenisRoti << " | Harga: Rp" << current->totalHarga << endl;
        current = current->next;
    }
}

// Fungsi untuk membatalkan pesanan terakhir (pop dari queue)
void batalkanPesanan() {
    if (front == NULL) {
        cout << "Tidak ada pesanan dalam antrean!" << endl;
        return;
    }
    
    // Jika hanya ada 1 pesanan
    if (front == rear) {
        delete front;
        front = rear = NULL;
    } else {
        // Cari pesanan sebelum terakhir
        Pesanan* current = front;
        while (current->next != rear) {
            current = current->next;
        }
        
        delete rear;
        rear = current;
        rear->next = NULL;
    }
    
    cout << "Pesanan terakhir berhasil dibatalkan!" << endl;
}

// Fungsi untuk menampilkan riwayat pesanan
void tampilkanHistory() {
    if (top == NULL) {
        cout << "Belum ada riwayat pesanan!" << endl;
        return;
    }
    
    Pesanan* current = top;
    cout << "\n=== RIWAYAT PESANAN ===" << endl;
    while (current != NULL) {
        cout << "No. " << current->nomorAntrean << " | Nama: " << current->nama 
             << " | Roti: " << current->jenisRoti << " | Harga: Rp" << current->totalHarga << endl;
        current = current->next;
    }
}

// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    cout << "\n=== SISTEM MANAJEMEN TOKO ROTI ===" << endl;
    cout << "1. Ambil Antrean" << endl;
    cout << "2. Layani Pembeli" << endl;
    cout << "3. Tampilkan Pesanan" << endl;
    cout << "4. Batalkan Pesanan" << endl;
    cout << "5. Tampilkan History Pesanan" << endl;
    cout << "6. Keluar" << endl;
    cout << "Pilih menu: ";
}

int main() {
    int pilihan;
    
    do {
        tampilkanMenu();
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                ambilAntrean();
                break;
            case 2:
                layaniPembeli();
                break;
            case 3:
                tampilkanPesanan();
                break;
            case 4:
                batalkanPesanan();
                break;
            case 5:
                tampilkanHistory();
                break;
            case 6:
                cout << "Terima kasih telah menggunakan sistem ini!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 6);
    hapusSemuaPesanan();

    return 0;
}