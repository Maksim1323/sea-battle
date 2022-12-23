//#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <math.h>
#include <ctime>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

const int N = 10;
int Ships_id = 1;
int Ships[11] = {0};

void gotox(int x, int y) {//переставления курсора в заданные кординаты в консольном окне
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void ship_show(int x, int y, int dir, int size_ship) {

    for (int i = 0; i < size_ship; i++) {//запись коробля в массив

        gotox(x+1, y+1);
        cout << "#";

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

void set_rand_ships(int map[N][N], int size_ship, int num_ships) {
    int x, y;
    int dir = 0;//направление
    int cout_ship = 0;
    while (cout_ship < num_ships) {
        x = rand() % N;//первичная позиция
        y = rand() % N;
        int temp_x = x;
        int temp_y = y;
        bool setting_is_possible = 1;// пройдина ли проверка
        dir = rand() % 4;//генератр напрваления
        for (int i = 0; i < size_ship; i++) {//проверка возможности постановки коробля
            if (x < 0 || y < 0 || x >= N || y >= N) {
                setting_is_possible = 0;
                break;
            }
            if (map[x][y] >= 1 || map[x][y + 1] >= 1 || map[x][y - 1] >= 1 || map[x + 1][y] >= 1 || map[x + 1][y + 1] >= 1 || map[x + 1][y - 1] >= 1 || map[x - 1][y] >= 1 || map[x - 1][y + 1] >= 1 || map[x - 1][y - 1] >= 1) {
                setting_is_possible = 0;
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
            cout_ship += 1;
        }
    }
}
void map_show(int map[N][N], int mask[N][N]) {
    cout << "  ";
    for (int i = 0; i < N; i++) cout <<i << " ";
    cout << endl;
    for (int i = 0; i < N; i++) {//прорисовка
        cout << i << " ";
        for (int j = 0; j < N; j++) {
            if (mask[j][i] == 1) {
                if (map[j][i] == 0) cout << "*";
                else if(map[j][i] == -1) cout << "*";
                else cout << "X ";
            }
            else cout << "  ";
        }
        cout << endl;
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");

    while (true) 
    {
        int map[N][N] = {0};

        int mask[N][N] = {0};

        //set_rand_ships(map, 4, 1);
        //set_rand_ships(map, 3, 2);
        //set_rand_ships(map, 2, 3);
        //set_rand_ships(map, 1, 4);

        int x = 0, y = 0;
        int dir = 1;
        int size_ship = 3;

        while (true) // ручная постановка корабля
        {
            map_show(map, mask);
            ship_show(x, y, dir, size_ship);
            //_getch();
            //system("cls");

        }

        while (true) {
            map_show(map, mask);

            cout << endl << "Введите кординаты цели" << endl;

            cin >> x >> y;

            if (map[x][y] >= 1)
            {
                Ships[map[x][y]] -= 1;
                if (Ships[map[x][y]] <= 0) cout << "Убил" << endl;
                else cout << "Попал" << endl;
            }
            else
            {
                cout << "Промах" << endl;
            }
            map[x][y] = -1;
            mask[x][y] = 1;
            Sleep(1000);
            system("cls");
            
        }

        Sleep(1000); // пауза
        system("cls");//отчистка консольного окошка
    }

    system("pause");
    return 0;
}
