#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Codon.h"
#include "Amino.h"
#include "HashMap.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void textChanged();

private:
    void updateList();
    HashMap<Codon, Amino> map;
    Ui::MainWindow *ui;
    QVector<int> index = QVector<int>();
};
#endif // MAINWINDOW_H
