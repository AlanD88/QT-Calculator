#include "mainwindow.h"
#include "ui_mainwindow.h"

double firstNum;
bool userIsTypingMore = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_zero, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_plusMinus, SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percent, SIGNAL(released()),this,SLOT(unary_operation_pressed()));

    connect(ui->pushButton_plus, SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_minus, SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_mult, SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_div, SIGNAL(released()),this,SLOT(binary_operation_pressed()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_mult->setCheckable(true);
    ui->pushButton_div->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton * button = (QPushButton*)sender();

    double labelNumber;
    QString newLabel;

    if((ui->pushButton_div->isChecked() || ui->pushButton_mult->isChecked() || ui->pushButton_plus->isChecked() || ui->pushButton_minus->isChecked()) && (!userIsTypingMore))
    {
        labelNumber = button->text().toDouble();
        userIsTypingMore = true;
        newLabel = QString::number(labelNumber, 'g', 15);
    }
    else
    {
        if(ui->label->text().contains('.') && button->text() == "0")
        {
            newLabel = ui->label->text() + button->text();
        }
        else
        {
             labelNumber = (ui->label->text() + button->text()).toDouble();
             newLabel = QString::number(labelNumber, 'g', 15);
        }

    }


    ui->label->setText(newLabel);
}

void MainWindow::on_pushButton_decimal_released()
{
        ui->label->setText(ui->label->text() + ".");

}

void MainWindow::unary_operation_pressed()
{
    double labelNumber;
    QString newLabel;

    QPushButton * button = (QPushButton*)sender();
    if(button->text() == "+/-")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber, 'g',15);
        ui->label->setText(newLabel);

    }
    else if(button->text() == "%")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number(labelNumber, 'g',15);
        ui->label->setText(newLabel);

    }
}

void MainWindow::on_PushButton_Clear_released()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_mult->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_div->setChecked(false);

    userIsTypingMore = false;

    ui->label->setText("0");
}

void MainWindow::on_pushButton_equal_released()
{
    double labelNumber, secondNum;
    QString newLabel;
    secondNum = ui->label->text().toDouble();

    if(ui->pushButton_div->isChecked())
    {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_div->setChecked(false);
    }
    else if(ui->pushButton_plus->isChecked())
    {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_plus->setChecked(false);
    }
    else if(ui->pushButton_mult->isChecked())
    {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_mult->setChecked(false);
    }
    else if(ui->pushButton_minus->isChecked())
    {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_minus->setChecked(false);
    }

    userIsTypingMore = false;
}

void MainWindow::binary_operation_pressed()
{
     QPushButton * button = (QPushButton*)sender();

     firstNum = ui->label->text().toDouble();

     button->setChecked(true);
}
