#include <string>
using namespace std;

struct akun {
    string nama;
    string kartu;
    string pin;
    long saldo;
    string no_rek;
};

akun akunList[10] = {
    {"Rafisyah", "BCA", "1234", 900000, "1234567890"},
    {"Ale", "BCA", "2345", 600000, "2345678901"},
    {"Razan", "BRI", "3456", 500000, "3456789012"},
    {"Yosep", "BRI", "4567", 400000, "4567890123"},
    {"Teguh", "BNI", "5678", 400000, "5678901234"},
    {"Rivaldi", "BNI", "6789", 400000, "6789012345"},
    {"Sakha", "BTN", "7890", 400000, "7890123456"},
    {"Aldi", "BTN", "8901", 400000, "8901234567"},
    {"Adil", "Mandiri", "9012", 400000, "9012345678"},
    {"Bajang", "Mandiri", "0123", 400000, "0123456789"}
};
