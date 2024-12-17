#include <iostream>
#include <fstream>
#include <vector>
#include <string>


void saveToFile(const std::string& filename, const std::vector<std::string>& data) {
    std::ofstream f1(filename);
    for (auto& d:data) {
        f1 << d << " ";
    }
    f1.close();
}

void loadFromFile(const std::string& filename, std::vector<std::string>& outData) {
    std::ifstream f2(filename);
    std::string word;
    while (f2 >> word) {
        outData.push_back(word);
    }
}


int main() {
    std::vector<std::string> data = {"ura", "proga", "rabotaet", "!!!"};
    std::vector<std::string> data_res;
    saveToFile("test.txt", data);
    loadFromFile("test.txt", data_res);
    for (auto& d:data_res) {
        std::cout << d << " ";
    }
    return 0;
}
