import logging
import os
import pickle
import sys
import threading

from PySide2 import QtCore, QtGui, QtQml

from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request


SCOPES = ["https://www.googleapis.com/auth/calendar.readonly"]
CURRENT_DIR = os.path.dirname(os.path.realpath(__file__))


logging.basicConfig(level=logging.DEBUG)


class CalendarBackend(QtCore.QObject):
    eventsChanged = QtCore.Signal(list)

    def __init__(self, parent=None):
        super().__init__(parent)
        self._service = None

    @property
    def service(self):
        return self._service

    def updateListEvents(self, kw):
        threading.Thread(target=self._update_list_events, args=(kw,)).start()

    def _update_list_events(self, kw):
        self._update_credentials()

        events_result = self.service.events().list(**kw).execute()
        events = events_result.get("items", [])

        qt_events = []
        if not events:
            logging.debug("No upcoming events found.")
        for event in events:
            start = event["start"].get("dateTime", event["start"].get("date"))
            end = event["end"].get("dateTime", event["end"].get("date"))
            logging.debug(f"From {start} - To {end}:  {event['summary']}")

            start_dt = QtCore.QDateTime.fromString(start, QtCore.Qt.ISODate)
            end_dt = QtCore.QDateTime.fromString(end, QtCore.Qt.ISODate)
            summary = event["summary"]

            e = {"start": start_dt, "end": end_dt, "summary": summary}
            qt_events.append(e)

        self.eventsChanged.emit(qt_events)

    def _update_credentials(self):
        creds = None
        if os.path.exists("token.pickle"):
            with open("token.pickle", "rb") as token:
                creds = pickle.load(token)
        if not creds or not creds.valid:
            if creds and creds.expired and creds.refresh_token:
                creds.refresh(Request())
            else:
                flow = InstalledAppFlow.from_client_secrets_file(
                    "credentials.json", SCOPES
                )
                creds = flow.run_local_server(port=0)
            with open("token.pickle", "wb") as token:
                pickle.dump(creds, token)

        self._service = build("calendar", "v3", credentials=creds)


class CalendarProvider(QtCore.QObject):
    loaded = QtCore.Signal()

    def __init__(self, parent=None):
        super().__init__(parent)

        self._cache_events = []
        self._backend = CalendarBackend()
        self._backend.eventsChanged.connect(self._handle_events)

    @QtCore.Slot("QVariant")
    def updateListEvents(self, parameters):
        d = dict()
        for k, v in parameters.toVariant().items():
            if isinstance(v, QtCore.QDateTime):
                v = v.toTimeSpec(QtCore.Qt.OffsetFromUTC).toString(
                    QtCore.Qt.ISODateWithMs
                )
            d[k] = v
        self._backend.updateListEvents(d)

    @QtCore.Slot(QtCore.QDate, result="QVariantList")
    def eventsForDate(self, date):
        events = []
        for event in self._cache_events:
            start = event["start"]
            if start.date() == date:
                events.append(event)
        return events

    @QtCore.Slot(list)
    def _handle_events(self, events):
        self._cache_events = events
        self.loaded.emit()
        logging.debug("Loaded")


def main():
    app = QtGui.QGuiApplication(sys.argv)

    QtQml.qmlRegisterType(CalendarProvider, "MyCalendar", 1, 0, "CalendarProvider")

    engine = QtQml.QQmlApplicationEngine()
    filename = os.path.join(CURRENT_DIR, "main.qml")
    engine.load(QtCore.QUrl.fromLocalFile(filename))

    if not engine.rootObjects():
        sys.exit(-1)

    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
