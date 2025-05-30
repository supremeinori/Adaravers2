#include <iostream>
#include <cstring> // Untuk strcmp()
#include <algorithm> // Untuk std::sort
using namespace std;

typedef struct 
{
    char nama [40];
    char nim  [9];
    float ipk ;
} mhs;

void pause(){
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore(); // Mengabaikan karakter newline
    cin.get();
}

mhs m[10]{
    {"Senku Ishigami", "10000001", 3.91},
    {"Taiju Oki", "10000002", 3.52},
    {"Yuzuriha Ogawa", "10000003", 3.73},
    {"Tsukasa Shishio", "10000004", 3.84},
    {"Gen Asagiri", "10000005", 3.67},
    {"Chrome", "10000006", 3.21},
    {"Kohaku", "10000007", 3.45},
    {"Ruri", "10000008", 3.16},
    {"Ukyo Saionji", "10000009", 3.34},
    {"Ryusui Nanami", "10000010", 3.09}
};

void ss(char nim[], int size);
void bs(char nama[], int size);
void quickSort(int low, int high);
int partition(int low, int high);
void bubbleSort(int size);

int main (){
    int pil;
    int size = sizeof(m) / sizeof(m[0]);

    do {
        cout << "\n1. Menampilkan semua data mahasiswa menggunakan Pointer";
        cout << "\n2. Mencari mahasiswa berdasarkan NIM menggunakan Sequential Search";
        cout << "\n3. Mencari mahasiswa berdasarkan Nama menggunakan Binary Search";
        cout << "\n4. Mengurutkan mahasiswa berdasarkan IPK secara ascending menggunakan Quick Sort";
        cout << "\n5. Mengurutkan mahasiswa berdasarkan IPK secara descending menggunakan Bubble Sort";
        cout << "\n6. EXIT";    
        cout << "\nMasukkan Pilihan anda: "; 
        cin >> pil;
        cin.ignore(); // Menghindari masalah dengan getline setelah cin

        switch (pil) {
            case 1: {
                mhs *ptr = m; // Pointer menunjuk ke array struct m

                for (int i = 0; i < size; i++) {
                    cout << i + 1 << ". Nama Mahasiswa : " << ptr->nama << endl;
                    cout << "   NIM : " << ptr->nim << endl;
                    cout << "   IPK : " << ptr->ipk << endl;
                    cout << endl;
                    ptr++;  // Pindah ke elemen berikutnya dalam array
                }
                pause();
                break;
            }
            
            case 2: { 
                // Pencarian berdasarkan NIM (Sequential Search)
                char nim[10];

                cout << "Cari data dengan menggunakan NIM: "; 
                cin.getline(nim, sizeof(nim));

                ss(nim, size);
                pause();
                break;
            }

            case 3: { 
                // Pencarian berdasarkan Nama (Binary Search)
                char nama[40];

                cout << "Cari data dengan menggunakan Nama: ";
                cin.getline(nama, sizeof(nama));

                bs(nama, size);
                pause();
                break;
            }

            case 4: { 
                // Mengurutkan mahasiswa berdasarkan IPK (Ascending) menggunakan Quick Sort
                quickSort(0, size - 1);

                cout << "\nData setelah diurutkan berdasarkan IPK (ascending - Quick Sort):\n";
                for (int i = 0; i < size; i++) {
                    cout << i + 1 << ". Nama Mahasiswa : " << m[i].nama << endl;
                    cout << "   NIM : " << m[i].nim << endl;
                    cout << "   IPK : " << m[i].ipk << endl;
                    cout << endl;
                }
                pause();
                break;
            }

            case 5: { 
                // Mengurutkan mahasiswa berdasarkan IPK (Descending) menggunakan Bubble Sort
                bubbleSort(size);

                cout << "\nData setelah diurutkan berdasarkan IPK (descending - Bubble Sort):\n";
                for (int i = 0; i < size; i++) {
                    cout << i + 1 << ". Nama Mahasiswa : " << m[i].nama << endl;
                    cout << "   NIM : " << m[i].nim << endl;
                    cout << "   IPK : " << m[i].ipk << endl;
                    cout << endl;
                }
                pause();
                break;
            }

            case 6:
                cout << "Keluar dari program.\n";
                break;

            default:
                cout << "Pilihan tidak valid, silakan coba lagi.\n";
                pause();
                break;
        }
    } while (pil != 6);

    return 0;
}

void ss(char nim[], int size){
    bool ditemukan = false;
    for (int i = 0; i < size; i++) {
        if (strcmp(m[i].nim, nim) == 0) { 
            cout << "\nData Mahasiswa Ditemukan:\n";
            cout << "Nama: " << m[i].nama << endl;
            cout << "NIM: " << m[i].nim << endl;
            cout << "IPK: " << m[i].ipk << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "\nData mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
    }
}

// Binary Search untuk mencari mahasiswa berdasarkan Nama
void bs(char nama[], int size) {
    sort(m, m + size, [](const mhs &a, const mhs &b) {
        return strcmp(a.nama, b.nama) < 0;
    });

    int left = 0, right = size - 1, mid;
    bool ditemukan = false;

    while (left <= right) {
        mid = left + (right - left) / 2;
        int cmp = strcmp(m[mid].nama, nama);

        if (cmp == 0) {
            cout << "\nData Mahasiswa Ditemukan:\n";
            cout << "Nama: " << m[mid].nama << endl;
            cout << "NIM: " << m[mid].nim << endl;
            cout << "IPK: " << m[mid].ipk << endl;
            ditemukan = true;
            break;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!ditemukan) {
        cout << "\nData mahasiswa dengan Nama " << nama << " tidak ditemukan.\n";
    }
}

// Quick Sort untuk mengurutkan berdasarkan IPK (ascending)
void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

int partition(int low, int high) {
    float pivot = m[high].ipk;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (m[j].ipk < pivot) {
            i++;
            swap(m[i], m[j]);
        }
    }
    swap(m[i + 1], m[high]);
    return i + 1;
}

// Bubble Sort untuk mengurutkan berdasarkan IPK (descending)
void bubbleSort(int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (m[j].ipk < m[j + 1].ipk) {
                swap(m[j], m[j + 1]);
            }
        }
    }
}
