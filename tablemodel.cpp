#include "tablemodel.h"
#include "packet.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent) {
     grid.resize(0);
}

int TableModel::rowCount(const QModelIndex &parent) const {
    return grid.size();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
         switch (index.column()) {
         case 0:
            return grid[index.row()].projectile();
            break;
         case 1:
            return grid[index.row()].name();
            break;
         case 2:
            return grid[index.row()].density();
            break;
         case 3:
            return grid[index.row()].depth();
            break;
         case 4:
            return grid[index.row()].res();
            break;
         default:
            break;
         }
    }
    return QVariant();
}

Packet TableModel::all_data(const QModelIndex &index, int role) {
    //Packet p;
    //if (role == Qt::DisplayRole) {
        int a = index.row();
        QString p = grid[index.row()].projectile();
        QString n = grid[index.row()].name();
        int den = grid[index.row()].density();
        int dep = grid[index.row()].depth();
        bool res = grid[index.row()].res();
        Packet p2(p, n, den, dep, res);
        return p2;
    //}
   // return p;
}

bool TableModel::set_data(const QModelIndex &index, const QVariant &value, int role) {
    //if (role == Qt::EditRole) {
         switch (index.column()) {
             case 0:
                 grid[index.row()].set_projectile(value.toString());
                 break;
             case 1:
                 grid[index.row()].set_name(value.toString());
                 break;
             case 2:
                 grid[index.row()].set_density(value.toInt());
                 break;
             case 3:
                 grid[index.row()].set_depth(value.toInt());
                 break;
             case 4:
                 grid[index.row()].set_res(value.toBool());
                 break;
         }
    //}
    return true;
}

bool TableModel::set_all_data( const QModelIndex &index, const Packet &p, int role) {
    //if (role == Qt::EditRole) {
         grid[index.row()].set_projectile(p.projectile());
         grid[index.row()].set_name(p.name());
         grid[index.row()].set_density(p.density());
         grid[index.row()].set_depth(p.depth());
         grid[index.row()].set_res(p.res());
    //}
    return true;
}

Qt::ItemFlags TableModel::flags(const QModelIndex & index) const {
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);

}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("Вид снаряда");
                    break;
                case 1:
                    return QString("Название материала");
                    break;
                case 2:
                    return QString("Плотность");
                    break;
                case 3:
                    return QString("Толщина");
                    break;
                case 4:
                    return QString("Результат");
                    break;
            }

       }
       return QVariant();
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent) {
     beginInsertRows(parent,row, row + count - 1);
     grid.insert(row, count, Packet());
     endInsertRows();
     return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent) {
     beginRemoveRows(parent,row, row + count - 1);
     grid.remove(row, count);
     endRemoveRows();
     return true;
}

