#include "cell.h"
#include <QPainter>

bool Cell::canAttack = false;

Cell::Cell(QGraphicsItem *parent):
    QGraphicsRectItem()
{
    setRect(QRectF(0, 0, 50, 50));
    QPen pen;
    pen.setColor(QColor(0,0,0,255));
    pen.setWidth(1);
    setPen(pen);
    Cell::setOpacity(1);
    setAcceptHoverEvents(true);
    isTaken = false;
}

Cell::~Cell(){}

void Cell::callEvent(){
    hoverLeaveEvent(nullptr);
}

void Cell::callEventEnter(){
    hoverEnterEvent(nullptr);
}

void Cell::setImain(bool imain){
    i_main = imain;
}


void Cell::setCanAttack(bool canAtt){
    canAttack = canAtt;
}

void Cell::setTaken(bool t_){
    isTaken  = t_;
}

bool Cell::getTaken(){
    return isTaken;
}

void Cell::hoverEnterEvent(QGraphicsSceneHoverEvent *event){

    if(canAttack)
    {
        if(i_main)
        {
            QPen pen;
            pen.setColor(QColor(255, 0, 0,255));
            pen.setWidth(2);
            setPen(pen);
        }
    }
}

void Cell::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    if(canAttack)
    {
        if(i_main)
        {
            QPen pen;
            pen.setColor(QColor(0,0,0,255));
            pen.setWidth(1);
            setPen(pen);
        }
    }
}


void Cell::mousePressEvent(QGraphicsSceneMouseEvent * event){
    QGraphicsItem::mousePressEvent(event);
    if(canAttack)
    {
        if(i_main)
        {
            emit signalClickToAttack(this->pos());
        }
    }
}

