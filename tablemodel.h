#ifndef TABLEMODEL_H
#define TABLEMODEL_H


#include <QAbstractTableModel>
#include "packet.h"

class TableModel : public QAbstractTableModel {
    Q_OBJECT

private:
    QVector <Packet> grid;

public:
    explicit TableModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
     QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
     Packet all_data(const QModelIndex &index, int role);
     bool set_data(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
     bool set_all_data(const QModelIndex &index, const Packet &p, int role = Qt::EditRole);
     Qt::ItemFlags flags(const QModelIndex & index) const;
     QVariant headerData(int section, Qt::Orientation orientation, int role) const;
     bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
     bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
};

#endif // TABLEMODEL_H
