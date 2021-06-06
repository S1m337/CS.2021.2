#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QTransform>
#include <math.h>
#include <QVector>

#include "player.h"
#include "enemy.h"
#include "enemy_view.h"
#include "cell.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    //класс, отвечающий за основное представление нашей системы
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setPlayer(Player* pl);
    QVector<Cell*> getCells(); //метод доступа к массиву клеток игрового поля
    void CreatePlayer();
    void CreateEnemy(Enemy* newEnemy);
    void TurnOffCells(); //отключение всех выделение на клетках
    void NextTurn();

public slots:
    void slotChangeMovePoint(int point);
    void slotGenerateMove(int moveValue);
    void Update();
    void slotCheckNotEnemy(QPointF coord);
    void slotAvailableTargets();
    void slotClickToAttack(QPointF coord);
    void slotTurnOffCells();
    void slotAddEnemy(Enemy* en);
    void slotDeleteEnemy(Enemy* en);
    void slotViewHP(int hp, int currhp);
    void slotEnemyCell(Enemy_view* enView);
    void slotGetCells();
    void slotEndGame();

signals:
    void signalGenerateMove(int moveValue);
    void signalEndTurn();
    void signalCheckNotEnemy(bool answer);
    void signalAddEnemy(Enemy* en);
    void signalClickToAttack(Enemy* en);
    void signalEnemyCell(Cell* c);
    void signalGetCells(QVector<Cell*> cells_);

private slots:
    void on_btNextTurn_clicked();
    void on_btMakeMove_clicked();
    void on_btAttack_clicked();

private:
    void EnemyAround();

    Ui::Widget *ui;
    QGraphicsScene *scene;
    Player *player;
    int move;
    bool nextTurnFlag;
    QVector<Cell*> cells;
    QVector<Enemy*> enemyAround; //враги на соседней клетке от игрока
    QVector<Enemy*> enemys; //все враги
    bool endGame; //флаг окончания игры
};

#endif // WIDGET_H
