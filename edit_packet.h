#ifndef EDIT_PACKET_H
#define EDIT_PACKET_H

#include <QWidget>
#include "packet.h"

namespace Ui {
class Edit_Packet;
}

class Edit_Packet : public QWidget
{
    Q_OBJECT

public:
    explicit Edit_Packet(QWidget *parent = nullptr);
    ~Edit_Packet();
    void set_p(Packet p);
    Packet send();

private slots:
    void on_push_add_clicked();
signals:
    void p_changed(Packet p);

private:
    Ui::Edit_Packet *ui;
    Packet p_;
};

#endif // EDIT_PACKET_H
