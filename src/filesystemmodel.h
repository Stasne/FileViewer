#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QFileSystemModel>
#include <QObject>

class FileSystemModel : public QFileSystemModel
{
    Q_OBJECT
public:
    explicit FileSystemModel(QObject* parent = nullptr);

public:
    int      columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const override;
};

#endif // FILESYSTEMMODEL_H
