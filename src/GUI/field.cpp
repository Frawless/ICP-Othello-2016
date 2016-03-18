#include "field.h"

#include <QWidget>
#include <QPixmap>
#include <QPainter>


QField::QField(QWidget *parrent)
{  

    field = new QWidget(parrent);
    /*QPixmap pm = QPixmap(field->size());
    QPainter p(&pm);
    p.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::blue, 2);
    p.setPen(pen);
    QBrush brush(Qt::green);
    p.setBrush(brush);
    p.drawEllipse(10, 10, 80, 80);

    field->render(&pm);*/



    field->setGeometry(0,0,50,50);
    field->setStyleSheet("background-color:red;");
    field->show();
}
