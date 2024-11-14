#include <iostream>
#include <limits> // Untuk clear buffer input
#include <string>
#include <vector>
#include <cmath> // Untuk fungsi sqrt
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;


// STRUCT account - faiz

// STRUCT tempat  - rafif

struct review { // pisah struct & refaktor code 
    string nama_tempat;
    string alamat;
    string review_ulasan;
    int penilaian;
    int id;
};

struct Node {
    review data;
    Node* next;
};

struct StackNode {
    review data;
    StackNode* next;
};

struct QueueNode {
    review data;
    QueueNode* next;
};

void mergeSort(Node *&head, int &callstack);
Node *merge(Node *left, Node *right);
void quickSort(Node *&headRef, int &callstack);
Node *getTail(Node *cur);
Node *quickSortRecur(Node *head, Node *end, int &callstack);
Node *partition(Node *head, Node *end, Node *&newHead, Node *&newEnd, int callstack);
bool compare(Node *a, Node *b);



//fungsi tambah linked list
void tambah_review(Node *&head, int &jumlahLinked) {
    Node *nodeBaru = new Node;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bersihkan buffer sebelum getline
    cout << "Masukkan Nama Tempat: ";
    getline(cin, nodeBaru->data.nama_tempat); 

    cout << "Masukkan Alamat: ";
    getline(cin, nodeBaru->data.alamat); 

    cout << "Masukkan Review/Ulasan: ";
    getline(cin, nodeBaru->data.review_ulasan); 

    cout << "Masukkan Penilaian (1-5): ";
    cin >> nodeBaru->data.penilaian;
    while (nodeBaru->data.penilaian < 1 || nodeBaru->data.penilaian > 5) {
        cout << "Penilaian harus berada di antara 1-5. Silakan masukkan lagi: ";
        cin >> nodeBaru->data.penilaian;
    }
    cin.ignore(); 

    nodeBaru->data.id = ++jumlahLinked;
    nodeBaru->next = nullptr;

    if (head == nullptr) {
        head = nodeBaru;
    } else {
        Node *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = nodeBaru;
    }

    cout << "Review berhasil ditambahkan.\n";
}

//fungsi tambah stack
void tambah_review_stack(StackNode *&top, int &jumlahStack) {
    StackNode *nodeBaru = new StackNode;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bersihkan buffer sebelum getline
    cout << "Masukkan Nama Tempat: ";
    getline(cin, nodeBaru->data.nama_tempat); 

    cout << "Masukkan Alamat: ";
    getline(cin, nodeBaru->data.alamat); 

    cout << "Masukkan Review/Ulasan: ";
    getline(cin, nodeBaru->data.review_ulasan); 

    cout << "Masukkan Penilaian (1-5): ";
    cin >> nodeBaru->data.penilaian;
    while (nodeBaru->data.penilaian < 1 || nodeBaru->data.penilaian > 5) {
        cout << "Penilaian harus berada di antara 1-5. Silakan masukkan lagi: ";
        cin >> nodeBaru->data.penilaian;
    }
    cin.ignore(); 

    nodeBaru->data.id = ++jumlahStack;
    nodeBaru->next = top;
    top = nodeBaru;

    cout << "Review berhasil ditambahkan.\n";
}

// fungsi tambah queue
void tambah_review_queue(QueueNode *&front, QueueNode *&rear, int &jumlahQueue) {
    QueueNode *nodeBaru = new QueueNode;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bersihkan buffer sebelum getline
    cout << "Masukkan Nama Tempat: ";
    getline(cin, nodeBaru->data.nama_tempat); 

    cout << "Masukkan Alamat: ";
    getline(cin, nodeBaru->data.alamat); 

    cout << "Masukkan Review/Ulasan: ";
    getline(cin, nodeBaru->data.review_ulasan); 

    cout << "Masukkan Penilaian (1-5): ";
    cin >> nodeBaru->data.penilaian;
    while (nodeBaru->data.penilaian < 1 || nodeBaru->data.penilaian > 5) {
        cout << "Penilaian harus berada di antara 1-5. Silakan masukkan lagi: ";
        cin >> nodeBaru->data.penilaian;
    }
    cin.ignore(); 

    nodeBaru->data.id = ++jumlahQueue;
    nodeBaru->next = nullptr;

    if (front == nullptr) {
        front = rear = nodeBaru;
    } else {
        rear->next = nodeBaru;
        rear = nodeBaru;
    }

    cout << "Review berhasil ditambahkan.\n";
}
// fungsi liked list menampilkan semua review
void tampilkan_review(Node *head) {
    if (head == nullptr) {
        cout << "Tidak ada review yang ditambahkan.\n";
        return;
    }

    Node *temp = head;
    cout << "ID\tNama Tempat\tAlamat\t\tReview\t\tPenilaian\n";
    while (temp != nullptr) {
        cout << "No. " << temp->data.id << endl;
        cout << "--------------------------------" << endl;
        cout << "Nama Tempat : " << temp->data.nama_tempat << endl;
        cout << "Alamat      : " << temp->data.alamat << endl;
        cout << "Review      : " << temp->data.review_ulasan << endl;
        cout << "Penilaian   : " << temp->data.penilaian << endl;
        cout << "  " << endl;
        temp = temp->next;
    }
}
//fungsi stack menampilkan review
void tampilkan_review_stack(StackNode *top){
    if (top == nullptr) {
        cout << "Tidak ada review yang ditambahkan.\n";
        return;
    }

    StackNode *temp = top;
    cout << "ID\tNama Tempat\tAlamat\t\tReview\t\tPenilaian\n";
    while (temp != nullptr) {
        cout << "No. " << temp->data.id << endl;
        cout << "--------------------------------" << endl;
        cout << "Nama Tempat : " << temp->data.nama_tempat << endl;
        cout << "Alamat      : " << temp->data.alamat << endl;
        cout << "Review      : " << temp->data.review_ulasan << endl;
        cout << "Penilaian   : " << temp->data.penilaian << endl;
        cout << "  " << endl;
        temp = temp->next;
    }
}

//fungsi queue menampilkan review
void tampilkan_review_queue(QueueNode *front){
    if (front == nullptr) {
        cout << "Tidak ada review yang ditambahkan.\n";
        return;
    }

    QueueNode *temp = front;
    cout << "ID\tNama Tempat\tAlamat\t\tReview\t\tPenilaian\n";
    while (temp != nullptr) {
        cout << "No. " << temp->data.id << endl;
        cout << "--------------------------------" << endl;
        cout << "Nama Tempat : " << temp->data.nama_tempat << endl;
        cout << "Alamat      : " << temp->data.alamat << endl;
        cout << "Review      : " << temp->data.review_ulasan << endl;
        cout << "Penilaian   : " << temp->data.penilaian << endl;
        cout << "  " << endl;
        temp = temp->next;
    }
}

// fungsi untuk memperbarui ID habis penghapusan
void perbarui_id(Node *&head) {
    Node *temp = head;
    int id_baru = 1;

    while (temp != nullptr) {
        temp->data.id = id_baru; // Update ID dengan urutan yang benar
        id_baru++;
        temp = temp->next;
    }
}

// fungsi untuk mengupdate 
void update_review(Node *&head) {
    if (head == nullptr) {
        cout << "Tidak ada review untuk diubah.\n";
        return;
    }

    tampilkan_review(head);  // Memanggil fungsi untuk menampilkan semua review

    int id;
    cout << "Masukkan ID review yang ingin diubah: ";
    cin >> id;

    Node *temp = head;
    while (temp != nullptr && temp->data.id != id) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Review dengan ID tersebut tidak ditemukan.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer

    cout << "Masukkan Nama Tempat baru: ";
    getline(cin, temp->data.nama_tempat); 

    cout << "Masukkan Alamat baru: ";
    getline(cin, temp->data.alamat); 

    cout << "Masukkan Review/Ulasan baru: ";
    getline(cin, temp->data.review_ulasan); 

    cout << "Masukkan Penilaian baru (1-5): ";
    cin >> temp->data.penilaian;

    cout << "Review berhasil diupdate.\n";
}

// fungsi untuk menghapus 
void menghapus_review(Node *&head, int &jumlahLinked) {
    if (head == nullptr) {
        cout << "Tidak ada review yang ditambahkan.\n";
        return;
    }
    
    tampilkan_review(head);  // memanggil fungsi untuk menampilkan semua review
    
    int id;
    cout << "Masukkan ID review yang ingin dihapus: ";
    cin >> id;

    Node *temp = head;
    Node *prev = nullptr;

    // mencari node dengan ID yang sesuai
    while (temp != nullptr && temp->data.id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Review dengan ID tersebut tidak ditemukan.\n";
        return;
    }

    // menghapus node
    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
    jumlahLinked--; // mengurangi jumlah linked list setelah penghapusan

    // perbarui ID setelah penghapusan
    perbarui_id(head);

    cout << "Review berhasil dihapus.\n";
}

/////////BAGIAN MERGE SORT///////////

/////////BAGIAN MERGE SORT///////////

// Fungsi Merge Sort untuk mengurutkan secara ascending berdasarkan ID
void mergeSort(Node *&head, int &callstack)
{
    callstack++;
    cout << "Callstack " << callstack << " : Start\n";
    if (!head || !head->next)
    {
        cout << "Callstack " << callstack << " : End\n";
        callstack--;
        return;
    }

    // Divide
    cout << "Callstack " << callstack << " : Divide\n";
    Node *slow = head, *fast = head->next;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node *mid = slow->next;
    slow->next = nullptr;

    // Recursive Sort
    mergeSort(head, callstack);
    mergeSort(mid, callstack);

    // Conquer
    cout << "Callstack " << callstack << " : Conquer\n";
    head = merge(head, mid);
    cout << "Callstack " << callstack << " : End\n";
    callstack--;
}

// Fungsi Merge untuk menggabungkan dua bagian terurut
Node *merge(Node *left, Node *right)
{
    // temp sebagai head sementara yang kosong untuk diisi hasil sort
    Node *temp = new Node;
    Node *tail = temp;
    while (left && right)
    {
        if (left->data.id <= right->data.id) // Urutkan berdasarkan ID secara ascending
        {
            // Addfirst
            tail->next = left;
            left = left->next;
        }
        else
        {
            // Addlast
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }

    // Sisa node yang belum diurutkan
    tail->next = left ? left : right;

    Node *result = temp->next;
    delete temp;
    return result;
}

/////////BAGIAN QUICK SORT///////////

// Fungsi Quick Sort untuk mengurutkan secara descending berdasarkan ID
void quickSort(Node *&headRef, int &callstack)
{
    headRef = quickSortRecur(headRef, getTail(headRef), callstack);
    return;
}

Node *getTail(Node *cur)
{
    while (cur && cur->next)
    {
        cur = cur->next;
    }
    return cur;
}

Node *quickSortRecur(Node *head, Node *end, int &callstack)
{
    callstack++;
    cout << "Callstack " << callstack << " : Start\n";
    if (!head || head == end)
    {
        cout << "Callstack " << callstack << " : End\n";
        callstack--;
        return head;
    }

    // Divide and Conquer
    Node *newHead = nullptr, *newEnd = nullptr;
    cout << "Callstack " << callstack << " : Divide\n";
    Node *pivot = partition(head, end, newHead, newEnd, callstack);

    // Multiple Divide and Conquer (Recur)
    if (newHead != pivot)
    {
        Node *tmp = newHead;
        while (tmp->next != pivot)
        {
            tmp = tmp->next;
        }
        tmp->next = nullptr;
        newHead = quickSortRecur(newHead, tmp, callstack);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }
    pivot->next = quickSortRecur(pivot->next, newEnd, callstack);
    cout << "Callstack " << callstack << " : End\n";
    callstack--;
    return newHead;
}

Node *partition(Node *head, Node *end, Node *&newHead, Node *&newEnd, int callstack)
{
    Node *pivot = end;
    Node *prev = nullptr, *cur = head, *tail = pivot;

    cout << "Callstack " << callstack << " : Conquer\n";
    while (cur != pivot)
    {
        if (compare(cur, pivot))
        {
            // Addfirst
            if (newHead == nullptr)
            {
                newHead = cur;
            }
            prev = cur;
            cur = cur->next;
        }
        else
        {
            // Addlast
            if (prev)
            {
                prev->next = cur->next;
            }
            Node *tmp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if (newHead == nullptr)
    {
        newHead = pivot;
    }
    newEnd = tail;
    return pivot;
}

bool compare(Node *a, Node *b)
{
    return a->data.id > b->data.id; // Perbandingan descending berdasarkan ID
}

/////////BAGIAN SEARCH///////////

int min(int x, int y) {
    return (x <= y) ? x : y;
}

void fibonacciSearch(Node *head, int x) {
    if (head == nullptr) {
        cout << "Tidak ada review yang ditambahkan.\n";
        return;
    }
    // Membuat array dari linked list
    if (x < 1 || x > 5) {
        cout << "Penilaian harus berada di antara 1-5.\n";
        return;
    }

    vector<Node*> nodes;
    Node *temp = head;
    while (temp != nullptr) {
        nodes.push_back(temp);
        temp = temp->next;
    }

    int n = nodes.size();
    // Fibonacci numbers
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;
    // Mencari nilai Fibonacci yang paling kecil yang lebih besar atau sama dengan n
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
    // Offset untuk memeriksa elemen terakhir
    int offset = -1;
    bool found = false;
    // Melakukan pencarian
    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (nodes[i]->data.penilaian < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (nodes[i]->data.penilaian > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else {
            cout << "Review ditemukan:\n";
            cout << "ID: " << nodes[i]->data.id << "\n";
            cout << "Nama Tempat: " << nodes[i]->data.nama_tempat << "\n";
            cout << "Alamat: " << nodes[i]->data.alamat << "\n";
            cout << "Review: " << nodes[i]->data.review_ulasan << "\n";
            cout << "Penilaian: " << nodes[i]->data.penilaian << "\n";
            found = true;

            // Lanjutkan pencarian dengan mengurangi nilai Fibonacci
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
    }

    // Cek elemen terakhir jika cocok dengan nilai yang dicari
    if (!found && fibMMm1 && offset + 1 < n && nodes[offset + 1]->data.penilaian == x) {
        cout << "Review ditemukan:\n";
        cout << "ID: " << nodes[offset + 1]->data.id << "\n";
        cout << "Nama Tempat: " << nodes[offset + 1]->data.nama_tempat << "\n";
        cout << "Alamat: " << nodes[offset + 1]->data.alamat << "\n";
        cout << "Review: " << nodes[offset + 1]->data.review_ulasan << "\n";
        cout << "Penilaian: " << nodes[offset + 1]->data.penilaian << "\n";
        found = true;
    }

    if (!found) {
        cout << "Review dengan penilaian " << x << " tidak ditemukan.\n";
    }
}

void jumpSearch(Node *head, int x) {
    if (head == nullptr) {
        cout << "Tidak ada review yang ditambahkan.\n";
        return;
    }

    if (x < 1 || x > 5) {
        cout << "Penilaian harus berada di antara 1-5.\n";
        return;
    }
    // Membuat array dari linked list
    vector<Node*> nodes;
    Node *temp = head;
    while (temp != nullptr) {
        nodes.push_back(temp);
        temp = temp->next;
    }
    // Mencari review dengan penilaian x
    int n = nodes.size();
    int step = sqrt(n);
    int prev = 0;

    // Melakukan jump search
    while (nodes[min(step, n) - 1]->data.penilaian < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            cout << "Review dengan penilaian " << x << " tidak ditemukan.\n";
            return;
        }
    }
    // Melakukan linear search
    bool found = false;
    while (prev < min(step, n) && nodes[prev]->data.penilaian <= x) {
        if (nodes[prev]->data.penilaian == x) {
            cout << "Review ditemukan:\n";
            cout << "ID: " << nodes[prev]->data.id << "\n";
            cout << "Nama Tempat: " << nodes[prev]->data.nama_tempat << "\n";
            cout << "Alamat: " << nodes[prev]->data.alamat << "\n";
            cout << "Review: " << nodes[prev]->data.review_ulasan << "\n";
            cout << "Penilaian: " << nodes[prev]->data.penilaian << "\n";
            found = true;
        }
        prev++;
    }

    if (!found) {
        cout << "Review dengan penilaian " << x << " tidak ditemukan.\n";
    }
}



void boyermooreSearch(Node *head, const string &pattern) {
    if (head == nullptr) {
        cout << "Tidak ada review yang ditambahkan.\n";
        return;
    }
    // Membuat array dari linked list
    int m = pattern.size();
    if (m == 0) {
        cout << "Pola pencarian tidak boleh kosong.\n";
        return;
    }

    // ubah jadi huruf kecil
    string lowerPattern = pattern;
    transform(lowerPattern.begin(), lowerPattern.end(), lowerPattern.begin(), ::tolower);

    // tabel bad character
    vector<int> badChar(256, -1);
    for (int i = 0; i < m; i++) {
        badChar[(int)lowerPattern[i]] = i;
    }

    Node *temp = head;
    bool found = false;

    while (temp != nullptr) {
        // ubah text menjadi huruf kecil
        string text = temp->data.nama_tempat;
        string lowerText = text;
        transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);

        int n = lowerText.size();
        int s = 0; // s adalah pergeseran dari pola terhadap teks

        while (s <= (n - m)) {
            int j = m - 1;

            // kurangi indeks j dari akhir ke awal
            while (j >= 0 && lowerPattern[j] == lowerText[s + j]) {
                j--;
            }
            // jika j < 0, berarti pattern ditemukan
            if (j < 0) {
                cout << "Review ditemukan:\n";
                cout << "ID: " << temp->data.id << "\n";
                cout << "Nama Tempat: " << temp->data.nama_tempat << "\n";
                cout << "Alamat: " << temp->data.alamat << "\n";
                cout << "Review: " << temp->data.review_ulasan << "\n";
                cout << "Penilaian: " << temp->data.penilaian << "\n";
                found = true;
                break;
            } else {

                s += max(1, j - badChar[(int)lowerText[s + j]]);
            }
        }

        temp = temp->next;
    }

    if (!found) {
        cout << "Review dengan nama tempat \"" << pattern << "\" tidak ditemukan.\n";
    }
}


int main() {
    Node *head = nullptr;
    StackNode *top = nullptr;
    int callstack = 0;
    QueueNode *front = nullptr, *rear = nullptr;
    int jumlahLinked = 0 , jumlahStack = 0 , jumlahQueue = 0;
    int pilihan;
    string pattern;
    
    while (true) {
        cout << "\nMenu Review Tempat\n";
        cout << "1. Menambahkan Review\n";
        cout << "2. Melihat Review\n";
        cout << "3. Mengedit Review\n";
        cout << "4. Menghapus Review\n";
        cout << "5. Mengurutkan Review\n";
        cout << "6. Mencari Review\n";
        cout << "7. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                cout << "Pilih Fungsi untuk menambahkan review:\n";
                cout << "1. Linked List\n";
                cout << "2. Stack\n";
                cout << "3. Queue\n";
                int pilihan_fungsi;
                cout << "Pilihan: ";
                cin >> pilihan_fungsi;
                switch (pilihan_fungsi) {
                    case 1:
                        tambah_review(head, jumlahLinked);
                        break;
                    case 2:
                        tambah_review_stack(top, jumlahStack);
                        break;
                    case 3:
                        tambah_review_queue(front, rear, jumlahQueue);
                        break;
                    default:
                        cout << "Pilihan tidak valid.\n";
                }
                break;
            }
            case 2: {
                cout << "Pilih Fungsi untuk melihat review:\n";
                cout << "1. Linked List\n";
                cout << "2. Stack\n";
                cout << "3. Queue\n";
                int pilihan_fungsi;
                cout << "Pilihan: ";
                cin >> pilihan_fungsi;
                switch (pilihan_fungsi) {
                    case 1:
                        tampilkan_review(head);
                        break;
                    case 2:
                        tampilkan_review_stack(top);
                        break;
                    case 3:
                        tampilkan_review_queue(front);
                        break;
                    default:
                        cout << "Pilihan tidak valid.\n";
                }
                break;
            }
                break;
            case 3:
                update_review(head);
                break;
            case 4:
                menghapus_review(head, jumlahLinked);
                break;
            case 5: {
                cout << "Pilih Algoritma Pengurutan review:\n";
                cout << "1. Merge Sort(Ascending)\n";
                cout << "2. Quick Sort(Descending)\n";
                int pilihan_sort;
                cout << "Pilihan: ";
                cin >> pilihan_sort;
                switch (pilihan_sort) {
                    case 1:
                        mergeSort(head, callstack);
                        tampilkan_review(head);
                        break;
                    case 2:
                        quickSort(head, callstack);
                        tampilkan_review(head);
                        break;
                    default:
                        cout << "Pilihan tidak valid.\n";
                }
                break;
            }
            case 6:
                cout << "Pilih Fungsi untuk mencari review:\n";
                cout << "1. Fibonacci Search\n";
                cout << "2. Jump Search\n";
                cout << "3. Boyer-Moore\n";
                int pilihan_fungsi;
                cout << "Pilihan: ";
                cin >> pilihan_fungsi;
                switch (pilihan_fungsi) {
                    case 1:
                        int penilaian;
                        cout << "Masukkan penilaian yang ingin dicari (1-5): ";
                        cin >> penilaian;
                        fibonacciSearch(head, penilaian);
                        break;
                    case 2:
                        cout << "Masukkan penilaian yang ingin dicari (1-5): ";
                        cin >> penilaian;
                        jumpSearch(head, penilaian);
                        break;
                    case 3:
                        cout << "Masukkan nama tempat yang ingin dicari: ";
                        cin.ignore();
                        getline(cin, pattern);
                        boyermooreSearch(head, pattern);
                        break;

                    default:
                        cout << "Pilihan tidak valid.\n";
                        break;
                }
                break;
            case 7:
                cout << "Keluar dari program.\n";
                return 0;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    }

    return 0;
}