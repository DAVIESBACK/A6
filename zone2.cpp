#include "zone2.h"

void loadZone2Data(vector<Zone2>& zone2s) {
    ifstream file("zone2.txt");
    if (!file) {
        cerr << "Error: Could not open zone2.txt\n";
        return;
    }

    zone2s.clear(); // เคลียร์ข้อมูลเก่า
    int id, price;
    string name, address;
    bool available;

    while (file >> id) {
        file.ignore();  // ข้ามช่องว่าง
        getline(file, name);
        getline(file, address);
        file >> price >> available;
        zone2s.push_back({id, name, address, price, available});
    }

    file.close();
}

int main() {
    vector<Zone2> zone2s;
    loadZone2Data(zone2s);
    displayZone2s(zone2s);
    return 0;
}
