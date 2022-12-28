#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Foxhole");

    this->setFixedSize(390, 380);

    //network
    socket = new QTcpSocket(this);

    socket->connectToHost("127.0.0.1", 2323);

    nextBlockSize = 0;

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    //connect(this, &QTcpSocket::aboutToClose, this, &MainWindow::exitUser);

    //windows
    ent = new EnterWindow(socket);
    connect(ent, &EnterWindow::Main_win, this, &MainWindow::show);
    connect(ent, &EnterWindow::setNick, this, &MainWindow::getNick);

    reg = new Registration(socket);
    connect(reg, &Registration::Enter_win, ent, &EnterWindow::show);
    connect(reg, &Registration::Main_win, this, &MainWindow::show);
    connect(reg, &Registration::setNick, this, &MainWindow::getNick);

    connect(this, &MainWindow::Enter_win, ent, &EnterWindow::show);
    connect(ent, &EnterWindow::Reg_win, reg, &Registration::show);

    chooseUser = new ChooseUsers;
    newGroup = new Group;

    connect(chooseUser, &ChooseUsers::rejected, newGroup, &Group::show);
    connect(chooseUser, &ChooseUsers::accepted, this, &MainWindow::createGroup);

    connect(newGroup, &Group::accepted, chooseUser, &ChooseUsers::show);
}

MainWindow::~MainWindow()
{
    exitUser();

    QMap <QString, QVector <QString>*>::Iterator iter;

    for (iter = chats.begin(); iter != chats.end(); iter++) {
        delete iter.value();
    }

    for (iter = chatGroups.begin(); iter != chatGroups.end(); iter++) {
        delete iter.value();
    }

    delete ui;

    delete ent;
    delete reg;
    delete chooseUser;
    delete newGroup;

    delete socket;
}

void MainWindow::SendToServer(QString str, int command)
{
    Data.clear();

    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << command << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));

    socket->write(Data);

    ui->lineEdit->clear();
}

void MainWindow::SendToServerCommand(int command)
{
    Data.clear();

    QDataStream usersInfo(&Data, QIODevice::WriteOnly);
    usersInfo.setVersion(QDataStream::Qt_6_4);

    usersInfo << quint16(0) << command;
    usersInfo.device()->seek(0);
    usersInfo <<quint16(Data.size() - sizeof(quint16));

    socket->write(Data);

}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_4);

    int command = 0;

    QString text;

    if(in.status() == QDataStream::Ok)
    {
        while(true)
        {
            if(nextBlockSize == 0)
            {
                if(socket->bytesAvailable() < 2)
                {
                    break;
                }

                in >> nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)
            {
                break;
            }

            in >> command >> text;

            nextBlockSize = 0;

            break;
        }

        if(command >= 1 && command <= 3)
        {
            reg->commandFromServer(command);
        }
        else if(command >= 4 && command <= 6)
        {
            ent->commandFromServer(command);
        }
        else
        {
            switch (command)
            {
                case userExist:
                {
                    QList <QListWidgetItem*> l = ui->listWidget->findItems(ui->lineEdit_2->text(), Qt::MatchFlags(8));

                    if(l.size() == 0)
                    {
                        ui->listWidget->addItem(ui->lineEdit_2->text());

                        QVector <QString> *newVec = new QVector <QString>;

                        chats.insert(ui->lineEdit_2->text(), newVec);
                    }

                    break;
                }

                case getMessage:
                {
                    QString message = QTime::currentTime().toString() + " " + text;

                    QString sender = text.section(':', 0 , 0);

                    QMap <QString, QVector <QString>*>::Iterator it = chats.begin();

                    it = chats.find(sender);

                    if(it != chats.end())
                    {
                        it.value()->push_back(message);
                    }
                    else
                    {
                        ui->listWidget->addItem(sender);

                        QVector <QString> *newVec = new QVector <QString>;

                        chats.insert(sender, newVec);

                        newVec->push_back(message);
                    }

                    if(ui->listWidget->count() != 0 && ui->listWidget->currentItem() != nullptr)
                    {
                        if(ui->listWidget->currentItem()->text() == sender)
                        {
                            ui->textBrowser->append(message);
                        }
                    }

                    break;
                }

                case groupCreated:
                {
                    ui->listWidget->addItem(nameOfGroup);

                    QVector <QString> *newVec = new QVector <QString>;

                    chatGroups.insert(nameOfGroup, newVec);

                    break;
                }

                case getMessageToGroup:
                {
                    QString message = QTime::currentTime().toString() + " " + text.section(':', 1, 2);

                    QString groupName = text.section(':', 0 , 0);

                    if(!chatGroups.isEmpty())
                    {
                        QMap <QString, QVector <QString>*>::Iterator it1 = chatGroups.begin();

                        it1 = chatGroups.find(groupName);

                        if(it1.key() == groupName)
                            it1.value()->push_back(message);
                        else
                        {
                            ui->listWidget->addItem(groupName);

                            QVector <QString> *newVec = new QVector <QString>;

                            chatGroups.insert(groupName, newVec);

                            newVec->push_back(message);
                        }
                    }
                    else
                    {
                        ui->listWidget->addItem(groupName);

                        QVector <QString> *newVec = new QVector <QString>;

                        chatGroups.insert(groupName, newVec);

                        newVec->push_back(message);
                    }

                    if(ui->listWidget->count() != 0 && ui->listWidget->currentItem() != nullptr)
                    {
                        if(ui->listWidget->currentItem()->text() == groupName)
                        {
                            ui->textBrowser->append(message);
                        }
                    }

                    break;
                }
            }
        }
    }
    else
    {
        ui->textBrowser->append("read error...");
    }
}

void MainWindow::createGroup()
{
    nameOfGroup = newGroup->getNameOfGroup();
    countOfMemberGroup = chooseUser->getCount() + 1;
    members = chooseUser->getMembers() + ',' + ui->label->text();

    QList <QListWidgetItem*> l = ui->listWidget->findItems(nameOfGroup, Qt::MatchFlags(8));

    if(l.size() == 0)
    {
        QString cnt = QString::number(countOfMemberGroup);
        QString str = cnt + '%' + nameOfGroup + '%' + members;

        SendToServer(str, buildGroup);
    }
    else
    {
        return;
    }


}

void MainWindow::exitUser()
{
    SendToServerCommand(exit);
}

void MainWindow::on_pushButton_clicked()
{
    QString nickname = ui->listWidget->currentItem()->text();
    QString text = ui->lineEdit->text();

    QString str = nickname + '%' + text;

    QString messageToClient = QTime::currentTime().toString() + " Me: " + text;

    ui->textBrowser->append(messageToClient);

    QMap <QString, QVector <QString>*>::Iterator it = chats.begin();

    it = chats.find(nickname);

    if(it != chats.end())
    {
        it.value()->push_back(messageToClient);

        SendToServer(str, message);
    }
    else
    {
        str = ui->label->text() + '%' + str;

        it = chatGroups.find(nickname);

        it.value()->push_back(messageToClient);

        SendToServer(str, messageToGroup);
    }
}


void MainWindow::on_lineEdit_returnPressed()
{
    QString nickname = ui->listWidget->currentItem()->text();
    QString text = ui->lineEdit->text();

    QString str = nickname + '%' + text;

    QString messageToClient = QTime::currentTime().toString() + " Me: " + text;

    ui->textBrowser->append(messageToClient);

    QMap <QString, QVector <QString>*>::Iterator it = chats.begin();

    it = chats.find(nickname);

    if(it.key() == nickname)
    {
        it.value()->push_back(messageToClient);

        SendToServer(str, message);
    }
    else
    {
        str = ui->label->text() + '%' + str;

        it = chatGroups.find(nickname);

        it.value()->push_back(messageToClient);

        SendToServer(str, messageToGroup);
    }
}


void MainWindow::on_lineEdit_2_returnPressed()
{
    QString nickname = ui->lineEdit_2->text();

    SendToServer(nickname, oneUser);
}


void MainWindow::on_listWidget_itemDoubleClicked()
{
    ui->textBrowser->clear();

    QMap <QString, QVector <QString>*>::Iterator it = chats.begin();

    it = chats.find(ui->listWidget->currentItem()->text());

    if(it != chats.end())
    {
        QVector <QString>::Iterator iter = it.value()->begin();

        while (iter != it.value()->end()) {
            ui->textBrowser->append(*iter);

            iter++;
        }
    }
    else
    {
        it = chatGroups.find(ui->listWidget->currentItem()->text());

        QVector <QString>::Iterator iter = it.value()->begin();

        while (iter != it.value()->end()) {
            ui->textBrowser->append(*iter);

            iter++;
        }
    }

}


void MainWindow::on_action_2_triggered()
{
    QVector <QString> nicknames;

    QMap <QString, QVector <QString>*>::Iterator it = chats.begin();

    for (; it != chats.end(); it++) {
        nicknames.push_back(it.key());
    }

    chooseUser->setNicknames(nicknames);

    newGroup->show();
}

void MainWindow::getNick(QString nick)
{
    ui->label->setText(nick);
}

