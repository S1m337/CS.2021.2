#ifndef ENEMY_VIEW_H
#define ENEMY_VIEW_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>

#include "cell.h"
#include <windows.h>

class Enemy_view : public QObject, public QGraphicsItem
{
    //класс, отвечающий за отображение данных о враге на виджет
    Q_OBJECT
public:
    explicit Enemy_view(QObject *parent = 0);
    ~Enemy_view();

    void callEventEnter(); //подсветка врага при наведении
    void callEventLeave(); //возвращение посвеченного элеменат в исходное состояние
    void callCellEvents();
    void ReceiveCell(); //метод для получения ссылки на клетку, на которой находится данное представление врага

    void setHP(int hp, int currhp);
    Cell* getCell(); //вовращаем ссылку на клетку, на которой находимся
    QVector<Cell*> getCells();


public slots:
    void slotEnemyCell(Cell* c);
    void slotGetCells(QVector<Cell*> cells_);

signals:
    void signalChangeMovePoint(int point);
    void signalViewHP(int hp, int currhp);
    void signalEnemyCell(Enemy_view* enView);
    void signalGetCells();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    qreal angle;    // Угол поворота графического объекта
    int move;
    int health;
    int current_health;
    Cell* cell;
    QVector<Cell*> cells;

};

#endif // ENEMY_VIEW_H
