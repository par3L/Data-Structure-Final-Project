#include <iostream>
#include <limits> // untuk clear buffer input
#include <string>
#include <vector>
#include <cmath> // untuk fungsi sqrt
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <map> // mapping file external

using namespace std;

string session; // track user yang login

struct Akun
{ // placeholder info akun, no linked list
    string username;
    string email;
    string password;
};

struct review // yes linked list
{
    string id;
    string user;
    string ulasan;
    int penilaian;
};
struct Node // nodes
{
    review data;
    Node *next;
};

struct tempat // also yes linked list
{
    string kode;
    string nama_tempat;
    string owner_tempat;
    string alamat;
    string deskripsi_tempat;
};

struct NodeTempat
{ // nodes
    tempat data;
    int review_count;
    NodeTempat *next;
};

struct StackNode
{
    review data;
    StackNode *next;
};

struct QueueNode
{
    review data;
    QueueNode *next;
};

// prototype-prototypean
bool containsChar(const string &str, char c);
bool isValidEmail(const string &email);
void saveAccount(const Akun &account);
bool existsInCSV(const string &key, int column);
bool registerAccount();
bool validateLogin(const string &userOrEmail, const string &password);
bool login();
void menuLogin();

int autoIncrementKode();
void tambah_tempat(NodeTempat *&head, int &jumlahLinked);
void tampilkan_tempat(NodeTempat *&head);
void addReview(Node *&head, const string &username, const string &kode, NodeTempat *&placesHead);
void displayPlaceReviews(Node *head, const string &kode);
void displayUserReviews(Node *head, string &username);
void mergeSort(NodeTempat *&head);
NodeTempat *merge(NodeTempat *left, NodeTempat *right);
NodeTempat *getTail(NodeTempat *cur);
NodeTempat *partition(NodeTempat *head, NodeTempat *end, NodeTempat *&newHead, NodeTempat *&newEnd);
void quickSort(NodeTempat *&head);
NodeTempat *quickSortRecur(NodeTempat *head, NodeTempat *end);
void SortbyReviews(NodeTempat *&placesHead, bool flag = true);
void boyerMooreSearch(NodeTempat *head, const string &pattern);
int fibonacciSearch(vector<Node *> &reviews, const string &reviewID);
void updateReviewInFile(const string &username, const string &reviewID);
int jumpSearch(vector<Node *> &reviews, const string &reviewID);
void deleteReviewFromFile(const string &username, const string &reviewID);
void editSection(Node *&head, const string &user);
void reviewSection(Node *head, NodeTempat *placesHead);
void mainMenu(NodeTempat *&placesHead, Node *head, int jumlahLinked);
void pushToStack(StackNode *&top, const review &data);
void enqueueToQueue(QueueNode *&front, QueueNode *&rear, const review &data);
void loadStackQueue(StackNode *&stackTop, QueueNode *&queueFront, QueueNode *&queueRear);
void displayStack(StackNode *top);
void displayQueue(QueueNode *front);

int main()
{
    menuLogin();
    NodeTempat *placesHead = nullptr;
    Node *head = nullptr;
    int jumlahLinked = 0;
    mainMenu(placesHead, head, jumlahLinked);
    return 0;
}

void menuLogin()
{
    int choice;
    bool flag = true;

    while (flag)
    {
        cout << "Welcome!\n";
        cout << "1. Register\n2. Login\n3. Exit\nPilihan: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (registerAccount())
            {
                cout << "Silahkan Login.\n";
            }
            break;
        case 2:
            flag = login();
            break;
        case 3:
            cout << "Terimakasih. Goodbye!\n";
            exit(0);
        default:
            cout << "Pilihan invalid. Coba lagi...\n";
        }
    }
}

// isi main menu
void mainMenu(NodeTempat *&placesHead, Node *head, int jumlahLinked)
{
    int choice;
    bool flag = true;

    while (flag)
    {
        cout << "Main Menu\n";
        cout << "1. Lihat Tempat\n";
        cout << "2. Tambah Tempat\n";
        cout << "3. Review Saya\n";
        cout << "4. Stack & Queue\n";
        cout << "5. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            tampilkan_tempat(placesHead);
            reviewSection(head, placesHead);
            break;
        case 2:
            tambah_tempat(placesHead, jumlahLinked);
            break;
        case 3:
            displayUserReviews(head, session);
            editSection(head, session);
            break;
        case 4:
        {
            StackNode *stackTop = nullptr;
            QueueNode *queueFront = nullptr, *queueRear = nullptr;
            loadStackQueue(stackTop, queueFront, queueRear);
            cout << "1. Tampilkan dengan Stack (LIFO)\n";
            cout << "2. Tampilkan dengan Queue (FIFO)\n";
            cout << "Pilihan: ";
            int subChoice;
            cin >> subChoice;
            if (subChoice == 1)
            {
                displayStack(stackTop);
            }
            else if (subChoice == 2)
            {
                displayQueue(queueFront);
            }
            else
            {
                cout << "Pilihan tidak valid.\n";
            }
            while (stackTop != nullptr)
            {
                StackNode *temp = stackTop;
                stackTop = stackTop->next;
                delete temp;
            }
            while (queueFront != nullptr)
            {
                QueueNode *temp = queueFront;
                queueFront = queueFront->next;
                delete temp;
            }
            break;
        }

        case 5:
            flag = false;
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }
    }
}

void reviewSection(Node *head, NodeTempat *placesHead)
{
    int choice, subchoice;
    string pattern, kode;
    cout << "1. Lihat Review Tempat\n";
    cout << "2. Sort Tempat\n";
    cout << "3. Cari Tempat\n";
    cout << "Pilihan: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        tampilkan_tempat(placesHead);
        cout << "Input Kode :";
        cin >> kode;
        displayPlaceReviews(head, kode);
        cout << "Ingin meninggalkan Review?\n";
        cout << "1. Ya\n";
        cout << "2. Tidak\n";
        cin >> subchoice;
        if (subchoice == 1)
        {
            addReview(head, session, kode, placesHead);
        }
        break;
    case 2:
        cout << "1. Sort Ascending (Merge Sort)\n";
        cout << "2. Sort Descending (Quick Sort)\n";
        cout << "Pilih metode sorting (berdasarkan jumlah review): ";
        int sortChoice;
        cin >> sortChoice;
        if (sortChoice == 1)
        {
            SortbyReviews(placesHead, true);
        }
        else if (sortChoice == 2)
        {
            SortbyReviews(placesHead, false);
        }
        tampilkan_tempat(placesHead);
        cout << "Tempat disortir.\n";
        break;
    case 3:
        cout << "Cari nama tempat: ";
        cin.ignore();
        getline(cin, pattern);
        boyerMooreSearch(placesHead, pattern);
        break;
    default:
        cout << "Pilihan invalid.\n";
    }
}

// cek chars ada di sebuah string
bool containsChar(const string &str, char c)
{
    return str.find(c) != string::npos;
}

// email format
bool isValidEmail(const string &email)
{
    return containsChar(email, '@') && containsChar(email, '.');
}

// push ke accounts.csv
void saveAccount(const Akun &account)
{
    ofstream file("accounts.csv", ios::app);
    if (file.is_open())
    {
        file << account.username << "," << account.email << "," << account.password << "\n";
        file.close();
        cout << "Akun berhasil di daftarkan!\n";
    }
    else
    {
        cout << "Error: file tidak berhasil di buka.\n";
    }
}

// cek credentials ada di .csv atau tidak
bool existsInCSV(const string &key, int column)
{
    ifstream file("accounts.csv");
    string line, word;
    while (getline(file, line))
    {
        stringstream ss(line);
        int currentColumn = 0;
        while (getline(ss, word, ','))
        {
            if (currentColumn == column && word == key)
            {
                return true;
            }
            currentColumn++;
        }
    }
    return false;
}

// Register
bool registerAccount()
{
    Akun newAccount;
    string confirmPassword;

    cout << "Username: ";
    cin >> newAccount.username;

    // cek username ada atau tidak
    if (existsInCSV(newAccount.username, 0))
    {
        cout << "Username sudah ada! coba yag lain.\n";
        return false;
    }

    cin.ignore(); // clear input buffer
    cout << "Email (optional, Enter to skip): ";
    getline(cin, newAccount.email);
    newAccount.email = newAccount.email.empty() ? "~" : newAccount.email;

    // validasi email (kalau ada inputan)
    if (newAccount.email != "~" && (!isValidEmail(newAccount.email) || existsInCSV(newAccount.email, 1)))
    {
        cout << "Email sudah ada atau invalid! Coba lagi...\n";
        return false;
    }

    // setup password
    do
    {
        cout << "Password (minimum 6 characters): ";
        cin >> newAccount.password;
        if (newAccount.password.length() < 6)
        {
            cout << "Password terlalu pendek! Minimum 6 karakter.\n";
        }
    } while (newAccount.password.length() < 6);

    // konfirmasi password
    cout << "Konfirmasi password: ";
    cin >> confirmPassword;
    if (newAccount.password != confirmPassword)
    {
        cout << "Password tidak sama! Coba lagi ...\n";
        return false;
    }

    saveAccount(newAccount);
    return true;
}

// validasi login
bool validateLogin(const string &userOrEmail, const string &password)
{
    ifstream file("accounts.csv");
    string line, word;
    while (getline(file, line))
    {
        stringstream ss(line);
        vector<string> userData;
        while (getline(ss, word, ','))
        {
            userData.push_back(word);
        }
        if ((userData[0] == userOrEmail || userData[1] == userOrEmail) && userData[2] == password)
        {
            session = userData[0];
            cout << "Login berhasil! Selamat datang, " << session << "!\n";
            return false;
        }
    }
    cout << "Username/email atau password invalid!\n";
    return true;
}

// Login fungsi
bool login()
{
    string userOrEmail, password;

    cout << "Login :\n";
    cout << "Username / Email: ";
    cin >> userOrEmail;
    cout << "Password: ";
    cin >> password;

    return validateLogin(userOrEmail, password);
}

void pushToStack(StackNode *&top, const review &data)
{
    StackNode *newNode = new StackNode;
    newNode->data = data;
    newNode->next = top;
    top = newNode;
}

void enqueueToQueue(QueueNode *&front, QueueNode *&rear, const review &data)
{
    QueueNode *newNode = new QueueNode;
    newNode->data = data;
    newNode->next = nullptr;
    if (rear == nullptr)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

void loadStackQueue(StackNode *&stackTop, QueueNode *&queueFront, QueueNode *&queueRear)
{
    ifstream file("reviews.csv");
    if (!file.is_open())
    {
        cout << "Error: Tidak dapat membuka file reviews.csv.\n";
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        review rev;
        getline(ss, rev.id, ',');
        getline(ss, rev.user, ',');
        getline(ss, rev.ulasan, ',');
        ss >> rev.penilaian;

        // Tambahkan ke Stack dan Queue
        pushToStack(stackTop, rev);
        enqueueToQueue(queueFront, queueRear, rev);
    }
    file.close();
}

void displayStack(StackNode *top)
{
    if (top == nullptr)
    {
        cout << "Stack kosong. Tidak ada review untuk ditampilkan.\n";
        return;
    }

    cout << "\nReviews (LIFO - Stack):\n";
    while (top != nullptr)
    {
        cout << "User: " << top->data.user << endl;
        cout << "Review: " << top->data.ulasan << endl;
        cout << "Rating: " << top->data.penilaian << "/5\n";
        cout << "----------------------------------\n";
        top = top->next;
    }
}

void displayQueue(QueueNode *front)
{
    if (front == nullptr)
    {
        cout << "Queue kosong. Tidak ada review untuk ditampilkan.\n";
        return;
    }

    cout << "\nReviews (FIFO - Queue):\n";
    while (front != nullptr)
    {
        cout << "User: " << front->data.user << endl;
        cout << "Review: " << front->data.ulasan << endl;
        cout << "Rating: " << front->data.penilaian << "/5\n";
        cout << "----------------------------------\n";
        front = front->next;
    }
}

// auto increment kode tempat
int autoIncrementKode()
{
    ifstream file("tempat.csv");
    string line, lastKodeStr;
    int lastKode = 0;

    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, lastKodeStr, ',');
        lastKode = stoi(lastKodeStr);
    }
    file.close();
    return lastKode;
}

// tambah tempat
void tambah_tempat(NodeTempat *&head, int &jumlahLinked)
{
    NodeTempat *nodeBaru = new NodeTempat;
    int lastKode = autoIncrementKode();
    nodeBaru->data.kode = to_string(lastKode + 1);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Nama Tempat: ";
    getline(cin, nodeBaru->data.nama_tempat);
    cout << "Masukkan Owner Tempat (boleh kosong): ";
    getline(cin, nodeBaru->data.owner_tempat);
    cout << "Masukkan Alamat: ";
    getline(cin, nodeBaru->data.alamat);
    cout << "Masukkan Deskripsi Tempat (boleh kosong): ";
    getline(cin, nodeBaru->data.deskripsi_tempat);
    nodeBaru->next = nullptr;

    if (head == nullptr)
    {
        head = nodeBaru;
    }
    else
    {
        NodeTempat *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = nodeBaru;
    }

    ofstream file("tempat.csv", ios::app);
    if (file.is_open())
    {
        file << nodeBaru->data.kode << ","
             << nodeBaru->data.nama_tempat << ","
             << (nodeBaru->data.owner_tempat.empty() ? "-" : nodeBaru->data.owner_tempat) << ","
             << nodeBaru->data.alamat << ","
             << (nodeBaru->data.deskripsi_tempat.empty() ? "-" : nodeBaru->data.deskripsi_tempat) << "\n";
        file.close();
        cout << "Data tempat berhasil ditambahkan ke file dan disimpan.\n";
    }
    else
    {
        cout << "Error: Tidak dapat membuka file untuk menyimpan data.\n";
    }
}

void tampilkan_tempat(NodeTempat *&head)
{
    ifstream reviewFile("reviews.csv");
    if (!reviewFile.is_open())
    {
        cout << "Error: Tidak dapat membuka file reviews.csv untuk membaca data.\n";
        return;
    }

    map<string, int> reviewCountMap;
    string line;

    while (getline(reviewFile, line))
    {
        stringstream ss(line);
        string kode;
        getline(ss, kode, ',');
        reviewCountMap[kode]++;
    }
    reviewFile.close();

    ifstream placeFile("tempat.csv");
    if (!placeFile.is_open())
    {
        cout << "Error: Tidak dapat membuka file tempat.csv untuk membaca data.\n";
        return;
    }

    while (head != nullptr)
    {
        NodeTempat *temp = head;
        head = head->next;
        delete temp;
    }

    while (getline(placeFile, line))
    {
        stringstream ss(line);
        NodeTempat *nodeBaru = new NodeTempat;

        getline(ss, nodeBaru->data.kode, ',');
        getline(ss, nodeBaru->data.nama_tempat, ',');
        getline(ss, nodeBaru->data.owner_tempat, ',');
        getline(ss, nodeBaru->data.alamat, ',');
        getline(ss, nodeBaru->data.deskripsi_tempat, ',');

        nodeBaru->review_count = reviewCountMap[nodeBaru->data.kode];
        nodeBaru->next = nullptr;

        if (head == nullptr)
        {
            head = nodeBaru;
        }
        else
        {
            NodeTempat *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = nodeBaru;
        }
    }
    placeFile.close();

    if (head == nullptr)
    {
        cout << "Tidak ada data tempat yang ditambahkan.\n";
    }
    else
    {
        NodeTempat *temp = head;
        int nomor = 1;
        cout << "Data Tempat:\n";
        while (temp != nullptr)
        {
            cout << "No. " << nomor++ << endl;
            cout << "--------------------------------" << endl;
            cout << "Kode Tempat   : " << temp->data.kode << endl;
            cout << "Nama Tempat   : " << temp->data.nama_tempat << endl;
            cout << "Owner Tempat  : " << (temp->data.owner_tempat == "-" ? "-" : temp->data.owner_tempat) << endl;
            cout << "Alamat        : " << temp->data.alamat << endl;
            cout << "Deskripsi     : " << (temp->data.deskripsi_tempat == "-" ? "-" : temp->data.deskripsi_tempat) << endl;
            cout << "Total Review  : " << temp->review_count << endl;
            cout << endl;
            temp = temp->next;
        }
    }
}

void addReview(Node *&head, const string &username, const string &kode, NodeTempat *&placesHead)
{
    Node *newNode = new Node;
    newNode->data.id = kode;
    newNode->data.user = username;

    cout << "Review: ";
    cin.ignore();
    getline(cin, newNode->data.ulasan);

    cout << "rating (1-5): ";
    cin >> newNode->data.penilaian;

    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    ofstream file("reviews.csv", ios::app);
    if (file.is_open())
    {
        file << kode << "," << username << "," << newNode->data.ulasan << "," << newNode->data.penilaian << "\n";
        file.close();
        cout << "Review berhasil di tambahkan!\n";
    }
    else
    {
        cout << "Error: File tidak berhasil dibuka!\n";
    }
}

void displayPlaceReviews(Node *head, const string &kode)
{
    ifstream file("reviews.csv");
    if (!file.is_open())
    {
        cout << "Error: File tidak berhasil dibuka!\n";
        return;
    }

    map<string, int> userReviewCount;
    map<string, vector<Node *>> userReviews;
    string line;
    bool foundReviews = false;

    // Baca file dan hitung kontribusi tiap user
    while (getline(file, line))
    {
        stringstream ss(line);
        Node *newNode = new Node;

        getline(ss, newNode->data.id, ',');
        getline(ss, newNode->data.user, ',');
        getline(ss, newNode->data.ulasan, ',');
        ss >> newNode->data.penilaian;
        newNode->next = nullptr;

        if (newNode->data.id == kode)
        {
            foundReviews = true;
            userReviewCount[newNode->data.user]++;
            userReviews[newNode->data.user].push_back(newNode);

            if (head == nullptr)
            {
                head = newNode;
            }
            else
            {
                Node *temp = head;
                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
    }

    file.close();

    if (!foundReviews)
    {
        cout << "Belum ada review...\n";
        return;
    }

    // Tampilkan semua review dengan kontribusi yang sesuai
    for (const auto &userReview : userReviews)
    {
        for (const auto &review : userReview.second)
        {
            cout << "User: " << review->data.user << endl;
            cout << "Review: " << review->data.ulasan << endl;
            cout << "Rating: " << review->data.penilaian << "/5\n";
            cout << "Contribution: " << userReviewCount[review->data.user] << endl;
            cout << "----------------------------------\n";
        }
    }
}

void displayUserReviews(Node *head, string &username)
{
    ifstream file("reviews.csv");
    if (!file.is_open())
    {
        cout << "Error:  File tidak berhasil dibuka!.\n";
        return;
    }

    map<string, string> placeMap;
    bool foundReviews = false;
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        Node *newNode = new Node;
        getline(ss, newNode->data.id, ',');
        getline(ss, newNode->data.user, ',');
        getline(ss, newNode->data.ulasan, ',');
        ss >> newNode->data.penilaian;
        newNode->next = nullptr;

        if (newNode->data.user == username)
        {
            foundReviews = true;

            string placeName = placeMap[newNode->data.id];

            cout << "Nama Tempat: " << placeName << endl;
            cout << "Kode Tempat: " << newNode->data.id << endl;
            cout << "Review: " << newNode->data.ulasan << endl;
            cout << "Rating: " << newNode->data.penilaian << "/5\n";
            cout << "----------------------------------\n";

            if (head == nullptr)
            {
                head = newNode;
            }
            else
            {
                Node *temp = head;
                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
    }

    file.close();

    if (!foundReviews)
    {
        cout << "Belum ada review...\n";
    }
}

NodeTempat *merge(NodeTempat *left, NodeTempat *right)
{
    NodeTempat dummy;
    NodeTempat *tail = &dummy;
    while (left && right)
    {
        if (left->review_count <= right->review_count)
        {
            tail->next = left;
            left = left->next;
        }
        else
        {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }
    tail->next = left ? left : right;
    return dummy.next;
}

void mergeSort(NodeTempat *&head)
{
    if (!head || !head->next)
        return;

    NodeTempat *slow = head, *fast = head->next;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    NodeTempat *mid = slow->next;
    slow->next = nullptr;

    mergeSort(head);
    mergeSort(mid);

    head = merge(head, mid);
}

NodeTempat *getTail(NodeTempat *cur)
{
    while (cur && cur->next)
        cur = cur->next;
    return cur;
}

NodeTempat *partition(NodeTempat *head, NodeTempat *end, NodeTempat *&newHead, NodeTempat *&newEnd)
{
    NodeTempat *pivot = end;
    NodeTempat *prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot)
    {
        NodeTempat *next = cur->next;
        if (cur->review_count > pivot->review_count)
        {
            cur->next = newHead;
            newHead = cur;
        }
        else
        {
            if (prev)
                prev->next = cur;
            prev = cur;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
        }
        cur = next;
    }

    if (!newHead)
        newHead = pivot;
    newEnd = tail;
    return pivot;
}

NodeTempat *quickSortRecur(NodeTempat *head, NodeTempat *end)
{
    if (!head || head == end)
        return head;

    NodeTempat *newHead = nullptr, *newEnd = nullptr;
    NodeTempat *pivot = partition(head, end, newHead, newEnd);

    if (newHead != pivot)
    {
        NodeTempat *temp = newHead;
        while (temp->next != pivot && temp->next != nullptr)
            temp = temp->next;

        if (temp != nullptr)
            temp->next = nullptr;

        newHead = quickSortRecur(newHead, temp);

        if (newHead != nullptr)
        {
            temp = getTail(newHead);
            temp->next = pivot;
        }
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead ? newHead : pivot;
}

void quickSort(NodeTempat *&head)
{
    head = quickSortRecur(head, getTail(head));
}

void SortbyReviews(NodeTempat *&placesHead, bool flag)
{
    ifstream file("reviews.csv");
    if (!file.is_open())
    {
        cout << "Error: File tidak berhasil dibuka!.\n";
        return;
    }

    map<string, int> reviewCountMap;
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string kode;
        getline(ss, kode, ',');
        reviewCountMap[kode]++;
    }
    file.close();

    NodeTempat *temp = placesHead;
    while (temp)
    {
        temp->review_count = reviewCountMap[temp->data.kode];
        temp = temp->next;
    }

    if (flag)
    {
        mergeSort(placesHead);
        cout << "List sorted by total review count in ascending order (Merge Sort).\n";
    }
    else
    {
        quickSort(placesHead);
        cout << "List sorted by total review count in descending order (Quick Sort).\n";
    }
}

void boyerMooreSearch(NodeTempat *head, const string &pattern)
{
    if (!head || pattern.empty())
    {
        cout << "Error: input kosong.\n";
        return;
    }

    int m = pattern.size();
    vector<int> badChar(256, -1);
    for (int i = 0; i < m; i++)
    {
        badChar[pattern[i]] = i;
    }

    bool found = false;
    NodeTempat *temp = head;
    while (temp)
    {
        string &text = temp->data.nama_tempat;
        int n = text.size();
        int s = 0;
        while (s <= (n - m))
        {
            int j = m - 1;
            while (j >= 0 && pattern[j] == text[s + j])
                j--;
            if (j < 0)
            {
                found = true;
                cout << "Tempat di temukan: " << temp->data.nama_tempat << " (kode: " << temp->data.kode << ")\n";
                break;
            }
            else
            {
                s += max(1, j - badChar[text[s + j]]);
            }
        }
        temp = temp->next;
    }
    if (!found)
        cout << "Tempat dengan pola \"" << pattern << "\" tidak di temukan.\n";
}

// Function to perform Fibonacci search for a review in the list by ID
int fibonacciSearch(vector<Node *> &reviews, const string &reviewID)
{
    int fibM2 = 0;
    int fibM1 = 1;
    int fibM = fibM1 + fibM2;
    int n = reviews.size();

    while (fibM < n)
    {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM1 + fibM2;
    }

    int offset = -1;
    while (fibM > 1)
    {
        int i = min(offset + fibM2, n - 1);

        if (reviews[i]->data.id < reviewID)
        {
            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            offset = i;
        }
        else if (reviews[i]->data.id > reviewID)
        {
            fibM = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM - fibM1;
        }
        else
        {
            return i;
        }
    }

    if (fibM1 && reviews[offset + 1]->data.id == reviewID)
    {
        return offset + 1;
    }

    return -1;
}

void updateReviewInFile(const string &username, const string &reviewID)
{
    vector<Node *> reviews;
    ifstream file("reviews.csv");
    ofstream tempFile("temp.csv");

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, user, ulasan;
        int penilaian;
        getline(ss, id, ',');
        getline(ss, user, ',');
        getline(ss, ulasan, ',');
        ss >> penilaian;

        Node *review = new Node;
        review->data.id = id;
        review->data.user = user;
        review->data.ulasan = ulasan;
        review->data.penilaian = penilaian;
        reviews.push_back(review);
    }

    file.close();
    sort(reviews.begin(), reviews.end(), [](Node *a, Node *b)
         { return a->data.id < b->data.id; });
    int index = fibonacciSearch(reviews, reviewID);

    if (index == -1)
    {
        cout << "Review tidak di temukan!\n";
        return;
    }

    Node *review = reviews[index];
    cout << "Update?\n1. Review\n2. Rating\nChoice: ";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        cout << "Text Review/Ulasan baru: ";
        cin.ignore();
        getline(cin, review->data.ulasan);
    }
    else if (choice == 2)
    {
        cout << "Penilaian (1-5): ";
        cin >> review->data.penilaian;
    }

    for (auto &rev : reviews)
    {
        tempFile << rev->data.id << "," << rev->data.user << "," << rev->data.ulasan << "," << rev->data.penilaian << "\n";
    }

    tempFile.close();
    remove("reviews.csv");
    rename("temp.csv", "reviews.csv");
    cout << "Review Berhasil di update.\n";
}

int jumpSearch(vector<Node *> &reviews, const string &reviewID)
{
    int n = reviews.size();
    int step = sqrt(n);
    int prev = 0;

    while (reviews[min(step, n) - 1]->data.id < reviewID)
    {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    while (reviews[prev]->data.id < reviewID)
    {
        prev++;
        if (prev == min(step, n))
            return -1;
    }

    if (reviews[prev]->data.id == reviewID)
        return prev;
    return -1;
}

void deleteReviewFromFile(const string &username, const string &reviewID)
{
    vector<Node *> reviews;
    ifstream file("reviews.csv");
    ofstream tempFile("temp.csv");

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, user, ulasan;
        int penilaian;
        getline(ss, id, ',');
        getline(ss, user, ',');
        getline(ss, ulasan, ',');
        ss >> penilaian;

        Node *review = new Node;
        review->data.id = id;
        review->data.user = user;
        review->data.ulasan = ulasan;
        review->data.penilaian = penilaian;
        reviews.push_back(review);
    }

    file.close();
    sort(reviews.begin(), reviews.end(), [](Node *a, Node *b)
         { return a->data.id < b->data.id; });
    int index = jumpSearch(reviews, reviewID);

    if (index == -1)
    {
        cout << "Review tidak di temukan!\n";
        return;
    }

    cout << "Are you sure you want to delete this review?\n1. Yes\n2. No\nChoice: ";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        reviews.erase(reviews.begin() + index);
        for (auto &rev : reviews)
        {
            tempFile << rev->data.id << "," << rev->data.user << "," << rev->data.ulasan << "," << rev->data.penilaian << "\n";
        }
        cout << "Review deleted successfully.\n";
    }
    else
    {
        cout << "Delete operation cancelled.\n";
    }

    tempFile.close();
    remove("reviews.csv");
    rename("temp.csv", "reviews.csv");
}

void editSection(Node *&head, const string &user)
{
    int choice;
    string reviewID;

    cout << "Edit:\n";
    cout << "1. Update Review\n";
    cout << "2. Delete Review\n";
    cout << "3. Keluar\n";
    cout << "Pilihan: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        displayUserReviews(head, session);
        cout << "Pilih review yang ingin di update (kode): ";
        cin >> reviewID;
        updateReviewInFile(user, reviewID);
        break;
    case 2:
        cout << "Pilih review yang ingin di hapus (kode): ";
        cin >> reviewID;
        deleteReviewFromFile(user, reviewID);
        break;
    case 3:
        cout << "Returning to the main menu.\n";
        return;
    default:
        cout << "Invalid choice.\n";
    }
}
