#ifndef BOOK_H
#define BOOK_H

#include <QObject>

class Book : public QObject
{
    Q_OBJECT
public:
    explicit Book(QObject *parent = nullptr);

    QString _title;
    QString _auther;
    QString _category;
    QString _barcode;

    // Move constructor
    Book(Book&& other) noexcept
        : QObject(other.parent())
    {
        _title    = std::move(other._title);
        _auther   = std::move(other._auther);
        _category = std::move(other._category);
        _barcode  = std::move(other._barcode);
    }

    // Move assignment operator
    Book& operator=(Book&& other) noexcept {
        if (this != &other) {
            _title    = std::move(other._title);
            _auther   = std::move(other._auther);
            _category = std::move(other._category);
            _barcode  = std::move(other._barcode);
        }
        return *this;
    }

    // Copy constructor
    Book(const Book& other)
        : QObject(other.parent())
    {
        _title    = other._title;
        _auther   = other._auther;
        _category = other._category;
        _barcode  = other._barcode;
    }

    // Copy assignment operator
    Book& operator=(const Book& other) {
        if (this != &other) {
            _title    = other._title;
            _auther   = other._auther;
            _category = other._category;
            _barcode  = other._barcode;
        }
        return *this;
    }

private:

};

#endif // BOOK_H
