#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Amino.h"

#include <QFileDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_3, &QPushButton::clicked, this, [this](){
        QString fname = QFileDialog::getSaveFileName(nullptr, "filename", ".", "Text files (*.txt)" );
        if (fname.isEmpty()) {
            return;
        }
        map.saveToFile(fname.toUtf8().begin());
    });

    connect(ui->pushButton_4, &QPushButton::clicked, this, [this](){
        QString fname = QFileDialog::getOpenFileName(nullptr, "filename", ".", "Text files (*.txt)" );
        if (fname.isEmpty()) {
            return;
        }
        map.clear();
        map.loadFromFile(fname.toUtf8().begin());
        updateList();

    });

    connect(ui->pushButton_5, &QPushButton::clicked, this, [this](){
        map.clear();
        updateList();
    });

    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged()));

   connect(ui->pushButton_2, &QPushButton::clicked, this, [this](){
       if (map.contains(ui->lineEdit->text().toUtf8().constData())) {
        map.remove(ui->lineEdit->text().toUtf8().constData());
        updateList();
       }
           });

    connect(ui->pushButton, &QRadioButton::clicked, this, [this](){
        std::string k = ui->lineEdit->text().toUtf8().constData();
        std::string v = ui->lineEdit_2->text().toUtf8().constData();

        map.put(k,v);
        updateList();

   });

}

void MainWindow::updateList() {
    ui->listWidget->clear();
    for (auto &a : map.keys()) {
        ui->listWidget->addItem(QString::fromStdString(a.toString() + " : " + map[a].toString()));
    }
}

void MainWindow::textChanged()
{
    ui->pushButton->setEnabled(!ui->lineEdit->text().isEmpty());
    ui->pushButton_2->setEnabled(!ui->lineEdit->text().isEmpty());
}


MainWindow::~MainWindow()
{
    delete ui;
}

