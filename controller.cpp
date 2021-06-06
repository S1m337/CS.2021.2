#include "Controller.h"
#include <QDebug>
#include <QApplication>

Controller::Controller(){
   currentTurn = false;
}

Controller::~Controller(){}

void Controller::StartGame()
{
    srand(time(0)); //сид для рандомизации очков передвижения игрока

    player = new Player();
    widget = new Widget();
    widget->setPlayer(player);
    ConnectSystem();
    widget->CreatePlayer();
    GenerateMove();
    CreateEnemy();
    CreateEnemy();
    CreateEnemy();
    widget->show();
}

void Controller::EndGame(){
    emit signalEndGame();
}

int Controller::GenerateMove(){
    return rand()%6 + 1;
}

void Controller::MakeBattle(Avatar* attaker, Avatar* defender){

    defender->GetDamage(attaker->GiveDamage());
}


void Controller::slotGenerateMove(int moveValue){
    moveValue = GenerateMove();
    emit signalGenerateMove(moveValue);
}

void Controller::slotStartTurn(){
    currentTurn = true;
    emit signalStartTurn(currentTurn);
}
void Controller::slotEndTurn(){
    currentTurn = false;
    player->getView()->setCanMove(false);
    widget->TurnOffCells();
    emit signalEndTurn(currentTurn);
    QVector <QPointF> coordEn;

    for(int i = 0; i < enemys.size(); i++)
    {
        enemys[i]->ChooseAction();
        coordEn.push_back(enemys[i]->getCoord());
    }
}

void Controller::slotChangeCoord(QPointF coords){
    player->setCoord(coords);
}

void Controller::slotAvailableTargets(){
    emit signalAvailableTargets();
}

void Controller::slotClickToAttack(Enemy* en){
    emit signalStartTurn(true);
    if(en != nullptr)
    {
        MakeBattle(player, en);
    }
}

void Controller::slotReleaseDamage(){ //после распределение всего урона, начинается следующий ход
    widget->NextTurn();
}

void Controller::slotTurnOffCells(){
    emit signalTurnOffCells();
}

void Controller::slotDeleteEnemy(Enemy* en){
    emit signalDeleteEnemy(en);

    QVector<Enemy*> newEnemys;

    for(int i = 0; i < enemys.size(); i++){

        if(enemys[i] != en){
            newEnemys.push_back(enemys[i]);
        }
    }

    enemys.clear();
    enemys = newEnemys;
}

void Controller::slotEnemyAtack(Enemy* en){
    MakeBattle(en,player);
}

void Controller::ConnectSystem(){

    timer = new QTimer();

    connect(timer, &QTimer::timeout, player->getView(), &Player_view::slotGameTimer);
    connect(timer, &QTimer::timeout, widget, &Widget::Update);


    connect(player->getView(),SIGNAL(signalChangeMovePoint(int)), widget,SLOT(slotChangeMovePoint(int)));
    connect(widget, SIGNAL(signalGenerateMove(int)), this, SLOT(slotGenerateMove(int)));

    connect(player->getView(), SIGNAL(signalChangeCoord(QPointF)), this, SLOT(slotChangeCoord(QPointF)));

    connect(this, SIGNAL(signalGenerateMove(int)), player->getView(), SLOT(slotGenerateMove(int)));
    connect(this, SIGNAL(signalGenerateMove(int)), widget, SLOT(slotGenerateMove(int)));

    connect(player->getView(), SIGNAL(signalStartTurn()),this, SLOT(slotStartTurn()));
    connect(this, SIGNAL(signalStartTurn(bool)), player, SLOT(slotStartTurn(bool)));
    connect(widget, SIGNAL(signalEndTurn()), this, SLOT(slotEndTurn()));
    connect(this, SIGNAL(signalEndTurn(bool)), player, SLOT(slotEndTurn(bool)));

    connect(player->getView(), SIGNAL(signalCheckNotEnemy(QPointF)), widget, SLOT(slotCheckNotEnemy(QPointF)));
    connect(widget, SIGNAL(signalCheckNotEnemy(bool)), player->getView(), SLOT(slotCheckNotEnemy(bool)));

    connect(player, SIGNAL(signalAvailableTargets()), this, SLOT(slotAvailableTargets()));
    connect(this, SIGNAL(signalAvailableTargets()), widget, SLOT(slotAvailableTargets()));

    connect(widget, SIGNAL(signalClickToAttack(Enemy*)), this, SLOT(slotClickToAttack(Enemy*)));
    connect(this, SIGNAL(signalAddEnemy(Enemy*)), widget, SLOT(slotAddEnemy(Enemy*)));

    connect(player, SIGNAL(signalTurnOffCells()), this, SLOT(slotTurnOffCells()));
    connect(this, SIGNAL(signalTurnOffCells()), widget, SLOT(slotTurnOffCells()));


    connect(this, SIGNAL(signalDeleteEnemy(Enemy*)), widget, SLOT(slotDeleteEnemy(Enemy*)));

    connect(player, SIGNAL(signalEndGame()), this, SLOT(slotEndGame()));
    connect(this, SIGNAL(signalEndGame()), widget, SLOT(slotEndGame()));

    timer->start(1000 / 10);
}


void Controller::CreateEnemy(){
    Enemy* enemy = new Enemy();

    QPointF coordEn(((rand()%4 + 1)*51*((rand()%2==0)?1:-1)),((rand()%4 + 1)*51*((rand()%2==0)?1:-1)));
    enemy->setCoord(coordEn);
    enemy->setPlayer(player);
    enemy->setMove(2);

    enemys.push_back(enemy);

    emit signalAddEnemy(enemy);
    connect(enemy, SIGNAL(signalReleaseDamage()), this, SLOT(slotReleaseDamage()));
    connect(enemy, SIGNAL(signalDeleteEnemy(Enemy*)), this, SLOT(slotDeleteEnemy(Enemy*)));
    connect(enemy->getView(), SIGNAL(signalViewHP(int, int)), widget, SLOT(slotViewHP(int, int)));

    connect(enemy->getView(), SIGNAL(signalEnemyCell(Enemy_view*)), widget, SLOT(slotEnemyCell(Enemy_view*)));
    connect(widget, SIGNAL(signalEnemyCell(Cell*)), enemy->getView(), SLOT(slotEnemyCell(Cell*)));

    connect(enemy, SIGNAL(signalEnemyAtack(Enemy*)), this, SLOT(slotEnemyAtack(Enemy*)));

    connect(enemy->getView(), SIGNAL(signalGetCells()), widget, SLOT(slotGetCells()));
    connect(widget, SIGNAL(signalGetCells(QVector<Cell*>)), enemy->getView(), SLOT(slotGetCells(QVector<Cell*>)));
    enemy->getView()->callCellEvents();
}

void Controller::slotEndGame(){
    EndGame();
}


