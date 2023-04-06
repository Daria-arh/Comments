// ConsoleApplication8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <cassert>

using namespace std;

//создание класса
class Matrix
{
	//приват
	//поля класса
	int sizeY;
	int sizeX;
	int* data;
	int index2D(int y, int x) const
	{
		return y * sizeX + x;
	}
	int index2D(int y, int x, int sizeXP) const
	{
		return y * sizeXP + x;
	}
public:
	//публичные методы
	//конструктор с параметрами
	Matrix(int sizeYP, int sizeXP)
		: sizeY{ sizeYP }, sizeX{ sizeXP }, data{ new int[sizeYP * sizeXP] } {}

	//оператор скобок с целочисленным типом данных
	int operator() (int y, int x) const
	{
		return *(data + index2D(y, x));
	}

	//оператор скобок с адресом
	int& operator() (int y, int x)
	{
		return *(data + index2D(y, x));
	}

	//изменение количества столбцов
	void deleteColumn(int columnPos)
	{
		--sizeX;
		int* newData{ new int[sizeY * sizeX] };
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(y, x)) = *(data + index2D(y, x + (x >= columnPos)));
			}
		}
		delete[] data;
		data = newData;
	}

	//Изменение элементов столбцов массива
	void addColumn(int columnPos, int* newCol = nullptr)
	{
		int* newData{ new int[sizeY * (sizeX + 1)] };
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(y, x + (x >= columnPos), sizeX + 1)) = *(data + index2D(y, x));
			}
			*(newData + index2D(y, columnPos, sizeX + 1)) = newCol ? *(newCol + y) : 0;
		}
		delete[] data;
		data = newData;
		++sizeX;
	}

	//изменение колличества строк
	void deleteRow(int rowPos)
	{
		--sizeY;
		int* newData{ new int[sizeY * sizeX] };
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(y, x)) = *(data + index2D(y, x + (x >= rowPos), x));
			}
		}
		delete[] data;
		data = newData;
	}

	//изменение элементов строк массива
	void addRow(int rowPos, int* newRow = nullptr)
	{
		int* newData{ new int[(sizeY + 1) * sizeX] };
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(y + (y >= rowPos), x)) = *(data + index2D(y, x));
			}
		}
		for (int x{ 0 }; x < sizeX; ++x)
		{
			*(newData + index2D(rowPos, x)) = newRow ? *(newRow + x) : 0;
		}
		delete[] data;
		data = newData;
		++sizeY;
	}

	//вывод всего массива
	void print() const
	{
		//цикл отвечающий за вывод столбцов
		for (int y{ 0 }; y < sizeY; ++y)
		{
			//цикл отвечающий за вывод строк
			for (int x{ 0 }; x < sizeX; ++x)
			{
				cout << (*this)(y, x) << '\t';
			}
			cout << '\n';
		}
		cout << '\n';
	}

	//деструктор класса
	~Matrix() { delete[] data; }

};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	//переменная, не учавствующая в основном коде
#define USER_INPUT 0;
	int rows{ 3 };
	int columns{ 3 };
	int counter{ 1 };

	//условие при котором выполняется часть кода внутри #if - #endif
#if USER_INPUT == 1
	cout << "Enter matrix rows count\n";
	cin >> rows;
	cout << "Enter matrix columns count\n";
	cin >> columns;
#endif

	//создание массива через класс. Обращение к конструктору с параметрами
	Matrix matrix{ rows, columns };
	//заполнение элементов массива
	for (int y{ 0 }; y < rows; ++y)
	{
		for (int x{ 0 }; x < columns; ++x)
		{
			matrix(y, x) = counter++;
		}
	}
	//вывод массива
	matrix.print();
	//переход на новую строку
	cout << endl;

	//вызов метода, который изменяет колличество столбцов созданного массива
	matrix.deleteColumn(2);
	matrix.print();
	cout << endl;

	//создание массива и вызов метода, который изменит значения столбца старого массива на значения нового
	int* newColumn{ new int[columns] {11, 22, 33} };
	matrix.addColumn(0, newColumn);
	matrix.print();
	cout << endl;

	//вызов метода, который изменяет колличество строк созданного массива
	matrix.deleteRow(2);
	matrix.print();
	cout << endl;

	//создание массива и вызов метода, который изменит значения строки старого массива на значения нового
	int* newRow{ new int[rows] {111, 222, 333} };
	matrix.addRow(2, newRow);
	matrix.print();
	cout << endl;

	//очищение новых массивов
	delete[] newRow;
	delete[] newColumn;

}