#ifndef AVATAR_H
#define AVATAR_H
#include <QObject>

class Avatar : public QObject {
Q_OBJECT
public:
    virtual void GetDamage(int damage) = 0;
    virtual int GiveDamage() = 0;

protected:
    virtual void Death() = 0;

    int health, move,damage;
    int Xcoord, Ycoord;
    int current_health;
};


#endif // AVATAR_H

