#ifndef PACKET_H
#define PACKET_H

#include <iostream>
#include <QVector>
#include <QDataStream>
#include <QDebug>

using namespace std;

class Packet
{
public:
    Packet();
    Packet(QString projectile, QString name, int density, int depth, bool res);
    void Write(Packet p);
    void Delete();
    QVector<Packet> Read();
    QString name() const;
    QString projectile() const;
    int density() const;
    int depth() const;
    bool res() const;

    void set_name(QString name);
    void set_projectile(QString proj);
    void set_density(int density);
    void set_depth(int depth);
    void set_res(bool res);

    friend inline QDataStream &operator<<(QDataStream &ds, const Packet &p);
    friend inline QDataStream &operator>>(QDataStream &ds, Packet &p);
    friend inline QDebug operator<<(QDebug qd, const Packet &p);

private:
    QString projectile_; //снаряд
    QString name_; //название материала
    int density_; // плотность материала
    int depth_; //толщина материала
    bool res_; // пробил ли снаряд материал
};

inline QDataStream &operator<<(QDataStream &ds, const Packet &p){
    return ds << p.projectile_ << p.name_ << p.density_ << p.depth_ << p.res_;
}
inline QDataStream &operator>>(QDataStream &ds, Packet &p){
    return ds >> p.projectile_ >> p.name_ >> p.density_ >> p.depth_ >> p.res_;
}
inline QDebug operator<<(QDebug qd, const Packet &p){
    return qd << p.projectile_ << p.name_ << p.density_ << p.depth_ << p.res_;
}


#endif // PACKET_H
