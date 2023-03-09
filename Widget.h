#pragma once

#include <QtWidgets>

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget* _parent = nullptr);

private:
    void initView();

private Q_SLOTS:
    void toogleStateChanged(int _state);

private:
    QListView* view_;
    QStringListModel* model_;
    QCheckBox* toogle_;
    QLabel* label_;
};
