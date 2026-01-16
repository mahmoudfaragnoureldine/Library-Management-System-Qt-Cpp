#ifndef MANAGELIB_H
#define MANAGELIB_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QTextStream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QCoreApplication>


#include "book.h"

class ManageLib : public QObject
{
    Q_OBJECT
public:
    explicit ManageLib(QObject *parent = nullptr);

    void init();
    void run();
    void load();
    void save();
    void openAdminPannel();
    void openUserPannel();
    void mainScren();
    void addBook();
    void searchBkDB();
    void removeBK();
    void exitApp();

    bool exitMainScreen = false;
    bool exitPannelScreem = false;
    bool exitSearchScreen = false;

private:
    QVector<Book> booksDB;
    QTextStream qin;
    QTextStream qout;

signals:
    void exitRequested();
};

#endif // MANAGELIB_H
