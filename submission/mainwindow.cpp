#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cmb_controller = ui->cmb_controller;
    tb_extra = ui->tb_extra;

    connect(ui->btn_zero, &QPushButton::clicked, this, [this](){
        onDigitClicked(0);
    });

    connect(ui->btn_one, &QPushButton::clicked, this, [this](){
        onDigitClicked(1);
    });
    connect(ui->btn_two, &QPushButton::clicked, this, [this](){
        onDigitClicked(2);
    });

    connect(ui->btn_three, &QPushButton::clicked, this, [this]() {
        onDigitClicked(3);
    });
    connect(ui->btn_four, &QPushButton::clicked, this, [this]() {
        onDigitClicked(4);
    });
    connect(ui->btn_five, &QPushButton::clicked, this, [this]() {
        onDigitClicked(5);
    });
    connect(ui->btn_six, &QPushButton::clicked, this, [this]() {
        onDigitClicked(6);
    });
    connect(ui->btn_seven, &QPushButton::clicked, this, [this]() {
        onDigitClicked(7);
    });
    connect(ui->btn_eight, &QPushButton::clicked, this, [this]() {
        onDigitClicked(8);
    });
    connect(ui->btn_nine, &QPushButton::clicked, this, [this]() {
        onDigitClicked(9);
    });
    connect(ui->btn_plus, &QPushButton::clicked, this, [this]() {
        onOperationClicked(Operation::ADDITION);
    });

    connect(ui->btn_minus, &QPushButton::clicked, this, [this]() {
        onOperationClicked(Operation::SUBTRACTION);
    });
    connect(ui->btn_multiply, &QPushButton::clicked, this, [this]() {
        onOperationClicked(Operation::MULTIPLICATION);
    });
    connect(ui->btn_divide, &QPushButton::clicked, this, [this]() {
        onOperationClicked(Operation::DIVISION);
    });
    connect(ui->btn_pow, &QPushButton::clicked, this, [this]() {
        onOperationClicked(Operation::POWER);
    });
    
    connect(ui->btn_equals, &QPushButton::clicked, this, &MainWindow::onEqualsClicked);
    connect(ui->btn_clear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->btn_clear_last_number, &QPushButton::clicked, this, &MainWindow::onClearLastNumberClicked);
    connect(ui->btn_plus_minus, &QPushButton::clicked, this, &MainWindow::onPlusMinusClicked);
    connect(ui->btn_mStore, &QPushButton::clicked, this, &MainWindow::onMemoryStoreClicked);
    connect(ui->btn_mRecall, &QPushButton::clicked, this, &MainWindow::onMemoryRecallClicked);
    connect(ui->btn_mClear, &QPushButton::clicked, this, &MainWindow::onMemoryClearClicked);
    connect(ui->tb_extra, &QPushButton::clicked, this, &MainWindow::onPointClicked);
    connect(ui->cmb_controller, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onControllerTypeChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDigitClicked(int digit) {
    if(digitCallback) {
        digitCallback(digit);
    }
}

void MainWindow::onPointClicked() {
    if(controlCallback) {
        controlCallback(ControlKey::EXTRA_KEY);
    }
}

void MainWindow::onOperationClicked(Operation op) {
    if(operationCallback) {
        operationCallback(op);
    }
}

void MainWindow::onEqualsClicked() {
    if(controlCallback) {
        controlCallback(ControlKey::EQUALS);
    }
}

void MainWindow::onClearClicked() {
    if(controlCallback) {
        controlCallback(ControlKey::CLEAR);
    }

}

void MainWindow::onClearLastNumberClicked() {
    if(controlCallback) {
        controlCallback(ControlKey::BACKSPACE);
    }
}

void MainWindow::onPlusMinusClicked() {
    if(controlCallback) {
        controlCallback(ControlKey::PLUS_MINUS);
    }

}

void MainWindow::onMemoryStoreClicked() {
    if(controlCallback) {
        controlCallback(ControlKey::MEM_SAVE);
    }

}
void MainWindow::onMemoryRecallClicked() {
    if(controlCallback) {
        controlCallback(ControlKey::MEM_LOAD);
    }

}

void MainWindow::onMemoryClearClicked() {
    if(controlCallback) {
        controlCallback(ControlKey::MEM_CLEAR);
    }

}

void MainWindow::onControllerTypeChanged(int index) {
    if(controllerCallback) {
        controllerCallback(static_cast<ControllerType>(index));
    }

}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key.has_value()) {
        tb_extra->setText(QString::fromStdString(key.value()));
        tb_extra->show();
    } else {
        tb_extra->hide();
    }
}

void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb) {
    digitCallback = cb;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb) {
    operationCallback = cb;

}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb) {
    controlCallback = cb;
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb) {
    controllerCallback = cb;
}
