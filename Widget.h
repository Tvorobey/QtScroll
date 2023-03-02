#pragma once

#include <QtWidgets>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);

signals:

private:
    void initView();
    void fillModel();

private Q_SLOTS:
    void toogleStateChanged(int state);

private:
    QToolButton* nextBtn;
    QToolButton* prevBtn;
    QListView* view;
    QStringListModel* model;
    QCheckBox* toogle;
    QLabel* label;
};

