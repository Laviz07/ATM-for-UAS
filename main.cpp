#include "db.cpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

bool login(int inputKartu, string &inputPin, int &count, akun &akunLogin);
void tampilkanMenu(akun &akun);
void cekSaldo(akun &akun);
string formatUang(int angka);
void tarikTunai(akun &akun);

string bye = "\nTerima kasih telah menggunakan ATM NGEPET BERSAMA!\n";
string failed = "\nTransaksi gagal...";
int akunIndex;

/* ---------------------------------- MAIN ----------------------------------*/
int main()
{
    int inputKartu;
    string inputPin;
    int count = 0;
    akun akunLogin;

    cout << "\n===========================\n";
    cout << "\n*** ATM NGEPET BERSAMA ***" << endl;
    cout << "\n===========================\n";

    cout << "Pilih Bank Yang Ingin Anda Gunakan : \n"
         << "1. Bank BCA\n"
         << "2. Bank BRI\n"
         << "3. Bank BNI\n"
         << "4. Bank BTN\n"
         << "5. Bank Mandiri" << endl;
    cout << "Pilih (1-5): ";
    cin >> inputKartu;

    if (inputKartu < 1 || inputKartu > 5)
    {
        cout << "Bank tidak tersedia" << endl;
        return 1;
    }

    cout << "\nMasukkan PIN anda: ";
    cin >> inputPin;

    // Memanggil fungsi login dengan batas
    // percobaan
    if (!login(inputKartu, inputPin, count, akunLogin))
    {
        return 1;
    }

    tampilkanMenu(akunLogin);
    return 0;
}

/* ------------------------------- LOGIN USER ------------------------------- */
bool login(int inputKartu, string &inputPin, int &count, akun &akunLogin)
{
    string bank;
    switch (inputKartu)
    {
    case 1:
        bank = "BCA";
        break;
    case 2:
        bank = "BRI";
        break;
    case 3:
        bank = "BNI";
        break;
    case 4:
        bank = "BTN";
        break;
    case 5:
        bank = "Mandiri";
        break;
    default:
        return false;
    }

    // for (auto &akun : akunList)
    for (int i = 0; i < 10; i++)
    {
        // mengecek jika input kartu dan pin
        // sesuai
        if (akunList[i].kartu == bank && akunList[i].pin == inputPin)
        {
            cout << "Login berhasil! Selamat "
                    "datang, "
                 << akunList[i].nama << endl;
            akunLogin = akunList[i];
            akunIndex = i;
            return true;
        }
    }

    // Jika PIN salah, tambah jumlah percobaan dan beri peringatan
    count++;
    if (count < 3)
    {
        cout << "PIN anda salah. Coba lagi (" << 3 - count << "x lagi)." << endl;
        cout << "Masukkan PIN anda: ";
        cin >> inputPin;
        return login(inputKartu, inputPin, count, akunLogin);
    }

    // Jika percobaan melebihi batas
    cout << "PIN salah tiga kali. Akun anda terblokir."
         << endl;
    return false;
}

/* -------------------- KONFIRMASI MELANJUTKAN TRANSAKSI -------------------- */
bool lanjutkanTransaksi()
{
    char lanjut;
    cout << "\nApakah anda ingin melakukan transaksi yang lain? (Y/N): ";
    cin >> lanjut;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "Input tidak valid, silakan pilih Y atau N." << endl;
        return lanjutkanTransaksi(); // Meminta input ulang
    }

    if (lanjut == 'Y' || lanjut == 'y')
    {
        return true; // Kembali ke menu utama
    }
    else if (lanjut == 'N' || lanjut == 'n')
    {
        cout << bye;
        return false; // Keluar dari program
    }
    else
    {
        cout << "\nInput tidak valid. Silakan coba lagi.\n";
        return false; // Ulangi  jika input tidak valid
    }
}

/* ---------------------------- MENAMPILKAN MENU ---------------------------- */
void tampilkanMenu(akun &akun)
{
    int pilihan;

    do
    {
        cout << "\n========== ATM Menu ==========" << endl;
        cout << "Nasabah " << akun.nama
             << " yang terhormat, silahkan pilih transaksi yang ingin anda lakukan" << endl;
        cout << "1. Cek Saldo\n"
             << "2. Tarik Tunai\n"
             << "3. Setor Tunai\n"
             << "4. Transfer\n"
             << "5. Keluar\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            // cout << "Input tidak valid. Silakan masukkan angka yang benar." << endl;
            // cout << "Pilih menu (1-5): ";
            // cin >> pilihan;
            // continue;
        }

        switch (pilihan)
        {
        case 1:
            cekSaldo(akun);
            break;
        case 2:
            tarikTunai(akun);
            break;
        case 3:
            // setorTunai(akun);
            break;
        case 4:
            // transfer(akun);
            break;
        case 5:
            cout << bye;
            return;
        default:
            cout << "\nPilihan tidak valid. Silakan coba lagi."
                 << endl;
            break;
        }

        // if (!lanjutkanTransaksi())
        // {
        //     cout << bye;
        //     return;
        // }

    } while (lanjutkanTransaksi());
}

/* ------------------------------- FORMAT UANG ------------------------------ */
string formatUang(int angka) // fungsi untuk memformat uang
{
    string str = to_string(angka); // merubah angka menjadi string, contoh: 1234567 -> "1234567"
    int n = str.length() - 3;      // mendekrankan variabel n sebagai  panjang string str dikurangi dengan 3
    while (n > 0)                  // mengulang selama variabel n lebih dari 0
    {
        str.insert(n, "."); // menambahkan titik di posisi  variabel n
        n -= 3;             // mengurangi variabel n dengan 3
    }
    return str;
}

/* -------------------------------- CEK SALDO ------------------------------- */
void cekSaldo(akun &akun)
{
    cout << "\n========== Cek Saldo ==========" << endl;
    cout << "Saldo Anda saat ini: Rp " << formatUang(akunList[akunIndex].saldo) << endl;
}

/* ----------------------------- UPDATE DATABASE ---------------------------- */
void updateDB()
{
    ofstream dbFile("db.cpp");
    if (!dbFile)
    {
        cerr << "Gagal membuka file untuk menyimpan data!"
             << endl;
        return;
    }
    dbFile << "#include <string>\n";
    dbFile << "using namespace std;\n\n";
    dbFile << "struct akun {\n";
    dbFile << "    string nama;\n";
    dbFile << "    string kartu;\n";
    dbFile << "    string pin;\n";
    dbFile << "    long saldo;\n";
    dbFile << "    string no_rek;\n";
    dbFile << "};\n\n";
    dbFile << "akun akunList[10] = {\n";

    for (int i = 0; i < 10; ++i)
    {
        const auto &akun = akunList[i];
        dbFile << "    {\"" << akun.nama << "\", "
               << "\"" << akun.kartu << "\", "
               << "\"" << akun.pin << "\", "
               << akunList[akunIndex].saldo << ", "
               << "\"" << akun.no_rek << "\"}";

        // Tambahkan koma di akhir kecuali untuk elemen terakhir
        if (i < 9)
        {
            dbFile << ",";
        }
        dbFile << "\n";
    }

    dbFile << "};\n";
    dbFile.close();
}

/* ------------------------------- TARIK TUNAI ------------------------------ */
void tarikTunai(akun &akun)
{
    long penarikan[5] = {100000, 200000, 300000, 1000000, 1500000};
    int pilihan;
    cout << "\n========== Tarik Tunai ==========" << endl;
    cout << "Silahkan pilih nominal penarikan:" << endl;
    cout << "1. Rp. 100.000\n"
         << "2. Rp. 200.000\n"
         << "3. Rp. 300.000\n"
         << "4. Rp. 1.000.000\n"
         << "5. RP. 1.500.000\n"
         << "6. Pilih nominal lainnya\n";
    cout << "Pilih (1-6): ";
    cin >> pilihan;

    if (pilihan >= 1 && pilihan <= 5)
    {
        if (akun.saldo < penarikan[pilihan - 1])
        {
            cout << "\nMaaf, saldo anda tidak mencukupi"
                 << endl;
            cout << "Saldo anda saat ini adalah: "
                 << formatUang(akunList[akunIndex].saldo) << failed << endl;
        }
        else
        {
            akunList[akunIndex].saldo -= penarikan[pilihan - 1];
            cout << "\nPenarikan berhasil. Sisa saldo Anda: Rp "
                 << formatUang(akunList[akunIndex].saldo) << endl;
            updateDB();
        }
    }
    else if (pilihan == 6)
    {
        const int pecahan[2] = {50000, 100000};
        int pilihPecahan;
        int nominal;
        cout << "\nSilahkan pilih pecahan uang yang anda inginkan:\n"
             << "Nominal penarikan tidak boleh lebih dari Rp 2.500.000\n";
        cout << "1. Rp. 50.000\n"
             << "2. Rp. 100.000\n";
        cout << "Pilih (1-2): ";
        cin >> pilihPecahan;

        if (pilihPecahan == 1 || pilihPecahan == 2)
        {
            cout << "Masukkan jumlah nominal penarikan: Rp ";
            cin >> nominal;

            if (nominal > 2500000)
            {
                cout << "Nominal penarikan tidak boleh lebih dari Rp 2.500.000\n"
                     << failed << endl;
            }
            else if (!(nominal % pecahan[pilihPecahan - 1] == 0))
            {
                cout << "\nNominal penarikan harus berupa pecahan Rp "
                     << formatUang(pecahan[pilihPecahan - 1]) << failed << endl;
            }
            else if (akunList[akunIndex].saldo < nominal)
            {
                cout << "\nMaaf, saldo anda tidak mencukupi" << endl;
                cout << "Saldo anda saat ini adalah: " << formatUang(akunList[akunIndex].saldo) << failed << endl;
            }

            else
            {
                akunList[akunIndex].saldo -= nominal; // Mengurangi saldo
                cout << "\nPenarikan berhasil. Sisa saldo Anda: Rp " << formatUang(akunList[akunIndex].saldo) << endl;
                updateDB(); // Memperbarui data ke file
            }
        }
        else
        {
            cout << "\nPilihan tidak tersedia" << failed << endl;
        }
    }
}