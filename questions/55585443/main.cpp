#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    QVBoxLayout *lay = new QVBoxLayout{&w};
    QComboBox combo;
    QLabel label{"Stack Overflow"};
    lay->addWidget(&combo);
    lay->addWidget(&label);
    QObject::connect(&combo, &QComboBox::currentTextChanged, [&label](const QString & name){
        label.setFont(QFont(name));
    });
    QDir directory(":/Roboto");
    for(const QFileInfo & info:  directory.entryInfoList()){
        int id = QFontDatabase::addApplicationFont(info.absoluteFilePath());
        if(id != -1){
            QStringList font_families = QFontDatabase::applicationFontFamilies(id);
            if(!font_families.isEmpty())
                combo.addItem(font_families.first());
        }
    }
    w.show();
    return a.exec();
}
