#include "enemy.h"

Enemy::Enemy(QObject *parent) :
    Avatar()
{
    Xcoord = 0;
    Ycoord = 0;
    health = 9;
    current_health = health;
    damage = 2;
    view = new Enemy_view();
    view->setHP(health, current_health);
}

Enemy::~Enemy(){
    delete view;
}

void Enemy::Death(){
    emit signalDeleteEnemy(this);
    view->callEventLeave();
    view->getCell()->setTaken(false);
    this->~Enemy();
}

void Enemy::GetDamage(int damage){
    current_health -= damage;
    view->setHP(health, current_health);
    view->callEventEnter();
    emit signalReleaseDamage();
    if(current_health <= 0)
    {
        Death();
    }
}

int Enemy::GiveDamage()
{
    return damage;
}

Enemy_view* Enemy::getView(){
    return view;
}

QPointF Enemy::getCoord(){
    QPointF coord(Xcoord, Ycoord);
    return coord;
}

void Enemy::setPlayer(Player* pl){
    player = pl;
}

void Enemy::setCoord(QPointF coord){
    Xcoord = coord.x();
    Ycoord = coord.y();
}

void Enemy::setMove(int m_){
    move = m_;//количество клеток, которое можем пройти
}


void Enemy::ChooseAction(){

    QPointF playerPos(player->getCoord());
    QPointF currPos(Xcoord,Ycoord);
    QPointF newPos= CalculateDistance(playerPos); //предполагаемая следующая позиция


    //выбираем четыре клетки вокруг игрока - т.е. единственное возможные варианты для атаки
    QPointF playerPosShiftUp(player->getCoord());
    playerPosShiftUp.setY(player->getCoord().y()-51);
    QPointF playerPosShiftDown(player->getCoord());
    playerPosShiftDown.setY(player->getCoord().y()+51);

    QPointF playerPosShiftLeft(player->getCoord());
    playerPosShiftLeft.setX(player->getCoord().x()-51);
    QPointF playerPosShiftRight(player->getCoord());
    playerPosShiftRight.setX(player->getCoord().x()+51);

    //смотри, находится ли данный враг на дистанции атаки
    if((currPos != playerPosShiftUp)&&(currPos != playerPosShiftDown)&&(currPos != playerPosShiftLeft)&&(currPos != playerPosShiftRight))
    {
        //если нет, то помечаем, что клетка, на которой враг стоит, больше не будет занята им
        view->getCell()->setTaken(false);

        //осуществляем движение, пока не подойдем на дистанцию атаки или по не закончатся очки передвижения
        do {
                view->setPos(newPos);
                Xcoord = newPos.x();
                Ycoord = newPos.y();
                currPos.setX(Xcoord);
                currPos.setY(Ycoord);
                newPos= CalculateDistance(playerPos);
                move--;

        } while (((currPos != playerPosShiftUp)&&(currPos != playerPosShiftDown)&&(currPos != playerPosShiftLeft)&&(currPos != playerPosShiftRight))&&(move > 0));

    }
    else
    {
        //если враг на дистанции атаки, производим атаку
        emit signalEnemyAtack(this);
    }

    //пометка, что клетка, на которой стоит враг, им занята
    view->getCell()->setTaken(true);

}

QPointF Enemy::CalculateDistance(QPointF distPlayer){

    QPointF newCoord(Xcoord,Ycoord);

    distanceX = distPlayer.x() - Xcoord; //расчитываем, сколько клеток до игрока по проекции оси X
    distanceY = distPlayer.y() - Ycoord; //расчитываем, сколько клеток до игрока по проекции оси Y

    //если мы не в дистанции атаки по одной из осей
    if(!((abs(distanceX) == 51) || (abs(distanceY) == 51)))
    {
        //выбираем, по какой оси приоритетней сдвигатся
        if(abs(distanceX) > abs(distanceY)){
            if(distanceX < 0){
               newCoord.setX(Xcoord - 51);
            }
            else if(distanceX > 0){
                newCoord.setX(Xcoord + 51);
            }

        }
        else {
            if(distanceY < 0){
               newCoord.setY(Ycoord - 51);
            }
            else if(distanceY > 0){
                newCoord.setY(Ycoord + 51);
            }

        }

    }

    //если по одной из осей уже в дистанции атаки, то сдвигаемся по второй оси
    if(abs(distanceX) == 51)
    {
        if(distanceY < 0){
           newCoord.setY(Ycoord - 51);
        }
        else if(distanceY > 0){
            newCoord.setY(Ycoord + 51);
        }
    }
    else if(abs(distanceY) == 51)
    {
        if(distanceX < 0){
           newCoord.setX(Xcoord - 51);
        }
        else if(distanceX > 0){
            newCoord.setX(Xcoord + 51);
        }
    }


    QPointF futPos(newCoord);

    //если клетка, на которую хотим переместится, занята, остаемся на месте
    int shift = 11*futPos.x()/51 + futPos.y()/51;
    if(view->getCells()[60+shift]->getTaken())
    {
        QPointF currPos(Xcoord,Ycoord);
        newCoord = currPos;
    }

    return newCoord;
}

