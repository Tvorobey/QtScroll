#include "Widget.h"
#include "ScrollUtils.h"
#include "DataParser.h"
#include "MyApp.h"

#include "QVBoxLayout"

namespace
{
    constexpr int viewHeight = 500;
    constexpr int viewSpacing = 5;
} // namespace

Widget::Widget(QWidget* _parent)
    : QWidget(_parent)
{
    initView();

    toogle_ = new QCheckBox(this);
    connect(toogle_, &QCheckBox::stateChanged, this, &Widget::toogleStateChanged);

    label_ = new QLabel("Modify scroll event", this);

    QHBoxLayout* toogleLayout = new QHBoxLayout;
    toogleLayout->addStretch();
    toogleLayout->addWidget(toogle_);
    toogleLayout->addWidget(label_);
    toogleLayout->addStretch();

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(toogleLayout);
    layout->addWidget(view_);
}

void Widget::initView()
{
    view_ = new QListView(this);
    view_->verticalScrollBar()->setObjectName("Vertical bar");
    view_->setSpacing(viewSpacing);
    view_->setFixedHeight(viewHeight);
    model_ = new QStringListModel(this);
    model_->setStringList(Utils::Parser::parse());
    view_->setModel(model_);
}

void Widget::toogleStateChanged(int _state)
{
    MyApp::setRequireCustomWheelEvent(view_->verticalScrollBar(), _state == 0 ? false : true);
}
