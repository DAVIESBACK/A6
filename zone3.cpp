#include "zone3.h"

void loadZone3Data(vector<Zone3>& zone3s) {
    ifstream file("zone3.txt");
    if (!file) {
        cerr << "Error: Could not open zone3.txt\n";
        return;
    }

    zone3s.clear(); // เคลียร์ข้อมูลเก่า
    int id, price;
    string name, address;
    bool available;

    while (file >> id) {
        file.ignore();  // ข้ามช่องว่าง
        getline(file, name);
        getline(file, address);
        file >> price >> available;
        zone3s.push_back({id, name, address, price, available});
    }

    file.close();
}

int main() {
    vector<Zone3> zone3s;
    loadZone3Data(zone3s);
    displayZone3s(zone3s);
    return 0;
}
