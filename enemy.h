#ifndef ENEMY_H
#define ENEMY_H

#include "avatar.h"
#include "enemy_view.h"
#include "player.h"
#include "math.h"

class Enemy: public Avatar{
    //класс, являющийся данными каждого врага
    Q_OBJECT

public:
    explicit Enemy(QObject *parent = 0);
    ~Enemy();

    void Death();
    void GetDamage(int damage);
    int GiveDamage();

    void ChooseAction(); //логика принятия решения, что надо делать в текущий ход
    QPointF CalculateDistance(QPointF distPlayer); //метод для определения вектора движения к игроку по клеткам

    void setCoord(QPointF coord);
    void setPlayer(Player* pl);
    void setMove(int m_);

    QPointF getCoord();
    Enemy_view* getView();

public slots:
signals:
    void signalReleaseDamage();
    void signalDeleteEnemy(Enemy* en);
    void signalEnemyAtack(Enemy* en);

private:
    Enemy_view* view; //представление данных о враге на виджете
    Player* player;
    int distanceX;
    int distanceY;
};

#endif // ENEMY_H
