#ifndef CHOOSEUSERS_H
#define CHOOSEUSERS_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class ChooseUsers;
}

class ChooseUsers : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseUsers(QWidget *parent = nullptr);
    ~ChooseUsers();

    int getCount();
    QString getMembers();

    void setNicknames(QVector <QString> nicknames);

private slots:
    void on_listWidget_itemDoubleClicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ChooseUsers *ui;

    int count = 0;

    QVector <QString> nicknames;

signals:
    void rejected();
    void accepted();
};

#endif // CHOOSEUSERS_H
