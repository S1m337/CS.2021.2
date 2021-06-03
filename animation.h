#ifndef ANIMATION_H
#define ANIMATION_H


#include <QWidget>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsScene>
#include <QMoveEvent>
#include <QStack>
#include <QPoint>

namespace Ui {
class Animation;
}

class Animation : public QWidget
{
    Q_OBJECT

public:
    explicit Animation(QWidget *parent = nullptr);
    ~Animation();
    void Paint();
    void set_res(bool res);
protected:
    void paintEvent(QPaintEvent*e);
protected slots:
    void onTimeout();
private:
    Ui::Animation *ui;
    QTimer* _timer;
    QGraphicsScene *scene_;
    QGraphicsItem *pool_;
    bool res_;
    int time_;
    QGraphicsRectItem *material;
};

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent = 0);
};

class Pool: public QGraphicsItem{
private:
    int x_;
    int y_;

public:
    Pool(int x, int y);
    ~Pool();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
#endif // ANIMATION_H
