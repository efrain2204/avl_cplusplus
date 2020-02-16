#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include"avl.h"
#include<QPixmap>
#include<QGraphicsScene>

namespace Ui {
class principal;
}

class principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit principal(QWidget *parent = 0);
    ~principal();

private slots:
    void on_btn_add_clicked();

    void on_btn_add_2_clicked();

    void on_btn_delete_clicked();

private:
    Ui::principal *ui;
    AVLtree<int> tree;
    QGraphicsScene *scene =  new QGraphicsScene;
};

#endif // PRINCIPAL_H
