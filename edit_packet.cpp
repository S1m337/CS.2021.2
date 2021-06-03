#include "edit_packet.h"
#include "ui_edit_packet.h"

Edit_Packet::Edit_Packet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_Packet)
{
    ui->setupUi(this);
    Packet p_ = Packet();

}

Edit_Packet::~Edit_Packet()
{
    delete ui;
}

void Edit_Packet::set_p(Packet p){
    p_ = p;
    ui->line_name->setText(p_.name() );
    ui->line_den->setText(QString::number(p_.density()) );
    ui->line_depth->setText(QString::number(p_.depth()) );
    ui->line_proj->setText(p_.projectile());
    if (p_.res()) ui->check_yes->setChecked(true);
}

Packet Edit_Packet::send(){
    return p_;
}

void Edit_Packet::on_push_add_clicked()
{
    p_.set_name( ui->line_name->text() );
    p_.set_density( ui->line_den->text().toInt() );
    p_.set_depth( ui->line_depth->text().toInt() );
    p_.set_projectile( ui->line_proj->text() );
    if (ui->check_yes->isChecked()) p_.set_res(true);
    else p_.set_res(false);
    emit p_changed(p_);
}
