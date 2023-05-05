#include "User.h"

User::User(int id,
           const QString &name,
           const QString &email,
           QString &position,
           const QString &phoneNumber,
           const QString &photoUrl):
    _id(id),
    _name(name),
    _email(email),
    _position(position),
    _photoUrl(photoUrl),
    _phoneNumber(phoneNumber) {
}

int User::getId() const {
    return _id;
}

QString User::getName() const {
    return _name;
}

QString User::getEmail() const {
    return _email;
}

QString User::getPosition() const {
    return _position;
}

QString User::getPhotoUrl() const {
    return _photoUrl;
}

QString User::getPhoneNumber() const {
    return _phoneNumber;
}

User User::fromJson(const QJsonObject& json) {
    int id = json["id"].toInt();
    QString name = json["name"].toString();
    QString email = json["email"].toString();
    QString position = json["position"].toString();
    QString photoUrl = json["photo"].toString();
    QString phoneNumber = json["phone"].toString();
    return User(id, name, email, position, phoneNumber, photoUrl);
}

QJsonObject User::toJson() const {
    QJsonObject json;
    json["id"] = _id;
    json["name"] = _name;
    json["email"] = _email;
    json["position"] = _position;
    json["number"] = _phoneNumber;
    json["photo"] = _photoUrl;
    return json;
}

