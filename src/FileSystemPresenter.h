#ifndef FILESYSTEMPRESENTER_H
#define FILESYSTEMPRESENTER_H

#include <QObject>
#include <QSharedPointer>

class FileSystemModel;
class QTreeView;
class QSortFilterProxyModel;
class IDisplaySettings;
namespace Ui {
class MainWindow;
};
class FileSystemPresenter : public QObject {
    Q_OBJECT
public:
    explicit FileSystemPresenter(const QSharedPointer<FileSystemModel> m, const QSharedPointer<Ui::MainWindow> ui, const QSharedPointer<IDisplaySettings>);
    ~FileSystemPresenter() = default;
    FileSystemPresenter() = delete;
    FileSystemPresenter& operator=(FileSystemPresenter) = delete;

private:
    bool eventFilter(QObject* target, QEvent* event);
    void deleteSelectedFiles() const;

private:
    QSharedPointer<Ui::MainWindow> ui_;
    QSharedPointer<QSortFilterProxyModel> nameFilter_;
    QSharedPointer<FileSystemModel> model_;
    QTreeView* tree_;
};

#endif // FILESYSTEMPRESENTER_H
