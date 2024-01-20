#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>
using namespace std;

class Logger
{
    static Logger* instance; // 1) приватный статический указатель на единственный экземпляр класса
    int log_сount = 0; // сколько раз происходила запись строки в файл

    Logger() // 2) конструктор - приватный (запрещает создавать объекты за пределами класса)
    {
    }

public:
    static Logger* GetInstance() // 3) публичный статический геттер на получение адреса единственного объекта
    {
        // если объекта журнала не существует - он создаётся
        return instance == nullptr ? instance = new Logger() : instance;
    }

    void Write(string message) // записать в журнал строку текста
    {
        log_сount++;
        cout << log_сount << ": " << message << "\n";
        // альтернативные варианты:
        // 1) записать строку в коллекцию (массив, список и тд) и хранить данные в памяти
        // 2) записать строку в файл
        ofstream output_file("log.txt", ios::app);
        if (output_file.is_open()) {
            output_file << message << "\n";
            output_file.close();
            //cout << "Строка успешно записана в файл.";
        }
        else {
            //cerr << "Не удалось открыть файл для записи.";
        }
        // 3) отправлять данные по сети
    }

    void Write(int value)
    {
        Write(to_string(value));
    }
};

Logger* Logger::instance = nullptr;

class Date {
    unsigned short day;
    unsigned short month;
    long long year;
public:
    Date() :Date(25, 12, 2023) {}

    Date(unsigned short day, unsigned short month, long long year)
    {
        SetDay(day);
        SetMonth(month);
        SetYear(year);
    }

    Date(unsigned short day, unsigned short month) :Date(day, month, 2005) {}

    void PrintDate() const
    {
        cout << day << "." << month << "." << year << "\n";
    }

    void SetDay(unsigned short day)
    {
        if (day == 0 || day > 31) throw "ERROR! The day must be from 0 to 31!";
        this->day = day;
    }

    void SetMonth(unsigned short month)
    {
        if (month == 0 || month > 12) throw "ERROR! The day must be from 0 to 12!";
        this->month = month;
    }

    void SetYear(long long year)
    {
        this->year = year;
    }

    unsigned short GetDay() const
    {
        return day;
    }

    unsigned short GetMonth() const
    {
        return month;
    }

    long long GetYear() const
    {
        return year;
    }
};

class Student {
    string surname;
    string name;
    string patronymic;
    string adress;
    string phoneNumber;
    unsigned int countPractic = 0;
    unsigned int countHW = 0;
    unsigned int countExam = 0;
    int* gradeOfPractic = new int[countPractic];
    int* gradeOfHW = new int[countHW];
    int* gradeOfExam = new int[countExam];

public:
    Student() :Student("Shostak", "Yevhenii", "Stanislavovich", "Mir cel Batrin 32", "0661124661") {}

    Student(string surname, string name, string patronymic, string adress, string phoneNumber)
    {
        SetSurname(surname);
        SetName(name);
        SetPatronymic(patronymic);
        SetAdress(adress);
        SetPhoneNumber(phoneNumber);
        Logger::GetInstance()->Write("Student has been created");
        TimeNow();
    }

    Student(string surname, string name, string patronymic, string adress) :Student(surname, name, patronymic, adress, "0661124661") {}

    ~Student()
    {
        if (gradeOfPractic != nullptr)
            delete[] gradeOfPractic;
        if (gradeOfHW != nullptr)
            delete[] gradeOfHW;
        if (gradeOfExam != nullptr)
            delete[] gradeOfExam;
        Logger::GetInstance()->Write("Student has been destroyed");
        TimeNow();
    }

    void PrintStudent() const
    {
        cout << "Surname: " << surname << "\n";
        cout << "Name: " << name << "\n";
        cout << "Patronymic: " << patronymic << "\n";
        cout << "Adress: " << adress << "\n";
        cout << "Phone number: " << phoneNumber << "\n";
    }

    void TimeNow()
    {
        SYSTEMTIME st;
        GetSystemTime(&st);
        
        st.wHour = (st.wHour + 2) % 24;
        printf("%04d-%02d-%02d %02d:%02d:%02d\n\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
    }

    void SetSurname(string surname)
    {
        this->surname = surname;
    }

    void SetName(string name)
    {
        this->name = name;
    }

    void SetPatronymic(string patronymic)
    {
        this->patronymic = patronymic;
    }

    void SetAdress(string adress)
    {
        this->adress = adress;
    }

    void SetPhoneNumber(string phoneNumber)
    {
        this->phoneNumber = phoneNumber;
    }

    string GetSurname() const
    {
        return surname;
    }

    string GetName() const
    {
        return name;
    }

    string GetPatronymic() const
    {
        return patronymic;
    }

    string GetAdress() const
    {
        return adress;
    }

    string GetPhoneNumber() const
    {
        return phoneNumber;
    }

    ///Practic
    void AddPractic(int grade)
    {
        int* temp = new int[countPractic + 1];
        for (int i = 0; i < countPractic; i++)
        {
            temp[i] = gradeOfPractic[i];
        }
        temp[countPractic] = grade;
        countPractic++;
        delete[] gradeOfPractic;
        gradeOfPractic = temp;
    }

    void PrintPractic() const
    {
        for (int i = 0; i < countPractic; i++)
        {
            cout << gradeOfPractic[i] << ", ";
        }
    }

    int GetPracticRates(unsigned int index) const
    {
        if (index < countPractic)
        {
            return gradeOfPractic[index];
        }
        else
        {
            cout << "Index is out of bounds\n";
        }
    }

    ///HW
    void AddHW(int grade)
    {
        int* temp = new int[countHW + 1];
        for (int i = 0; i < countHW; i++)
        {
            temp[i] = gradeOfHW[i];
        }
        temp[countHW] = grade;
        countHW++;
        delete[] gradeOfHW;
        gradeOfHW = temp;
    }

    void PrintHW() const
    {
        for (int i = 0; i < countHW; i++)
        {
            cout << gradeOfHW[i] << ", ";
        }
    }

    int GetHWRates(unsigned int index) const
    {
        if (index < countHW)
        {
            return gradeOfHW[index];
        }
        else
        {
            cout << "Index is out of bounds\n";
        }
    }

    ///Exam
    void AddExam(int grade)
    {
        int* temp = new int[countExam + 1];
        for (int i = 0; i < countExam; i++)
        {
            temp[i] = gradeOfExam[i];
        }
        temp[countExam] = grade;
        countExam++;
        delete[] gradeOfExam;
        gradeOfExam = temp;
    }

    void PrintExam() const
    {
        for (int i = 0; i < countExam; i++)
        {
            cout << gradeOfExam[i] << ", ";
        }
    }

    int GetExamRates(unsigned int index) const
    {
        if (index < countExam)
        {
            return gradeOfExam[index];
        }
        else
        {
            cout << "Index is out of bounds\n";
        }
    }
};

int main()
{
    Sleep(NULL);

    srand(time(NULL));

    Student student;
    Date date;

    Date d(11, 8);

    student.PrintStudent();
    cout << "Birthday: ";
    d.PrintDate();
    cout << "Start study: ";
    date.PrintDate();
    cout << "\n";

    cout << "Practic: ";
    student.AddPractic(12);
    student.AddPractic(10);
    student.AddPractic(8);
    student.PrintPractic();
    cout << "\n\n";

    cout << "Home Work: ";
    student.AddHW(10);
    student.AddHW(12);
    student.PrintHW();
    cout << "\n\n";

    cout << "Exam: ";
    student.AddExam(7);
    student.AddExam(7);
    student.AddExam(10);
    student.PrintExam();
    cout << "\n\n";
}

