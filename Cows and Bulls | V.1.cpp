#include <random>
#include <iostream>
#include <string>
#include <tuple>
using namespace std;

class BullsAndCows
{

public:

    vector<bool> myArray;

    BullsAndCows() : myArray(9000, true)
    {
        generateNumber = generateNum();
        for (int i = 0; i < 9000; i++)
        {
            int num = i + 1000;
            if (checkNumber(num) == false)
            {
                myArray[i] = false;
            }
        }
    }

    tuple<bool, int> playSecondGame(int i)
    {
        int choiсe = 9;
        int bulls = 0;
        int cows = 0;

        for (int j = 0; j < 9000; j++)
        {

            if (myArray[j] == true)
            {
                choiсe = j;
                break;
            }
        }
        if (choiсe == 9)
        {
            cout << "\033[31m" << "Please, double-check the number of bulls and cows again" << "\033[0m" << endl;
            return make_tuple(true, -1);
        }
        cout << "attempt number" << i + 1 << ": " << 1000 + choiсe << endl;
        cout << "Number of bulls: ";
        cin >> bulls;
        cout << "Number of cows: ";
        cin >> cows;
        if (bulls == 4)
        {
            cout << "The hidden number is " << 1000 + choiсe << endl;
            return make_tuple(true, 0);
        }
        for (int j = 0; j < 9000; j++)
        {

            if (j == choiсe) {
                myArray[j] = false;
            }
            if (myArray[j] == true) {
                tuple<int, int> bullsAndCowsTuple = bullsAndCowsCounter(to_string(1000 + choiсe), to_string(1000 + j));
                int count_bulls = get<0>(bullsAndCowsTuple);
                int count_cows = get<1>(bullsAndCowsTuple);
                if ((count_cows != cows) || (count_bulls != bulls)) {
                    myArray[j] = false;
                }
            }
        }
        return make_tuple(false, 0);

    }



private:

    tuple<int, int> bullsAndCowsCounter(string mainNumber, string iteratedNumber) {
        int bullsCounter = 0;
        int cowsCounter = 0;
        for (int i = 0; i < 4; i++) {
            if (iteratedNumber[i] == mainNumber[i]) {
                bullsCounter += 1;
            }
            else {
                if (mainNumber.find_first_of(iteratedNumber[i]) != string::npos) {
                    cowsCounter += 1;
                }
            }
        }
        return make_tuple(bullsCounter, cowsCounter);

    }


    bool checkNumber(int num) {
        string number = to_string(num);
        int count = 0;
        for (char x : number) {
            for (int j = 0; j < 4; j++) {
                if (number[j] == x) {
                    count += 1;
                }
            }
        }
        if (count != 4) {
            return false;
        }
        return true;

    }

    string generateNumber;

    string generateNum() {
        string randomNumber;
        while (true) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(1000, 9999);
            randomNumber = to_string(dis(gen));
            bool flag = false;
            int count = 0;
            for (char x : randomNumber)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (randomNumber[i] == x)
                    {
                        count += 1;
                    }
                }
            }
            if (count == 4) {
                break;
            }
        }
        return randomNumber;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    bool playAgain = true;
    while (playAgain) { // бесконечный цикл для перезапуска игры
        cout << "Hi, let's play" << endl << endl;
        BullsAndCows game;
        bool flag = false;
        for (int i = 0; i < 10; i++)
        {
            tuple<bool, int> secondResult = game.playSecondGame(i);
            bool res = get<0>(secondResult);
            int num = get<1>(secondResult);
            if (res == true) {
                flag = true;
                break;
            }
        }
        if (flag == false)
        {
            cout << "Неудача" << endl;
        }
        cout << "Хотите начать новую игру? Введите 1 для продолжения или другое число для выхода: ";
        int choice;
        cin >> choice;
        playAgain = (choice == 1); // если пользователь ввел 1, то перезапускаем игру, иначе выводим сообщение об окончании программы
    }
    cout << "До новых встреч!" << endl;
}