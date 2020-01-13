#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QByteArray>
#include <QUrl>

namespace Constants {
    const QByteArray SPOTIFY_CLIENT_ID = "client-id";
    const QByteArray SPOTIFY_CLIENT_SECRET = "client-secret";

    const QUrl SPOTIFY_AUTHORIZATION_URL = QUrl("https://accounts.spotify.com/authorize");
    const QUrl SPOTIFY_ACCESSTOKEN_URL = QUrl("https://accounts.spotify.com/api/token");
}

#endif // CONSTANTS_H
