#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QFileSystemModel>
#include <QObject>

class FileSystemModel : public QFileSystemModel {
    Q_OBJECT
public:
    enum Column {
        NAME = 0,
        SIZE,
        TYPE,
    };
    enum Roles {
        isDirRole = FilePermissions + 1,
    };
    explicit FileSystemModel(QObject* parent = nullptr);

    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QString size(const QModelIndex& index) const;
};

#endif // FILESYSTEMMODEL_H
