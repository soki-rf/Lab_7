#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

struct Book
{
    std::string Author;
    std::string Title;
    int Year;
};

void saveToFile(const std::string& filename, const std::vector<Book>& data) {
    std::ofstream f1(filename);
    for (const auto& book : data) {
        f1 << "'" << book.Author << "'" << " " << "'"<< book.Title <<"'"<< " " << "'" << book.Year<< "'" << "\n";
    }
    f1.close();
}

void loadFromFile(const std::string& filename, std::vector<Book>& outData) {
    std::ifstream f2(filename);
    std::string line;
    std::vector<std::string> words;
    int k = 0;
    while (std::getline(f2, line)) {
        words.clear();
        std::string s1 = "";
        for (auto& x : line) {
            if ((x != '\'') && (k == 0)) {
                s1 += x;
            } else {
                if (s1 != "") {
                    k = 1;
                    words.push_back(s1);
                    s1 = "";
                } else {
                    k = 0;
                    s1 = "";
                }
            }
        }
        Book buf;
        buf.Author = words[0];
        buf.Title = words[1];
        buf.Year = std::stoi(words[2]);
        outData.push_back(buf);
    }


}


int main() {
    std::vector<Book> data = {{"Oleg", "Bebra", 1999}, {"Lena", "Where am i?", 2000}};
    std::vector<Book> books;
    saveToFile("books.txt", data);
    loadFromFile("books.txt", books);
    for (const auto& book : books) {
        std::cout << book.Author << " " << book.Title << " " << book.Year << "\n";
    }
    return 0;
}
