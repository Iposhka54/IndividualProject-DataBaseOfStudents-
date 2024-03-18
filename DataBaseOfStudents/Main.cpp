#include <iostream>
#include <fstream>
#include <Windows.h>
#include <String>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include "Head.h"
using namespace std;

int main()
{

    setlocale(0, "");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    bool isEdit = true;
    int count;
    struct Student students[1000];

    srand(time(0));
    Setup(count);
    FillStudents(count, students);
    do
    {
        DrawTable(count, students);
        Menu(count, students, isEdit);
    } while (isEdit);

    cout << "Спасибо за работу!" << endl;
    Sleep(1000);
    return 0;
}
