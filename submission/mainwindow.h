#pragma once

#include "enums.h"
#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <functional>
#include <string>
#include <optional>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void SetInputText(const std::string& text);
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);
    void SetDigitKeyCallback(std::function<void(int key)> cb);
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);
    void SetControllerCallback(std::function<void(ControllerType controller)> cb);

private slots:

    void onDigitClicked(int digit);
    void onPointClicked();
    void onOperationClicked(Operation op);
    void onEqualsClicked();
    void onClearClicked();
    void onClearLastNumberClicked();
    void onPlusMinusClicked();
    void onMemoryStoreClicked();
    void onMemoryRecallClicked();
    void onMemoryClearClicked();
    void onControllerTypeChanged(int index);

private:
    Ui::MainWindow *ui;

    QComboBox *cmb_controller;
    QPushButton *tb_extra;

    std::function<void(int key)> digitCallback;
    std::function<void(Operation key)> operationCallback;
    std::function<void(ControlKey key)> controlCallback;
    std::function<void(ControllerType type)> controllerCallback;

};
