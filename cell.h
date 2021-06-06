#ifndef CELL_H
#define CELL_H

#include <QGraphicsRectItem>
#include <QPen>
#include <QVector>
#include <QObject>

class Cell: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Cell(QGraphicsItem *parent=0); //класс, для создания ячейки в качестве отдельной единицы
    ~Cell();

    void callEvent(); //вызов из вне события прекращения наведения на ячейку
    void callEventEnter(); //вызов из вне события начала наведения на ячейку

    void setImain(bool imain);
    void setCanAttack(bool canAtt);
    void setTaken(bool t_);

    bool getTaken();

public slots:
signals:
    void signalClickToAttack(QPointF coord); //игрок атакует данную клетку

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event); //подкрашивание в цвет выделения при наведении
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event); //подкрашивание в стандартный цвет при окончании наведения
    void mousePressEvent(QGraphicsSceneMouseEvent * event); //отслеживание совершения атаки на данную клетку

private:
    bool i_main = false; //на данный клетке находится враг
    static bool canAttack; //на данную клетку можно провести атаку
    bool isTaken;

};

#endif // CELL_H
