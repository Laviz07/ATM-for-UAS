#include "db.cpp"    //untuk memanggil file db.cpp

#include <cctype>    //untuk mengatur karakter spesial
#include <fstream>   //untuk membaca dan menulis file
#include <iostream>  //untuk operasi input dan output (cin dan cout)
#include <limits>    //untuk mengatur batasan input
#include <string>    //untuk membuat, memeriksa, dan memodifikasi urutan string

using namespace std; // menggunakan namespace std

/* --------------------------- DEKLARASI FUNCTION --------------------------- */
bool   login(int inputKartu, string &inputPin, int &count, akun &akunLogin);
void   tampilkanMenu(akun &akun);
bool   lanjutkanTransaksi();
void   cekSaldo(akun &akun);
string formatUang(int angka);
void   tarikTunai(akun &akun);
void   setorTunai(akun &akun);
void   transfer(akun &akun);
void   ubahPin(akun &akun);

string bank[5] = {"BCA", "BRI", "BNI", "BTN", "Mandiri"};
int    inputKartu;
string bye    = "\nTerima kasih telah menggunakan ATM NGEPET BERSAMA!\n";
string failed = "\nTransaksi gagal...";
int    akunIndex;
int    tujuanIndex;
int    nominal;

/* ---------------------------------- MAIN ----------------------------------*/
int main() {
    string inputPin;
    int    count = 0;
    akun   akunLogin;

    cout << "\n============================================\n";
    cout << "\n************ ATM NGEPET BERSAMA ************" << endl;
    cout << "\n============================================\n";

    cout << "Pilih Bank Yang Ingin Anda Gunakan : \n"
         << "1. Bank BCA\n"
         << "2. Bank BRI\n"
         << "3. Bank BNI\n"
         << "4. Bank BTN\n"
         << "5. Bank Mandiri" << endl;
    cout << "Pilih (1-5): ";
    cin >> inputKartu;

    // Jika input kartu tidak sesuai
    if (inputKartu < 1 || inputKartu > 5) {
        cout << "Bank tidak tersedia" << endl;
        return 1;
    }

    cout << "\nMasukkan PIN anda: ";
    cin >> inputPin;

    // Jika login gagal
    if (!login(inputKartu, inputPin, count, akunLogin)) { return 1; }

    tampilkanMenu(akunLogin);
    return 0;
}

/* ------------------------------- LOGIN USER ------------------------------- */
bool login(int inputKartu, string &inputPin, int &count, akun &akunLogin) {
    for (int i = 0; i < 10; i++) {
        // mengecek jika input kartu dan pin sesuai
        if (akunList[i].kartu == bank[inputKartu - 1] && akunList[i].pin == inputPin) {
            cout << "Login berhasil! Selamat datang, " << akunList[i].nama << endl;
            akunLogin = akunList[i];
            akunIndex = i;
            return true;
        }
    }

    // Jika PIN salah, tambah jumlah percobaan dan beri peringatan
    count++;
    if (count < 3) {
        cout << "PIN anda salah. Coba lagi (" << 3 - count << "x lagi)." << endl;
        cout << "Masukkan PIN anda: ";
        cin >> inputPin;
        return login(inputKartu, inputPin, count, akunLogin);
    }

    // Jika percobaan melebihi batas
    cout << "PIN salah tiga kali. Akun anda terblokir." << endl;
    return false;
}

/* ---------------------------- MENAMPILKAN MENU ---------------------------- */
void tampilkanMenu(akun &akun) {
    int pilihan;

    do {
        cout << "\n=============================================\n";
        cout << "\n*************** - ATM Menu - ***************" << endl;
        cout << "\n=============================================\n";
        cout << "Nasabah " << akun.nama << " yang terhormat, silahkan pilih transaksi yang ingin anda lakukan"
             << endl;
        cout << "1. Cek Saldo\n"
             << "2. Tarik Tunai\n"
             << "3. Setor Tunai\n"
             << "4. Transfer\n"
             << "5. Ubah PIN\n"
             << "6. Keluar\n";
        cout << "Pilih menu (1-6): ";
        cin >> pilihan;

        // Jika input tidak valid, seperti memasukkan tipe data yg tidak sesuai
        if (cin.fail()) {
            // Membersihkan status error yang disimpan di buffer (tempat sementara untuk menyimpan data).
            cin.clear();
            // Mengabaikan karakter yang tidak diinginkan
            cin.ignore(1000, '\n');
            // 100 merupakan jumlah maksimal karakter yang diabaikan
            //'\n' akan membuat proses pengabaian berhenti
        }

        // Memilih transaksi
        switch (pilihan) {
            case 1 : cekSaldo(akun); break;
            case 2 : tarikTunai(akun); break;
            case 3 : setorTunai(akun); break;
            case 4 : transfer(akun); break;
            case 5 : ubahPin(akun); break;
            case 6 : cout << bye; return;
            default: cout << "\nPilihan tidak valid. Silakan coba lagi." << endl; break;
        }

    } while (lanjutkanTransaksi());
}

/* -------------------- KONFIRMASI MELANJUTKAN TRANSAKSI -------------------- */
bool lanjutkanTransaksi() {
    char lanjut;
    cout << "\nApakah anda ingin melakukan transaksi yang lain? (Y/N): ";
    cin >> lanjut;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Input tidak valid, silakan pilih Y atau N." << endl;
        return lanjutkanTransaksi(); // Meminta input ulang
    }

    if (lanjut == 'Y' || lanjut == 'y') {
        return true;                 // Kembali ke menu utama
    } else if (lanjut == 'N' || lanjut == 'n') {
        cout << bye;
        return false;                // Keluar dari program
    } else {
        cout << "\nInput tidak valid. Silakan coba lagi.";
        return lanjutkanTransaksi(); // Ulangi  jika input tidak valid
    }
}

/* ------------------------------- FORMAT UANG ------------------------------ */
string formatUang(int angka) {
    string str = to_string(angka); // merubah angka menjadi string, contoh: 1234567 -> "1234567"
    int    n   = str.length() - 3; // mendekrankan variabel n sebagai  panjang string str dikurangi dengan 3
    while (n > 0)                  // mengulang selama variabel n lebih dari 0
    {
        str.insert(n, ".");        // menambahkan titik di posisi  variabel n
        n -= 3;                    // mengurangi variabel n dengan 3
    }
    return str;
}

/* -------------------------------- CEK SALDO ------------------------------- */
void cekSaldo(akun &akun) {
    cout << "\n=============================================\n";
    cout << "\n*************** - Cek Saldo - ***************" << endl;
    cout << "\n=============================================\n";

    // Menampilkan saldo
    cout << "\nSaldo Anda saat ini: Rp " << formatUang(akunList[akunIndex].saldo) << endl;
}

/* ----------------------------- UPDATE DATABASE ---------------------------- */
void updateDB() {
    // Membuka file db.cpp
    ofstream dbFile("db.cpp");

    // Jika file gagal dibuka, program akan mencetak pesan error
    if (!dbFile) {
        cerr << "Gagal membuka file untuk menyimpan data!" << endl;
        return;
    }

    // Menulis data ke dalam file
    dbFile << "#include <string>\n"
           << "using namespace std;\n\n"
           << "struct akun {\n"
           << "    string nama;\n"
           << "    string kartu;\n"
           << "    string pin;\n"
           << "    long saldo;\n"
           << "    string no_rek;\n"
           << "};\n\n"
           << "akun akunList[10] = {\n";

    // Menulis semua data akun ke dalam file
    for (int i = 0; i < 10; ++i) {
        const auto &akun = akunList[i];
        dbFile << "    {\"" << akun.nama << "\", "
               << "\"" << akun.kartu << "\", "
               << "\"" << akun.pin << "\", " << akun.saldo << ", "
               << "\"" << akun.no_rek << "\"}";

        // Tambahkan koma di akhir kecuali untuk elemen terakhir
        if (i < 9) { dbFile << ","; }
        dbFile << "\n";
    }

    dbFile << "};\n";

    // Menutup file
    dbFile.close();
}

/* --------------------------- CHECK INVALID INPUT -------------------------- */
bool checkInvalidInput() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan seluruh karakter dalam buffer
        cout << "\nInput tidak valid! Harap masukkan angka saja.\n";
        return false;
    }
    return true;
}

/* ------------------------------- TARIK TUNAI ------------------------------ */
void tarikTunai(akun &akun) {
    long penarikan[5] = {100000, 200000, 300000, 1000000, 1500000};
    int  pilihan;
    cout << "\n=============================================\n";
    cout << "\n************** - Tarik Tunai - **************" << endl;
    cout << "\n=============================================\n";
    cout << "\nSilahkan pilih nominal penarikan:" << endl;
    cout << "1. Rp. 100.000\n"
         << "2. Rp. 200.000\n"
         << "3. Rp. 300.000\n"
         << "4. Rp. 1.000.000\n"
         << "5. RP. 1.500.000\n"
         << "6. Pilih nominal lainnya\n";
    cout << "Pilih (1-6): ";
    cin >> pilihan;

    // Mengecek apakah user memilih opsi 1-5
    if (checkInvalidInput() && (pilihan >= 1 && pilihan <= 5)) {
        // Memeriksa apakah saldo user mencukupi
        if (akun.saldo < penarikan[pilihan - 1]) {
            cout << "\nMaaf, saldo anda tidak mencukupi" << endl;
            cout << "Saldo anda saat ini adalah: " << formatUang(akunList[akunIndex].saldo) << failed << endl;
        } else {
            // Melakukan penarikan berdasarkan opsi yang dipilih
            akunList[akunIndex].saldo -= penarikan[pilihan - 1];
            cout << "\nPenarikan berhasil! Sisa saldo Anda: Rp " << formatUang(akunList[akunIndex].saldo)
                 << endl;
            updateDB();
        }
        // Mencek apakah user memilih opsi 6
    } else if (pilihan == 6) {
        const int pecahan[2] = {50000, 100000};
        int       pilihPecahan;
        cout << "\nSilahkan pilih pecahan uang yang anda inginkan:\n"
             << "Nominal penarikan tidak boleh lebih dari Rp 2.500.000\n";
        cout << "1. Rp. 50.000\n"
             << "2. Rp. 100.000\n";
        cout << "Pilih (1-2): ";
        cin >> pilihPecahan;

        // Memeriksa pilihan pecahan
        if (checkInvalidInput() && (pilihPecahan == 1 || pilihPecahan == 2)) {
            cout << "Masukkan jumlah nominal penarikan: Rp ";
            cin >> nominal;

            if (!checkInvalidInput()) { return; }

            // Memeriksa apakah nominal penarikan valid
            // Jika nominalnya lebih dari Rp 2.500.000
            if (nominal > 2500000) {
                cout << "Nominal penarikan tidak boleh lebih dari Rp 2.500.000\n" << failed << endl;
            }
            // Jika nominal penarikan bukan kelipatan pecahan
            else if (!(nominal % pecahan[pilihPecahan - 1] == 0)) {
                cout << "\nNominal penarikan harus berupa pecahan Rp "
                     << formatUang(pecahan[pilihPecahan - 1]) << failed << endl;
            }
            // Jika saldo tidak mencukupi
            else if (akunList[akunIndex].saldo < nominal) {
                cout << "\nMaaf, saldo anda tidak mencukupi" << endl;
                cout << "Saldo anda saat ini adalah: " << formatUang(akunList[akunIndex].saldo) << failed
                     << endl;
            }
            // Jika semua syarat terpenuhi
            else {
                akunList[akunIndex].saldo -= nominal; // Mengurangi saldo
                cout << "\nPenarikan berhasil! Sisa saldo Anda: Rp " << formatUang(akunList[akunIndex].saldo)
                     << endl;
                updateDB();                           // Memperbarui data ke file
            }
        } else {
            cout << "\nPilihan tidak tersedia" << failed << endl;
        }
    }
}

/* ------------------------------- SETOR TUNAI ------------------------------ */
void setorTunai(akun &akun) {
    cout << "\n=============================================\n";
    cout << "\n************** - Setor Tunai - **************" << endl;
    cout << "\n=============================================\n";
    cout << "\nPastikan nominal uang yang anda masukkan adalah kelipatan Rp 50.000 atau Rp 100.000" << endl;
    cout << "Masukkan Nominal uang: Rp ";
    cin >> nominal;

    if (!checkInvalidInput()) { return; }

    // Memeriksa apakah nominal setor lebih dari Rp 50.000.000
    if (nominal > 50000000) {
        cout << "Tidak bisa menyetor uang melebihi Rp 50.000.000" << failed << endl;
        return;
    }

    // Memeriksa apakah nominal setor kelipatan Rp 50.000 atau Rp 100.000
    if (nominal % 50000 == 0 || nominal % 100000 == 0) {
        akunList[akunIndex].saldo += nominal; //menambah saldo
        cout << "\nSetor berhasil! Jumlah saldo Anda: Rp " << formatUang(akunList[akunIndex].saldo) << endl;
        updateDB();
    } else {
        cout << "\nNominal setor harus berupa pecahan Rp 50.000 atau Rp 100.000" << failed << endl;
    }
}

/* -------------------------------- TRANSFER -------------------------------- */
void transfer(akun &akun) {
    string rekTujuan;
    bool   found = false;

    cout << "\n=============================================\n";
    cout << "\n*************** - Transfer - ***************" << endl;
    cout << "\n=============================================\n";
    cout << "\nMasukkan nomor rekening tujuan anda: ";
    cin >> rekTujuan;

    for (int j = 0; j < 10; j++) {
        // Memeriksa apakah rekTujuan ada di akunList
        if (akunList[j].no_rek == rekTujuan) {
            found       = true;
            tujuanIndex = j;
            cout << "\nNomor Rekening tujuan: " << akunList[tujuanIndex].no_rek << endl;
            cout << "Nama akun tujuan: " << akunList[tujuanIndex].nama << endl;
            cout << "Bank tujuan: " << akunList[tujuanIndex].kartu << endl;
            cout << "\nMasukkan nominal transfer: Rp ";
            cin >> nominal;

            // Memeriksa apakah nominal transfer kurang dari Rp 10.000 atau melebihi Rp 50.000.000
            if ((nominal < 10000) || (nominal > 50000000)) {
                cout << "\nNominal transfer tidak boleh kurang dari Rp 10.000 atau melebihi Rp 50.000.000"
                     << failed << endl;
                return;
            }
            // Memeriksa apakah saldo cukup
            if (checkInvalidInput() && (akunList[akunIndex].saldo >= nominal)) {
                akunList[akunIndex].saldo -= nominal; //mengurangi saldo pengirim
                akunList[tujuanIndex].saldo += nominal; //menambah saldo tujuan

                cout << "Transfer ke rekening " << akunList[tujuanIndex].no_rek << " berhasil!\n"
                     << "Sisa saldo anda: Rp " << formatUang(akunList[akunIndex].saldo) << endl;
                updateDB();
            } else {
                cout << "Saldo tidak cukup untuk melakukan transfer." << endl;
            }
            break;
        }
    }
    // Jika rekening Tujuan tidak ditemukan
    if (!found) { cout << "Nomor rekening tujuan tidak ditemukan" << endl; }
}

/* -------------------------------- UBAH PIN -------------------------------- */
void ubahPin(akun &akun) {
    string oldPin;
    string newPin;
    string confirmPin;

    cout << "\n=============================================\n";
    cout << "\n*************** - Ubah Pin - ***************" << endl;
    cout << "\n=============================================\n";

    cout << "\nMasukkan pin lama: ";
    cin >> oldPin;

    // Memeriksa apakah pin lama cocok
    if (oldPin != akun.pin) {
        cout << "\nPin lama salah!" << failed << endl;
        return;
    }

    cout << "\nSilahkan masukkan pin baru anda.\nPin harus terdiri dari 6 angka." << endl;
    cout << "\nMasukkan pin baru: ";
    cin >> newPin;

    // Memeriksa apakah panjang pin baru kurang dari 6
    if (newPin.length() != 6) {
        cout << "\nPin harus terdiri dari 6 angka." << failed << endl;
        return;
    }

    // Memeriksa apakah pin baru hanya mengandung angka
    for (char digit : newPin) {
        if (!isdigit(digit)) { // Cek apakah karakter bukan angka
            cout << "PIN hanya boleh mengandung angka." << endl;
            return;
        }
    }

    // Memeriksa apakah pin baru sama dengan pin lama
    // Jika tidak, maka akan meminta user untuk memasukkan pin kembali
    do {
        cout << "\nKonfirmasi kembali pin baru: ";
        cin >> confirmPin;

        if (newPin != confirmPin) {
            cout << "\nPin baru tidak cocok!" << failed << endl;
            cout << "\nHarap masukkan pin dengan benar." << endl;
        }
    } while (newPin != confirmPin);

    akunList[akunIndex].pin = newPin; // Mengubah pin menjadi pin baru
    cout << "\nPin berhasil diubah!" << endl;
    updateDB();
}