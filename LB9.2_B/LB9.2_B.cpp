#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>


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
        int grade_prog;
        int grade_nm;
    };
};

#pragma pack(pop)

void Create(Students* S, const int N);
double student_avarage_evaluation(Students* S, const int i);
void Print(Students* S, const int N);
void p_sort(Students* S, const int N);
int* i_sort(Students* S, const int N);
void i_print(Students* S, int* I, const int N);
bool b_search(Students* S, const int N, const string surname, const double avarage_evaluation, const int math_grade);


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: "; cin >> N;

    Students* S = new Students[N];

    string f_surname;
    double f_avarage_evaluation;
    int f_math_grade;

    int MenuItem;

    while (true)
    {
        cout << endl << endl << endl;
        cout << "Оберіть дію:" << endl;
        cout << "1 - Ввести інформацію про студентів" << endl;
        cout << "2 - Вивести інформацію про студентів" << endl;
        cout << "3 - Фізично впорядкувати інформацію" << endl;
        cout << "4 - Індексно впорядкувати інформацію" << endl;
        cout << "5 - Пошук студента"; cout << endl;
        cout << "0 - Завершити роботу програми" << endl;
        cout << "Введіть: "; cin >> MenuItem; cout << endl;

        switch (MenuItem)
        {
        case 1:
            Create(S, N);
            break;
        case 2:
            Print(S, N);
            break;
        case 3:
            p_sort(S, N);
            Print(S, N);
            break;
        case 4:
            i_print(S, i_sort(S, N), N);
            break;
        case 5:
            cout << "Введіть критерії пошуку: " << endl;
            cout << "Прізвище" << endl;
            cin.get();
            cin.sync();
            getline(cin, f_surname); cout << endl;

            do
            {
                cout << "Середній бал" << endl;
                cin >> f_avarage_evaluation; cout << endl;
            } while (f_avarage_evaluation < 1 || f_avarage_evaluation > 5);

            do
            {
                cout << "Бал з математики" << endl;
                cin >> f_math_grade; cout << endl;
            } while (f_math_grade < 1 || f_math_grade > 5);

            if (b_search(S, N, f_surname, f_avarage_evaluation, f_math_grade))
            {
                cout << "Студент знайдений" << endl;
            }
            else {
                cout << "Студент не знайдений" << endl;
            }
        }

        if (MenuItem == 0) break;
    }

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

        do
        {
            cout << "Курс: "; cin >> S[i].course; cout << endl;
        } while (S[i].course < 1 || S[i].course > 6);

        do
        {
            cout << "Спеціальність(0 - Інформатика, 1 - Радіоелектроніка, 2 - Комп'ютерні науки,";
            cout << "\n3 - Комп'ютерна інженерія, 4 - Програмне забезпечення): ";
            cin >> speciality;
            S[i].speciality = (Speciality)speciality;
        } while (S[i].speciality < 0 || S[i].speciality > 4);

        do
        {
            cout << "Оцінка з фізики: "; cin >> S[i].grade_physics; cout << endl;
        } while (S[i].grade_physics < 1 || S[i].grade_physics > 5);

        do
        {
            cout << "Оцінка з математики: "; cin >> S[i].grade_math; cout << endl;
        } while (S[i].grade_math < 1 || S[i].grade_math > 5);
        switch (S[i].speciality)
        {
        case KN:
            do
            {
                cout << "Оцінка з програмування: "; cin >> S[i].grade_prog; cout << endl;
            } while (S[i].grade_prog < 1 || S[i].grade_prog > 5);
            break;

        case ITIS:
            do
            {
                cout << "Оцінка з чисельних методів: "; cin >> S[i].grade_nm; cout << endl;
            } while (S[i].grade_nm < 1 || S[i].grade_nm > 5);
            break;

        default:
            do
            {
                cout << "Оцінка з педагогіки: "; cin >> S[i].grade_ped; cout << endl;
            } while (S[i].grade_ped < 1 || S[i].grade_ped > 5);
        }
        cout << endl;
    }
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
            cout << "|" << setw(9) << S[i].grade_prog << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        case ITIS:
            cout << "|" << setw(9) << "-" << setw(9);
            cout << "|" << setw(9) << S[i].grade_nm << setw(11);
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

double student_avarage_evaluation(Students* S, int i)
{
    double avarage;
    switch (S[i].speciality)
    {
    case KN:
        avarage = (S[i].grade_math * 1. + S[i].grade_physics * 1. + S[i].grade_prog * 1.) / 3.;
        break;
    case ITIS:
        avarage = (S[i].grade_math * 1. + S[i].grade_physics * 1. + S[i].grade_nm * 1.) / 3.;
        break;
    default:
        avarage = (S[i].grade_math * 1. + S[i].grade_physics * 1. + S[i].grade_ped * 1.) / 3.;
    }
    cout << endl;
    return avarage;
}

void p_sort(Students* S, int N)
{
    Students temp;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if ((student_avarage_evaluation(S, j) > student_avarage_evaluation(S, j + 1))
                || (student_avarage_evaluation(S, j) == student_avarage_evaluation(S, j + 1))
                && (S[j].grade_math > S[j + 1].grade_math)
                || (student_avarage_evaluation(S, j) == student_avarage_evaluation(S, j + 1))
                && (S[j].grade_math == S[j + 1].grade_math)
                && (S[j].surname > S[j].surname))
            {
                temp = S[j];
                S[j] = S[j + 1];
                S[j + 1] = temp;
            }

        }
    }
}

int* i_sort(Students* S, const int N)
{
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;

    int j, value;
    for (int i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1;
            (student_avarage_evaluation(S, j) > student_avarage_evaluation(S, j + 1))
            || (student_avarage_evaluation(S, j) == student_avarage_evaluation(S, j + 1))
            && (S[j].grade_math > S[j + 1].grade_math)
            || (student_avarage_evaluation(S, j) == student_avarage_evaluation(S, j + 1))
            && (S[j].grade_math == S[j + 1].grade_math)
            && (S[j].surname > S[j].surname);
            j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

void i_print(Students* S, int* I, const int N)
{
    cout << "====================================================================================================================================" << endl;
    cout << "|  №  |   Прізвище   | Курс |     Спеціальність     |  Фізика  |  Математика  |  Програмування  |  Чисельні методи  |  Педагогіка  |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << S[I[i]].surname
            << "| " << setw(4) << right << S[I[i]].course << " "
            << "| " << setw(22) << left << speciality_str[S[I[i]].speciality]
            << "|  " << setw(7) << right << S[I[i]].grade_physics << " "
            << "|  " << setw(11) << right << S[I[i]].grade_math << " ";
        switch (S[I[i]].speciality)
        {
        case KN:
            cout << "|" << setw(9) << S[I[i]].grade_prog << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        case ITIS:
            cout << "|" << setw(9) << S[I[i]].grade_nm << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        default:
            cout << "|" << setw(9) << "-" << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << S[I[i]].grade_ped << setw(7) << "|";
        }
        cout << endl;
    }
    cout << "====================================================================================================================================" << endl << endl;
}

bool b_search(Students* S, const int N, const string surname, const double avarage_evaluation, const int math_grade)
{
    int L = 0, R = N - 1, m;
    do
    {
        m = (L + R) / 2;
        if ((S[m].surname == surname
            &&
            (student_avarage_evaluation(S, m) == avarage_evaluation)
            &&
            (S[m].grade_math == math_grade)))
        {
            return 1;
        }

        if ((S[m].grade_math < math_grade)
            ||
            (S[m].grade_math == math_grade
                &&
                student_avarage_evaluation(S, m) < avarage_evaluation)
            ||
            (S[m].grade_math == math_grade
                &&
                student_avarage_evaluation(S, m) == avarage_evaluation
                &&
                S[m].surname < surname))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);

    return 0;
}