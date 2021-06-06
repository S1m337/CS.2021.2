#include "player.h"

Player::Player(QObject *parent) :
    Avatar()
{
    view = new Player_view();
    makeMove = false;
    attack = false;
    currentTurn = false;
    Xcoord = 0;
    Ycoord = 0;
    health = 9;
    current_health = health;
    damage = 3;
}

Player::~Player(){
    delete  view;
}

void Player::MakeMove(){
    if(!currentTurn)
    {
        makeMove = true;
        attack = false;
        Update();
    }
}

void Player::Attack(){
    if(!currentTurn)
    {
        makeMove = false;
        attack = true;
        Update();
    }
}

void Player::Death(){
    emit signalEndGame(); //при смерти оканчиваем игру
    delete view;
}

void Player::Update(){

    if(makeMove){
        view->setCanMove(true);
        Cell* c = new Cell();
        emit signalTurnOffCells();
        c->setCanAttack(false);
    }
    else if(attack){
        view->setCanMove(false);
        Cell* c = new Cell();
        c->setCanAttack(true);
        emit signalAvailableTargets();
    }
}
void Player::GetDamage(int damage){
    if(current_health > 0)
    {
        current_health -= damage;
        view->setHP(health, current_health);
        if(current_health <= 0)
        {
            Death();
        }
    }
}

int Player::GiveDamage(){
    return damage;
}

void Player::setCoord(QPointF coord){
    Xcoord = coord.x();
    Ycoord = coord.y();
}

Player_view* Player::getView(){
    return view;
}

QPointF Player::getCoord(){
    QPointF coord;
    coord.setX(Xcoord);
    coord.setY(Ycoord);
    return coord;
}

int Player::getHealth(){
    return current_health;
}

void Player::slotStartTurn(bool currTurn){
    currentTurn = currTurn;
}

void Player::slotEndTurn(bool currTurn){
    currentTurn = currTurn;
    makeMove = false;
    attack = false;
}
