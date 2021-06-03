#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tablemodel.h"

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
     void set_row (Packet p);
     void change_row (Packet p);

private slots:
    void on_button_from_file_clicked();

    void on_button_in_file_clicked();

    void on_button_delete_clicked();

    void on_button_add_clicked();

    void on_button_show_clicked();

    void on_button_edit_clicked();

private:
    Ui::MainWindow *ui;
    TableModel *MyModel;
};
#endif // MAINWINDOW_H
