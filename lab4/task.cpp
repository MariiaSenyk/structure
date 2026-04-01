#include <iostream>
#include <string>
using namespace std;
struct Abiturient
{
    string name;
    string gender;
    string specialty;
    int exam[3];

    Abiturient()
    {
        name = "";
        gender = "";
        specialty = "";
        for (int i = 0; i < 3; i++)
            exam[i] = 0;
    }

    Abiturient(string n, string g, string s, const int e[3])
    {
        name = n;
        gender = g;
        specialty = s;
        for (int i = 0; i < 3; i++)
            exam[i] = e[i];
    }

    float getAverageScore() const
    {
        return (exam[0] + exam[1] + exam[2]) / 3.0f;
    }

    int countVowels() const
    {
        int count = 0;
        // char vowels = 'aeo', ['a', 'o']
        for (char c : name) {
            char lowerChar = tolower(c);
            if (lowerChar == 'a' || lowerChar == 'e' || lowerChar == 'i' || lowerChar == 'o' || lowerChar == 'u' || lowerChar == 'y') {
                count++;
            }
        }
        return count;
    }

    void display() const
    {
        cout << "Surname: " << name << "\n";
        cout << "Specialty: " << specialty << "\n";
        cout << "Genre: " << gender << "\n";
        cout << "Exam results: " << exam[0] << ", " << exam[1] << ", " << exam[2] << "\n";
        cout << "Average score: " << getAverageScore() << "\n\n";
    }

    bool lessThan3() const
    {
        return countVowels() <= 3;
    }

    static void printStudentsBelow(Abiturient students[], int n, float passingScore)
    {
        bool found = false;
        cout << "\nApplicants with a score below the passing score:\n";
        for (int i = 0; i < n; i++) {
            if (students[i].getAverageScore() < passingScore) {
                students[i].display();
                found = true;
            }
        }
        if (!found)
        {
            cout << "There are no students with a score below passing grade\n";
        }
    }

    static void printStudentsWithLessThan3(Abiturient students[], int n)
    {
        bool found = false;
        cout << "\nАбітурієнти з менше ніж 3 голосними в прізвищі:\n";
        for (int i = 0; i < n; i++) {
            if (students[i].lessThan3()) {
                students[i].display();
                found = true;
            }
        }
        if (!found)
        {
            cout << "No abiturients with fewer than 3 vowels in their last name were found\n";
        }
    }

    static void printAllStudents(Abiturient students[], int n)
    {
        cout << "\nAll abiturients:\n";
        for (int i = 0; i < n; i++) {
            students[i].display();
        }
    }

    static void removeWithAverage(Abiturient students[], int& n)
    {
        for (int i = 0; i < n; i++) {
            if (students[i].getAverageScore() == 5) {
                for (int j = i; j < n - 1; j++) {
                    students[j] = students[j + 1];
                }
                n--;
                i--;
            }
        }
    }
};

int main()
{
    int numberOfAbi;
    cout << "Enter the number of abiturients: ";
    cin >> numberOfAbi;
    Abiturient students[numberOfAbi];

    for (int i = 0; i < numberOfAbi; i++)
    {
        string name, gender, spec;
        int exam[3];
        cout << "\nEnter data for the abiturient " << i + 1 << ":\n";
        cout << "Surname: ";
        cin >> name;
        cout << "Gender(M/F): ";
        cin >> gender;
        cout << "Specialty: ";
        cin >> spec;
        cout << "Scores for three exams: ";
        for (int j = 0; j < 3; j++) {
            cin >> exam[j];
        }
        students[i] = Abiturient(name, gender, spec, exam);
    }

    float passingScore;
    cout << "\nEnter passing score: ";
    cin >> passingScore;

    Abiturient abiturient;
    abiturient.printStudentsBelow(students, numberOfAbi, passingScore);
    abiturient.printStudentsWithLessThan3(students, numberOfAbi);
    abiturient.printAllStudents(students, numberOfAbi);
    abiturient.removeWithAverage(students, numberOfAbi);

    if (numberOfAbi > 0) {
        cout << "\nAfter deletion with an average score of 5:\n";
        abiturient.printAllStudents(students, numberOfAbi);
    } else {
        cout << "\nThere are no abiturients after removal with an average score of 5\n";
    }

    return 0;
}