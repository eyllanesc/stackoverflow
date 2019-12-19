#include <QtWidgets>

#include <QrCode.hpp>

static QImage slotCreateQrCode(const QString& qrCodeContents)
{
    qrcodegen::QrCode qr0=qrcodegen::QrCode::encodeText(qrCodeContents.toLocal8Bit().constData(),
                                                        qrcodegen::QrCode::Ecc::MEDIUM);

    const int s = qr0.getSize();
    const int margin = 1;
    QImage imageQrCodePNG((s + 2 * margin) * QSize(1, 1), QImage::Format_Mono);

    {
    	QPainter painter(&imageQrCodePNG);
    	painter.fillRect(imageQrCodePNG.rect(), Qt::white);
    	painter.setPen(Qt::NoPen);
    	painter.setBrush(Qt::black);
    	for (int i = 0; i < s ; ++i)
    	{
    		for (int j = 0; j < s; ++j)
    		{
    			if(qr0.getModule(i, j))
    				painter.drawRect(i + margin, j + margin, 1, 1);
    		}
    	}

    }
    return imageQrCodePNG;
}   // slotCreateQrCode

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	QImage image = slotCreateQrCode("Stack Overflow");

	const QSize size(512, 512);

	QLabel label;
	label.setPixmap(QPixmap::fromImage(image.scaled(size)));
	label.setFixedSize(size);
	label.show();

	return a.exec();
}