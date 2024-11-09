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
    {"Rafisyah", "BCA", "1234", 750000, "1234567890"},
    {"Ale", "BCA", "2345", 750000, "2345678901"},
    {"Razan", "BRI", "3456", 750000, "3456789012"},
    {"Yosep", "BRI", "4567", 750000, "4567890123"},
    {"Teguh", "BNI", "5678", 750000, "5678901234"},
    {"Rivaldi", "BNI", "6789", 750000, "6789012345"},
    {"Sakha", "BTN", "7890", 750000, "7890123456"},
    {"Aldi", "BTN", "8901", 750000, "8901234567"},
    {"Adil", "Mandiri", "9012", 750000, "9012345678"},
    {"Bajang", "Mandiri", "0123", 750000, "0123456789"}
};
