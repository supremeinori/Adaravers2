#include <iostream>
#include <cstring>
using namespace std;

struct vid
{
    string judul;
    int durasi;
    string status;    
};

struct node
{
    vid data;
    node* next;
};

// stack
node* top = NULL;

void push(vid value){
    node* newnode = new node;
    newnode->data = value;
    newnode->next = top;
    top = newnode;
}

void pop(){
    if (top != NULL)
    {
        node* temp = top;
        top = top->next;
        delete temp;
    }
    
}

void displaystack(){
    node* temp = top;
    while (temp != NULL)
    {
        cout << temp->data.judul << endl;
        temp = temp->next;
    }
    
}

//fungsi queue 

node* front = NULL;
node* rear = NULL;

void enqueue(vid value) {
    node* newNode = new node;
    newNode->data = value;
    newNode->next = NULL;
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

void dequeue(){
        if (front != NULL)
        {
            node* temp = front;
            front = front->next;
            if (front == NULL) rear = NULL;
            delete temp;
         }
        
}

void displayqueue(){
    if (front == NULL)
    {
        cout << "Data kosong";
    }
    
    node* temp = front;
    while (temp != NULL)
    {
        cout << "Judul : "<<temp->data.judul << endl;
        temp = temp->next;
    }
    
}



//Binary Search
struct PTB
{
    vid data;
    PTB* left;
    PTB* right;
};

PTB* insert(PTB* root, vid value){
        if (root == NULL)
        {
            root = new PTB;
            root->data = value;
            root->left = root->right = NULL;
        } else if (value.judul < root->data.judul){
            root->left = insert(root->left, value);
        } else {
            root->right = insert(root->right, value);
        }
        return root;
        
} 

void inorder (PTB* root) {
        if (root != NULL)
        {
            inorder(root->left);
            cout << "JUDUL : " <<root->data.judul << "- DURASI : " <<root->data.durasi << " Menit - " << "STATUS : " <<root->data.status << endl;
            inorder(root->right);
        }
    
}

PTB* hapusPTB(PTB* root, string judul) {
    if (root == NULL) return NULL;

    if (judul < root->data.judul) {
        root->left = hapusPTB(root->left, judul);
    } else if (judul > root->data.judul) {
        root->right = hapusPTB(root->right, judul);
    } else {
        // Kasus: node ditemukan
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        } else if (root->left == NULL) {
            PTB* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            PTB* temp = root->left;
            delete root;
            return temp;
        } else {
            PTB* succ = root->right;
            while (succ->left != NULL) {
                succ = succ->left;
            }
            root->data = succ->data;
            root->right = hapusPTB(root->right, succ->data.judul);
        }
    }

    return root;
}


bool Emptystack(){
    return top == NULL;
}

bool Emptyqueue(){
    return front == NULL;
}
enum Aksi {
    TAMBAH_VIDEO,
    HAPUS_VIDEO,
    MASUK_PLAYLIST,
    TONTON_VIDEO
};

struct LogUndo {
    Aksi aksi;
    vid video;
};

struct UndoNode {
    LogUndo data;
    UndoNode* next;
};

UndoNode* undoTop = NULL;

void pushUndo(LogUndo value) {
    UndoNode* newNode = new UndoNode;
    newNode->data = value;
    newNode->next = undoTop;
    undoTop = newNode;
}
void popUndo() {
    if (undoTop != NULL) {
        UndoNode* temp = undoTop;
        undoTop = undoTop->next;
        delete temp;
    }
}

bool emptyUndo() {
    return undoTop == NULL;
}


PTB* carijudul (PTB* root, const string& key){
    if (root == NULL)
    {
        return NULL;
    }
    
    if (key == root->data.judul)
    {
        return root;
    } else if (key < root->data.judul)
    {
        return carijudul(root->left, key); // cari dikiri
    } else {
        return carijudul(root->right, key);
    }
}

void masukplaylist(PTB* root){
        string key;
        inorder(root);
        cout << "Masukkan judul yang ingin dimasukkan Playlist : " ; getline(cin, key);
        PTB* hasil = carijudul(root, key);
        if (hasil != NULL)
        {
            enqueue(hasil->data);
            hasil->data.status = "Dalam Antrean";
            LogUndo log;
            log.aksi = MASUK_PLAYLIST;
            log.video = hasil->data;
            pushUndo(log);
            cout << "Video dengan judul " << key << "Berhasil Masuk Playlist "<< endl;
            
        }
        
}
void dummy(PTB*& root){
    vid video[3];
    video[0] = {"Hitam" , 2, "DEFAULT"};
    video[1] = {"biru" , 2, "DEFAULT"};
    video[2] = {"putih" , 2, "DEFAULT"};

    for (int i = 0; i < 3; i++)
    {
        root = insert(root, video[i]);
    }
    
}






void tontonvideo(PTB* root){
    if (Emptyqueue())
    { 
        cout << "Tidak Ada Di playlist" << endl;
        return;
    }
    
    vid vtonton = front->data; // ini datanya
    dequeue();

    PTB* tonton = carijudul(root, vtonton.judul);
    if (tonton != NULL)
    {
        tonton->data.status = "Sedang Diputar";
    }

    cout << "Video dengan judul " << tonton->data.judul << " Sedang diputar" << endl;
    cout << "+--------------------------------------+" << endl;
    cout << "|                                      |"<< endl;
    cout << "|                                      |"<< endl;
    cout << "|       Anggap kotak ini video         |"<< endl;
    cout << "|                                      |"<< endl;
    cout << "|                                      |"<< endl;
    cout << "+--------------------------------------+"<< endl;
    // stop();

    tonton->data.status = "DEFAULT";
    if (tonton != NULL)
    {
        tonton->data.status = "DEFAULT";
    }
    
    push(vtonton);
    LogUndo log;
    log.aksi = TONTON_VIDEO;
    log.video = vtonton;
    pushUndo(log);
    


}

void clearScreen() {
    system("cls || clear");
}

void stop(){
    cout << "Tekan Enter Untuk Lanjut..."; cin.get(); 
}

void hapusptb(PTB* root)
    {
        string target;
        inorder(root);
        cout << "Masukkan judul video yang ingin dihapus: ";
        getline(cin, target);

        PTB* cek = carijudul(root, target);
        
        if (cek == NULL) {
            cout << "Data tidak ditemukan!" << endl;
        } else {
            LogUndo log;
            log.aksi = HAPUS_VIDEO;
            log.video = cek->data; // cek adalah node yang akan dihapus
            pushUndo(log);
            root = hapusPTB(root, target);
            cout << "Video dengan judul '" << target << "' berhasil dihapus!" << endl;
        }
    }

void undo(PTB*& root) {
    if (emptyUndo()) {
        cout << "Tidak ada aksi yang bisa di-undo\n";
        return;
    }

    LogUndo lastAction = undoTop->data;
    popUndo();

    switch (lastAction.aksi) {
        case TAMBAH_VIDEO: {
            // Undo penambahan video: hapus video
            root = hapusPTB(root, lastAction.video.judul);
            cout << "Undo: Video '" << lastAction.video.judul << "' dihapus\n";
            break;
        }
        case HAPUS_VIDEO: {
            // Undo penghapusan video: tambahkan kembali
            root = insert(root, lastAction.video);
            cout << "Undo: Video '" << lastAction.video.judul << "' dikembalikan\n";
            break;
        }
        case MASUK_PLAYLIST: {
            // Undo penambahan ke playlist: hapus dari playlist
            // Kita perlu cari video di playlist dan hapus
            if (front != NULL) {
                node* prev = NULL;
                node* current = front;
                
                while (current != NULL) {
                    if (current->data.judul == lastAction.video.judul) {
                        // Update status di BST
                        PTB* videoBST = carijudul(root, lastAction.video.judul);
                        if (videoBST != NULL) {
                            videoBST->data.status = "DEFAULT";
                        }
                        
                        // Hapus dari playlist
                        if (prev == NULL) {
                            front = current->next;
                            if (front == NULL) rear = NULL;
                        } else {
                            prev->next = current->next;
                            if (current == rear) rear = prev;
                        }
                        
                        delete current;
                        cout << "Undo: Video '" << lastAction.video.judul << "' dikeluarkan dari playlist\n";
                        return;
                    }
                    prev = current;
                    current = current->next;
                }
            }
            cout << "Video tidak ditemukan di playlist\n";
            break;
        }
        case TONTON_VIDEO: {
            // Undo menonton video: kembalikan ke playlist dan hapus dari riwayat
            // 1. Hapus dari riwayat jika ada
            if (top != NULL && top->data.judul == lastAction.video.judul) {
                pop();
            }
            
            // 2. Tambahkan kembali ke playlist
            enqueue(lastAction.video);
            
            // 3. Update status di BST
            PTB* videoBST = carijudul(root, lastAction.video.judul);
            if (videoBST != NULL) {
                videoBST->data.status = "Dalam Antrean";
            }
            
            cout << "Undo: Video '" << lastAction.video.judul << "' dikembalikan ke playlist\n";
            break;
        }
        default:
            cout << "Aksi tidak dikenali\n";
    }
}


int main (){    
    PTB* root = NULL;
    dummy(root);
    int pil; vid vid;
    int jml = 0;
    do
    {   
        clearScreen();
        cout << "1.Tambah Video" << endl; //V
        cout << "2.Tampilkan Semua Video" << endl; // V
        cout << "3.Tambahkan ke playlist" << endl; //V
        cout << "4.Tonton Video" << endl; //  V
        cout << "5.Riwayat Tontonan" << endl; // V
        cout << "6.Hapus Video" << endl;
        cout << "7.Undo Tindakan Terakhir" << endl;
        cout << "0.Keluar" << endl;
        cout << "Masukka Pilihan : " ; cin >> pil; cin.ignore();

        switch (pil)
        {
        case 1:
            int byk;
            cout << "Masukkan Jumlah video yang ingin ditambahkan : " ; cin >> byk; cin.ignore();
            
            for (int i = 0; i < byk; i++)
            {
            cout << "Masukka data ke-"<< jml+1 << endl;
            bool r = true;
            do
            {
                cout << "Masukkan Judul : " ; getline(cin, vid.judul);
                PTB* hasil = carijudul(root, vid.judul);
            if (hasil != NULL)
            {
                cout << "video dengan judul " << vid.judul << " sudah ada masukkan judul lain" <<endl;
                r = false;
            } else if (hasil == NULL){
                r = true;
            }
               
            } while (r != true);
            
            
            cout << "Masukkan Durasi : " ; cin >> vid.durasi; 
            vid.status = "DEFAULT";
            cout << "Masukkan Status : " << vid.status << endl;    cin.ignore();
            root = insert(root, vid);
             LogUndo log;
            log.aksi = TAMBAH_VIDEO;
            log.video = vid;
            pushUndo(log);
            jml++;
            }
            stop();
            break;
        
        case 2:
            inorder(root);
            char x;
            cout << "Apakah Anda ingin mencari video (y/t)?" ; cin >> x; cin.ignore();
            if (x == 'y' || x == 'Y')
            {
                string key1;
                cout << "Masukkan Judul yang ingin dicari : " ; getline(cin, key1);
                PTB* hasil = carijudul(root, key1);
                if (hasil != NULL)
                {
                    cout << "Video ditemukan" << endl;
                    cout << "Judul : " << hasil->data.judul << endl;
                    cout << "Durasi : " << hasil->data.durasi <<endl;
                    cout << "Status : " << hasil->data.status<< endl;
                } else {
                    cout << "data tidak ditemukan";
                }
                
                
            }
            stop();
            break;
            
        case 3:
                masukplaylist(root);
                stop();
                break;

        case 4 :
                tontonvideo(root);
                stop();
                break;
        case 5 :
                displaystack();
                stop();
        case 6 :
                hapusptb(root);
                stop();
        break;
        case 7 :
                undo(root);
        break;
        default:

            break;
        }

    } while (pil != 0);
    
}