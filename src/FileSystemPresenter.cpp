#include "FileSystemPresenter.h"
#include "./ui_MainWindow.h"
#include "FileSystemModel.h"
#include "IDisplaySettings.h"
#include "IniLetterDelegate.h"
#include "NameFilterProxy.h"
#include <QDebug>
#include <QHeaderView>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTreeView>
FileSystemPresenter::FileSystemPresenter(QSharedPointer<FileSystemModel> m, QSharedPointer<Ui::MainWindow> ui)
    : ui_(ui)
    , model_(m)
    , tree_(ui->twMain)
{
    Q_ASSERT(model_);
    Q_ASSERT(tree_);

    model_->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::AllEntries);
    model_->setRootPath("");

    tree_->setModel(model_.get());
    //    auto filter = new QSortFilterProxyModel();
    //    filter->setSourceModel(model_.get());
    //    tree_->setModel(filter);

    auto settings = QSharedPointer<IDisplaySettings>::create();
    auto initiaLetterDelegate = new IniLetterDelegate(settings);
    tree_->setItemDelegateForColumn(FileSystemModel::Column::NAME, initiaLetterDelegate);
    tree_->header()->setSectionResizeMode(FileSystemModel::Column::NAME, QHeaderView::ResizeMode::Stretch);
    tree_->installEventFilter(this);
}

void FileSystemPresenter::deleteSelectedFiles()
{
    auto deletePrompt = [](const QList<QModelIndex>& indexes) {
        QMessageBox msgBox;
        msgBox.setText(tr("Are you sure?"));
        msgBox.setInformativeText(tr("You are about to delete %1 files?").arg(indexes.size()));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        QString details { tr("Files to delete:\n") };
        for (const auto& index : indexes)
            details += index.data().toString() + '\n';
        msgBox.setDetailedText(details);
        msgBox.setDefaultButton(QMessageBox::Yes);
        return msgBox.exec();
    };
    auto deleteErrorPrompt = [](const QModelIndex& index) {
        QMessageBox msgBox;
        msgBox.setText(tr("Error"));
        msgBox.setInformativeText(tr("Can't delete file %1").arg(index.data().toString()));
        msgBox.setStandardButtons(QMessageBox::Ignore | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        return msgBox.exec();
    };

    const auto indexesToDelete = tree_->selectionModel()->selectedRows();
    if (not indexesToDelete.size())
        return;

    if (deletePrompt(indexesToDelete) != QMessageBox::Yes)
        return;

    for (const auto& index : indexesToDelete) {
        if (not model_->remove(index))
            if (deleteErrorPrompt(index) != QMessageBox::Ignore)
                return;
    }
    tree_->selectionModel()->clearSelection();
}

bool FileSystemPresenter::eventFilter(QObject* target, QEvent* event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Delete) {
            deleteSelectedFiles();
            return true;
        }
    }
    return false;
}
