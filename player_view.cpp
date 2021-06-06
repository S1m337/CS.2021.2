#include "player_view.h"

Player_view::Player_view(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    angle = 0;
    setRotation(angle);
    canMove = false;
    nearEnemy = false;
}

Player_view::~Player_view(){}

void Player_view::setCanMove(bool flag){
    canMove = flag;
}

void Player_view::setHP(int hp, int currhp)
{
    health = hp;
    current_health = currhp;
}

QRectF Player_view::boundingRect() const
{
    return QRectF(-10,-15,20,30);
}

void Player_view::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        QPolygon polygon;
        polygon << QPoint(0,-15) << QPoint(10,15) << QPoint(-10,15);
        painter->setBrush(QColor(173, 255, 47,255));
        painter->drawPolygon(polygon);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Player_view::slotGameTimer()
{
    if(canMove)
    {
        if(move > 0){

            if(GetAsyncKeyState(65)& 0x8000){
                angle -= 90;
                setRotation(angle);
                emit signalStartTurn(); //ход начался, изменить решение уже не получится
            }
            if(GetAsyncKeyState(68)& 0x8000){
                angle += 90;
                setRotation(angle);
                emit signalStartTurn();
            }
            if(GetAsyncKeyState(87)& 0x8000){

                QPointF coord = this->mapToParent(0, -51);

                emit signalCheckNotEnemy(coord);

                if(!nearEnemy) //если на соседней клетке нет врага, передвигаемся на эту клетку
                {
                    setPos(mapToParent(0, -51));
                    move--;
                    emit signalStartTurn();
                    emit signalChangeMovePoint(move);
                }

            }
            if(GetAsyncKeyState(83)& 0x8000){
                QPointF coord = this->mapToParent(0, 51);

                emit signalCheckNotEnemy(coord);

                if(!nearEnemy)
                {
                    setPos(mapToParent(0, 51));
                    move--;
                    emit signalStartTurn();
                    emit signalChangeMovePoint(move);
                }
            }
        }
    }


    //ограничиваем область, чтобы игрок не мог выйти на край экрана
    if(this->x() - 25.5 < -281){
        this->setX(-255);
        move++;
        emit signalChangeMovePoint(move);
    }
    if(this->x() + 25.5 > 281){
        this->setX(255);
        move++;
        emit signalChangeMovePoint(move);
    }

    if(this->y() - 25.5 < -281){
        this->setY(-255);
        move++;
        emit signalChangeMovePoint(move);
    }
    if(this->y() + 25.5 > 281){
        this->setY(255);
        move++;
        emit signalChangeMovePoint(move);
    }

    QPointF coord(this->x(),this->y());
    emit signalChangeCoord(coord);

}

void Player_view::slotGenerateMove(int moveValue){
    move = moveValue;
}

void Player_view::slotCheckNotEnemy(bool answer){
    nearEnemy = answer;
}










