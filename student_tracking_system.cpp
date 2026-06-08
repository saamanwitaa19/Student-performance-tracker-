#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <limits>
struct SubjectGrade {
    std::string subjectName;
    double score;
};
class Student {
private:
    std::string name;
    int id;
    std::vector<SubjectGrade> grades;
public:
    Student(std::string studentName, int studentId) 
        : name(studentName), id(studentId) {}
    void addGrade(const std::string& subject, double score) {
        grades.push_back({subject, score});
    }
    std::string getName() const { return name; }
    int getId() const { return id; }
    const std::vector<SubjectGrade>& getGrades() const { return grades; }
    double calculateAverage() const {
        if (grades.empty()) return 0.0;
        
        double total = std::accumulate(grades.begin(), grades.end(), 0.0, 
            [](double sum, const SubjectGrade& sg) { return sum + sg.score; });
            
        return total / grades.size();
    }
    char getLetterGrade() const {
        double avg = calculateAverage();
        if (avg >= 90.0) return 'A';
        if (avg >= 80.0) return 'B';
        if (avg >= 70.0) return 'C';
        if (avg >= 60.0) return 'D';
        return 'F';
    }
};
class PerformanceTracker {
private:
    std::vector<Student> roster;
public:
    void addStudent(const Student& student) {
        roster.push_back(student);
    }
    bool isEmpty() const {
        return roster.empty();
    }
    void printClassReport() const {
        if (roster.empty()) {
            std::cout << "\n?? No student records found in the tracker.\n";
            return;
        }
        std::cout << "\n====================================================================\n";
        std::cout << "                      CLASS PERFORMANCE REPORT\n";
        std::cout << "====================================================================\n";
        std::cout << std::left << std::setw(10) << "ID" 
                  << std::setw(20) << "Name" 
                  << std::setw(15) << "Average Score" 
                  << std::setw(10) << "Grade" << "\n";
        std::cout << "--------------------------------------------------------------------\n";
        for (const auto& student : roster) {
            std::cout << std::left << std::setw(10) << student.getId()
                      << std::setw(20) << student.getName()
                      << std::fixed << std::setprecision(2) << std::setw(15) << student.calculateAverage()
                      << std::setw(10) << student.getLetterGrade() << "\n";
        }
        std::cout << "====================================================================\n";
    }
    void printClassAnalytics() const {
        if (roster.empty()) return;
        double overallSum = 0.0;
        double highest = 0.0;
        double lowest = 100.0;
        std::string topStudent = "None";
        for (const auto& student : roster) {
            double avg = student.calculateAverage();
            overallSum += avg;
            if (avg > highest) {
                highest = avg;
                topStudent = student.getName();
            }
            if (avg < lowest) {
                lowest = avg;
            }
        }
        std::cout << "\n==================================================\n";
        std::cout << "                ACADEMIC ANALYTICS\n";
        std::cout << "==================================================\n";
        std::cout << " Class Size:         " << roster.size() << " students\n";
        std::cout << " Class Average:      " << (overallSum / roster.size()) << "%\n";
        std::cout << " Highest Average:    " << highest << "% (" << topStudent << ")\n";
        std::cout << " Lowest Average:     " << lowest << "%\n";
        std::cout << "==================================================\n";
    }
};
void fixInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
int main() {
    PerformanceTracker tracker;
    int choice = 0;
    std::cout << "Welcome to the Academic Performance Tracker Engine \n";
    do {
        std::cout << "\n--- MAIN MENU ---\n";
        std::cout << "1. Add New Student & Grades\n";
        std::cout << "2. Generate Class Report Card\n";
        std::cout << "3. View Class Analytics Dashboard\n";
        std::cout << "4. Exit Application\n";
        std::cout << "Select an option: ";
        if (!(std::cin >> choice)) {
            std::cout << "? Invalid choice structure. Please select 1-4.\n";
            fixInputStream();
            continue;
        }
        if (choice == 1) {
            std::string name;
            int id;
            int totalSubjects;
            std::cin.ignore(); 
            std::cout << "Enter Student Name: ";
            std::getline(std::cin, name);
            while (true) {
                std::cout << "Enter Student ID (Numeric): ";
                if (std::cin >> id && id > 0) break;
                std::cout << "? Invalid ID format. ";
                fixInputStream();
            }
            while (true) {
                std::cout << "How many subjects to add for " << name << "? ";
                if (std::cin >> totalSubjects && totalSubjects > 0) break;
                std::cout << "? Must evaluate at least 1 subject. ";
                fixInputStream();
            }
            Student newStudent(name, id);
            for (int i = 0; i < totalSubjects; ++i) {
                std::string subject;
                double score;
                std::cin.ignore();
                std::cout << "  Enter Subject " << (i + 1) << " Name: ";
                std::getline(std::cin, subject);
                while (true) {
                    std::cout << "  Enter score for " << subject << " (0-100): ";
                    if (std::cin >> score && score >= 0.0 && score <= 100.0) break;
                    std::cout << "  ? Score must be between 0 and 100. ";
                    fixInputStream();
                }
                newStudent.addGrade(subject, score);
            }
            tracker.addStudent(newStudent);
            std::cout << "Student record compiled successfully.\n";
        } else if (choice == 2) {
            tracker.printClassReport();
        } 
		else if (choice == 3) {
            if (tracker.isEmpty()) {
                std::cout << "\n Dashboard empty. Please seed roster details first.\n";
            } 
			else {
                tracker.printClassAnalytics();
            }
        } 
		else if (choice != 4) {
            std::cout << "Choice out of bounds. Please enter a valid menu item.\n";
        }
    } 	while (choice != 4);
    std::cout << "\n?? System closed successfully. Good luck with your assignment!\n";
    return 0;
}