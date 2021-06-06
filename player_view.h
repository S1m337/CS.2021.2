#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <windows.h>

class Player_view : public QObject, public QGraphicsItem
{
    //класс, отвечающий за отображение данных о враге на виджет
    Q_OBJECT
public:
    explicit Player_view(QObject *parent = 0);
    ~Player_view();
    void setCanMove(bool flag);
    void setHP(int hp, int currhp);

public slots:
    void slotGameTimer(); // Слот, который отвечает за обработку перемещения
    void slotGenerateMove(int moveValue);
    void slotCheckNotEnemy(bool answer); //слот, который помогает определить, есть ли на соседней клетке враг

signals:
    void signalChangeMovePoint(int point);
    void signalStartTurn();
    void signalChangeCoord(QPointF coords);
    void signalCheckNotEnemy(QPointF coord);


protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal angle;    // Угол поворота графического объекта
    int move;
    bool canMove;
    bool nearEnemy;
    int health;
    int current_health;
};

#endif // PLAYER_VIEW_H
