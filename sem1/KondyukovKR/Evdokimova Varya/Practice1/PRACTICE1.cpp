#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

class Student {
private:
    int id;
    std::string full_name;
    float average_grade;
    std::string speciality;

public:
    Student(int id, const std::string full_name, float average_grade, const std::string speciality)
        : id(id), full_name(full_name), average_grade(average_grade), speciality(speciality) {}

    int GetId()
    {
        return id;
    }

    std::string GetStudentFullName()
    {
        return full_name;
    }

    int GetAverageGrade()
    {
        return average_grade;
    }

    std::string GetStudentSpeciality()
    {
        return speciality;
    }
};

class StudentBase {
private:
    std::vector<Student> students;
    const std::string filename = "StudentsBase.txt";

    std::string ConvertToString(Student student) const {
        std::ostringstream memory;
        memory << student.GetId() << ", " << student.GetStudentFullName() << ", " << student.GetAverageGrade() << ", " << student.GetStudentSpeciality();
        return memory.str();
    }

    //сплитим из памяти необходимые данные о студенте, переводим нужное в циферки и возвращаем студента в базу
    Student ConvertFromString(std::string str) {
        std::istringstream memory(str);
        std::string idStr, averageGradeStr;
        int id;
        float averageGrade;
        std::string studentFullName, speciality;

        getline(memory, idStr, ',');
        memory.ignore();
        getline(memory, studentFullName, ',');
        getline(memory, averageGradeStr, ',');
        memory.ignore(); 
        getline(memory, speciality, ',');

        id = std::stoi(idStr); //возвращает целочисленное значение
        averageGrade = std::stof(averageGradeStr); //возвращает среднюю оценку как тип float
        return Student(id, studentFullName, averageGrade, speciality);
    }

    //загружаем из файла в оперативную память
    void LoadFromMemory() {
        std::ifstream file(filename);
        std::string line;
        while (getline(file, line)) {  
            students.push_back(ConvertFromString(line)); 
        }
    }

    //добавляем в наш файл(память) информацию о студенте
    void SaveToFile() {
        std::ofstream file(filename, std::ios::trunc);
        for (Student student : students) {
            file << ConvertToString(student) << std::endl;
        }
    }

public:
    StudentBase() {
        LoadFromMemory();
    }

    void AddNewStudent(int id, const std::string full_name, float avgScore, const std::string speciality) {
        students.emplace_back(id, full_name, avgScore, speciality);
        SaveToFile();
    }

    void ShowAllStudents() {
        for (Student student : students) {
            std::cout << "ID: " << student.GetId() << ", Full name: " << student.GetStudentFullName()
                << ", Average grade: " << student.GetAverageGrade()
                << ", Speciality: " << student.GetStudentSpeciality() << std::endl;
        }
        std::cout << std::endl;
    }

    void FindStudentByID(const std::string request) {
        bool found = false;
        for (Student student : students) {
            if (std::to_string(student.GetId()) == request ||
                student.GetStudentSpeciality().find(request) != std::string::npos) //определяет максимальное значение

            {
                std::cout << "ID: " << student.GetId() << ", Name: " << student.GetStudentFullName()
                    << ", Average Score: " << student.GetAverageGrade()
                    << ", Speciality: " << student.GetStudentSpeciality() << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "Sorry, there is no student by this request. Try one more time." << std::endl;
        }
        std::cout << std::endl;
    }

    void DeleteStudentByID(int id) {
        auto inf = remove_if(students.begin(), students.end(), [id](Student info)
            {
            return info.GetId() == id;
            }
        );

        if (inf != students.end()) {
            students.erase(inf, students.end());
            SaveToFile();
            
        }
        else {
            std::cout << "Sorry, there is no student with this ID. Perhaps you allready deleted him or heсk ID. " << std::endl << std::endl;
        }
    }
};

int main() {
    StudentBase base;
    int choice;
    int id;
    float average_grade;
    std::string full_name, speciality, query;

    do {
        std::cout << "1. Add new student in base.\n2. Show all students in base.\n3. Search student by ID or speciality.\n4. Delete student by ID.\n5. Exit from program.\n";
        std::cout << "Enter number of your choice: ";
        std::cin >> choice;
        std::cout << "----------------------------------------------------------\n";

        switch (choice)
        {
        case 1:
            std::cout << "Enter student ID: ";
            std::cin >> id;
            if (id < 1)
            {
                std::cout << "Sorry, but ID must be more then 0." << std::endl;
                break;
            }
            std::cout << "Enter student name and surname: ";
            std::cin.ignore();
            getline(std::cin, full_name);
            std::cout << "Enter average grade: ";
            std::cin >> average_grade;
            if (average_grade < 0)
            {
                std::cout << "Error. Average grade can't be negative. Check all ine more time." << std::endl;
                break;
            }
            std::cout << "Enter student speciality: ";
            std::cin.ignore();
            getline(std::cin, speciality);
            base.AddNewStudent(id, full_name, average_grade, speciality);
            std::cout << "Congratulations, you have added a student." << std::endl << std::endl;
            break;

        case 2:
            base.ShowAllStudents();
            break;

        case 3:
            std::cout << "Enter ID or speciality to search (but it'll be easier for you to search through the id): ";
            std::cin.ignore();
            getline(std::cin, query);
            base.FindStudentByID(query);
            break;

        case 4:
            int id;
            std::cout << "Enter student ID to delete: ";
            std::cin >> id;
            std::cout << "Goodbye, unhappy little student:(";
            base.DeleteStudentByID(id);

        }
    } while (choice != 5);

    return 0;
}