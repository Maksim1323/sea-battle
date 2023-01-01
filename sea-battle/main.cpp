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

// передвижения курсора
void gotox(int x, int y) {//переставления курсора в заданные кординаты в консольном окне
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
// растановка коробля на поле
void ship_show(int x, int y, int dir, int size_ship) {

    for (int i = 0; i < size_ship; i++) {

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
                y++;
                break;
            case 2:
                x--;
                x--;
                break;
            case 3:
                y--;
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
bool ship_in_map(int x, int y, int dir, int size_ship) {
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
//проверка возможности постановки коробля при ручной постанки
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
// рандомная расстановка короблей
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
void map_show(int map[N][N], int mask[N][N], string gemer, bool usemask) {
    cout << gemer << endl;
    cout << "  ";
    for (int i = 0; i < N; i++) cout << i << " ";
    cout << endl;
    for (int i = 0; i < N; i++) {//прорисовка
        cout << i << "";
        for (int j = 0; j < N; j++) {
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
int shot(int map[N][N], int mask[N][N], int ships[Num_Ships + 1], int x, int y) {
    int result = 0;
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

    int map[N][N] = { 0 }; // поле человека
    int map2[N][N] = { 0 }; // поле бота

    int mask[N][N] = { 0 };// туман войны человека
    int mask2[N][N] = { 0 }; // туман войны бота

    int ships[Num_Ships + 1] = { 0 }; // коробли человека
    int ships2[Num_Ships + 1] = { 0 }; // коробли бота

    int x = 0, y = 0; // кординаты цели
    int dir = 0; // направление
    int size_ship = 4; // размер коробля
    int ch = 0; // какая нажата клавиша
    int amount_ship = 0;// количество кораблей на поле

    int resultshot = 0; // попадание в корабль

    int semmbot = 0; // остались ли у бота корабли
    int semm = 0; // остались ли у человека корабли

    string gemer = "Поле Человека";
    string gemer2 = "Поле Бота";

    bool turn = 1; // 1 ходит человек

    bool bot = 0; // выйграл ли бот
    bool human = 0; // выйграл ли человек

    // заполнение массива с короблями человека
    for (int i = 1; i <= Num_Ships; i++)
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
    /*for (int i = 1; i <= Num_Ships; i++)
    {
        set_rand_ships(map, ships[i], i);
    }*/
    // расстановка кораблей человека вручную
    size_ship = 4;
    while (size_ship != 0) {
        int temp_x = x, temp_y = y;
        int temp_dir = dir;
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
            y++;
            break;
        case 97:// a влево
            x--;
            x--;
            break;
        case 119:// w вверх
            y--;
            y--;
            break;
        case 114:// r поворот
            dir = !dir;
            break;
        case 13:// enter установка коробля
            if (x % 2 == 0) x /= 2;
            else x /= 2;
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
    }
    // расстановка кораблей бота рандомно
    for (int i = 1; i <= Num_Ships; i++)
    {
        set_rand_ships(map2, ships2[i], i);
    }
    while (bot == false && human == false) {
        // отвечает за стрельбу пока не будет промах
        do
        {
            map_show(map, mask, gemer, 0);
            map_show(map2, mask2, gemer2, 1);
            
            if (turn == 1)
            {
                cout << endl << "Введите кординаты цели" << endl;
                cin >> x >> y;
                resultshot = shot(map2, mask2, ships2, x, y);
                if (resultshot == 2)
                {
                    cout << "Убил" << endl;
                    for (int i = 1; i <= Num_Ships; i++)
                    {
                        semm += ships2[i];
                    }
                    if (semm == 0)
                    {
                        human = 1;
                        break;
                    }

                }
                else if (resultshot == 1)
                {
                    cout << "Попал" << endl;
                }
                else
                {
                    cout << "Промах";
                }
            }
            else
            {
                cout << endl << "Ход компьютера" << endl;
                x = rand() % N;
                y = rand() % N;
                resultshot = shot(map, mask, ships, x, y);

                if (resultshot == 2)
                {
                    cout << "Убил" << endl;
                    for (int i = 1; i <= Num_Ships; i++)
                    {
                        semmbot += ships[i];
                    }
                    if (semmbot == 0)
                    {
                        bot = 1;
                        break;
                    }
                }
                else if (resultshot == 1)
                {
                    cout << "Попал" << endl;
                }
                else
                {
                    cout << "Промах";
                }
            }
            Sleep(1000);
            system("cls");
        } while (resultshot != 0);
        turn = !turn;
    }
    map_show(map, mask, gemer, 0);
    map_show(map2, mask2, gemer2, 1);
    if (human)
    {
        cout << "Вы победили" << endl;
    }
    else
    {
        cout << "Вы проиграли" << endl;
    }

    system("pause");
    return 0;
}
