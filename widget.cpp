#include "widget.h"
#include "ui_widget.h"
#include <QDebug>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(700,650); //задаем размеры виджета, то есть окна
    this->setFixedSize(700,650); //фиксируем размеры виджета
    ui->graphicsView->setBackgroundBrush(QColor(128,128,128,255));

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(-275,-275,550,550);


    //заполняем игровое поле объектами клеток
    for(float i = -280.5; i < 280.5; i += 51)
    {
        for(float j = -280.5; j < 280.5; j += 51){
            Cell *c = new Cell();
            scene->addItem(c);
            c->setPos(i,j);
            QTransform tr;
            cells.push_back(static_cast<Cell*>(scene->itemAt(i,j,tr)));
            connect(static_cast<Cell*>(scene->itemAt(i,j,tr)), SIGNAL(signalClickToAttack(QPointF)), this, SLOT(slotClickToAttack(QPointF)));
        }
    }

    nextTurnFlag = false;
    endGame = false;
}

Widget::~Widget()
{
    delete player;
    delete ui;
}

void Widget::setPlayer(Player *pl){
    player = pl;
}

QVector<Cell*> Widget::getCells(){
    return cells;
}

void Widget::CreatePlayer(){
    scene->addItem(player->getView());
    player->getView()->setPos(0,0);
    emit signalGenerateMove(move);
    ui->PointMove->display(move);
    QPointF pos(0,0);
    player->setCoord(pos);

    ui->playerHP->setRange(0,player->getHealth());
    ui->playerHP->setValue(player->getHealth());
}

void Widget::CreateEnemy(Enemy* newEnemy){

    scene->addItem(newEnemy->getView());
    QPointF currPos(newEnemy->getCoord());
    newEnemy->getView()->setPos(currPos);
}

void Widget::EnemyAround(){
    QPointF coordUp(player->getView()->x(), player->getView()->y()+51);
    QPointF coordDown(player->getView()->x(), player->getView()->y()-51);
    QPointF coordLeft(player->getView()->x()-51, player->getView()->y());
    QPointF coordRight(player->getView()->x()+51, player->getView()->y());

    for(int i = 0; i < enemys.size(); i++)
    {
        QPointF currCoord = enemys[i]->getView()->pos();

        if((currCoord == coordUp)||(currCoord == coordDown)||(currCoord == coordLeft)||(currCoord == coordRight))
        {
            enemyAround.push_back(enemys[i]);
        }
    }

    for(int i = 0; i < enemyAround.size(); i++){

        int currCoordX = int(enemyAround[i]->getView()->x())/51;
        int currCoordY = int(enemyAround[i]->getView()->y())/51;

        int shift = 11*currCoordX + currCoordY;

        cells[60 + shift]->setImain(true);
    }
}

void Widget::NextTurn(){
    nextTurnFlag = true;
    TurnOffCells();
    enemyAround.clear();
    emit signalEndTurn();
}

void Widget::TurnOffCells(){
    for(int i = 0; i < enemyAround.size(); i++){

        int currCoordX = int(enemyAround[i]->getView()->x())/51;
        int currCoordY = int(enemyAround[i]->getView()->y())/51;

        int shift = 11*currCoordX + currCoordY;

        cells[60 + shift]->callEvent();
        cells[60 + shift]->setImain(false);
    }

    cells[0]->setCanAttack(false);
}











void Widget::slotChangeMovePoint(int point){
    ui->PointMove->display(point);
    move = point;
}

void Widget::slotAddEnemy(Enemy* en){
    enemys.push_back(en);
    CreateEnemy(en);
}

void Widget::Update(){
    ui->PointMove->display(move);

    if(nextTurnFlag)
    {
        emit signalGenerateMove(move);
        ui->PointMove->display(move);
        nextTurnFlag = false;
        ui->playerHP->setValue(player->getHealth());

        if(player->getHealth() < 0)
        {
            ui->playerHP->setValue(0);
        }
    }
}


void Widget::on_btNextTurn_clicked()
{
    if(!endGame)
    {
       NextTurn();
    }
}

void Widget::on_btMakeMove_clicked()
{
    if(!endGame)
    {
       player->MakeMove();
    }
}

void Widget::slotGenerateMove(int moveValue){

    move = moveValue;
}

void Widget::slotCheckNotEnemy(QPointF coord){
    bool en = false;

    for(int i = 0; i < enemys.size(); i++)
    {
        if(enemys[i]->getView()->pos() == coord)
        {
            en = true;
        }
    }

    if(!en){
        emit signalCheckNotEnemy(false);
    }
    else{
        emit signalCheckNotEnemy(true);
    }

}

void Widget::on_btAttack_clicked()
{
    if(!endGame)
    {
      player->Attack();
    }
}


void Widget::slotAvailableTargets(){
    EnemyAround();
}

void Widget::slotClickToAttack(QPointF coord){
    QPointF coordEn(coord.x()+25.5,coord.y()+25.5);
    Enemy* clickedEn = nullptr;

    for(int i = 0; i < enemyAround.size(); i++)
    {
        QPointF currPos = enemyAround[i]->getView()->pos();
        if(currPos == coordEn)
        {
             clickedEn = enemyAround[i];
        }
    }

    emit signalClickToAttack(clickedEn);
}


void Widget::slotTurnOffCells(){
    TurnOffCells();
}


void Widget::slotDeleteEnemy(Enemy* en)
{
    QVector<Enemy*> newEnemys;

    for(int i = 0; i < enemys.size(); i++){

        if(enemys[i] != en){
            newEnemys.push_back(enemys[i]);
        }
    }

    enemys.clear();
    enemys = newEnemys;
}

void Widget::slotViewHP(int hp, int currhp){
    ui->enemyHP->setRange(0,hp);
    ui->enemyHP->setValue(currhp);
}

void Widget::slotEnemyCell(Enemy_view* enView){
    QPointF pos = enView->pos();

    int shift = 11*pos.x()/51 + pos.y()/51;
    emit signalEnemyCell(cells[60 + shift]);
}


void Widget::slotGetCells(){
    emit signalGetCells(cells);
}

void Widget::slotEndGame(){
    endGame = true;
}
