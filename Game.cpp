#include "View.h"
#include "Map_generator.h"
#include "Help.h"
#include "Player.h"
#include "Entity.h"
#include "Timer.h"
#include "Map.h"
#include "Menu.h"
#include "Bullet.h"
#include "Npc.h"
#include "Item.h"
#include "Sounds.h"
#include "Pause.h"
#include "Interface.h"
#include "DeathMenu.h"

sf::View calcView(const sf::Vector2f& windowSize, float minRatio, float maxRatio)
{
    sf::Vector2f viewSize = windowSize;

    // clip ratio
    float ratio = viewSize.x / viewSize.y;
    if (ratio < minRatio) // too high
        viewSize.y = viewSize.x / minRatio;
    else if (ratio > maxRatio) // too wide
        viewSize.x = viewSize.y * maxRatio;

    sf::View view(sf::FloatRect(sf::Vector2f(), viewSize));

    sf::FloatRect viewport((windowSize - viewSize) / 2.f, viewSize);
    viewport.left /= windowSize.x;
    viewport.top /= windowSize.y;
    viewport.width /= windowSize.x;
    viewport.height /= windowSize.y;
    view.setViewport(viewport);

    return view;
}

int main()
{

    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    bool** MAP = new bool* [MAP_HEIGHT];
    if (GENERATE_MAP(MAP) == false) return 0;

    Timer T;
    Map M;
    Player P;
    Interface I(P);

    int BulletCoolDown = 51;

    list<Bullet*> bullets;
    list<Bullet*> ::iterator BuIt;

    list<NPC*> enemies;
    list<NPC*>::iterator EnIt;

    list<Item*> items;
    list<Item*>::iterator ItIt;

    //from now
    Sounds SS;

    sf::Music music1;
    sf::Music music2;
    sf::Music music3;
    sf::Music music4;
#ifdef _WIN32
    music1.openFromFile("tuctuctuc/1.flac");
    music2.openFromFile("tuctuctuc/2.flac");
    music3.openFromFile("tuctuctuc/3.flac");
    music4.openFromFile("tuctuctuc/4.flac");
#else
    music1.openFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/tuctuctuc/1.flac");
    music2.openFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/tuctuctuc/2.flac");
    music3.openFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/tuctuctuc/3.flac");
    music4.openFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/tuctuctuc/4.flac");
#endif // _WIN32
    RenderWindow window(VideoMode(1920, 1080), "Game", Style::Fullscreen);
    //RenderWindow window(VideoMode(1920, 1080), "Game");


    music1.setPlayingOffset(sf::seconds(5.f));
    music1.setVolume(60.f);
    music2.setVolume(30.f);
    music3.setVolume(30.f);
    music4.setVolume(30.f);
    music1.setLoop(1);
    music1.play();
    menu(window);
    music1.stop();
    music1.setVolume(30.f);

    //to now


   //generating enemies
    int EnemiesCounter = tr.tree.size();
    int* tempX = new int; int* tempY = new int; int* tempHealth = new int; int* tempDamage = new int;

    for (unsigned int j = 0; j < tr.tree[EnemiesCounter - 1].size(); j++) {
        int roomsize = tr.tree[EnemiesCounter - 1][j]->room.x2 - tr.tree[EnemiesCounter - 1][j]->room.x1 - tr.tree[EnemiesCounter - 1][j]->room.y2 + tr.tree[EnemiesCounter - 1][j]->room.y1;
        cout << roomsize << " - room" << endl;
        int gene = generate_random_number(0, (roomsize - 2) / 6);
        for (int i = 0; i < gene; i++) {
            *tempX = generate_random_number(tr.tree[EnemiesCounter - 1][j]->room.x1 * 128, tr.tree[EnemiesCounter - 1][j]->room.x2 * 128);
            *tempY = generate_random_number(tr.tree[EnemiesCounter - 1][j]->room.y2 * 128, tr.tree[EnemiesCounter - 1][j]->room.y1 * 128);
            *tempHealth = generate_random_number(30, 70);
            *tempDamage = generate_random_number(20, 50);
            NPC* en = new NPC(*tempX, *tempY, 20, *tempHealth, 3000, *tempDamage, 1);
            enemies.push_back(en);
            //entities.push_back(en);
            cout << j * i << "-th enemy generated" << endl;

        }
        for (int i = 0; i < roomsize / 6 - gene; i++) {
            *tempX = generate_random_number(tr.tree[EnemiesCounter - 1][j]->room.x1 * 128, tr.tree[EnemiesCounter - 1][j]->room.x2 * 128);
            *tempY = generate_random_number(tr.tree[EnemiesCounter - 1][j]->room.y2 * 128, tr.tree[EnemiesCounter - 1][j]->room.y1 * 128);
            *tempHealth = generate_random_number(60, 100);
            *tempDamage = generate_random_number(30, 50);
            NPC* en = new NPC(*tempX, *tempY, 30, *tempHealth, 100, *tempDamage);
            enemies.push_back(en);
            //entities.push_back(en);
            //cout << j*i << "-th enemy generated" << endl;

        }
    }


    delete(tempHealth, tempDamage);

    //generating items
    for (unsigned int j = 0; j < tr.tree[EnemiesCounter - 1].size(); j++) {
        int roomsize = tr.tree[EnemiesCounter - 1][j]->room.x2 - tr.tree[EnemiesCounter - 1][j]->room.x1 - tr.tree[EnemiesCounter - 1][j]->room.y2 + tr.tree[EnemiesCounter - 1][j]->room.y1;

        int gene = generate_random_number(0, roomsize / 7);
        for (int i = 0; i < gene; i++) {
            *tempX = generate_random_number(tr.tree[EnemiesCounter - 1][j]->room.x1 * 128, tr.tree[EnemiesCounter - 1][j]->room.x2 * 128);
            *tempY = generate_random_number(tr.tree[EnemiesCounter - 1][j]->room.y2 * 128, tr.tree[EnemiesCounter - 1][j]->room.y1 * 128);
            Item* CurrentItem = new Item(*tempX, *tempY);
            items.push_back(CurrentItem);
            //entities.push_back(en);
            //cout << j*i << "-th marlboro generated" << endl;

        }
        //gene = generate_random_number(0,roomsize/14);
        for (int i = 0; i < (gene / 2); i++) {
            *tempX = generate_random_number(tr.tree[EnemiesCounter - 1][j]->room.x1 * 128, tr.tree[EnemiesCounter - 1][j]->room.x2 * 128);
            *tempY = generate_random_number(tr.tree[EnemiesCounter - 1][j]->room.y2 * 128, tr.tree[EnemiesCounter - 1][j]->room.y1 * 128);
            Item* CurrentItem = new Item(*tempX, *tempY, 5);
            items.push_back(CurrentItem);
            //entities.push_back(en);
            //cout << j*i << "-th bible generated" << endl;

        }
    }
    delete (tempX, tempY);
    P.view.setSize(1920, 1080);
    while (window.isOpen())
    {
        //from now
            //cout<<"misuc 1 is"<<music1.Playing<<music1.getStatus()<<endl;
        if (music1.getStatus() == 0 and music2.getStatus() == 0 and music3.getStatus() == 0 and music4.getStatus() == 0) {
            int temporaryShit = generate_random_number(0, 4);
            //temporaryShit = 0;
            if (temporaryShit == 0) {
                music1.play();
                cout << "first track" << endl;
            }
            else if (temporaryShit == 1) {
                music2.play();
                cout << "Second track" << endl;
            }
            else if (temporaryShit == 2) {
                music3.play();
                cout << "Third track" << endl;
            }
            else {
                music4.play();
                cout << "fourth track" << endl;
            }
        }
        //to now
        if (P.is_life == false) {
            death_menu(window, P);
        }

        T.time = T.clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        T.clock.restart(); //перезагружает время
        T.time = T.time / 800; //скорость игры


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                bullets_clear(bullets, BuIt);
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    P.view.setSize(1920, 1080);
                    pause(window, T, P);
                    //window.close();
                }
            }

            if (event.type == Event::MouseButtonPressed and BulletCoolDown > 30) {
                if (event.key.code == Mouse::Left) {
                    Bullet* B = new Bullet(P);
                    B->shoot_animate(P);
                    bullets.push_back(B);
                    //entities.push_back(B);
                    BulletCoolDown = 0;
                }
            }



            if (event.type == Event::MouseButtonReleased) {
                bullets_clear(bullets, BuIt);
            }
        }


        BulletCoolDown += 1;


        /////////////////////////////Рисуем карту/////////////////////

        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                map_draw(MAP, M, i, j);
                window.draw(M.sprite);
            }
        }
        for (ItIt = items.begin(); ItIt != items.end(); ItIt++) {
            (*ItIt)->taken(P);
            if ((*ItIt)->IsTaken == 1) {
                delete(*ItIt);
                items.erase(ItIt);
                break;
            }
            else {
                window.draw((*ItIt)->sprite);

            }

        }
#pragma omp parallel num_threads(4)
        {


#pragma omp for

            for (EnIt = enemies.begin(); EnIt != enemies.end(); EnIt++) {
                if ((*EnIt)->is_life) {
                    //cout << "InViewField" << endl;
                    (*EnIt)->Trace(P.x, P.y);
                    //cout << "Direct is " << (*EnIt)->direction << endl;
                    (*EnIt)->move(T.time, MAP, P, SS);
                    if ((*EnIt)->bulletFlag == 1) {

                        Bullet* B = new Bullet(*EnIt);
                        //B->shoot_animate(P);
                        bullets.push_back(B);
                        //entities.push_back(B);
                    }
                    window.draw((*EnIt)->sprite);
                }
                else {
                    delete(*EnIt);
                    enemies.erase(EnIt);
                    break;
                }
            }
        }


        P.control();
        window.setView(P.view);
        P.update(T.time, MAP);
        window.draw(P.sprite);

        I.render(P, window);



        for (BuIt = bullets.begin(); BuIt != bullets.end(); BuIt++) {
            if ((*BuIt)->is_life == true) {
                (*BuIt)->EnemyStrike(enemies);
                (*BuIt)->PlayerStrike(P);
                (*BuIt)->update(T.time, MAP);
                window.draw((*BuIt)->sprite);
                window.draw((*BuIt)->ba_sprite);
            }
            else {
                delete(*BuIt);
                bullets.erase(BuIt);
                break;
            }
        }


        window.display();
        window.clear();

    }

    bullets.clear();
    enemies.clear();

    return 1;
}
