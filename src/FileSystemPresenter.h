#ifndef FILESYSTEMPRESENTER_H
#define FILESYSTEMPRESENTER_H

#include <QObject>
#include <QSharedPointer>
class FileSystemModel;
class QTreeView;

class FileSystemPresenter : public QObject {
    Q_OBJECT
public:
    FileSystemPresenter() = delete;
    FileSystemPresenter(QSharedPointer<FileSystemModel> m, QTreeView* tree);

private:
    bool eventFilter(QObject* target, QEvent* event);
    void deleteSelectedFiles();

private:
    QSharedPointer<FileSystemModel> model_;
    QTreeView* tree_;
};

#endif // FILESYSTEMPRESENTER_H
