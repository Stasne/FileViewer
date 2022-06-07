#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "FileSystemModel.h"
#include "FileSystemPresenter.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto model = QSharedPointer<FileSystemModel>(new FileSystemModel());
    presenter_.reset(new FileSystemPresenter(model, ui->twMain));
}

MainWindow::~MainWindow()
{
    delete ui;
}
