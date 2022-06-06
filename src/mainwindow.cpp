#include "mainwindow.h"

#include <QPainter>
#include <QStaticText>
#include <QStyledItemDelegate>

#include "filesystemmodel.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString mPath = "";
    auto dirModel = new FileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::AllEntries);
    dirModel->setRootPath(mPath);
    ui->twMain->setModel(dirModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
