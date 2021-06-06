#ifndef PLAYER_H
#define PLAYER_H
#include "avatar.h"
#include "player_view.h"
#include "cell.h"

class Player: public Avatar
{
    //класс данных об игроке
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    ~Player();

    void Attack();
    void MakeMove();
    void Death();

    void Update();
    void GetDamage(int damage);
    int GiveDamage();

    void setCoord(QPointF coord);

    Player_view* getView();
    QPointF getCoord();
    int getHealth();

public slots:
    void slotStartTurn(bool currTurn);
    void slotEndTurn(bool currTurn);
signals:
    void signalAvailableTargets();
    void signalTurnOffCells();
    void signalEndGame();

private:
    Player_view* view;
    bool makeMove;
    bool attack;
    bool currentTurn; //игрок начал действия хода или он ещё раздумывает и выбирает
};


#endif // PLAYER_H
