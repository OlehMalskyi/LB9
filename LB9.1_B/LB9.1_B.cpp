#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>


using namespace std;

#pragma pack(push, 1)

enum Speciality { ITIS, RE, KN, KI, PZ };
string speciality_str[] = { "Інформатика ",
                            "Радіоелектроніка", "Комп'ютерні науки",
                            "Комп'ютерна інженерія", "Програмне забезпечення" };

struct Students
{
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;
    int grade_ped;
    union
    {
        int grade_program;
        int grade_nm;
    };
};

#pragma pack(pop)

void Create(Students* S, const int N);
void Print(Students* S, const int N);
double max_average_evaluation(Students* S, int N);
double Percentage(Students* S, const int N);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: "; cin >> N;

    Students* S = new Students[N];

    Create(S, N);
    Print(S, N);
    cout << "Найвищий середній бал " << setprecision(2) << max_average_evaluation(S, N) << endl;
    cout << "Процент студентів, які отримали 5 або 4 з фізики: " << setprecision(2) << Percentage(S, N) << "%";

    return 0;
}

void Create(Students* S, const int N)
{
    for (int i = 0; i < N; i++)
    {
        int speciality;
        cout << "Номер студента: " << i + 1 << endl;
        cin.get();
        cin.sync();
        cout << "Прізвище: "; getline(cin, S[i].surname); cout << endl;
        cout << "Курс: "; cin >> S[i].course; cout << endl;
        cout << "Спеціальність(0 - Інформатика, 1 - Радіоелектроніка, 2 - Комп'ютерні науки,";
        cout << "\n3 - Комп'ютерна інженерія, 4 - Програмне забезпечення): ";
        cin >> speciality;
        S[i].speciality = (Speciality)speciality;
        cout << "Оцінка з фізики: "; cin >> S[i].grade_physics; cout << endl;
        cout << "Оцінка з математики: "; cin >> S[i].grade_math; cout << endl;
        cout << "Оцінка з інформатики: "; cin >> S[i].grade_ped; cout << endl;
        switch (S[i].speciality)
        {
        case KN:
            cout << "Оцінка з програмування: "; cin >> S[i].grade_program; cout << endl;
            break;
        case ITIS:
            cout << "Оцінка з чисельних методів: "; cin >> S[i].grade_nm; cout << endl;
            break;
        default:
            cout << "Оцінка з педагогіки: "; cin >> S[i].grade_ped; cout << endl;
            break;
        }
        cout << endl;
    }
}

double max_average_evaluation(Students* S, int N)
{
    double max_average_kn = 0;
    double max_average_itis = 0;
    double max_average_default = 0;

    for (int i = 0; i < N; i++) {
        double average = 0;
        switch (S[i].speciality)
        {
        case KN:
            average = (S[i].grade_math + S[i].grade_physics + S[i].grade_program) / 3.0;
            max_average_kn = fmax(max_average_kn, average);
            break;
        case ITIS:
            average = (S[i].grade_math + S[i].grade_physics + S[i].grade_nm) / 3.0;
            max_average_itis = fmax(max_average_itis, average);
            break;
        default:
            average = (S[i].grade_math + S[i].grade_physics + S[i].grade_ped) / 3.0;
            max_average_default = fmax(max_average_default, average);
        }
    }

    double max_average = fmax(max_average_kn, fmax(max_average_itis, max_average_default));

    return max_average;
}

void Print(Students* S, const int N)
{
    cout << "====================================================================================================================================" << endl;
    cout << "|  №  |   Прізвище   | Курс |     Спеціальність     |  Фізика  |  Математика  |  Програмування  |  Чисельні методи  |  Педагогіка  |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << S[i].surname
            << "| " << setw(4) << right << S[i].course << " "
            << "| " << setw(22) << left << speciality_str[S[i].speciality]
            << "|  " << setw(7) << right << S[i].grade_physics << " "
            << "|  " << setw(11) << right << S[i].grade_math << " ";

        switch (S[i].speciality)
        {
        case KN:
            cout << "|" << setw(9) << S[i].grade_program << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        case ITIS:
            cout << "|" << setw(9) << S[i].grade_nm << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        default:
            cout << "|" << setw(9) << "-" << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << S[i].grade_ped << setw(7) << "|";
        }

        cout << endl;
    }
    cout << "====================================================================================================================================" << endl << endl;
}

double Percentage(Students* S, const int N)
{
    int k = 0;
    for (int i = 0; i < N; i++)
        if (S[i].grade_physics == 5 || S[i].grade_physics == 4)
            k++;
    return k / (N * 1.0) * 100;
}
