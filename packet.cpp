#include "packet.h"
#include <iostream>
#include <QDebug>
#include <QString>
#include <fstream>
#include <QFile>
#include <QDataStream>

using namespace std;



Packet::Packet()
{
    name_ = "";
    density_ = 0;
    depth_ = 0;
    projectile_ ="";
    res_ = false;
}

Packet::Packet(QString projectile, QString name, int density, int depth, bool res){
    name_ = name;
    density_ = density;
    depth_ = depth;
    projectile_ = projectile;
    res_ = res;
}

QString Packet::name() const{
    return this->name_;
}

QString Packet::projectile() const{
    return this->projectile_;
}

int Packet::density() const{
    return this->density_;
}

int Packet::depth() const{
    return this->depth_;
}

bool Packet::res() const{
    return this->res_;
}


void Packet::set_name(QString name){
    this->name_ = name;
}

void Packet::set_projectile(QString proj){
    this->projectile_ = proj;
}

void Packet::set_density(int density){
    this->density_ = density;
}

void Packet::set_depth(int depth){
    this->depth_ = depth;
}

void Packet::set_res(bool res){
    this->res_ = res;
}

void Packet::Delete(){
    QFile file("file.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
      file.close();
}

void Packet::Write(Packet p){
    QFile file("file.txt");
    file.open( QIODevice::Append );
    QDataStream out(&file);   // we will serialize the data into the file
    out << p;
    file.close();
}

QVector<Packet> Packet::Read(){
    QVector <Packet> v;
    Packet p;
    QFile file("file.txt");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);   // we will serialize the data into the file
    while(!in.atEnd()){
        in >> p;
        qDebug() << p;
        v.push_back(p);
    }
    file.close();


    return v;
}

