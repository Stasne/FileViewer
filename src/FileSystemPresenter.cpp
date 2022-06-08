#include "FileSystemPresenter.h"
#include "./ui_MainWindow.h"
#include "FileSystemModel.h"
#include "IDisplaySettings.h"
#include "IniLetterDelegate.h"
#include <QHeaderView>
#include <QKeyEvent>
#include <QLineEdit>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QTreeView>

FileSystemPresenter::FileSystemPresenter(const QSharedPointer<FileSystemModel> m, const QSharedPointer<Ui::MainWindow> ui, const QSharedPointer<IDisplaySettings> settings)
    : ui_(ui)
    , model_(m)
    , nameFilter_(new QSortFilterProxyModel())
{
    Q_ASSERT(model_);
    Q_ASSERT(ui);
    Q_ASSERT(settings);

    model_->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::AllEntries);
    model_->setRootPath("");

    nameFilter_->setSourceModel(model_.get());
    nameFilter_->setRecursiveFilteringEnabled(true);
    // самым примитивным способом фильтруем
    connect(ui_->leFilter, &QLineEdit::textChanged, [this](const QString& expr) {
        QRegExp regExp(expr, Qt::CaseInsensitive, QRegExp::FixedString);
        nameFilter_->setFilterRegExp(regExp);
    });

    tree_ = ui_->twMain;
    tree_->setModel(nameFilter_.get());
    tree_->setItemDelegateForColumn(FileSystemModel::Column::NAME, new IniLetterDelegate(FileSystemModel::Roles::isDirRole, settings, tree_));
    tree_->header()->setSectionResizeMode(FileSystemModel::Column::NAME, QHeaderView::ResizeMode::Stretch);
    tree_->installEventFilter(this);

    QWidget::setTabOrder(tree_, ui_->leFilter);
    QWidget::setTabOrder(ui_->leFilter, tree_);
}

void FileSystemPresenter::deleteSelectedFiles() const
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

    for (const auto& indexProxy : indexesToDelete) {
        auto index = nameFilter_->mapToSource(indexProxy);
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
