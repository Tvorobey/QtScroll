#include "MainWindow.h"
#include "QListView"
#include "QStringListModel"
#include "QPushButton"

#include "QDebug"
#include "QVBoxLayout"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QPushButton(this));

//    QListView* view = new QListView(this);
//    QStringListModel* model = new QStringListModel(this);
//    QStringList list;
//    list << "a" << "b" << "c";
//    model->setStringList(list);

//    view->setModel(model);

//    view->setFixedWidth(300);
//    view->setFixedHeight(400);

//    view->show();
}

MainWindow::~MainWindow()
{
}

