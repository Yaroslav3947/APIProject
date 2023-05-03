#pragma once

#include <QString>
#include <QJsonObject>


class User {
public:
    User(int id,
         const QString &name,
         const QString &email,
         QString &position,
         const QString &photoUrl);

    int getId() const;
    QString getName() const;
    QString getEmail() const;
    QString getPosition() const;
    QString getPhotoUrl() const;

    static User fromJson(const QJsonObject &json);
    QJsonObject toJson() const;

private:
    int _id;
    QString _name;
    QString _email;
    QString _position;
    QString _photoUrl;
};


