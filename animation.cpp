#include "animation.h"
#include "ui_animation.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QtDebug>
#include <math.h>

Animation::Animation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Animation)
{
    ui->setupUi(this);
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &Animation::onTimeout);
    _timer->start(100);
     scene_ = new QGraphicsScene;
     pool_= new Pool(0, 30);
    material = new QGraphicsRectItem (500, -50,30, 200);
    time_=1;
}

Animation::~Animation()
{
    delete ui;
}

void Animation::set_res(bool res){
    res_ = res;
}

void Animation::Paint(){

    scene_->addItem(pool_);

    material->setPen(QPen(QColor("#d4d4d4"), 0.1));
    material->setBrush(QBrush(QColor("#c56c00"), Qt::SolidPattern));
    scene_->addItem(material);

    ui->graphicsView->setScene(scene_);
    ui->graphicsView->show();
}

void Animation::onTimeout()
{
    int a = 30;
    int v0 = 336;
    float g = 9.8;
    float pi=3.1415926;
    QPointF oldPos = pool_->pos();
    if (oldPos.x() < 450){
        //QPointF newPos = QPointF(pool_->pos().x()+10, pool_->pos().y());
        qreal xx = (v0*cos(a*pi/180)*time_)/20-pool_->pos().x();
        qreal yy = -(v0*sin(a*pi/180)*time_-g*time_*time_/2)/20-pool_->pos().y();
        time_++;
        QPointF newPos = QPointF(pool_->pos().x()+xx, pool_->pos().y()+yy);
        pool_->setPos(newPos);
    } else{
        QGraphicsTextItem *textItem = new QGraphicsTextItem ("Материал не пробит");
        if (res_ == true){
            textItem = new QGraphicsTextItem ("Материал пробит");
            scene_->removeItem(material);

            QTransform tr;
            tr.rotate (-30);
            QGraphicsRectItem *m1 = new QGraphicsRectItem (450, 200,30, 100);
            m1->setPen(QPen(QColor("#d4d4d4"), 0.1));
            m1->setBrush(QBrush(QColor("#c56c00"), Qt::SolidPattern));
            m1->setTransform(tr);
            scene_->addItem(m1);
            tr.rotate (60);
            QGraphicsRectItem *m2 = new QGraphicsRectItem (500, -250,30, 100);
            m2->setPen(QPen(QColor("#d4d4d4"), 0.1));
            m2->setBrush(QBrush(QColor("#c56c00"), Qt::SolidPattern));
            m2->setTransform(tr);
            scene_->addItem(m2);
        }
        textItem->setPos(100, 0);
        QFont font("Georgia", 14);
        textItem->setFont(font);
        scene_->addItem(textItem);
    }
}

void Animation::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);
  Paint();
}

GraphicsScene::GraphicsScene(QObject *parent) :
    QGraphicsScene(parent){}


Pool::Pool(int x, int y): QGraphicsItem(), x_(x), y_(y) {};
Pool::~Pool(){}

QRectF Pool::boundingRect() const{
    return QRectF(0, 0, 80, 80);
}

void Pool::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
     Q_UNUSED(option) Q_UNUSED(widget);

     painter->setPen(QColor("#d4d4d4"));
     painter->setBrush(QBrush("#9c2f1e"));
     painter->drawEllipse(x_,y_, 30,30);
}
