#ifndef OBJECTLISTMODEL_H
#define OBJECTLISTMODEL_H
#include <QAbstractItemModel>
#include "object.h"

class ObjectListModel : public QAbstractListModel
{
    std::vector<Object*> *_objects;


public:
    ObjectListModel(){}
    ObjectListModel(std::vector<Object*> *objects);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // OBJECTLISTMODEL_H
