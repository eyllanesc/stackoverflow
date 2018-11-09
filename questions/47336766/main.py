import sys

import pandas as pd
import numpy as np
from PyQt5.QtCore import QDir, QUrl
from PyQt5.QtGui import QPixmap
from PyQt5.QtWebEngineWidgets import QWebEngineView, QWebEnginePage
from PyQt5.QtWidgets import QApplication, QWidget, QGridLayout, QLabel, QSpacerItem, QComboBox, QStackedWidget, \
    QSizePolicy
import plotly
import plotly.graph_objs as go


def test():
    path = QDir.current().filePath('plotly-latest.min.js')
    local = QUrl.fromLocalFile(path).toString()
    data_frame = pd.DataFrame(np.random.randn(100, 5), columns=['Date', 'Lines', 'Orders', 'Eaches', 'SKUs'])

    name = "test"

    trace_lines = go.Bar(x=data_frame['Date'], y=data_frame['Lines'], name='Lines', visible=True)
    trace_orders = go.Bar(x=data_frame['Date'], y=data_frame['Orders'], name='Orders', visible=False)
    trace_eaches = go.Bar(x=data_frame['Date'], y=data_frame['Eaches'], name='Eaches', visible=False)
    trace_SKUs = go.Bar(x=data_frame['Date'], y=data_frame['SKUs'], name='SKUs', visible=False)

    data = [trace_lines, trace_orders, trace_eaches, trace_SKUs]

    lines_title = "%s Lines" % name
    orders_title = "%s Orders" % name
    eaches_title = "%s Eaches" % name
    skus_title = "%s SKUs" % name

    update_menus = list([dict(active=0,
                              buttons=list([dict(label='Lines',
                                                 method='update',
                                                 args=[{'visible': [True, False, False, False]},
                                                       {'title': lines_title}]),
                                            dict(label='Orders',
                                                 method='update',
                                                 args=[{'visible': [False, True, False, False]},
                                                       {'title': orders_title}]),
                                            dict(label='Eaches',
                                                 method='update',
                                                 args=[{'visible': [False, False, True, False]},
                                                       {'title': eaches_title}]),
                                            dict(label='SKUs',
                                                 method='update',
                                                 args=[{'visible': [False, False, False, True]},
                                                       {'title': skus_title}])]))])

    layout = dict(title=lines_title, showlegend=False, updatemenus=update_menus, xaxis=dict(
        rangeselector=dict(buttons=list([dict(count=1, label='1m', step='month', stepmode='backward'),
                                         dict(count=6, label='6m', step='month', stepmode='backward'),
                                         dict(step='all')])),
        rangeslider=dict(),
        type='date'
    ))

    fig = dict(data=data, layout=layout)

    raw_html = '<html><head><meta charset="utf-8" /><script src="{}"></script></head>'.format(local)
    raw_html += '<body>'
    raw_html += plotly.offline.plot(fig, include_plotlyjs=False, output_type='div')
    raw_html += '</body></html>'

    return raw_html


class Widget(QWidget):
    isFirst = True

    def __init__(self, *args, **kwargs):
        QWidget.__init__(self, *args, **kwargs)
        grid_layout = QGridLayout(self)
        logo = QLabel()
        logo_pixmap = QPixmap('logo.jpg')
        logo.setPixmap(logo_pixmap)
        grid_layout.addWidget(logo, 0, 0, 2, 6)
        grid_layout.addItem(QSpacerItem(500, 50, QSizePolicy.Minimum, QSizePolicy.Expanding), 0, 6)

        graph_label = QLabel('Graph')
        self.graph_names_combobox = QComboBox()

        grid_layout.addWidget(graph_label, 0, 7, 1, 1)
        grid_layout.addWidget(self.graph_names_combobox, 0, 8, 1, 4)

        self.graph_widget = QStackedWidget()
        grid_layout.addWidget(self.graph_widget, 2, 1, 10, 12)

        temp_webpage = QWebEngineView(self)
        temp_webpage.setHtml(test())
        self.graph_widget.addWidget(temp_webpage)
        temp_webpage.loadFinished.connect(self.onLoadFinished)

    def onLoadFinished(self, ok):
        if self.isFirst:
            # self.sender().page().action(QWebEnginePage.Reload).trigger()
            self.sender().reload()
        self.isFirst = False


if __name__ == '__main__':
    sys.argv.append("--disable-web-security")
    sys.argv.append("--remote-debugging-port=8000")
    app = QApplication(sys.argv)
    w = Widget()
    w.showMaximized()
    sys.exit(app.exec_())
