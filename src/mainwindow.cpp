#include "MainWindow.h"
#include "IDisplaySettings.h"
#include <QPainter>
#include <QStaticText>
#include <QStyledItemDelegate>

#include "./ui_MainWindow.h"
#include "FileSystemModel.h"
#include "IniLetterDelegate.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString rootPath = "";
    auto dirModel = new FileSystemModel(this);

    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::AllEntries);

    dirModel->setRootPath(rootPath);

    ui->twMain->setModel(dirModel);
    ui->twMain->header()->setSectionResizeMode(FileSystemModel::Column::NAME, QHeaderView::ResizeMode::Stretch);

    auto settings = QSharedPointer<IDisplaySettings>::create();
    auto initiaLetterDelegate = new IniLetterDelegate(settings);
    ui->twMain->setItemDelegateForColumn(0, initiaLetterDelegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}
