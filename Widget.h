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
    void scrollModifyToogleStateChanged(int _state);
    void onScrollBarValueChanged(int);
    void onIsGameModeToogleStateChanged(int _state);
    void onResetBtnClicked();
    void onWheelTimerTimeout();

private:
    QListView* view_;
    QStringListModel* model_;
    QCheckBox* scrollModifyToogle_;
    QCheckBox* isGameMode_;
    QPushButton* resetBtn_;
    QLabel* label_;
    QTimer* wheelTimer_;
    QDialog* dialog_;
    bool firstWheel_;
};
