#include "FileSystemModel.h"

namespace {

const QMap<int, QString> Headers {
    { FileSystemModel::Column::NAME, QObject::tr("Name") },
    { FileSystemModel::Column::SIZE, QObject::tr("Size") },
    { FileSystemModel::Column::TYPE, QObject::tr("Type") }
};
const QString DirectorySizePlaceholder { QObject::tr("<DIR>") };

}
FileSystemModel::FileSystemModel(QObject* parent)
    : QFileSystemModel(parent)
{
    setReadOnly(false);
}

int FileSystemModel::columnCount(const QModelIndex& parent) const
{
    return Headers.size();
}

QVariant FileSystemModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole and index.column() == SIZE)
        return size(index);
    if (role == isDirRole)
        return isDir(index);
    return QFileSystemModel::data(index, role);
}

QString FileSystemModel::size(const QModelIndex& index) const
{
    if (!index.isValid())
        return QString();
    static const QFileSystemModel* model = static_cast<const QFileSystemModel*>(index.model());

    if (model->isDir(index))
        return DirectorySizePlaceholder;

    return QFileSystemModel::data(index).toString();
}
QVariant FileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole and Headers.contains(section))
        return Headers[section];

    return QFileSystemModel::headerData(section, orientation, role);
}
