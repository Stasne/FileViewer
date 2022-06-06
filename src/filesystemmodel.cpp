#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(QObject* parent)
    : QFileSystemModel(parent)
{
    setReadOnly(false);
}

int FileSystemModel::columnCount(const QModelIndex& parent) const
{
    return 3; // QFileSystemModel::columnCount(parent);
}

QVariant FileSystemModel::data(const QModelIndex& index, int role) const
{
    return QFileSystemModel::data(index, role);
}
