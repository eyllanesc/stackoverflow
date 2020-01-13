#ifndef SPOTIFYWRAPPER_H
#define SPOTIFYWRAPPER_H

#include <QOAuth2AuthorizationCodeFlow>
#include <QObject>

class SpotifyWrapper : public QObject
{
    Q_OBJECT
public:
    explicit SpotifyWrapper(QObject *parent = nullptr);
    QNetworkReply *me();
public Q_SLOTS:
    void grant();
Q_SIGNALS:
    void authenticated();
private:
    QOAuth2AuthorizationCodeFlow oauth2;
};

#endif // SPOTIFYWRAPPER_H
