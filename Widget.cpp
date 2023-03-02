#include "Widget.h"
#include "ScrollUtils.h"
#include "DataParser.h"

#include "QVBoxLayout"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    initView();

    toogle = new QCheckBox(this);
    connect(toogle, &QCheckBox::stateChanged, this, &Widget::toogleStateChanged);

    label = new QLabel("Modify scroll event", this);

    QHBoxLayout* toogleLayout = new QHBoxLayout;
    toogleLayout->addStretch();
    toogleLayout->addWidget(toogle);
    toogleLayout->addWidget(label);
    toogleLayout->addStretch();

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(toogleLayout);
    layout->addWidget(view);
}

void Widget::initView()
{
    view = new QListView(this);
    view->verticalScrollBar()->setObjectName("Vertical bar");
    view->setSpacing(5);
    view->setFixedHeight(500);
    model = new QStringListModel(this);
    model->setStringList(Utils::Parser::parse());
//    fillModel();
    view->setModel(model);
}

void Widget::fillModel()
{
    QStringList list;
    list << "a" << "b" << "c" << "d" << "e" << "f" << "g" << "h" << "i" << "j" << "k";
    model->setStringList(list);
}

void Widget::toogleStateChanged(int state)
{
    view->verticalScrollBar()->setProperty(Utils::Scroll::wheelEventModificationProperty.data(), state == 0 ? false : true);
}
