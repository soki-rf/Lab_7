#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

enum Score
{
    Unsatisfactorily = 2,
    Satisfactorily,
    Good,
    Excellent
};

struct Student
{
    std::string Name;
    int Year;
    std::map<std::string, Score> RecordBook;
};
using Groups = std::map<std::string, std::vector<Student>>;

void saveToFile(const std::string &filename, const Groups &groups)
{

    std::fstream out(filename);
    for (const auto &gr : groups)
    {
        out << "Group " << gr.first << std::endl;
        for (const auto &stud : gr.second)
        {
            out << "Student " << stud.Name << "\t" << stud.Year << "\t" << std::endl;
            for (const auto &rec : stud.RecordBook)
            {
                out << rec.first << "\t" << rec.second << std::endl;
            }
        }
        out << "end of group" << std::endl;
    }
    out.close();
}

void loadFromFile(const std::string &filename, Groups &outGroups)
{
    std::fstream in(filename);

    std::string line;
    std::string currentGroup;
    Student currentStudent;
    bool readingStudent = false;

    while (std::getline(in, line)){
        if (line.find("Group ") == 0){
            currentGroup = line.substr(6);
            outGroups[currentGroup] = std::vector<Student>();
        }
        else if (line.find("Student ") == 0){
            if (readingStudent){
                outGroups[currentGroup].push_back(currentStudent);
                currentStudent = Student();
            }
            readingStudent = true;
            std::stringstream ss(line.substr(8));
            ss >> currentStudent.Name >> currentStudent.Year;
        }
        else if (line == "end of group"){
            outGroups[currentGroup].push_back(currentStudent);
            currentStudent = Student();
            readingStudent = false;
        }
        else if (line == "EndGroup"){
            continue;
        }
        else{
            std::string subject;
            int score;
            std::stringstream ss(line);
            ss >> subject >> score;
            currentStudent.RecordBook[subject] = static_cast<Score>(score);
        }
    }

    in.close();
}

int main(){
    Groups groups = {
        {"IU", {{"Oleg", 1999, {{"Algosi", Good}, {"Math", Excellent}}}, {"Polina", 1999, {{"Algosi", Satisfactorily}, {"Math", Good}}}}},
        {"SM", {{"Nikita", 1998, {{"Algosi", Excellent}, {"Math", Good}}}, {"Richi", 1998, {{"Algosi", Satisfactorily}, {"Math", Unsatisfactorily}}}}},
        {"MT",{{"BlackHomie",1997,{{"Algosi",Unsatisfactorily},{"Math",Good}}},{"Atati",1997,{{"Algosi",Excellent},{"Math",Good}}}}}
    };
    std::ofstream f1;
    f1.open("test.txt");

    saveToFile("test.txt", groups);
    Groups loadedGroups;
    loadFromFile("test.txt", loadedGroups);
    for (const auto &group : loadedGroups){
        std::cout << "Group: " << group.first << std::endl;
        for (const auto &student : group.second){
            std::cout << "  Student: " << student.Name << ", Year: " << student.Year << std::endl;
            for (const auto &record : student.RecordBook){
                std::cout << "    " << record.first << ": " << record.second << std::endl;
            }
        }
    }
    f1.close();
}
