#include "Widget.h"
#include "ScrollUtils.h"
#include "MyApp.h"

#include <QVBoxLayout>
#include <QStringList>
#include <QScopedValueRollback>

namespace
{
    constexpr int viewHeight = 500;
    constexpr int viewSpacing = 5;
    constexpr int dataLenght = 1000;
    constexpr int wheelTime = 5000;

    QStringList generateModelData()
    {
        QStringList data;

        for (auto i = 0; i < dataLenght; ++i)
        {
            data << QString::number(i + 1);
        }

        return data;
    }

    QHBoxLayout* createToogleLayout(QCheckBox* _checkBox, const QString& _label)
    {
        QHBoxLayout* toogleLayout = new QHBoxLayout;
        toogleLayout->addStretch();
        toogleLayout->addWidget(_checkBox);
        toogleLayout->addWidget(new QLabel(_label, _checkBox));
        toogleLayout->addStretch();

        return toogleLayout;
    }
} // namespace

Widget::Widget(QWidget* _parent)
    : QWidget(_parent)
    , wheelTimer_ { new QTimer(this) }
    , firstWheel_ { true }
{
    wheelTimer_->setSingleShot(true);
    connect(wheelTimer_, &QTimer::timeout, this, &Widget::onWheelTimerTimeout);

    initView();

    scrollModifyToogle_ = new QCheckBox(this);
    connect(scrollModifyToogle_, &QCheckBox::stateChanged, this, &Widget::scrollModifyToogleStateChanged);

    isGameMode_ = new QCheckBox(this);
    isGameMode_->setChecked(true);
    connect(isGameMode_, &QCheckBox::stateChanged, this, &Widget::onIsGameModeToogleStateChanged);

    resetBtn_ = new QPushButton("Reset", this);
    connect(resetBtn_, &QPushButton::clicked, this, &Widget::onResetBtnClicked);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(createToogleLayout(scrollModifyToogle_, "Modify scroll event"));
    layout->addLayout(createToogleLayout(isGameMode_, "Game mode"));
    layout->addWidget(resetBtn_);
    layout->addWidget(view_);
}

void Widget::initView()
{
    view_ = new QListView(this);
    view_->verticalScrollBar()->setObjectName("Vertical bar");
    view_->setSpacing(viewSpacing);
    view_->setFixedHeight(viewHeight);
    model_ = new QStringListModel(this);
    model_->setStringList(generateModelData());
    view_->setModel(model_);

    connect(view_->verticalScrollBar(), &QScrollBar::valueChanged, this, &Widget::onScrollBarValueChanged);
}

void Widget::scrollModifyToogleStateChanged(int _state)
{
    MyApp::setRequireCustomWheelEvent(view_->verticalScrollBar(), _state == 0 ? false : true);
}

void Widget::onScrollBarValueChanged(int)
{
    if (!isGameMode_->isChecked())
        return;

    if (firstWheel_)
    {
        firstWheel_ = false;
        wheelTimer_->start(wheelTime);
    }
}

void Widget::onIsGameModeToogleStateChanged(int _state)
{
    if (_state == 0)
    {
        if (wheelTimer_->isActive())
        {
            wheelTimer_->stop();
            firstWheel_ = true;
        }

        view_->setEnabled(true);
        view_->scrollToTop();
        resetBtn_->setEnabled(false);
        return;
    }

    firstWheel_ = false;
    view_->scrollToTop();
    resetBtn_->setEnabled(true);
    firstWheel_ = true;
}

void Widget::onResetBtnClicked()
{
    firstWheel_ = false;
    view_->setEnabled(true);
    view_->scrollToTop();
    firstWheel_ = true;
}

void Widget::onWheelTimerTimeout()
{
    view_->setEnabled(false);
    firstWheel_ = true;
}
