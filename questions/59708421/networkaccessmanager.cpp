#include "networkaccessmanager.h"
#include "constants.h"
#include <QtGlobal>

QNetworkReply *NetworkAccessManager::createRequest(QNetworkAccessManager::Operation op,
                                                   const QNetworkRequest &request,
                                                   QIODevice *outgoingData)
{
    QNetworkRequest r(request);
    if(r.url() == Constants::SPOTIFY_ACCESSTOKEN_URL)
        r.setRawHeader("Authorization",
                       "Basic " +
                       QByteArray(Constants::SPOTIFY_CLIENT_ID + ":" + Constants::SPOTIFY_CLIENT_SECRET).toBase64());
    return QNetworkAccessManager::createRequest(op, r, outgoingData);
}
