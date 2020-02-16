#include "principal.h"
#include "ui_principal.h"


principal::principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::principal)
{
    ui->setupUi(this);

}

principal::~principal()
{
    delete ui;
}

void principal::on_btn_add_clicked()
{
    if(ui->txt_add->text()!=""){
        scene->clear();
        tree.insert(this->ui->txt_add->text().toInt());
        tree.display();

        QPixmap pixmap("out.png");
        scene->addPixmap(pixmap);
        ui->img_hd->setScene(scene);
        ui->img_hd->show();
    }
}

void principal::on_btn_add_2_clicked()
{
    scene->clear();
    for(int i= 1 ; i<50;i++){
        tree.insert(i);
    }
    tree.display();


    QPixmap pixmap("out.png");
    scene->addPixmap(pixmap);
    ui->img_hd->setScene(scene);
    ui->img_hd->show();
}

void principal::on_btn_delete_clicked()
{
    if(ui->txt_delete->text()!=""){
        scene->clear();
        tree.deletedato(this->ui->txt_delete->text().toInt());
        tree.display();

        QPixmap pixmap("out.png");
        scene->addPixmap(pixmap);
        ui->img_hd->setScene(scene);
        ui->img_hd->show();
    }
}
