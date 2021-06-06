#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>

#include "player.h"
#include "enemy.h"
#include "widget.h"

class Controller : QObject {
//класс контроллера
    Q_OBJECT

public:

    Controller();
    ~Controller();

    void StartGame();
    void EndGame();
    int GenerateMove(); //генерация очков передвижения для игрока
    void MakeBattle(Avatar* attaker, Avatar* defender); //вызов атаки
    void ConnectSystem(); //создания соединений слотов и сигналов системы
    void CreateEnemy(); //создание одного врага

public slots:
    void slotGenerateMove(int moveValue);
    void slotStartTurn();
    void slotEndTurn();
    void slotChangeCoord(QPointF coords);
    void slotAvailableTargets();
    void slotClickToAttack(Enemy* en);
    void slotReleaseDamage();
    void slotTurnOffCells();
    void slotDeleteEnemy(Enemy* en);
    void slotEnemyAtack(Enemy* en);
    void slotEndGame();
signals:
    void signalGenerateMove(int moveValue);
    void signalStartTurn(bool currTurn);
    void signalEndTurn(bool currTurn);
    void signalAvailableTargets();
    void signalAddEnemy(Enemy* en);
    void signalTurnOffCells();
    void signalDeleteEnemy(Enemy* en);
    void signalEndGame();

private:
    bool currentTurn;
    Player* player;
    QVector<Enemy*> enemys;
    Widget* widget;
    QTimer *timer;
};


#endif // CONTROLLER_H
