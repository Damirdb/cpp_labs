#include "Club.h"
#include "KaraokeClub.h"
#include "DanceClub.h"
#include "VIPKaraokeClub.h"
#include <iostream>

int main() {
    Club* clubs[128];
    int nclubs = 0;

    int command;
    do {
        std::cout << "\n1. Добавить общий клуб\n2. Добавить караоке клуб\n3. Добавить танцевальный клуб\n4. Добавить VIP караоке\n5. Показать клубы\n0. Выход\n-> ";
        std::cin >> command;

        switch (command) {
            case 1:
                clubs[nclubs] = new Club();
                clubs[nclubs]->input();
                nclubs++;
                break;
            case 2:
                clubs[nclubs] = new KaraokeClub();
                clubs[nclubs]->input();
                nclubs++;
                break;
            case 3:
                clubs[nclubs] = new DanceClub();
                clubs[nclubs]->input();
                nclubs++;
                break;
            case 4:
                clubs[nclubs] = new VIPKaraokeClub();
                clubs[nclubs]->input();
                nclubs++;
                break;
            case 5:
                for (int i = 0; i < nclubs; ++i) {
                    clubs[i]->print();
                }
                break;
            case 0:
                for (int i = 0; i < nclubs; ++i) {
                    delete clubs[i];
                }
                std::cout << "\nДо свидания!\n";
                break;
            default:
                std::cout << "\nНеверная команда! Попробуйте снова.\n";
                break;
        }
    } while (command != 0);

    return 0;
}
