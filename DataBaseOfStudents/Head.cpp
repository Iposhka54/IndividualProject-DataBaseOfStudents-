#include "Head.h"

void Setup(int& count)
{
    srand(time(0));

    do
    {
        cout << "Введите количество студентов: " << endl;
        cin >> count;
        if (count <= 0)
        {
            cout << "Количество студентов не может быть меньше или равна 0!" << endl;
            Sleep(1000);
        }
    } while (count <= 0);
    CreateStudents(count);
}

void CreateStudents(int count)
{
    ofstream file("Students.txt");
    if (file.is_open())
    {
        for (int i = 1; i <= count; i++)
        {
            int gender = rand() % 2;
            if (gender == 0)
            {
                CreateMan(file);
            }
            else
            {
                CreateWoman(file);
            }
            if (i != count)
            {
                file << endl;
            }
        }
        file.close();
    }
    else
    {
        cout << "Ошибка открытия файла 'Students.txt'!" << endl;
    }
}

void CreateWoman(ofstream& file)
{
    string name = GetRandomLineFromFile("FemaleNames.txt");
    string lastname = GetRandomLineFromFile("FemaleLastNames.txt");
    string surname = GetRandomLineFromFile("FemaleSurnames.txt");

    file << lastname << " " << name << " " << surname;
}

void CreateMan(ofstream& file)
{
    string name = GetRandomLineFromFile("MaleNames.txt");
    string lastname = GetRandomLineFromFile("MaleLastNames.txt");
    string surname = GetRandomLineFromFile("MaleSurnames.txt");

    file << lastname << " " << name << " " << surname;
}

string GetRandomLineFromFile(const string& filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        int lineNumber = 0;
        int randLine = rand() % 200;
        while (getline(file, line))
        {
            if (lineNumber == randLine)
            {
                file.close();
                return line;
            }
            ++lineNumber;
        }
        file.close();
    }
    else
    {
        cout << "Ошибка чтения файла: " << filename << "!" << endl;
        return "";
    }
}

void FillStudents(int size, struct Student* students)
{
    ifstream file("Students.txt");
    if (file.is_open())
    {
        setlocale(LC_ALL, "Russian");
        for (int i = 0; i < size; i++)
        {
            string line;
            getline(file, line);
            students[i].FIO = line;
            students[i].averageGrade = ((rand() % (500 - 200 + 1) + 200)) / 100.0;
        }
    }
    file.close();
}

void DrawTable(int& count, struct Student* students)
{
    SortByAlphabet(count, students);
    system("cls");
    cout << "----------------------------------------------" << endl;
    cout << "| № |" << setw(17) << "ФИО" <<  "                  |" << "Балл| " << endl;
    cout << "----------------------------------------------" << endl;
    for (int i = 0; i < count; i++)
    {
        cout << "|" << setw(3) << i + 1 << "|";
        cout << setw(35) << students[i].FIO << "|";
        cout << setw(4) << students[i].averageGrade << "|" << endl;
        cout << "----------------------------------------------" << endl;

    }
}

void Menu(int& count, Student* students, bool& isEdit)
{
    char tmp;
    do
    {
        cout << "__________________________" << endl;
        cout << "|Что вы хотите сделать:  |" << endl;
        cout << "|Добавить студента - \"1\" |" << endl;
        cout << "|Удалить студента - \"2\"  |" << endl;
        cout << "|Изменить студента - \"3\" |" << endl;
        cout << "|Сортировка таблицы - \"4\"|" << endl;
        cout << "|Выйти из программы - \"e\"|" << endl;
        cout << "--------------------------" << endl;
        cin >> tmp;
        if (tmp != '1' and tmp != '2' and tmp != '3' and tmp != '4' and tmp != 'e')
        {
            cout << "Выберите из списка!" << endl;
            Sleep(1000);
        }
        cin.ignore();
    } while (tmp != '1' and tmp != '2' and tmp != '3' and tmp != '4' and tmp != 'e');
    switch (tmp)
    {
    case '1':
        AddStudent(count, students);
        break;
    case '2':
        DeleteStudent(count, students);
        break;
    case '3':
        EditStudent(count, students);
        break;
    case '4':
        SortStudents(count, students);
        break;
    case 'e':
        isEdit = false;
        break;
    }
}

void AddStudent(int& count, Student* students)
{
    count += 1;

    cout << "Введите ФИО нового студента: " << endl;
    getline(cin, students[count - 1].FIO);
    do
    {
        cout << "Введите средний балл студента:" << endl;
        cin >> students[count - 1].averageGrade;
        if (students[count - 1].averageGrade < 2 || students[count - 1].averageGrade > 5)
        {
            cout << "Введите корректное значение!" << endl;
        }
    } while (students[count - 1].averageGrade < 2 || students[count - 1].averageGrade > 5);

    //Округление оценки до двух знаков после запятой
    students[count - 1].averageGrade = round(students[count - 1].averageGrade * 100) / 100;
}

void DeleteStudent(int& count, Student* students)
{
    int number, proverka;
    do
    {
        do
        {
            cout << "Введите номер студента, которого хотите удалить: " << endl;
            cin >> number;
            if (number < 1 or number > count)
            {
                cout << "Введите корректное значение!" << endl;
            }
        } while (number < 1 or number > count);

        cout << "Повторите номер студента:" << endl;
        cin >> proverka;
        if (number != proverka)
        {
            cout << "Что-то произошло не так!" << endl;
        }
    } while (number != proverka);

    for (int i = number - 1; i < count - 1; i++)
    {
        students[i] = students[i + 1];
    }

    count--;
}

void EditStudent(int count, Student* students)
{
    int number;
    do
    {
        cout << "Введите номер студента, которого хотите отредактировать: " << endl;
        cin >> number;
        if (number < 1 or number > count)
        {
            cout << "Введите корректное значение!" << endl;
        }
    } while (number < 1 or number > count);

    char tmp;
    do
    {
        do
        {
            cout << "---------------------------------------------" << endl;
            cout << "|" << setw(3) << number << "|";
            cout <<setw(35) << students[number - 1].FIO << "|";
            cout << setw(4) << students[number - 1].averageGrade << "|" << endl;
            cout << "----------------------------------------------" << endl;
            Sleep(1500);
            cout << "_____________________________" << endl;
            cout << "|" << "Что вы хотите сделать:     |" << endl;
            cout << "|" << "Изменить ФИО - \"1\"         |" << endl;
            cout << "|" << "Изменить средний балл - \"2\"|" << endl;
            cout << "|" << "Выйти из редактора - \"0\"   |" << endl;
            cout << "-----------------------------" << endl;
            cin >> tmp;
            if (tmp != '1' and tmp != '2' and tmp != '0')
            {
                cout << "Выберите из списка!" << endl;
                Sleep(1000);
            }
            cin.ignore();
        } while (tmp != '1' and tmp != '2' and tmp != '0');

        switch (tmp)
        {
        case '1':
            cout << "Введите новое ФИО:" << endl;
            getline(cin, students[number - 1].FIO);
            break;
        case '2':
            double tempNumber;
            do
            {
                cout << "Введите новый средний балл:" << endl;
                cin >> tempNumber;
                if (tempNumber < 2 or tempNumber > 5)
                {
                    cout << "Введите корректное значение!" << endl;
                }
            } while (tempNumber < 2 or tempNumber > 5);
            students[number - 1].averageGrade = round(tempNumber * 100.0) / 100.0;
            break;
        }
    } while (tmp != '0');
}

void SortByAlphabet(int count, Student* students)
{
    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = i + 1; j < count; ++j)
        {
            if (students[i].FIO > students[j].FIO)
            {
                swap(students[i], students[j]);
            }
        }
    }
}

void SortByAveragePoint(int count, Student* students)
{
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (students[j].averageGrade > students[j + 1].averageGrade) {
                // Если текущий элемент больше следующего, меняем их местами
                swap(students[j], students[j + 1]);
            }
        }
    }
}

void ReverseStudents(int count, Student* students)
{
    int half = count / 2;

    for (int i = 0; i < half; i++)
    {
        swap(students[i], students[count - i - 1]);
    }
}

void SortStudents(int count, Student* students)
{
    char tmp;
    do
    {
        cout << "_________________________________________________" << endl;
        cout << "|Как хотите сортировать таблицу:                |" << endl;
        cout << "|По алфавиту(от А до Я) - \"1\"                   |" << endl;
        cout << "|По алфавиту(от Я до А) - \"2\"                   |" << endl;
        cout << "|По среднему баллу(от меньшего к большему) - \"3\"|" << endl;
        cout << "|По среднему баллу(от большего к меньшему) - \"4\"|" << endl;
        cout << "-------------------------------------------------" << endl;
        cin >> tmp;
        if (tmp != '1' and tmp != '2' and tmp != '3' and tmp != '4')
        {
            cout << "Выберите из списка!" << endl;
            Sleep(1000);
        }
        cin.ignore();
    } while (tmp != '1' and tmp != '2' and tmp != '3' and tmp != '4');
    switch (tmp)
    {
    case '1':
        SortByAlphabet(count, students);//От А до Я
        break;
    case '2':
        SortByAlphabet(count, students);//От А до Я
        ReverseStudents(count, students);//Перевернуть массив
        break;
    case '3':
        SortByAveragePoint(count, students);//От меньшего к большему
        break;
    case '4':
        SortByAveragePoint(count, students);//От меньшего к большему
        ReverseStudents(count, students);//Перевернуть массив
        break;
    }
}