__author__ = 'pc'
import requests
from bs4 import BeautifulSoup
from PyQt5 import QtCore, QtWidgets, QtWebEngineWidgets
import sqlite3
import sys, getopt, time
from PyQt5.QtCore import QTimer

records = []
def scrape_page(url, html):
    soup = BeautifulSoup(html, 'html.parser')
    data = soup.find('div', class_='tablo_dual_board')
    try:
        datas = data.text.splitlines()
        datas1 = list(filter(None, datas))
        records.append(datas1)
    except:
        pass

def process_records():
    # add record to database ...
    print('process records:', len(records))

def generate_urls():
    onexurl = "https://1xbahis19.com/en/live/Football/"
    reply = requests.get(onexurl)
    soup = BeautifulSoup(reply.content, "html.parser")
    income = soup.find_all("ul", {"id":"games_content"})
    links = soup.find_all("a", {"class": "c-events__name"})
    urls = []
    for matchlink in links:
        urls.append("https://1xbahis19.com/en/"+(matchlink.get("href")))
    return urls

class WebPage(QtWebEngineWidgets.QWebEnginePage):
    def __init__(self):
        super(WebPage, self).__init__()
        self.loadFinished.connect(self.handleLoadFinished)

    def start(self, urls):
        self._urls = iter(urls)
        self.fetchNext()

    def fetchNext(self):
        try:
            url = next(self._urls)
        except StopIteration:
            return False
        else:
            self.load(QtCore.QUrl(url))
        return True

    def processCurrentPage(self, html):
        scrape_page(self.url().toString(), html)
        if not self.fetchNext():
            process_records()
            print(records)
            QtWidgets.qApp.quit()

    def handleLoadFinished(self):
        self.toHtml(self.processCurrentPage)

app = QtWidgets.QApplication(sys.argv)
webpage = WebPage()
webpage.start(generate_urls())
app.exec_()