#include <QApplication>

#include <QtCharts>
QT_CHARTS_USE_NAMESPACE

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

static cv::Mat QImageToMat(const QImage &image) {
  cv::Mat out;
  switch (image.format()) {
  case QImage::Format_Invalid: {
    cv::Mat empty;
    empty.copyTo(out);
    break;
  }
  case QImage::Format_RGB32: {
    cv::Mat view(image.height(), image.width(), CV_8UC4,
                 (void *)image.constBits(), image.bytesPerLine());
    view.copyTo(out);
    break;
  }
  case QImage::Format_RGB888: {
    cv::Mat view(image.height(), image.width(), CV_8UC3,
                 (void *)image.constBits(), image.bytesPerLine());
    cv::cvtColor(view, out, cv::COLOR_RGB2BGR);
    break;
  }
  default: {
    QImage conv = image.convertToFormat(QImage::Format_ARGB32);
    cv::Mat view(conv.height(), conv.width(), CV_8UC4, (void *)conv.constBits(),
                 conv.bytesPerLine());
    view.copyTo(out);
    break;
  }
  }
  return out;
}

static std::vector<cv::Mat> calculate_histogram(const QImage &image) {
  cv::Mat src = QImageToMat(image);

  std::vector<cv::Mat> bgr_planes;
  cv::split(src, bgr_planes);
  /// Establish the number of bins
  int histSize = 256;

  /// Set the ranges ( for B,G,R) )
  float range[] = {0, 256};
  const float *histRange = {range};

  bool uniform = true;
  bool accumulate = false;

  std::vector<cv::Mat> hist;
  for (std::size_t i = 0; i < bgr_planes.size(); ++i) {
    hist.push_back(cv::Mat());
    cv::calcHist(&bgr_planes[i], 1, 0, cv::Mat(), hist[i], 1, &histSize,
                 &histRange, uniform, accumulate);
  }

  return hist;
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QImage image(":/lena.png");

  QChartView *view = new QChartView;
  view->setWindowTitle("Histogram");
  QChart *chart = new QChart;
  view->setChart(chart);

  const QStringList titles{"Blue", "Green", "Red"};
  std::vector<cv::Mat> hist_planes = calculate_histogram(image);

  for (std::size_t i = 0; i < 3; ++i) {
    const cv::Mat mat = hist_planes[i];
    QLineSeries *series = new QLineSeries;
    series->setColor(QColor(titles[i]));
    series->setName(titles[i]);
    for (int j = 0; j < mat.rows; ++j) {
      *series << QPoint(j, mat.at<float>(j));
    }
    chart->addSeries(series);
  }

  chart->createDefaultAxes();
  chart->axisX()->setGridLineVisible(false);
  chart->axisY()->setGridLineVisible(false);

  QLabel *label = new QLabel;
  label->setPixmap(QPixmap::fromImage(image));

  QWidget w;
  QHBoxLayout *lay = new QHBoxLayout(&w);
  lay->addWidget(label);
  lay->addWidget(view);

  w.show();

  return a.exec();
}
