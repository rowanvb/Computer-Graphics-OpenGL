#include "objectlistmodel.h"

ObjectListModel::ObjectListModel(std::vector<Object*> *objects)
{
    _objects = objects;
}

int ObjectListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return (int) _objects->size();
}

QVariant ObjectListModel::data(const QModelIndex &index, int role) const
{
    switch(role){
    case Qt::DisplayRole:
        return _objects->at(index.row())->getObjectID();
    }
    return QVariant::Invalid;
}
