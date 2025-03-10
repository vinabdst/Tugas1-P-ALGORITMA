#include <iostream>
#include <iomanip>
using namespace std;

char pil;
int pilihan;

struct daftarroti
{
    string nama;
    int kode;
    int harga;
};

daftarroti daftar[] =
{
    {"Roti Tawar", 101, 15000},
    {"Roti Coklat", 102, 18000},
    {"Roti Gandum", 103, 20000},
    {"Roti Keju", 104, 25000},
    {"Roti Kacang", 105, 14000}
};

int jumlahRoti = sizeof(daftar) / sizeof(daftar[0]);
daftarroti *ptr = daftar;

void menu()
{
    cout << "======= AK Bakery =======" << endl;
    cout << "1. Menu Roti" << endl;
    cout << "2. Cari berdasarkan kode" << endl;
    cout << "3. Cari berdasarkan nama" << endl;
    cout << "4. Sort harga roti (asc)" << endl;
    cout << "5. Sort harga roti (desc)" << endl;
    cout << "6. Exit" << endl;
    cout << setfill(' ') << setw(50) << " " << endl;
}

void data()
{
    cout << "==================================\n";
    cout << "  Nama Roti   |   Kode  |  Harga\n";
    cout << "==================================\n";

    for (int i = 0; i < jumlahRoti; i++) {
        cout << setw(12) << left << ptr[i].nama << "  |  ";
        cout << setw(5) << ptr[i].kode << "  |  ";
        cout << setw(6) << ptr[i].harga << endl;
    }
    cout << "==================================\n";
    cout << setfill(' ') << setw(50) << " " << endl;
}

void cari1()
{
    int cari;
    bool ketemu = false;

    cout << "Masukkan kode roti: ";
    cin >> cari;

    for (int i = 0; i < jumlahRoti; i++) {
        if (daftar[i].kode == cari) {
            ketemu = true;
            cout << "Nama Roti  : " << daftar[i].nama << endl;
            cout << "Harga      : " << daftar[i].harga << endl;
            break;
        }
    }

    if (!ketemu)
    {
        cout << "Roti dengan kode " << cari << " tidak ditemukan." << endl;
    }
    cout << setfill(' ') << setw(50) << " " << endl;

}

void urutkandata()
{
    for (int i = 0; i < jumlahRoti - 1; i++) {
        for (int j = 0; j < jumlahRoti - i - 1; j++) {
            if (daftar[j].nama > daftar[j + 1].nama) {
                swap(daftar[j], daftar[j + 1]);
            }
        }
    }
}

void cari2()
{
    string nilaiCari;
    int awal, akhir, tengah;
    bool found = false;

    urutkandata();

    cout << "Masukkan nama roti: "; cin.ignore(); getline(cin, nilaiCari);

    awal = 0;
    akhir = jumlahRoti - 1;

    while (awal <= akhir) {
        tengah = (awal + akhir) / 2;

        if (daftar[tengah].nama == nilaiCari) {
            found = true;
            cout << "Nama Roti  : " << daftar[tengah].nama 
                 << "Kode       : " << daftar[tengah].kode 
                 << "Harga      : " << daftar[tengah].harga << endl;
            break;
        } else if (daftar[tengah].nama < nilaiCari) {
            awal = tengah + 1;
        } else {
            akhir = tengah - 1;
        }
    }

    if (!found) {
        cout << "Roti dengan nama \"" << nilaiCari << "\" tidak ditemukan." << endl;
    }
    cout << setfill(' ') << setw(50) << " " << endl;
}

void quick_asc(daftarroti arr[], int awal, int akhir) {
    if (awal < akhir) {
        int pivot = arr[akhir].harga;
        int low = awal, high = akhir;
        int i = awal - 1;

        for (int j = awal; j < akhir; j++) {
            if (arr[j].harga < pivot) { 
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[akhir]);
        low++;
        high--;

        if (awal < high)
        quick_asc(arr, awal, high);
        if (low < akhir)
        quick_asc(arr, low, akhir);
    }
}

void bubble_desc()
{
    for (int i = 0; i < jumlahRoti - 1; i++) {
        for (int j = 0; j < jumlahRoti - i - 1; j++) {
            if (daftar[j].harga < daftar[j + 1].harga) {
                swap(daftar[j], daftar[j + 1]);
            }
        }
    }
}



int main()
{
    system("cls");
    
    do
    {
        menu();
        cout << setfill(' ') << setw(50) << " " << endl;
        cout << "Pilih Menu: "; cin >> pilihan;
        switch (pilihan)
        {
        case 1:
            data();
            break;

        case 2:
            cari1();
            break;

        case 3:
            cari2();
            break;

        case 4:
            quick_asc(daftar, 0, jumlahRoti - 1);
            cout << "\nData setelah sorting harga (Ascending - Quick Sort):\n";
            data();
            break;

        case 5:
            bubble_desc();
            cout << "\nData setelah sorting harga (Descending - Bubble Sort):\n";
            data();
            break;

        case 6:
            cout << "Thank You!" << endl;
            exit(0);
            break;
        
        default:
            cout << "\nMaaf, menu tidak tersedia.\n";
            break;
        }
        cout << "Apakah anda ingin kembali ke menu? (y/n) : "; cin >> pil;
    } while (pil == 'y' || pil == 'Y');
    
    return 0;
}