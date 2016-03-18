#ifndef FIELD_H
#define FIELD_H

#include <QPushButton>

class QField
{
public:
    QField(QWidget *parrent);
    QWidget *getField() {return field;};
private:
    QWidget *field;
};

#endif // FIELD_H
