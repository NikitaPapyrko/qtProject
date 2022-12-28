#ifndef GROUP_H
#define GROUP_H

#include <QDialog>

namespace Ui {
class Group;
}

class Group : public QDialog
{
    Q_OBJECT

public:
    explicit Group(QWidget *parent = nullptr);
    ~Group();

    QString getNameOfGroup();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Group *ui;

signals:
    void groupCreated();

};

#endif // GROUP_H
