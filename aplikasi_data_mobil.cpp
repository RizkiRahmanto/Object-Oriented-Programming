#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Abstraksi
class Kendaraan {
protected:
    string merek;
    int tahun;

public:
    Kendaraan(const string &merek, int tahun) : merek(merek), tahun(tahun) {}

    virtual string tipeKendaraan() const = 0; // Polimorfisme (metode abstrak)

    string getMerek() const {
        return merek;
    }

    int getTahun() const {
        return tahun;
    }

    void setMerek(const string &merek) {
        this->merek = merek;
    }

    void setTahun(int tahun) {
        this->tahun = tahun;
    }
};

// Pewarisan
class Mobil : public Kendaraan {
    int jumlahPintu;

public:
    Mobil(const string &merek, int tahun, int jumlahPintu)
        : Kendaraan(merek, tahun), jumlahPintu(jumlahPintu) {}

    string tipeKendaraan() const override { // Polimorfisme
        return "Mobil";
    }

    int getJumlahPintu() const {
        return jumlahPintu;
    }

    void setJumlahPintu(int jumlahPintu) {
        this->jumlahPintu = jumlahPintu;
    }
};

class Motor : public Kendaraan {
    string jenisMotor;

public:
    Motor(const string &merek, int tahun, const string &jenisMotor)
        : Kendaraan(merek, tahun), jenisMotor(jenisMotor) {}

    string tipeKendaraan() const override { // Polimorfisme
        return "Motor";
    }

    string getJenisMotor() const {
        return jenisMotor;
    }

    void setJenisMotor(const string &jenisMotor) {
        this->jenisMotor = jenisMotor;
    }
};

// Pengelolaan kendaraan
class ManajemenKendaraan {
    vector<shared_ptr<Kendaraan>> kendaraanList;

public:
    void tambahKendaraan(const shared_ptr<Kendaraan> &kendaraan) {
        kendaraanList.push_back(kendaraan);
    }

    void hapusKendaraan(int index) {
        if (index >= 0 && index < kendaraanList.size()) {
            kendaraanList.erase(kendaraanList.begin() + index);
        } else {
            cout << "Indeks tidak valid." << endl;
        }
    }

    void tampilkanKendaraan() const {
        if (kendaraanList.empty()) {
            cout << "Tidak ada kendaraan." << endl;
        } else {
            for (int i = 0; i < kendaraanList.size(); ++i) {
                const auto &kendaraan = kendaraanList[i];
                if (dynamic_pointer_cast<Mobil>(kendaraan)) {
                    auto mobil = dynamic_pointer_cast<Mobil>(kendaraan);
                    cout << i << ". " << mobil->getMerek() << " - " << mobil->tipeKendaraan()
                         << " - " << mobil->getTahun() << " - " << mobil->getJumlahPintu() << " pintu" << endl;
                } else if (dynamic_pointer_cast<Motor>(kendaraan)) {
                    auto motor = dynamic_pointer_cast<Motor>(kendaraan);
                    cout << i << ". " << motor->getMerek() << " - " << motor->tipeKendaraan()
                         << " - " << motor->getTahun() << " - " << motor->getJenisMotor() << endl;
                }
            }
        }
    }
};

// Main Program
int main() {
    ManajemenKendaraan manajemenKendaraan;
    int pilihan;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Tambah Mobil" << endl;
        cout << "2. Tambah Motor" << endl;
        cout << "3. Tampilkan Kendaraan" << endl;
        cout << "4. Hapus Kendaraan" << endl;
        cout << "5. Keluar" << endl;

        cout << "Pilih menu: ";
        cin >> pilihan;

        if (pilihan == 1) {
            string merek;
            int tahun, jumlahPintu;
            cout << "Masukkan merek mobil: ";
            cin >> merek;
            cout << "Masukkan tahun mobil: ";
            cin >> tahun;
            cout << "Masukkan jumlah pintu mobil: ";
            cin >> jumlahPintu;
            auto mobil = make_shared<Mobil>(merek, tahun, jumlahPintu);
            manajemenKendaraan.tambahKendaraan(mobil);
        } else if (pilihan == 2) {
            string merek, jenisMotor;
            int tahun;
            cout << "Masukkan merek motor: ";
            cin >> merek;
            cout << "Masukkan tahun motor: ";
            cin >> tahun;
            cout << "Masukkan jenis motor: ";
            cin >> jenisMotor;
            auto motor = make_shared<Motor>(merek, tahun, jenisMotor);
            manajemenKendaraan.tambahKendaraan(motor);
        } else if (pilihan == 3) {
            manajemenKendaraan.tampilkanKendaraan();
        } else if (pilihan == 4) {
            int index;
            cout << "Masukkan indeks kendaraan yang akan dihapus: ";
            cin >> index;
            manajemenKendaraan.hapusKendaraan(index);
        } else if (pilihan == 5) {
            break;
        } else {
            cout << "Pilihan tidak valid, coba lagi." << endl;
        }
    } while (pilihan != 5);

    return 0;
}
