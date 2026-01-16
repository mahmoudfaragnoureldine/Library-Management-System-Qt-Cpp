#include "managelib.h"

ManageLib::ManageLib(QObject *parent)
    : QObject{parent}, qin(stdin), qout(stdout)
{}

void ManageLib::init()
{
    load();
}

void ManageLib::run()
{
    qDebug() << "________________ Welcome _______________";
    while (!exitMainScreen) {
        qDebug() << "Pleases enter your username and password";
        qout << "USERNAME: ";
        qout.flush();
        QString username = qin.readLine();
        qout << "PASSWORD: ";
        qout.flush();
        QString password = qin.readLine();

        QJsonDocument jdoc;
        QFile users("../../../database/users.json");
        if(users.open(QIODevice::ReadOnly))
        {
            jdoc = QJsonDocument::fromJson(users.readAll());
            users.close();
        } else {
            qInfo() << users.errorString();
        }

        QJsonObject rootObj = jdoc.object();
        QJsonArray usersArray = rootObj["users"].toArray();

        bool flag = false;
        qint32 role = 0;    // 1: admin , 2: user
        for (qint32 i = 0; i < usersArray.size(); i++) {
            QJsonObject user = usersArray[i].toObject();
            if(user["username"].toString() == username && user["password"].toString() == password)
            {
                if(user["role"].toString() == "admin")
                {
                    flag = true;
                    openAdminPannel();
                }
                else if(user["role"].toString() == "user")
                {
                    flag = true;
                    openUserPannel();
                }
            }
        }

        if(!flag)
        {
            qDebug() << "Invalid username or password";
            qDebug() << "________________________________________";
        }
    }
}

void ManageLib::load()
{
    QJsonDocument jdoc;
    QFile books("../../../database/books.json");
    if(books.open(QIODevice::ReadOnly))
    {
        jdoc = QJsonDocument::fromJson(books.readAll());
        books.close();
    } else {
        qInfo() << books.errorString();
    }

    QJsonObject rootObj = jdoc.object();
    QJsonArray booksArray = rootObj["books"].toArray();

    for (int var = 0; var < booksArray.size(); ++var) {
        QJsonObject obj = booksArray[var].toObject();

        Book bk;
        bk._title = obj["title"].toString();
        bk._auther = obj["auther"].toString();
        bk._category = obj["category"].toString();
        bk._barcode = obj["barcode"].toString();
        booksDB.push_back(bk);
    }
}

void ManageLib::save()
{
    QJsonArray booksArray;

    for (const Book &book : booksDB) {
        QJsonObject obj;
        obj["title"] = book._title;
        obj["auther"] = book._auther;
        obj["category"] = book._category;
        obj["barcode"] = book._barcode;

        booksArray.append(obj);
    }

    QJsonObject rootObj;
    rootObj["books"] = booksArray;

    QJsonDocument jdoc(rootObj);

    QFile file("../../../database/books.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qInfo() << file.errorString();
        return;
    }

    file.write(jdoc.toJson(QJsonDocument::Indented));
    file.close();
}

void ManageLib::openAdminPannel()
{
    qint32 choice;
    while (!exitPannelScreem) {
        mainScren();
        qout << "Enter your choice: ";
        qout.flush();
        choice = qin.readLine().toInt();

        if(choice == 1)
            addBook();
        else if(choice == 2)
            searchBkDB();
        else if(choice == 3)
            removeBK();
        else if(choice == 4)
            exitApp();
        else
            qDebug() << "Invalid choice, try again.." << Qt::endl;
    }
}

void ManageLib::openUserPannel()
{
    qint32 choice;
    while (!exitPannelScreem) {
        mainScren();
        qout << "Enter your choice: ";
        qout.flush();
        choice = qin.readLine().toInt();

        if(choice == 1)
            qDebug() << "   ---Pernission Denied---" << Qt::endl;
        else if(choice == 2)
            searchBkDB();
        else if(choice == 3)
            qDebug() << "   ---Pernission Denied---" << Qt::endl;
        else if(choice == 4)
            exitApp();
        else
            qDebug() << "Invalid choice, try again.." << Qt::endl;
    }
}

void ManageLib::mainScren()
{
    qDebug() << "==============================";
    qDebug() << "       Library System         ";
    qDebug() << "==============================";
    qDebug() << "1. Add a New Book";
    qDebug() << "2. Search Books Database";
    qDebug() << "3. Remove a Book";
    qDebug() << "4. Exit";
    qDebug() << "------------------------------";
}

void ManageLib::addBook()
{
    Book bk;
    qDebug() << "Book information";
    qout << "title: ";
    qout.flush();
    bk._title = qin.readLine();
    qout << "auther: ";
    qout.flush();
    bk._auther = qin.readLine();
    qout << "category: ";
    qout.flush();
    bk._category = qin.readLine();
    qout << "barcode: ";
    qout.flush();
    bk._barcode = qin.readLine();

    booksDB.push_back(bk);

    save();
    qDebug() << "--Book added succesfully--" << Qt::endl;
}

void ManageLib::searchBkDB()
{
    while (!exitSearchScreen) {
        qDebug() << "Enter book information (Use N/A if unknown)";
        qout << "title: ";
        qout.flush();
        QString title = qin.readLine();
        qout << "auther: ";
        qout.flush();
        QString auther = qin.readLine();
        qout << "category: ";
        qout.flush();
        QString category = qin.readLine();
        qout << "barcode: ";
        qout.flush();
        QString barcode = qin.readLine();

        bool found = false;

        for(const Book& bk : booksDB)
        {
            if(bk._title == title || bk._auther == auther || bk._category == category || bk._barcode == barcode)
            {
                qDebug() << Qt::endl << "---- Book Info ----";
                qDebug() << "title: " << bk._title;
                qDebug() << "auther: " << bk._auther;
                qDebug() << "category: " << bk._category;
                qDebug() << "barcode: " << bk._barcode;
                found = true;
                exitSearchScreen = true;
                break;
            }
        }

        if(!found)
        {
            qDebug() << "--- Book dose't exist ---";
        }
    }
}

void ManageLib::removeBK()
{
    while (true) {
        qout << "Enter the book title: ";
        qout.flush();
        QString name = qin.readLine();

        bool found = false;

        for (qint32 i = 0; i < booksDB.size(); i++) {
            if(booksDB[i]._title == name)
            {
                booksDB.removeAt(i);
                found = true;
            }
        }

        if(found)
        {
            save();
            qDebug() << "--Book removesd succesfully--" << Qt::endl;
            break;
        } else {
            qDebug() << "Invalid title, please try again.." << Qt::endl;
        }
    }
}

void ManageLib::exitApp()
{
    qInfo() << Qt::endl << "Exiting application...";
    exitPannelScreem = true;
    exitMainScreen = true;
}
