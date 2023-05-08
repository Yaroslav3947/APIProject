#pragma once

#include <QString>
#include <QJsonObject>

class User {
public:
    User() = default;
    User(int id,
         const QString &name,
         const QString &email,
         QString &position,
         const QString &phoneNumber,
         const QString &photoUrl);

    int getId() const;
    QString getName() const;
    QString getEmail() const;
    QString getPosition() const;
    QString getPhotoUrl() const;
    QString getPhoneNumber() const;

    void setId(int id);
    void setName(QString name);
    void setEmail(QString email);
    void setPosition(QString position);
    void setPhotoUrl(QString photoUrl);
    void setPhoneNumber(QString phoneNumber);

    static User fromJson(const QJsonObject &json);
    QJsonObject toJson() const;

private:
    int _id;
    QString _name;
    QString _email;
    QString _position;
    QString _photoUrl;
    QString _phoneNumber;
};


