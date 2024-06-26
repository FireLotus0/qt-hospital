#include "nethelp.h"
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonArray>

NetHelp::NetHelp(QObject* parent)
    : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    initMap();
}

void NetHelp::send(const QString &subPath,bool blocked, const QJsonObject &jsonObject,
                   QJsonArray array)
{
    auto netHelp = getThis();
    QNetworkRequest request;
    request.setUrl(QUrl(serverAddr + subPath));
    request.setRawHeader("Content-Type","application/json");
    // 创建JSON文档
    QJsonDocument jsonDocument;
    if(array.empty()) {
        jsonDocument = QJsonDocument(jsonObject);
    } else {
        jsonDocument = QJsonDocument(array);
    }
    QByteArray jsonData = jsonDocument.toJson();

    // 发送POST请求
    if(!blocked) {
        auto reply = netHelp->manager->post(request, jsonData);
        connect(reply, &QNetworkReply::finished, getThis(), [reply, subPath]{
            getThis()->sigEmit(subPath, reply->readAll());
            reply->deleteLater();
        });
    } else {
        QNetworkReply* reply = netHelp->manager->post(request, jsonData);
        QEventLoop eventLoop;
        connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
        eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
        getThis()->sigEmit(subPath, reply->readAll());
        reply->deleteLater();
    }
}

NetHelp *NetHelp::getThis()
{
   static NetHelp netHelp;
   return &netHelp;
}

QList<QJsonObject> NetHelp::parseResult(const QByteArray &data)
{
    // 将 QByteArray 转换为 QString
    QString jsonString = QString::fromUtf8(data);
    QList<QJsonObject> res;
    // 将 QString 转换为 QJsonObject
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());

    for(const auto& obj : jsonDocument.array()){
        res << obj.toObject();
    }
    return res;
}

void NetHelp::initMap()
{
    MAPDEF(login);
    MAPDEF(medical);
    MAPDEF(modifyMedical);
    MAPDEF(commitCheck);
    MAPDEF(medicine);
    MAPDEF(prescription);
    MAPDEF(notify);
    MAPDEF(prove);

}

void NetHelp::sigEmit(const QString &name, const QByteArray& data)
{
    (this->*sigMapFunc.value(name))(data);
}
