#include <iostream>
#include <math.h>
#include <windows.h>
#include <sstream>
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
void evaluation();
void generator();
double S_temp=0;
int count_L;
int main()
{
	setlocale(LC_ALL, "rus");
	int key = 10;
	while (key != 0)
	{
		cout << "Введите действие:\n1)Оценка стойкости;\n2)Генератор паролей;\n0)Завершение работы\nНомер функции: ";
		cin >> key;
		if ((key == 1) || (key == 2) || (key == 0))
		{
			switch (key)
			{
			case 1:
				evaluation();
				break;
			case 2:
				generator();
				break;
			case 0:
				cout << "До свидания!\n";
				break;
			}
		}
		else
		{
			SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_INTENSITY);
			cout << "Неправильный номер!\n\n";
			SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
	}
	system("pause");
	return 0;
}
void evaluation()
{
	system("cls");
	char P[100], V[100], T[100], snoop1[10], snoop2[10], snoop3[10], snoop4[10];
	double S, P_d, V_d, T_d;
	int n;
	cout << "Введите вероятность подбора пароля\n";
	SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Пример:(10^-7)\n";
	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "Ввод: ";
	cin >> P;
	cout << "Введите скорость подбора пароля\n";
	SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Пример:(15p/second, 15p/minute, 15p/hour, 15p/day, 15p/week, 15p/month, 15p/year)\n";
	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "Ввод: ";
	cin >> V;
	cout << "Введите срок действия пароля\n";
	SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Пример:(15/seconds, 15/minutes, 15/hours, 15/days, 15/weeks, 15/months, 15/years)\n";
	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "Ввод: ";
	cin >> T;
	n = strlen(P);
	bool check = 0;
	int coord;
	for (int i = 0; i < n; i++)
	{
		if (P[i] == '^')
		{
			check = 1;
			coord = i;
		}
	}
	if (check == 0)
	{
		std::stringstream ss(P);
		ss >> P_d;
	}
	else
	{
		double temp, temp2;
		for (int i = 0; i < coord; i++)
		{
			snoop1[i] = P[i];
		}
		std::stringstream ss(snoop1);
		ss >> temp;
		for (int i = (coord + 1); i < n; i++)
		{
			snoop2[i - (coord + 1)] = P[i];
		}
		std::stringstream ss1(snoop2);
		ss1 >> temp2;
		P_d = pow(temp, temp2);
	}
	n = strlen(V);
	for (int i = 0; i < n; i++)
	{
		if (V[i] == '/')
		{
			coord = i;
		}
	}
	n = coord - 1;
	for (int i = 0; i < n; i++)
	{
		snoop3[i] = V[i];
	}
	std::stringstream ss2(snoop3);
	ss2 >> V_d;
	switch (V[coord + 1])
	{
	case 's':
		V_d = V_d * 60;
		break;
	case 'h':
		V_d = V_d / 60;
		break;
	case 'd':
		V_d = V_d / 1440;
		break;
	case 'w':
		V_d = V_d / 10080;
		break;
	case 'y':
		V_d = V_d / 525600;
		break;
	case 'm':
		switch (V[coord + 2])
		{
		case 'o':
			V_d = V_d / 42192;
			break;
		}
		break;
	}
	n = strlen(T);
	for (int i = 0; i < n; i++)
	{
		if (T[i] == '/')
		{
			coord = i;
		}
	}
	for (int i = 0; i < coord; i++)
	{
		snoop4[i] = T[i];
	}
	std::stringstream ss3(snoop4);
	ss3 >> T_d;
	switch (T[coord + 1])
	{
	case 's':
		T_d = T_d / 60;
		break;
	case 'h':
		T_d = T_d * 60;
		break;
	case 'd':
		T_d = T_d * 1440;
		break;
	case 'w':
		T_d = T_d * 10080;
		break;
	case 'y':
		T_d = T_d * 525600;
		break;
	case 'm':
		switch (T[coord + 2])
		{
		case 'o':
			T_d = T_d * 42192;
			break;
		}
		break;
	}
	cout << "\nВведеные данные:\nВероятность подбора пароля: " << P_d << "\nСкорость перебора паролей в минуту: " << V_d << "\nСрок действия пароля в минутах: " << T_d << endl;
	S_temp = ceil(V_d * T_d / P_d);
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "Нижняя граница числа возможных паролей: " << S_temp << endl;
	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "Известна ли мощность алфавита? Если да, укажите мощность, если нет, укажите 0: ";
	int A;
	cin >> A;
	if (A == 0)
	{
		int count_A = 10;
		check = 0;
		while ((count_A <= 128) && (check == 0))
		{
			count_L = 4;
			while ((count_L <= 128) && (check == 0))
			{
				if (S_temp <= pow(count_A, count_L))
				{
					check = 1;
				}
				count_L++;
			}
			count_A++;
		}
		count_L--;
		count_A--;
		SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Количество символов в алфавите:" << count_A << "\nКоличество символов в пароле: " << count_L << endl << endl;
		SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		if (check == 0)
		{
			SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "При заданных параметрах невозможно подобрать варианты пароля!\n\n";
			SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
	}
	else
	{
		check = 0;
		int count_L = 4;
		while ((S_temp <= pow(A, count_L))&&(count_L<=128))
		{
			count_L++;
			check = 1;
		}
		if (check == 1)
		{
			SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "Длина пароля может составлять: " << count_L << endl << endl;
			SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else
		{
			SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "При заданных параметрах невозможно подобрать варианты пароля!\n\n";
			SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
	}
}
void generator()
{
	char answer;
	system("cls");
	int A = 36, L;
	cout << "Добро пожаловать в генератор пароля!\n";
	char alfabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	char numbers[10] = { '0','1','2','3','4','5','6','7','8','9' };
	if (S_temp != 0)
	{
		cout << "Программа предлагает длину пароля: " << count_L;
		cout << "\nВы согласны с этим?(Y/N): ";
		cin >> answer;
		if (answer == 'N')
		{
			cout << "Введите желаемую длину пароля: ";
			cin >> L;
		}
		else
		{
			L = count_L;
		}
	}
	else
	{
		cout << "Программа не смогла определить ранее введеные параметры!\nВведите желаемую длину пароля: ";
		cin >> L;
	}
	int temp;
	char* quest = new char[L];
	for (int i = 0; i < L; i++)
	{
		temp = rand() % 2 + 1;
		switch (temp)
		{
		case 1:
			quest[i] = alfabet[rand() % 26 + 1];
			break;
		case 2:
			quest[i] = numbers[rand() % 10 + 1];
			break;
		}
	}
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "Полученый пароль: ";
	for (int i = 0; i < L; i++)
	{
		cout << quest[i];
	}
	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << endl<<endl;
	delete[] quest;
}