#include "enemy_view.h"

Enemy_view::Enemy_view(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    angle = 0; //задаём угол поворота графического объекта
    setRotation(angle); //устанавилваем угол поворота графического объекта
    this->setAcceptHoverEvents(true); //разрешаем срабатывания событий при наведении на объект
}

Enemy_view::~Enemy_view() {}

void Enemy_view::callEventEnter(){
    hoverEnterEvent(nullptr);
}

void Enemy_view::callEventLeave(){
    hoverLeaveEvent(nullptr);
}

void Enemy_view::callCellEvents(){
    ReceiveCell();
    emit signalGetCells();
}

void Enemy_view::ReceiveCell(){
    emit signalEnemyCell(this);
}

void Enemy_view::setHP(int hp, int currhp)
{
    health = hp;
    current_health = currhp;
}

Cell* Enemy_view::getCell(){
    emit signalEnemyCell(this);
    return cell;
}
QVector<Cell*> Enemy_view::getCells(){
    return cells;
}

void Enemy_view::slotEnemyCell(Cell* c){
    cell = c;
    c->callEventEnter();
}

void Enemy_view::slotGetCells(QVector<Cell*> cells_){
    cells = cells_;
}

QRectF Enemy_view::boundingRect() const
{
    return QRectF(-10,-15,20,30);   /// Ограничиваем область, в которой лежит треугольник
}

void Enemy_view::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        QPolygon polygon;
        polygon << QPoint(-10,-15) << QPoint(10,-15) << QPoint(10,15) << QPoint(-10,15);
        painter->setBrush(QColor(178, 34, 34,255));
        painter->drawPolygon(polygon);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Enemy_view::hoverEnterEvent(QGraphicsSceneHoverEvent *event){

    emit signalViewHP(health,current_health);
    emit signalEnemyCell(this);
}

void Enemy_view::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    emit signalViewHP(health,0);
}
