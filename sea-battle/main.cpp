#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

const short N = 10;
const short Num_Ships = 10;

short Ships_id = 1;
short Ships[11] = { 0 };
short Ships2[11] = { 0 };

// передвижения курсора
void gotox(short x, short y) {//переставления курсора в заданные кординаты в консольном окне
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
// растановка коробля на поле
void ship_show(short x, short y, short dir, short size_ship) {

	for (short i = 0; i < size_ship; i++) {

		gotox(x + 2, y + 2);
		cout << "#";
		if (dir == 0){
			switch (dir) {
			case 0:
				x++;
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				x--;
				break;
			case 3:
				y--;
				break;
			}
		}
		else {
			switch (dir) {
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			}
		}
	}
}
//находится ли корабль в пределах карты
bool ship_in_map(short x, short y, short dir, short size_ship) {
	bool in_map = 1;// пройдина ли проверка
	for (short i = 0; i < size_ship; i++) {
		if (x < 0 || y < 0 || x >= N || y >= N) {
			in_map = 0;
			break;
		}
		switch (dir) {
		case 0:
			x++;
			break;
		case 1:
			y++;
			break;
		case 2:
			x--;
			break;
		case 3:
			y--;
			break;
		}
	}
	return in_map;
}
//проверка возможности постановки коробля при ручной постанки
bool set_ship(short map[N][N], short x, short y, short dir, short size_ship) {
	short temp_x = x;
	short temp_y = y;
	bool setting_is_possible = 1;// пройдина ли проверка
	//проверка возможности постановки коробля
	for (short i = 0; i < size_ship; i++) {
		if (x < 0 || y < 0 || x >= N || y >= N) {
			setting_is_possible = 0;
			break;
		}
		if (map[x][y] >= 1) {
			setting_is_possible = 0;
			break;
		}
		if (y < N - 1) {
			if (map[x][y + 1] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		if (y > 0) {
			if (map[x][y - 1] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		if (x < N - 1) {
			if (map[x + 1][y] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		if (x < N - 1 && y < N - 1) {
			if (map[x + 1][y + 1] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		if (x < N - 1 && y > 0) {
			if (map[x + 1][y - 1] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		if (x > 0) {
			if (map[x - 1][y] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		if (x > 0 && y < N - 1) {
			if (map[x - 1][y + 1] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		if (x > 0 && y > 0) {
			if (map[x - 1][y - 1] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}

		switch (dir) {
		case 0:
			x++;
			break;
		case 1:
			y++;
			break;
		case 2:
			x--;
			break;
		case 3:
			y--;
			break;
		}
	}
	if (setting_is_possible == 1) {
		x = temp_x;
		y = temp_y;
		for (int i = 0; i < size_ship; i++) {//запись коробля в массив
			map[x][y] = Ships_id;
			switch (dir) {
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			}
		}
		Ships[Ships_id] = size_ship;
		Ships_id += 1;
	}

	return setting_is_possible;
}
// рандомная расстановка короблей
void set_rand_ships(short map[N][N], short size_ship, short ship_id) {
	short x, y;
	short dir = 0;//направление
	short cout_ship = 0;
	short temp_x = 0;
	short temp_y = 0;
	while (cout_ship < 1) {
		x = rand() % N;//первичная позиция
		y = rand() % N;
		temp_x = x;
		temp_y = y;
		dir = rand() % 4;//генератр напрваления
		bool setting_is_possible = 1;// пройдина ли проверка
		//проверка возможности постановки коробля
		for (short i = 0; i < size_ship; i++) {
			if (x < 0 || y < 0 || x >= N || y >= N) {
				setting_is_possible = 0;
				break;
			}
			if (map[x][y] >= 1) {
				setting_is_possible = 0;
				break;
			}
			if (y < N - 1) {
				if (map[x][y + 1] >= 1) {
					setting_is_possible = 0;
					break;
				}
			}
			if (y > 0) {
				if (map[x][y - 1] >= 1) {
					setting_is_possible = 0;
					break;
				}
			}
			if (x < N - 1) {
				if (map[x + 1][y] >= 1) {
					setting_is_possible = 0;
					break;
				}
			}
			if (x < N - 1 && y < N - 1) {
				if (map[x + 1][y + 1] >= 1) {
					setting_is_possible = 0;
					break;
				}
			}
			if (x < N - 1 && y > 0) {
				if (map[x + 1][y - 1] >= 1) {
					setting_is_possible = 0;
					break;
				}
			}
			if (x > 0) {
				if (map[x - 1][y] >= 1) {
					setting_is_possible = 0;
					break;
				}
			}
			if (x > 0 && y < N - 1) {
				if (map[x - 1][y + 1] >= 1) {
					setting_is_possible = 0;
					break;
				}
			}
			if (x > 0 && y > 0) {
				if (map[x - 1][y - 1] >= 1) {
					setting_is_possible = 0;
					break;
				}
			}

			switch (dir) {
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			}
		}
		if (setting_is_possible == 1) {
			x = temp_x;
			y = temp_y;
			for (int i = 0; i < size_ship; i++) {//запись коробля в массив
				map[x][y] = ship_id;
				switch (dir) {
				case 0:
					x++;
					break;
				case 1:
					y++;
					break;
				case 2:
					x--;
					break;
				case 3:
					y--;
					break;
				}
			}
			cout_ship += 1;
		}
	}
}
//прорисовка полей
void map_show(short map[N][N], short mask[N][N], string gemer, bool usemask) {
	cout << gemer << endl;
	cout << "  ";
	for (short i = 0; i < N; i++) cout << i << " ";
	cout << endl;
	for (short i = 0; i < N; i++) {//прорисовка
		cout << i << "";
		for (short j = 0; j < N; j++) {
			if (mask[j][i] == 1 || usemask == 0) {
				if (map[j][i] == 0)
				{
					cout << " -";
				}
				else if (map[j][i] == -1)
				{
					cout << " O";
				}
				else if (map[j][i] == -2)
				{
					cout << " *";
				}
				else
				{
					cout << " X";
				}
			}
			else cout << "  ";

		}
		cout << endl;
	}
	cout << endl;
}
// выстрел
short shot(short map[N][N], short mask[N][N], short ships[Num_Ships + 1], short x, short y) {
	short result = 0; // куда побали убит ранен или промах
	if (map[x][y] >= 1)
	{
		ships[map[x][y]] -= 1;
		if (ships[map[x][y]] <= 0) {
			result = 2;
		}
		else {
			result = 1;
		}
		map[x][y] = -1;
	}
	else {
		map[x][y] = -2;
	}

	mask[x][y] = 1;

	return result;
}

int main() {
	setlocale(LC_ALL, "Russian");

	short map[N][N] = { 0 }; // поле человека
	short map2[N][N] = { 0 }; // поле бота

	short mask[N][N] = { 0 };// туман войны человека
	short mask2[N][N] = { 0 }; // туман войны бота

	short ships[Num_Ships + 1] = { 0 }; // коробли человека
	short ships2[Num_Ships + 1] = { 0 }; // коробли бота

	short x = 0, y = 0; // кординаты цели
	short dir = 0; // направление
	short size_ship = 4; // размер коробля
	short ch = 0; // какая нажата клавиша
	short amount_ship = 0;// количество кораблей на поле

	short resultshot = 0; // попадание в корабль

	short semmbot = 0; // остались ли у бота корабли
	short semmhuman = 0; // остались ли у человека корабли

	short temp_x = x;
	short temp_y = y;
	short temp_dir = dir;

	string gemer = "Поле Человека";
	string gemer2 = "Поле Бота";

	bool turn = 1; // 1 ходит человек

	bool bot = 1; // выйграл ли бот
	bool human = 1; // выйграл ли человек

	bool winbot = 0; // выйграл ли бот
	bool winhuman = 0; // выйграл ли человек

	// заполнение массива с короблями человека
	for (short i = 1; i <= Num_Ships; i++)
	{
		switch (size_ship) {
		case 4:
			if (amount_ship == 0)
				amount_ship = 1;
			if (amount_ship > 0)
				amount_ship--;
			if (amount_ship == 0) {
				ships[i] = size_ship;
				size_ship--;
			}
			break;
		case 3:
			if (amount_ship == 0)
				amount_ship = 2;
			if (amount_ship > 0)
				amount_ship--;
			ships[i] = size_ship;
			if (amount_ship == 0) {
				ships[i] = size_ship;
				size_ship--;
			}
			break;
		case 2:
			if (amount_ship == 0)
				amount_ship = 3;
			if (amount_ship > 0)
				amount_ship--;
			ships[i] = size_ship;
			if (amount_ship == 0) {
				ships[i] = size_ship;
				size_ship--;
			}
			break;
		case 1:
			if (amount_ship == 0)
				amount_ship = 4;
			if (amount_ship > 0)
				amount_ship--;
			ships[i] = size_ship;
			if (amount_ship == 0) {
				ships[i] = size_ship;
				size_ship--;
			}
			break;
		}
	}
	amount_ship = 0;
	size_ship = 4;
	// заполнение массива с короблями бота
	for (int i = 1; i <= Num_Ships; i++)
	{
		switch (size_ship) {
		case 4:
			if (amount_ship == 0)
				amount_ship = 1;
			if (amount_ship > 0)
				amount_ship--;
			if (amount_ship == 0) {
				ships2[i] = size_ship;
				size_ship--;
			}
			break;
		case 3:
			if (amount_ship == 0)
				amount_ship = 2;
			if (amount_ship > 0)
				amount_ship--;
			ships2[i] = size_ship;
			if (amount_ship == 0) {
				ships2[i] = size_ship;
				size_ship--;
			}
			break;
		case 2:
			if (amount_ship == 0)
				amount_ship = 3;
			if (amount_ship > 0)
				amount_ship--;
			ships2[i] = size_ship;
			if (amount_ship == 0) {
				ships2[i] = size_ship;
				size_ship--;
			}
			break;
		case 1:
			if (amount_ship == 0)
				amount_ship = 4;
			if (amount_ship > 0)
				amount_ship--;
			ships2[i] = size_ship;
			if (amount_ship == 0) {
				ships2[i] = size_ship;
				size_ship--;
			}
			break;
		}
	}
	// расстановка кораблей человека рандомно
	for (short i = 1; i <= Num_Ships; i++)
	{
		set_rand_ships(map, ships[i], i);
	}
	// расстановка кораблей человека вручную
	size_ship = 4;
	/*while (size_ship != 0) {
		map_show(map, mask, gemer, 0);
		ship_show(x, y, dir, size_ship);
		ch = _getch();
		// изменить координаты или направление
		switch (ch) {
		case 100:// d вправо
			x++;
			x++;
			break;
		case 115:// s вниз
			y++;
			break;
		case 97:// a влево
			x--;
			x--;
			break;
		case 119:// w вверх
			y--;
			break;
		case 114:// r поворот
			dir = dir == 0 ? 1 : 0;
			break;
		case 13:// enter установка коробля
			if (set_ship(map, x/2, y, dir, size_ship)) {
				x = 0;
				y = 0;
				dir = 0;
				switch (size_ship) {
				case 4:
					amount_ship = amount_ship == 0 ? 1 : 0;
					//if (amount_ship == 0)
						//amount_ship = 1;
					if (amount_ship > 0)
						amount_ship--;
					if (amount_ship == 0)
						size_ship--;
					break;
				case 3:
					if (amount_ship == 0)
						amount_ship = 2;
					if (amount_ship > 0)
						amount_ship--;
					if (amount_ship == 0)
						size_ship--;
					break;
				case 2:
					if (amount_ship == 0)
						amount_ship = 3;
					if (amount_ship > 0)
						amount_ship--;
					if (amount_ship == 0)
						size_ship--;
					break;
				case 1:
					if (amount_ship == 0)
						amount_ship = 4;
					if (amount_ship > 0)
						amount_ship--;
					if (amount_ship == 0)
						size_ship--;
					break;
				}
			}
			break;
		}
		if (!ship_in_map(x/2, y, dir, size_ship)) {
			x = temp_x;
			y = temp_y;
			dir = temp_dir;
		}
		system("cls");
	}*/
	// расстановка кораблей бота рандомно
	for (short i = 1; i <= Num_Ships; i++)
	{
		set_rand_ships(map2, ships2[i], i);
	}
	// отвечает за стрельбу пока не будет промах
	while (winbot == false && winhuman == false) {
		do
		{
			map_show(map, mask, gemer, 0);
			map_show(map2, mask2, gemer2, 1);
			
			if (turn == 1)
			{
				cout << "Введите кординаты цели: ";
				cin >> x >> y;
				resultshot = shot(map2, mask2, ships2, x, y);
				if (resultshot == 2)
				{
					cout << "Убил" << endl;
					Sleep(1000);
					system("cls");
					for (int i = 1; i <= Num_Ships; i++)
					{
						if (ships2[i] != 0) {
							human = 0;
							break;
						}
					}
					if (human == 1) {
						winhuman = 1;
					}
					human = semmhuman <= 0 ? 1 : 0;
				}
				else if (resultshot == 1)
				{
					cout << "Попал" << endl;
					Sleep(1000);
					system("cls");
				}
				else
				{
					cout << "Промах";
					Sleep(1000);
					system("cls");
				}
			}
			else
			{
				cout << "Ход компьютера: ";
				Sleep(1000);
				do {
					x = rand() % N;
					y = rand() % N;
					cout << x << " " << y << endl;
				} while (map[x][y] < 0);
				resultshot = shot(map, mask, ships, x, y);

				if (resultshot == 2){
					for (int i = 1; i <= Num_Ships; i++)
					{
						if (ships[i] != 0) {
							bot = 0;
							break;
						}
					}
					if (bot == 1) {
						winbot = 1;
						break;
					}
					cout << "Убил" << endl;
					Sleep(1000);
				}
				else if (resultshot == 1)
				{
					cout << "Попал" << endl;
					Sleep(1000);
				}
				else
				{
					cout << "Промах";
					Sleep(1000);
				}
			}
			system("cls");
		} while (resultshot != 0);
		turn = turn == 0 ? 1 : 0;
	}
	map_show(map, mask, gemer, 0);
	map_show(map2, mask2, gemer2, 1);
	if (winhuman == true)
	{
		cout << "Вы победили" << endl;
		Sleep(1000);
	}
	else
	{
		cout << "Вы проиграли" << endl;
		Sleep(1000);
	}
	system("pause");
	return 0;
}
