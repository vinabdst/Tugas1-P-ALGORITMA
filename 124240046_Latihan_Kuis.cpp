#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
using namespace std;

char pil;
int pilihan;

struct dataKependudukan
{
    char nomor_kependudukan[20];
    char nama[50];
    char alamat[100];
    char jkel;
};

void menu()
{
    cout << "========Kecamatan Depok========" << endl;
    cout << "1. Input Data" << endl;
    cout << "2. Data" << endl;
    cout << "3. Cari Data" << endl;
    cout << "4. Edit Data" << endl;
    cout << "5. Hapus Data" << endl;
    cout << "6. Keluar" << endl;
}

void input()
{
    FILE *file;
    file = fopen("kependudukan.dat", "ab");
    if (file == NULL)
    {
        cout << "Gagal membuka file untuk menulis!" << endl;
        return;
    }

    dataKependudukan data;
    cout << "Masukkan nomor kependudukan    : "; cin >> data.nomor_kependudukan;
    cout << "Masukkan nama                  : "; cin.ignore(); cin.getline(data.nama, 50);
    cout << "Masukkan alamat                : "; cin.getline(data.alamat, 100);
    cout << "Masukkan jenis kelamin (L/P)   : "; cin >> data.jkel;
    fwrite(&data, sizeof(data), 1, file);

    fclose(file);
}

void tampil()
{
    FILE *file;
    file = fopen("kependudukan.dat", "rb");
    if (file == NULL)
    {
        cout << "Gagal membuka file untuk membaca!" << endl;
        return;
    }

    dataKependudukan data;
    cout << "==== Data Kependudukan ====" << endl;
    while (fread(&data, sizeof(dataKependudukan), 1, file))
    {
        cout << "NIK            : " << data.nomor_kependudukan << endl;
        cout << "Nama           : " << data.nama << endl;
        cout << "Alamat         : " << data.alamat << endl;
        cout << "Jenis Kelamin  : " << data.jkel << endl;
        cout << "-----------------------------" << endl;
    }
    fclose(file);
}

void cari()
{
    FILE *file;
    file = fopen("kependudukan.dat", "rb");
    if (file == NULL)
    {
        cout << "File tidak ditemukan." << endl;
        return;
    }

    char cariNIK[20];
    cout << "Masukkan Nomor Kependudukan yang dicari: ";
    cin >> cariNIK;

    dataKependudukan data;
    bool found = false;

    while (fread(&data, sizeof(dataKependudukan), 1, file))
    {
        if (strcmp(data.nomor_kependudukan, cariNIK) == 0) // Bandingkan string
        {
            cout << "=== Data Ditemukan ===" << endl;
            cout << "NIK            : " << data.nomor_kependudukan << endl;
            cout << "Nama           : " << data.nama << endl;
            cout << "Alamat         : " << data.alamat << endl;
            cout << "Jenis Kelamin  : " << data.jkel << endl;
            cout << "-----------------------------" << endl;
            found = true;
            break; // Keluar dari loop setelah ditemukan
        }
    }

    fclose(file);

    if (!found)
    {
        cout << "Data dengan NIK " << cariNIK << " tidak ditemukan!" << endl;
    }
}

void edit() {
    int jumlah = 0;
    FILE *file = fopen("kependudukan.dat", "rb");
    if (file == NULL) {
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    dataKependudukan dataArr[100]; // Maksimal 100 data

    // read data
    while (fread(&dataArr[jumlah], sizeof(dataKependudukan), 1, file)) {
        jumlah++;
    }
    fclose(file);

    // Input NIK yang ingin diedit
    char cariNIK[20];
    cout << "Masukkan Nomor Kependudukan yang ingin diedit  : "; cin.ignore(); cin.getline(cariNIK, 20);

    // Cari data di dalam array
    bool found = false;
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(dataArr[i].nomor_kependudukan, cariNIK) == 0) {
            cout << "Data ditemukan!" << endl;
            cout << "Nama           : " << dataArr[i].nama << endl;
            cout << "Alamat lama    : " << dataArr[i].alamat << endl;
            
            // Input alamat baru
            cout << "Masukkan alamat baru: ";
            cin.getline(dataArr[i].alamat, 100);
            
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Data dengan NIK " << cariNIK << " tidak ditemukan!" << endl;
        return;
    }

    // Simpan kembali data ke file
    file = fopen("kependudukan.dat", "wb");
    if (file == NULL) {
        cout << "Gagal membuka file!" << endl;
        return;
    }
    fwrite(dataArr, sizeof(dataKependudukan), jumlah, file);
    fclose(file);

    cout << "Alamat berhasil diperbarui!" << endl;
}

void hapus() {
    int jumlah = 0;
    FILE *file = fopen("kependudukan.dat", "rb");
    if (file == NULL) {
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    dataKependudukan dataArr[100];

    // Membaca data dari file ke dalam array
    while (fread(&dataArr[jumlah], sizeof(dataKependudukan), 1, file)) {
        jumlah++;
    }
    fclose(file);

    if (jumlah == 0) {
        cout << "File kosong, tidak ada data untuk dihapus!" << endl;
        return;
    }

    // Input NIK yang ingin dihapus
    char cariNIK[20];
    cout << "Masukkan Nomor Kependudukan yang ingin dihapus : "; 
    cin >> cariNIK;

    // Cari indeks data yang akan dihapus
    int hapusData = -1;
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(dataArr[i].nomor_kependudukan, cariNIK) == 0) {
            hapusData = i;
            break;
        }
    }

    if (hapusData == -1) {
        cout << "Data dengan NIK " << cariNIK << " tidak ditemukan!" << endl;
        return;
    }

    // Tukar data yang akan dihapus dengan data terakhir
    if (hapusData != jumlah - 1) {
        swap(dataArr[hapusData], dataArr[jumlah - 1]);
    }

    // Kurangi jumlah data (tidak menyertakan data terakhir yang dihapus)
    jumlah--;

    // Tulis ulang data ke file tanpa data terakhir
    file = fopen("kependudukan.dat", "wb");
    if (file == NULL) {
        cout << "Gagal membuka file!" << endl;
        return;
    }
    fwrite(dataArr, sizeof(dataKependudukan), jumlah, file);
    fclose(file);

    cout << "Data berhasil dihapus!" << endl;
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
            input();
            cout << "Data berhasil disimpan ke file!\n";
            break;
        case 2:
            tampil();
            break;
        case 3:
            cari();
            break;
        case 4:
            edit();
            break;
        case 5:
            hapus();
            break;
        case 6:
            exit(0);
            break;
        
        default:
            cout << "\nMaaf, menu tidak tersedia.\n";
            break;
        }
        cout << "Apakah anda ingin kembali ke menu? (y/n) : "; cin >> pil;
    } while (pil == 'y' || pil == 'Y');
    
}