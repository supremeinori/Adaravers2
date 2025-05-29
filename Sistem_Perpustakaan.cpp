#include <iostream>
#include <iomanip> // Untuk setw
#include <cstring>
using namespace std;

struct Buku {
    char isbn[10];
    char judul[100];
    char pengarang [100];
    char genre [100];
    int tahun;
    bool status;
};
/*Catatan : Fitur yang belum 
1.Hapus Data (V)
3.Sorting by A-Z, Z-A, Tahun, Genre (V) 
2.Tambahkan Ke file riwayat untuk implementasi append (V)
4.Tambah File Riwayat Penambahan / Pengurangan Buku 
5. Berarti ada 3 File :
   1.Nyimpen Buku (w) (V)
   2.Nyimpen Riwayat Peminjaman (a) (V)
   3.Nyimpen Riwayat penambahan/pengurangan buku (a)*/
struct nodebuku
{
    Buku data;
    nodebuku* prev;
    nodebuku* next;
};

nodebuku* buatnode(Buku isi){
    nodebuku* nodebaru = new nodebuku;
        nodebaru->data= isi;
        nodebaru->prev=NULL;
        nodebaru->next=NULL;
        return nodebaru;
};
void clearScreen() {
    system("cls || clear");
}
void stop(){
    cout << "Press any key to continue...";
    cin.get(); // Ini yang bikin program nunggu user tekan tombol
}

const char* databuku = "perpustakaan.dat";
const char* RB = "riwayatbuku.dat";
const char* RP = "riwayatpeminjaman.dat";

nodebuku* head = NULL;
nodebuku* tail = NULL;
int jumlahbuku = 0;
void isiDummy();
nodebuku* tambahbuku(Buku bukubaru){
    nodebuku* newnode = buatnode (bukubaru);

    if (head == NULL)
    {
        head = newnode;
        tail = newnode;
        return newnode;
    } else {
        tail->next= newnode; // point dari tail ke newnode
        newnode->prev = tail; // newnode ke tail
        tail = newnode;
    }
    jumlahbuku ++;
    return newnode;
};

struct riwayat{
    char aksi[20];
    char isbn[20];
    char peminjaman[50];
    char timestamp[30];
};
struct buku
{
    char aksi[20];
    char isbn[20];
    char judul[50];
    char timestamp[30];
};




int hitungbuku(){
    
    int count = 0;
    nodebuku* current = head;
    while (current != NULL)
    {
        count ++; 
        current = current->next;
    };
    return count;
};

int pagesize=5;


// perfilean
void savetofile();  void readfromfile(); // Data Buku
void saveriwayat(const char* aksi, const char* isbn, const char* peminjam); void readriwayat();  // Data Riwayat
void savebuku(const char* aksi, const char* isbn, const char* judul); void readbuku();  // Data penambahan dan pengurangan buku


//tampilan
void showbuku(); 
void tampilpaging(int hal);
void pilihgenre(char* genre);
nodebuku* cariisbn(char isbn);

//Sorting dan searching
void pinjamBuku(); void pengembalianbuku(); void sortby(); 
void hapus(char* isbn); void search(); void hapusbuku();void sortBukuAZ(); void sortbukuZA();
nodebuku* carijudul(char* isbn); void sorttahun1(); void sorttahun2();
void sortbygenre();

int main (){
    readfromfile();
    int pil; int currentpage = 1; 
    // isiDummy();
    do
    { clearScreen();  // ketika program jalan langsung read file dan reconstrusi linked list
    cout << "SISTEM PERPUSTAKAAN" << endl; // Menu Utama
    cout << "1.Peminjaman Buku" << endl; // ini nanti isinya ada paging, search, sorting
    cout << "2.Penambahan/Pengurangan Buku" << endl; // ini nanti ada nambah buku, hapus buku,
    cout << "0.Keluar Program" << endl; // sorting secara otomatis dari A-Z lalu otomatis di ke file
    cout << "Masukkan Pilihan Anda : " ; cin >> pil;
   
    switch (pil)
    {
    case 1:
        int pil1;
        do
        {    
            clearScreen();
        cout << "PEMINJAMAN" << endl; //Menu Peminjaman
        cout << "1.Tampilkan Buku" << endl; //Tampil buku ada sort, search, paging,
        cout << "2.Pinjam Buku" << endl;
        cout << "3.Pengembalian Buku" << endl;
        cout << "4.Riwayat Peminjaman" << endl;
        cout << "0.Kembali Ke Menu Utama" << endl;
        cout << "Masukkan Pilihan : "; cin >> pil1;
        switch (pil1)
        {
        case 1:
            int piltam;
                do
                {
                    clearScreen();
                    tampilpaging(currentpage);
                cout << "Masukkan Pilihan : " ; cin >> piltam;
                
                if (piltam == 1)
                {
                    if (currentpage > 1){currentpage--;}
                    else{cout << "Sudah Dihalaman Pertama" << endl;}
                }
                else if (piltam == 2)
                {
                    int maxpage = (hitungbuku() + pagesize - 1)/pagesize;
                    if (currentpage < maxpage)
                    {
                        currentpage ++;
                    }else {
                        cout << "Sudah Dihalaman Terakhir";
                    }
                    
                }
                else if (piltam == 3){
                    search();
                    stop();
                }
                else if (piltam == 4){
                    sortby();
                    stop();
                }
                else if (piltam == 5 ){
                    pinjamBuku();
                    char x;
                    cout << "Apakah Anda ingin Kembali Ke menu utama Y/N?" ; cin >> x;
                    if (x == 'y' || x == 'Y')
                    {
                        piltam = 0;
                    }
                }
                else if (piltam == 6)
                {
                    cout << "Show ISBN" << endl;
                }
                
                else if (piltam == 0){
                    cout << "Kembali Ke halaman Sebelumnya" << endl;
                }

                } while (piltam != 0);
            break;
        case 2:
            pinjamBuku();
            break;
        case 3:
            pengembalianbuku();
            break;
        case 4:
            readriwayat();
            cin.ignore();
            stop();
            break;
        case 0:
            cout << "Masih Proses" << endl;
            break;
        
        default:
            break;
        }

        } while (pil1 != 0);

    break;
        case 2:
            int pil2;
        do
        { clearScreen();
        cout << "PENAMBAHAN & PENGURANGAN BUKU" << endl;
        cout << "1.Tambah Buku" << endl;
        cout << "2.Hapus Buku" << endl;
        cout << "3.Riwayat Penambahan/Pengurangan Buku" << endl;
        cout << "0.Kembali Ke Menu Utama" << endl;
        cout << "Masukkan Pilihan : "; cin >> pil2;
        switch (pil2)
        {
        case 1:
            int byk;
            cout << "Masukkan Jumlah Buku yang Ingin Di tambahkan : "; cin >> byk; cin.ignore();
            for (int i = 0; i < byk; i++)
            {   

                Buku BB;
                if (jumlahbuku >= 100)
                {
                    cout << "Kapasitas Penyimanan Penuh" << endl;
                    break;
                }
        
                if (byk==1)
                {
                    cout << "Tambahkan Buku" << endl;
                } else {
                cout << "Tambahkan Buku Ke-" << i+1 <<endl; 
                }
                cout << "Masukkan Judul Buku : " ; cin.getline(BB.judul, 100); 
                cout << "Masukkan Pengarang : " ; cin.getline(BB.pengarang, 100); 
                cout << "Masukkan ISBN : " ; cin.getline(BB.isbn, 10);
                pilihgenre(BB.genre);
                cout << "Masukkan Tahun Terbit : " ; cin >> BB.tahun; cin.ignore();
                BB.status = false;
                savebuku("Tambah", BB.isbn, BB.judul);
                tambahbuku(BB);

            }
            cout << "Buku Berhasil ditambahkan" << endl;
            stop();
            break;
        case 2:
            hapusbuku();
            stop();
            break;
        case 3:
        readbuku();
        cin.ignore();
        stop();
        case 0:
            /* code */
            break;
        
        default:
            break;
        }
        } while (pil2 != 0);
        break;
        case 0:
        sortBukuAZ();
        savetofile();
        cout << "Data Sudah Otomatis Di Sorting & Tersimpan ! " << endl;
        cout << "Terimakasih Sudah Menggunakan Program SISTEM PERPUSTAKAAN ini" << endl;
        break;
    default:
        break;
    }
    } while (pil != 0);
    return 0;
} // Main


void tampilpaging(int hal){    
    int total = hitungbuku();
    int totalhalaman = (hitungbuku() + pagesize - 1) / pagesize;
    if (hal < 1 || hal > totalhalaman)
    {
        cout << "Halaman Tidak Tersedia !" << endl;
        cout << "\n1. Prev  2. Next  3. Search  4. Sort/Filter  5. Pinjam Buku  6.ShowIsbn 0. Keluar\n";
        return;
    }

    int index = 0;
    nodebuku* temp = head;
    int start = (hal - 1) * pagesize;
    int end = start + pagesize;
    
    

 // Simple table header
    cout << "+=======+===============================+===================+=============+==========+=======+" << endl;
    cout << "| " << setw(7) << "ISBN" << " | " << setw(30) << "JUDUL BUKU" << " | " << setw(18) << "PENGARANG"
         << " | " << setw(12) << "GENRE" << " | " << setw(9) << "TAHUN" << " | STATUS |" << endl;
    cout << "+=======+===============================+===================+=============+==========+=======+" << endl;
    string status;
    // Simple table content
    while (temp) {
        if (index >= start && index < end) {
            if (temp->data.status == false){
                status = "Tersedia";
            } else {
                status = "Dipinjam";
            }
            cout << "| " << setw(7) << temp->data.isbn << " | " << setw(30) << temp->data.judul 
                 << " | " << setw(18) << temp->data.pengarang << " | " << setw(12) << temp->data.genre
                 << " | " << setw(9) << temp->data.tahun << " | "<< status << "|" << endl;
        }
        temp = temp->next;
        index++;
    }
    cout << "+=======+===============================+===================+=============+==========+=======+" << endl;
    

    // cout << "+=================================================================================================================+" << endl;
    // cout << "|     " << "ISBN" << "\t" <<"|\t" << "JUDUL BUKU " << "\t|\t" << "PENGARANG" << "\t|\t" << "  GENRE\t" << "\t|" << "TAHUN TERBIT" << "|   " << "STATUS   " << "|" << endl;
    // cout << "+=================================================================================================================+" << endl;

    // while (temp)
    // {
    //    if (index >= start && index < end)
    // {
    //     cout << "|     " << temp->data.isbn << "\t" << "|\t" << temp->data.judul << "\t|\t" << temp->data.pengarang << "\t|\t" << temp->data.genre << "\t" << "\t|" << temp->data.tahun << "|   " << "STATUS   " << "|" << endl;
    //     // cout << "| "<< temp->data.isbn << "| " << temp->data.judul << " | "<< temp->data.pengarang << "| "
    //     // << temp->data.genre << "| " << temp->data.tahun << "|" << endl; 
    // }
    // temp = temp->next;
    // index++;
    // }
    
    cout << "\n1. Prev  2. Next  3. Search  4. Sort/Filter  5. Pinjam Buku  6.showisbn 0. Keluar\n";

}

void pilihgenre(char *genre) {
    int pil; 
        cout << "Pilih Genre" << endl;
        cout << "1.Romance" << endl;
        cout << "2.Sci-fi" << endl;
        cout << "3.Self-Improvement" << endl; 
        cout << "4.Mistery" << endl;
        cout << "Masukkan Pilihan : " ; cin >> pil;

        switch (pil) {
        case 1: strcpy(genre, "Romance"); break;
        case 2: strcpy(genre, "Sci-fi"); break;
        case 3: strcpy(genre, "Self-Improvement"); break;
        case 4: strcpy(genre, "Mistery"); break;
        default: strcpy(genre, "Unknown"); break;
    }
        
        cout << "Genre Yang Anda Pilih Adalah " << genre << endl;

};

void isiDummy() {
    Buku Dummy[20];

    Dummy[0] = {"001", "Matahari", "Tere Liye", "Romance", 2015 , false};
    Dummy[1] = {"002", "Laut Bercerita", "Leila S", "Mystery", 2017, false};
    Dummy[2] = {"003", "Dilan 1990", "Pidi Baiq", "Romance", 2014, false};
    Dummy[3] = {"004", "Atomic Habits", "James Clear", "Self-Improvement", 2018, false};
    Dummy[4] = {"005", "Bumi", "Tere Liye", "Sci-Fi", 2014, false};
    Dummy[5] = {"006", "Bulan", "Tere Liye", "Sci-Fi", 2015, false};
    Dummy[6] = {"007", "Bintang", "Tere Liye", "Sci-Fi", 2016, false};
    Dummy[7] = {"008", "Orang-Orang Biasa", "Andrea Hirata", "Mystery", 2019, false};
    Dummy[8] = {"009", "Negeri 5 Menara", "Ahmad Fuadi", "Self-Improvement", 2009, false};
    Dummy[9] = {"010", "Ayah", "Andrea Hirata", "Romance", 2015};
    Dummy[10] = {"011", "Rich Dad Poor Dad", "Robert Kiyosaki", "Self-Improvement", 1997, false};
    Dummy[11] = {"012", "Sang Pemimpi", "Andrea Hirata", "Romance", 2006, false};
    Dummy[12] = {"013", "Rindu", "Tere Liye", "Romance", 2016, false};
    Dummy[13] = {"014", "Mindset", "Carol Dweck", "Self-Improvement", 2006, false};
    Dummy[14] = {"015", "The Martian", "Andy Weir", "Sci-Fi", 2011, false};
    Dummy[15] = {"016", "The Silent Patient", "Alex Michaelides", "Mystery", 2019, false};
    Dummy[16] = {"017", "To All the Boys I've Loved Before", "Jenny Han", "Romance", 2014 ,false};
    Dummy[17] = {"018", "Ikigai", "Francesc Miralles", "Self-Improvement", 2016, false};
    Dummy[18] = {"019", "Project Hail Mary", "Andy Weir", "Sci-Fi", 2021, false};
    Dummy[19] = {"020", "Before I Go to Sleep", "S.J. Watson", "Mystery", 2011, false};

    // Tambahkan semua buku ke linked list
    for (int i = 0; i < 5; i++) {
        tambahbuku(Dummy[i]);
    }
}

nodebuku* cariisbn(char* isbn) {
    nodebuku* current = head;
    while (current != NULL) {
        if (strcmp(current->data.isbn, isbn) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void pinjamBuku() {
    // clearScreen();
    char isbn[20];
    char namaPeminjam[50];
    
    cout << "=== PINJAM BUKU ===" << endl;
    cout << "Masukkan ISBN buku: ";
    cin.ignore();
    cin.getline(isbn, 20);
    
    nodebuku* buku = cariisbn(isbn);
    if (buku == NULL) {
        cout << "Buku tidak ditemukan!" << endl;
        return;
    }
    
    if (buku->data.status) {
        cout << "Buku sedang dipinjam!" << endl;
        return;
    }
    
    cout << "Masukkan nama peminjam: ";
    cin.getline(namaPeminjam, 50);
    
    if (buku->data.status == false) {
        buku->data.status = true;
        cout << "Buku Berhasil Dipinjam" << endl;
        cout << "Selamat Membaca Kak " << namaPeminjam << endl;
    };
    
    saveriwayat("PINJAM", isbn, namaPeminjam);
    cout << "Buku berhasil dipinjam!" << endl;
}

void pengembalianbuku(){
    char isbn[20];
    char namaPeminjam[50];
    
    cout << "=== Pengembalian Buku ===" << endl;
    cout << "Masukkan ISBN buku: ";
    cin.ignore();
    cin.getline(isbn, 20);
    
    nodebuku* buku = cariisbn(isbn);
    if (buku == NULL) {
        cout << "Buku tidak ditemukan!" << endl;
        return;
    }
    
    if (buku->data.status = false) {
        cout << "Buku sedang Tersedia!" << endl;
        return;
    }
    
    cout << "Masukkan nama peminjam: ";
    cin.getline(namaPeminjam, 50);
    
    if (buku->data.status == true){
        buku->data.status = false;
        cout << "Buku Berhasil Dikembalikan" << endl;
        cout << "Terimakasih kak" << namaPeminjam << endl;
    }          
    saveriwayat("KEMBALI", isbn, namaPeminjam);  // Tambahkan ini
}


nodebuku* carijudul(char* judul) {
    nodebuku* current = head;
    while (current != NULL) {
        if (strstr(current->data.judul, judul) != NULL) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}



void search(){
        int pil;

        do
        {
            cout << "Search Buku" << endl;
        cout << "1.Cari By Judul" << endl;
        cout << "2.Cari By ISBN " << endl;
        cout << "0.Keluar" << endl;
        cout << "Masukkan Pilihan : " ; cin >> pil; cin.ignore();

        if (pil == 1)
        {
            char judul[100]; string status;
            cout << "Masukkan judul Yang ingin dicari : " ; cin.getline(judul, 100);
            nodebuku* result = carijudul(judul);
            if (result == NULL)
            {
                cout << "Buku Dengan Judul " << judul << "Tidak Ditemukan" << endl;
            }
            
            else {
                // Header tabel
                cout << "+=======+===============================+===================+=============+==========+=======+" << endl;
                cout << "| " << setw(7) << "ISBN" << " | " << setw(30) << "JUDUL BUKU" << " | " << setw(18) << "PENGARANG"
                     << " | " << setw(12) << "GENRE" << " | " << setw(9) << "TAHUN" << " | STATUS |" << endl;
                cout << "+=======+===============================+===================+=============+==========+=======+" << endl;
                
                // Tampilkan hasilnya
                string status = result->data.status ? "Dipinjam" : "Tersedia";
                cout << "| " << setw(7) << result->data.isbn << " | " << setw(30) << result->data.judul 
                     << " | " << setw(18) << result->data.pengarang << " | " << setw(12) << result->data.genre
                     << " | " << setw(9) << result->data.tahun << " | " << setw(7) << status << " |" << endl;
                
                cout << "+=======+===============================+===================+=============+==========+=======+" << endl;
                stop();
            }
            
        } else if (pil == 2){
            char isbn[10]; string status;
            cout << "Masukkan ISBN Yang ingin dicari : " ; cin.getline(isbn, 100);
            nodebuku* result = cariisbn(isbn);
            if (result == NULL)
            {
                cout << "Buku Dengan ISBN " << isbn << "Tidak Ditemukan" << endl;
            }
            
            else {
                // Header tabel
                cout << "+=======+===============================+===================+=============+==========+=======+" << endl;
                cout << "| " << setw(7) << "ISBN" << " | " << setw(30) << "JUDUL BUKU" << " | " << setw(18) << "PENGARANG"
                     << " | " << setw(12) << "GENRE" << " | " << setw(9) << "TAHUN" << " | STATUS |" << endl;
                cout << "+=======+===============================+===================+=============+==========+=======+" << endl;
                
                // Tampilkan hasilnya
                string status = result->data.status ? "Dipinjam" : "Tersedia";
                cout << "| " << setw(7) << result->data.isbn << " | " << setw(30) << result->data.judul 
                     << " | " << setw(18) << result->data.pengarang << " | " << setw(12) << result->data.genre
                     << " | " << setw(9) << result->data.tahun << " | " << setw(7) << status << " |" << endl;
                
                cout << "+=======+===============================+===================+=============+==========+=======+" << endl;
                stop();
            }
        }
        else if (pil == 0){
            cout << "Kembali Ke Halaman Sebelumnya";
            stop();
        }
        else {
            cout << "Pilih (0-2) saja " ;
        }

        } while (pil != 0);        

}

void savetofile() {
    FILE* file = fopen(databuku, "wb");
    if (file == NULL) {
        cout << "Gagal membuka file untuk penyimpanan!" << endl;
        return;
    }

    nodebuku* current = head;
    while (current != NULL) {
        fwrite(&(current->data), sizeof(Buku), 1, file);
        current = current->next;
    }

    fclose(file);
    cout << "Data berhasil disimpan ke file!" << endl;
}

void readfromfile() {
    FILE* file = fopen(databuku, "rb");
    if (file == NULL) {
        cout << "File tidak ditemukan, menggunakan data dummy..." << endl;
        isiDummy(); // Gunakan data dummy jika file tidak ada
        return;
    }

    // Kosongkan linked list terlebih dahulu
    nodebuku* current = head;
    while (current != NULL) {
        nodebuku* temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = NULL;
    jumlahbuku = 0;

    // Baca data dari file
    Buku tempBuku;
    while (fread(&tempBuku, sizeof(Buku), 1, file) == 1) {
        tambahbuku(tempBuku);
    }

    fclose(file);
    cout << "Data berhasil dimuat dari file!" << endl;
}



void hapusbuku() {
    char isbn[10];
    cout << "Masukkan ISBN buku yang ingin dihapus: ";
    cin.ignore();  // Bersihkan newline sebelumnya
    cin.getline(isbn, 10);
    
    nodebuku* buku = cariisbn(isbn);
    if (buku == NULL) {
        cout << "Buku dengan ISBN " << isbn << " tidak ditemukan!" << endl;
        return;
    }

    // Pindahkan logika penghapusan ke sini (lebih efisien)
    if (buku->data.status) {
        cout << "Buku sedang dipinjam, tidak bisa dihapus!" << endl;
        return;
    }

    if (buku == head && buku == tail) {
        head = tail = NULL;
    } else if (buku == head) {
        head = head->next;
        head->prev = NULL;
    } else if (buku == tail) {
        tail = tail->prev;
        tail->next = NULL;
    } else {
        buku->prev->next = buku->next;
        buku->next->prev = buku->prev;
    }
       
    savebuku("Hapus", isbn, buku->data.judul);

    delete buku;
    jumlahbuku--;
    // savetofile();  // Simpan perubahan ke file
    cout << "Buku berhasil dihapus." << endl;
}


void sortBukuAZ() {
    if (head == NULL || head->next == NULL) {
        return; // Tidak perlu sorting jika list kosong atau hanya 1 elemen
    }

    bool swapped;
    nodebuku* ptr1;
    nodebuku* lptr = NULL;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->data.judul, ptr1->next->data.judul) > 0) {
                // Tukar data antara node saat ini dan node berikutnya
                Buku temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    // savetofile(); // Simpan hasil sorting ke file
    cout << "Buku berhasil diurutkan A-Z berdasarkan judul." << endl;
}


void sortBukuZA() {
    if (head == NULL || head->next == NULL) {
        return; // Tidak perlu sorting jika list kosong atau hanya 1 elemen
    }

    bool swapped;
    nodebuku* ptr1;
    nodebuku* lptr = NULL;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->data.judul, ptr1->next->data.judul) < 0) {
                // Tukar data antara node saat ini dan node berikutnya
                Buku temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    // savetofile(); // Simpan hasil sorting ke file
    cout << "Buku berhasil diurutkan A-Z berdasarkan judul." << endl;
}

void sorttahun1() {
    if (head == NULL || head->next == NULL) {
        return; // Tidak perlu sorting jika list kosong atau hanya 1 elemen
    }

    bool swapped;
    nodebuku* ptr1;
    nodebuku* lptr = NULL;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data.tahun > ptr1->next->data.tahun) {
                // Tukar data antara node saat ini dan node berikutnya
                Buku temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    // savetofile(); // Simpan hasil sorting ke file
    cout << "Buku berhasil diurutkan A-Z berdasarkan judul." << endl;
}


void sorttahun2() {
    if (head == NULL || head->next == NULL) {
        return; // Tidak perlu sorting jika list kosong atau hanya 1 elemen
    }

    bool swapped;
    nodebuku* ptr1;
    nodebuku* lptr = NULL;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data.tahun < ptr1->next->data.tahun) {
                // Tukar data antara node saat ini dan node berikutnya
                Buku temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    // savetofile(); // Simpan hasil sorting ke file
    cout << "Buku berhasil diurutkan A-Z berdasarkan judul." << endl;
}

void sortbygenre(){
        if (head == NULL)
        {
            cout << "Node Kosong" << endl;
        }
          // Meminta input genre dari user
    char genre[50];
    cout << "Pilih Genre untuk Ditampilkan:" << endl;
    cout << "1. Romance" << endl;
    cout << "2. Sci-fi" << endl;
    cout << "3. Self-Improvement" << endl;
    cout << "4. Mistery" << endl;
    cout << "Pilihan: ";
    int choice;
    cin >> choice;
    cin.ignore();  // Membersihkan newline

    // Konversi pilihan ke string genre
    switch(choice) {
        case 1: strcpy(genre, "Romance"); break;
        case 2: strcpy(genre, "Sci-fi"); break;
        case 3: strcpy(genre, "Self-Improvement"); break;
        case 4: strcpy(genre, "Mistery"); break;
        default: 
            cout << "Pilihan tidak valid!" << endl;
            return;
    }
        nodebuku* temp  = head;
        bool f = false;
    cout << "+=======+===============================+===================+=============+==========+=======+" << endl;
    cout << "| " << setw(7) << "ISBN" << " | " << setw(30) << "JUDUL BUKU" << " | " << setw(18) << "PENGARANG"
         << " | " << setw(12) << "GENRE" << " | " << setw(9) << "TAHUN" << " | STATUS |" << endl;
    cout << "+=======+===============================+===================+=============+==========+=======+" << endl;
  
        while (temp != NULL)
        { 
            if (strcmp(temp->data.genre, genre) == 0)
        {
            f = true;
            string status;
    // Simple table content
            if (temp->data.status == false){
                status = "Tersedia";
            } else {
                status = "Dipinjam";
            }
            cout << "| " << setw(7) << temp->data.isbn << " | " << setw(30) << temp->data.judul 
                 << " | " << setw(18) << temp->data.pengarang << " | " << setw(12) << temp->data.genre
                 << " | " << setw(9) << temp->data.tahun << " | "<< status << "|" << endl;
    }
        temp = temp->next;
        }
    cout << "+=======+===============================+===================+=============+==========+=======+" << endl;   
    if (!f)
    {
        cout << "Tidak Ada buku dengan Genre " << genre << "ditemukan" ;
    }
    
}

void sortby(){
    int pil;
    cout << "Filter by / Sort By" << endl;
    cout << "1. Sort By Judul (A-Z) " << endl;
    cout << "2. Sort By Judul (Z-A) " << endl;
    cout << "3. Filter By Genre" << endl;
    cout << "4. Sort By Tahun (terlama)" << endl;
    cout << "5. Sort By Tahun (terbaru)" << endl;
    cout << "0. Keluar" << endl;
    cout << "Masukkan Pilihan : " ; cin >> pil;

    switch (pil)
    {
        case 1:
        sortBukuAZ();
        break;
        case 2:
        sortBukuZA();
        break;
        case 3:
        sortbygenre();
        break;
        case 4:
        sorttahun1();
        break;
        case 5:
        sorttahun2();
        break;
        case 0:
        cout << "Kembali ke halaman sebelumnnya" << endl;
        break;
    default:
        break;
    }

}


void saveriwayat(const char* aksi, const char* isbn, const char* peminjam){
    FILE* file = fopen(RP, "ab");
        if (file == NULL)
        {
            cout << "gagal membuka file riwayat peminjaman" << endl;
            return;
        }
        
        riwayat r ;

        //timestamp;
        time_t now = time(0);
        strftime(r.timestamp, sizeof(r.timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

        //isi data pengguna
        strncpy(r.aksi, aksi, sizeof(r.aksi));
        strncpy(r.isbn, isbn, sizeof(r.isbn));
        strncpy(r.peminjaman, peminjam, sizeof(r.peminjaman));

        fwrite(&r, sizeof(r), 1, file); 

    fclose(file);
    cout <<"Riwayat berhasil ditambahkan";
}

void readriwayat() {
    FILE* file = fopen(RP, "rb");
    if (file == NULL) {
        cout << "Belum ada riwayat peminjaman.\n";
        return;
    }

    riwayat r;
    bool data = false;
    cout << "=== Daftar Riwayat Peminjaman ===" << endl;

    while (fread(&r, sizeof(r), 1, file) == 1) {
        data = true;
        cout << "Timestamp  : " << r.timestamp << "  Aksi       : " << "["<< r.aksi << "]" <<"  ISBN       : " << r.isbn << "   Peminjam   : " << r.peminjaman << endl;
        cout << "------------------------------------------" << endl;
    }

    if(data == false){
        cout << "Belum ada Data" << endl;
    }


    fclose(file);
}

void savebuku(const char* aksi, const char* isbn, const char* judul){
    FILE* file = fopen(RB, "ab");   
        if (file == NULL)
        {
            cout << "gagal membuka file"<< endl;
        }
        
        buku b;

        time_t now = time(0);
        strftime(b.timestamp, sizeof(b.timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
        strncpy(b.aksi, aksi, sizeof(b.aksi));
        strncpy(b.isbn, isbn, sizeof(b.isbn));
        strncpy(b.judul, judul, sizeof(b.judul));
        
        fwrite(&b,sizeof(b), 1, file);

    fclose(file);

}

void readbuku(){
    FILE * file = fopen(RB, "rb");
        if (file == NULL)
        {
            cout << "gagal membuka file"<< endl;
        }
        buku b;

        while (fread(&b, sizeof(b), 1, file) == 1)
        {
            cout << b.timestamp << " " << b.aksi << " " << b.isbn << " " << b.judul << endl;
            cout << "---------------------------------------------------------"<< endl;
        }
        

    fclose(file);


}
