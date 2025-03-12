#include <iostream>
#include <fstream>
#include <cstring> // strcmp
using namespace std;

    struct Mhs{
        char nama[50];
        int nim;
        char jurusan[20];
        int thn;
        float ipk;
    };
    void addmahasiswa();
    void show_data();
    void search_databynim();
    void search_databys();
    void update_ipk();
    void simpankefile();
    void bacafile();
    void bubblesort();
    void delete_data();
    int binarysearch(int key);
    void quicksort();

    int const MAX = 100;
    Mhs m[MAX];
    int jmlmhs = 0;



int main () {
    int pil;
    do
    {
    cout << "1. Manambahkan Mahasiswa Baru" << endl;
    cout << "2. Menampilkan Data Mahasiswa" << endl;
    cout << "3. Mencari Data Mahasiswa Berdasarkan NIM (Binary search & Quick Sort)" << endl;
    cout << "4. Mencari Data Mahasiswa Berdasarkan Jurusan" << endl;
    cout << "5. Memperbarui IPK Mahasiswa" << endl;
    cout << "6. Menghapus Data Mahasiswa dari database" << endl;
    cout << "7. Keluar Dari Program" << endl;
    cout << "Pilih Menu : "; cin >> pil;

    switch (pil)
    {
    case 1:addmahasiswa();break;
    case 2:show_data();break;
    case 3:search_databynim();break;
    case 4:search_databys();break;
    case 5:update_ipk();break;
    case 6:delete_data();break;
    case 7:
        cout << "Terimakasih Telah Menggunakan Program Kami semoga lancar studynya";
        break;
    default:
        cout << "Harap Pilih 1-7 saja ya" << endl;
        break;
    }
    } while (pil != 7);
}


   void addmahasiswa(){
    if (jmlmhs >= MAX)
    {
        cout << "Database Penuh" << endl;
        return;
    }
    Mhs *ptrm = &m[jmlmhs];
    int byk;
    cout << "Masukkan Jumlah Mahasiswa : "; cin >> byk;
    for (int i = 0; i < byk; i++)
    {
        cout << "Data Ke-" << i + 1 << endl;
        cout << "Masukkan Nama : "; cin.getline(ptrm->nama, 50);
        cin.ignore();
        cout << "Masukkan NIM : "; cin >> ptrm->nim; cin.ignore();
        cout << "Masukkan Jurusan : " ; cin.getline(ptrm->jurusan, 20);
        cout << "Masukkan Tahun Masuk : "; cin >> ptrm->thn; cin.ignore();
        ptrm->ipk = 0.0;
        ptrm++;
        jmlmhs++;
        // jangan lupa untuk kasih ptrm++; untuk nambah arraynya
    }
    simpankefile();

    cout << "Mahasiswa Berhasil Ditambahkan!\n";
   };
    void show_data(){;
        if (jmlmhs == 0)
        {
            cout << "database kosong isi dulu databasenya";
        }

        bubblesort();
        cout << "Data Mahasiswa\n";
        for (int i = 0; i < jmlmhs; i++)
        {
            cout << "NIM : " << m[i].nim << endl;
            cout << "Nama : " << m[i].nama << endl;
            cout << "Jurusan : " << m[i].jurusan << endl;
            cout << "IPK : " << m[i].ipk << endl;
            cout << "Tahun Masuk : " << m[i].thn << endl;
        }
    }
    void search_databynim(){
        if (jmlmhs == 0)
        {
            cout << "database kosong isi dulu databasenya";
            return;
        }
        int key;
        cout << "Masukkan NIM yang dicari : "; cin >> key;
        bubblesort();
        int index = binarysearch(key);
        if (index != -1)
        {
            cout << "Mahasiswa ditemukan!\n";
            cout << "NIM : " << m[index].nim << endl;
            cout << "Nama : " << m[index].nama << endl;
            cout << "Jurusan : " << m[index].jurusan << endl;
            cout << "IPK : " << m[index].ipk << endl;
            cout << "Tahun Masuk : " << m[index].thn << endl;
        } else {
            cout << "Mahasiswa dengan nim" << key << "tidak ditemukan!\n";
        }
    }
    void search_databys(){
        if (jmlmhs == 0)
        {
            cout << "database kosong" << endl;
        }
        char jur[20];
        cout << "Masukkan Jurusan yang dicari : ";
        cin.ignore();
        cin.getline(jur, sizeof(jur));
        bool found = false;
         for (int i = 0; i < jmlmhs; i++)
         {
            // strcmp jika mau membandingan char
            if (strcmp(m[i].jurusan, jur) == 0)
            {
                cout << "Mahasiswa ditemukan!\n";
                cout << "NIM : " << m[i].nim << endl;
                cout << "Nama : " << m[i].nama << endl;
                cout << "Jurusan : " << m[i].jurusan << endl;
                cout << "IPK : " << m[i].ipk << endl;
                cout << "Tahun Masuk : " << m[i].thn << endl;
            }
            
            
         }
         if (!found)
            {
                cout << "Mahasiswa dengan jurusan" << jur << "tidak ditemukan!\n";
            }
    };
     
    int binarysearch(int key){
        int i = 0, j = jmlmhs - 1, mid;
        while (i <= j){
            mid = (i + j) / 2;
            if (m[mid].nim == key){
                return mid;
            }
            else if (m[mid].nim < key) i = mid + 1;
                else j = mid - 1;
        }
        return -1;
    }
        
    
    

    void update_data();
    void delete_data();
    void bubblesort();
    void quicksort();

   void simpanfile() {
    ofstream file("Mahasiswa.dat", ios::binary);
    file.write((char*) &jmlmhs, sizeof(jmlmhs)); // Simpan jumlah mahasiswa
    file.write((char*) m, jmlmhs * sizeof(Mhs)); // Simpan hanya data yang ada
    file.close();
   }
    void bacafile() {
    ifstream file("Mahasiswa.dat", ios::binary);
    if (file) {
        file.read((char*) &jmlmhs, sizeof(jmlmhs)); // Baca jumlah mahasiswa
        file.read((char*) m, jmlmhs * sizeof(Mhs)); // Baca hanya data yang ada
    }
    file.close();
}