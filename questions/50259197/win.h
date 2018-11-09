#ifndef WIN_H
#define WIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QMap>
#include <QLabel>
#include <QLineEdit>
#include <QMap>
#include <QMultiMap>

#include "graphwidget.h"


class Win : public QWidget
{
    Q_OBJECT
public:
    explicit Win(QWidget *parent = nullptr);
    ~Win();
private:
    QPushButton *btnCreateNode;
    QPushButton *btnConnectNode;
    QPushButton *btnDelete;
    GraphWidget *grafViewScene;
    Node *_source;  // сохраняет вершину при нажатии на кнопку "Соединить"
    bool connFlag;
signals:

public slots:
    void onBtnConnectNodeClicked();
    void onBtnDeleteClicked();
    void sceneSelectionChanged();
};

#endif // WIN_H
