#ifndef FILESYSTEMPRESENTER_H
#define FILESYSTEMPRESENTER_H

#include <QObject>
#include <QSharedPointer>
class FileSystemModel;
class QTreeView;
namespace Ui {
class MainWindow;
};
class FileSystemPresenter : public QObject {
    Q_OBJECT
public:
    FileSystemPresenter() = delete;
    FileSystemPresenter(QSharedPointer<FileSystemModel> m, QSharedPointer<Ui::MainWindow> ui);

private:
    bool eventFilter(QObject* target, QEvent* event);
    void deleteSelectedFiles();

private:
    QSharedPointer<Ui::MainWindow> ui_;
    QSharedPointer<FileSystemModel> model_;
    QTreeView* tree_;
};

#endif // FILESYSTEMPRESENTER_H
