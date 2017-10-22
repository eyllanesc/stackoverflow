import time
import warnings

import serial
import serial.tools.list_ports
from DynoTest1 import Ui_DynoTest1
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *


class GetData(QThread):
    dataChanged = pyqtSignal(int, int, int, int, int)
    Distance = 0.5

    def __init__(self, parent=None):
        QThread.__init__(self, parent)

        arduino_ports = [  # automatically searches for an Arduino and selects the port it's on
            p.device
            for p in serial.tools.list_ports.comports()
            # if 'Arduino' in p.description
        ]

        if not arduino_ports:
            raise IOError("No Arduino found - is it plugged in? If so, restart computer.")
        if len(arduino_ports) > 1:
            warnings.warn('Multiple Arduinos found - using the first')
        self.Arduino = serial.Serial(arduino_ports[0], 9600, timeout=1)

    def __del__(self):  # part of the standard format of a QThread
        self.wait()

    def run(self):  # also a required QThread function, the working part
        self.Arduino.close()
        self.Arduino.open()

        self.Arduino.flush()
        self.Arduino.reset_input_buffer()
        start_time = time.time()

        while True:
            while self.Arduino.inWaiting() == 0:
                pass
            try:
                data = self.Arduino.readline()
                dataarray = data.decode().rstrip().split(',')
                self.Arduino.reset_input_buffer()
                Force = round(float(dataarray[0]), 3)
                RPM = round(float(dataarray[1]), 3)
                Torque = round(Force * GetData.Distance, 3)
                HorsePower = round(Torque * RPM / 5252, 3)
                Run_Time = round(time.time() - start_time, 3)
                print(Force, 'Grams', ",", RPM, 'RPMs', ",", Torque, "ft-lbs", ",", HorsePower, "hp", Run_Time,
                      "Time Elasped")
                self.dataChanged.emit(Force, RPM, Torque, HorsePower, Run_Time)
            except (KeyboardInterrupt, SystemExit, IndexError, ValueError):
                pass


class GUI(QWidget, Ui_DynoTest1):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)
        self.thread = GetData(self)
        self.thread.dataChanged.connect(self.onDataChanged)
        self.thread.start()

    def onDataChanged(self, Force, RPM, Torque, HorsePower, Run_Time):
        self.lcdNumber_4.display(RPM)
        self.lcdNumber_5.display(Torque)
        self.lcdNumber_6.display(HorsePower)
        self.lcdNumber_7.display(Run_Time)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    Dyno = GUI()
    Dyno.show()
    sys.exit(app.exec_())
