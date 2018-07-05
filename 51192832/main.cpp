#include <QApplication>

#include <QAction>
#include <QLineEdit>
#include <QToolButton>

class PasswordLineEdit: public QLineEdit{
public:
    PasswordLineEdit(QWidget *parent=nullptr):
        QLineEdit(parent)
    {
        setEchoMode(QLineEdit::Password);

        QAction *action = addAction(QIcon(":/eyeOff"), QLineEdit::TrailingPosition);
        QToolButton *button = qobject_cast<QToolButton *>(action->associatedWidgets()[1]);
        connect(button, &QToolButton::pressed, this, &PasswordLineEdit::onPressed);
        connect(button, &QToolButton::released, this, &PasswordLineEdit::onReleased);
    }
private slots:
    void onPressed(){
        QToolButton *button = qobject_cast<QToolButton *>(sender());
        button->setIcon(QIcon(":/eyeOn"));
        setEchoMode(QLineEdit::Normal);
    }
    void onReleased(){
        QToolButton *button = qobject_cast<QToolButton *>(sender());
        button->setIcon(QIcon(":/eyeOff"));
        setEchoMode(QLineEdit::Password);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PasswordLineEdit w;
    w.show();

    return a.exec();
}
