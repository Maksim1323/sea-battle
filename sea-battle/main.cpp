#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

const int N = 10;
const int Num_Ships = 10;

int Ships_id = 1;
int Ships[11] = { 0 };
int Ships2[11] = { 0 };


void gotox(int x, int y) {//переставления курсора в заданные кординаты в консольном окне
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void ship_show(int x, int y, int dir, int size_ship) {

    for (int i = 0; i < size_ship; i++) {//запись коробля в массив

        gotox(x + 1, y + 2);
        cout << "# ";

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

bool ship_in_map(int x, int y, int dir, int size_ship) {//находится ли корабль в пределах каоты
    bool setting_is_possible = 0;
    bool in_map = 1;// пройдина ли проверка
    //проверка возможности постановки коробля
    for (int i = 0; i < size_ship; i++) {
        if (x < 0 || y < 0 || x >= N || y >= N) {
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
    return in_map;
}

bool set_ship(int map[N][N], int x, int y, int dir, int size_ship) {
    int temp_x = x;
    int temp_y = y;
    bool setting_is_possible = 1;// пройдина ли проверка
    //проверка возможности постановки коробля
    for (int i = 0; i < size_ship; i++) {
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

void set_rand_ships(int map[N][N], int size_ship, int ship_id) {
    int x, y;
    int dir = 0;//направление
    int cout_ship = 0;
    while (cout_ship < 1) {
        x = rand() % N;//первичная позиция
        y = rand() % N;
        int temp_x = x;
        int temp_y = y;
        dir = rand() % 4;//генератр напрваления
        bool setting_is_possible = 1;// пройдина ли проверка
        //проверка возможности постановки коробля
        for (int i = 0; i < size_ship; i++) {
            if (x < 0 || y < 0 || x >= N || y >= N) {
                setting_is_possible = 0;
                break;
            }
            if (map[x][y] >= 1 ||
                map[x][y + 1] >= 1 ||
                map[x][y - 1] >= 1 ||
                map[x + 1][y] >= 1 ||
                map[x + 1][y + 1] >= 1 ||
                map[x + 1][y - 1] >= 1 ||
                map[x - 1][y] >= 1 ||
                map[x - 1][y + 1] >= 1 ||
                map[x - 1][y - 1] >= 1)
            {
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
            for (int i = 0; i < size_ship; i++ ) {//запись коробля в массив
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
void map_show(int map[N][N], int mask[N][N], string gemer, bool usemask) {
    cout << gemer << endl;
    cout << " ";
    for (int i = 0; i < N; i++) cout << i << "";
    cout << endl;
    for (int i = 0; i < N; i++) {//прорисовка
        cout << i << "";
        for (int j = 0; j < N; j++) {
            if (mask[j][i] == 1 || usemask == 0)
            {
                if (map[j][i] == 0) 
                {
                    cout << "-";
                }
                else if (map[j][i] == -1) 
                {
                    cout << "o";
                }
                else 
                {
                    cout << "X";
                }
            }
            else 
            {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int shot(int map2[N][N], int mask[N][N], int ships[Num_Ships+1], int x, int y) {
    int result = 0;
    if (map2[x][y] >= 1)
    {
        ships[map2[x][y]] -= 1;
        if (ships[map2[x][y]] <= 0) {
           result = 2;
        }
        else {
            result = 1;
        }
        map2[x][y] = -1;
    }

    mask[x][y] = 1;

    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");

    while (true)
    {
        int map[N][N] = { 0 };
        int map2[N][N] = { 0 };

        int mask[N][N] = { 0 };
        int mask2[N][N] = { 0 };

        int ships[Num_Ships+1] = { 0 };
        int ships2[Num_Ships+1] = { 0 };

        int x = 0, y = 0;
        int dir = 0;
        int size_ship = 4;
        int ch;
        int amount_ship = 0;//количество кораблей на поле

        int resultshot = 0;

        string gemer = "Поле Игрока";
        string gemer2 = "Поле Бота";

        for (int i = 1; i <= Num_Ships; i++) {
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

        for (int i = 1; i <= Num_Ships; i++) {
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

        for(int i = 1; i <= Num_Ships; i++)
            set_rand_ships(map, ships[i], i);

        for(int i = 1; i <= Num_Ships; i++)
            set_rand_ships(map2, ships2[i], i);


        /*while (size_ship != 0) // ручная постановка корабля
        {
        int temp_x = x, temp_y = y;
        int temp_dir = dir;
            map_show(map, mask, gemer);
            ship_show(x, y, dir, size_ship);

            ch = _getch();
            // изменить координаты или направление
            switch (ch) {
            case 100:// d вправо
                x++;
                break;
            case 115:// s вниз
                y++;
                break;
            case 97:// a влево
                x--;
                break;
            case 119:// w вверх
                y--;
                break;
            case 114:// r поворот
                dir = !dir;
                break;
            case 13:// enter установка коробля
                if (set_ship(map, x, y, dir, size_ship)) {
                    x = 0;
                    y = 0;
                    dir = 0;
                    switch (size_ship) {
                    case 4:
                        if (amount_ship == 0)
                            amount_ship = 1;
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
            if (!ship_in_map(x, y, dir, size_ship)) {
                x = temp_x;
                y = temp_y;
                dir = temp_dir;
            }
            _getch();
            system("cls");
        }*/
        
        bool turn = 1; // 1 ходит человек
        bool usemask = 0;

        while (true){
            do
             { // отвечает за стрельбу пока не будет промах
                map_show(map, mask, gemer, usemask);
                usemask = 1;
                map_show(map2, mask2, gemer2, usemask);
                

                if (turn == 1)
                {
                    cout << endl << "Введите кординаты цели" << endl;
                    cin >> x >> y;
                    resultshot = shot(map2, mask2, ships2, x, y);
                }
                else
                {
                    cout << endl << "Ход компьютера" << endl;
                    x = rand() % N;
                    y = rand() % N;
                    resultshot = shot(map, mask, ships, x, y);
                    Sleep(1000);
                }
                if (resultshot == 2)
                {
                    cout << "Убил" << endl;
                }
                else if (resultshot == 1)
                {
                    cout << "Попал" << endl;
                }
                else
                {
                    cout << "Промах";
                }
                Sleep(1000);
                system("cls");
            }while (resultshot != 0);
            turn = !turn;
        }
        system("cls");//отчистка консольного окошка
    }
    system("pause");
    return 0;
}
