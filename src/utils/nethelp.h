#pragma once

#include <QString>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>

#define SIGDEF(name) void name##Finished(const QByteArray& data)

#define MAPDEF(name) sigMapFunc[#name] = &NetHelp::name##Finished

#define GETSIG(name) &NetHelp::name##Finished

const QString serverAddr = "http://192.168.3.149:8020/HSQ/";

class NetHelp : public QObject
{
    Q_OBJECT
public:
    NetHelp(QObject* parent = nullptr);
    // 发送请求获取数据
    static void send(const QString& subPath, bool blocked = false, const QJsonObject& jsonObject = QJsonObject(),
                      QJsonArray array = QJsonArray());

    static NetHelp* getThis();

    static QList<QJsonObject> parseResult(const QByteArray& data);

private:

    void initMap();

    void sigEmit(const QString& name, const QByteArray& data);
signals:

    SIGDEF(login);
    SIGDEF(medical);
    SIGDEF(modifyMedical);
    SIGDEF(commitCheck);
    SIGDEF(medicine);
    SIGDEF(prescription);
    SIGDEF(notify);
    SIGDEF(prove);

private:
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QMap<QString, void(NetHelp::*)(const QByteArray&)> sigMapFunc;
};

