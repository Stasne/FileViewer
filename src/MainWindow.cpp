#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "FileSystemModel.h"
#include "FileSystemPresenter.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    auto fileModel = QSharedPointer<FileSystemModel>::create();
    filePresenter_.reset(new FileSystemPresenter(fileModel, ui_));
}

MainWindow::~MainWindow()
{
}
