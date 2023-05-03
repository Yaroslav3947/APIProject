#include "User.h"

User::User(int id, const QString& name, const QString& email, const QString& position, const QString& photoUrl) :
    _id(id),
    _name(name),
    _email(email),
    _position(position),
    _photoUrl(photoUrl) {
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

User User::fromJson(const QJsonObject& json) {
    int id = json["id"].toInt();
    QString name = json["name"].toString();
    QString email = json["email"].toString();
    QString position = json["position"].toString();
    QString photoUrl = json["photo_url"].toString();
    return User(id, name, email, position, photoUrl);
}

QJsonObject User::toJson() const {
    QJsonObject json;
    json["id"] = _id;
    json["name"] = _name;
    json["email"] = _email;
    json["position"] = _position;
    json["photo_url"] = _photoUrl;
    return json;
}

