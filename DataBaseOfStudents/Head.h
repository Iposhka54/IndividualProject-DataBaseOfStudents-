#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <ctime>
#include <conio.h>
#include <iomanip>

using namespace std;

struct Student
{
    string FIO;
    double averageGrade;
};
void Setup(int& count);
void CreateStudents(int count);
void CreateWoman(ofstream& file);
void CreateMan(ofstream& file);
string GetRandomLineFromFile(const string& filename);
void FillStudents(int size, struct Student* students);
void DrawTable(int& count, struct Student* students);
void Menu(int& count, Student* students, bool& isEdit);
void AddStudent(int& count, Student* students);
void DeleteStudent(int& count, Student* students);
void EditStudent(int count, Student* students);
void SortByAlphabet(int count, Student* students);
void SortByAveragePoint(int count, Student* students);
void ReverseStudents(int count, Student* students);
void SortStudents(int count, Student* students);