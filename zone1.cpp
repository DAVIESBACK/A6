#include "zone1.h"

void loadZone1Data(vector<Zone1>& zone1s) {
    ifstream file("zone1.txt");
    if (!file) {
        cerr << "Error: Could not open zone1.txt\n";
        return;
    }

    zone1s.clear(); // เคลียร์ข้อมูลเก่า
    int id, price;
    string name, address;
    bool available;

    while (file >> id) {
        file.ignore();  // ข้ามช่องว่าง
        getline(file, name);
        getline(file, address);
        file >> price >> available;
        zone1s.push_back({id, name, address, price, available});
    }

    file.close();
}

int main() {
    vector<Zone1> zone1s;
    loadZone1Data(zone1s);
    displayZone1s(zone1s);
    return 0;
}
