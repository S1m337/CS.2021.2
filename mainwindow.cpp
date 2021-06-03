#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "packet.h"
#include "tablemodel.h"
#include <QVector>
#include "animation.h"
#include "edit_packet.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyModel = new TableModel;
    ui->tableView->setModel(MyModel);
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->resizeColumnsToContents();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_from_file_clicked()
{
    Packet p;
    QVector<Packet> v;
    v = p.Read();
    for (int i=0; i<v.size(); i++){
         int kol = MyModel->rowCount();
         MyModel->insertRows(kol,1);
         QModelIndex in = MyModel->index(kol, 0);
         MyModel->set_all_data(in, v[i],0);
    }
}

void MainWindow::on_button_in_file_clicked()
{
    QModelIndex in = MyModel->index(0, 0);
    Packet p = MyModel->all_data(in, 0);
    p.Delete();
    int kol = MyModel->rowCount();
    for (int i=0; i<kol; i++){
         QModelIndex in = MyModel->index(i, 0);
         Packet p = MyModel->all_data(in, 0);
         p.Write(p);
    }
}

void MainWindow::on_button_delete_clicked()
{
    QModelIndex in  = ui->tableView->currentIndex();
    MyModel->removeRows(in.row(),1);
}

Edit_Packet *edit;

void MainWindow::on_button_add_clicked()
{
    Packet p;
    edit = new Edit_Packet();
    edit->set_p(p);

    QObject::connect(edit, SIGNAL(p_changed(Packet)),
                         this, SLOT(set_row(Packet)));

    edit->show();
}

void MainWindow::set_row ( Packet p){
    int kol = MyModel->rowCount();
    MyModel->insertRows(kol,1);
    QModelIndex in2 = MyModel->index(kol, 0);
    Packet p2 = edit->send();
    MyModel->set_all_data(in2, p2, 0);
}

void MainWindow::on_button_show_clicked()
{
    QModelIndex in  = ui->tableView->currentIndex();
    Packet p = MyModel->all_data(in, 0);
    Animation *animation = new Animation(0);
    animation->set_res(p.res());
    animation->show();
}

void MainWindow::on_button_edit_clicked()
{

    QModelIndex in  = ui->tableView->currentIndex();
    Packet p = MyModel->all_data(in, 0);
    edit = new Edit_Packet();
    edit->set_p(p);

    QObject::connect(edit, SIGNAL(p_changed(Packet)),
                         this, SLOT(change_row(Packet)));

    edit->show();
}

void MainWindow::change_row ( Packet p){
    int kol = MyModel->rowCount();
    QModelIndex in  = ui->tableView->currentIndex();
    Packet p2 = edit->send();
    MyModel->set_all_data(in, p2, 0);
}
