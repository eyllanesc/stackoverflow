import serial
import time
import sqlite3

database_name = '/home/dragoncoder/Schreibtisch/facharbeit/navigation/datenbank/facharbeit.db';
table_name = 'coordinates';
latitude_column = 'latitude';
longtitude_column = 'longitude';
data_column = 'datum';


goToInformationOfGPS = serial.Serial("/dev/ttyUSB0", baudrate = 9600)#access to the usb0

while True:
    #time.sleep(1)
    line = goToInformationOfGPS.readline()

    information = line.split(",".encode())

    if (information[0] =="$GPRMC"):
        if (information[2]=="A"):
            try:
                print (information [3] , information [4])
                print (information [5] , information [6])
                print (information [9])
                try:
                    x = float(information [3]) / 100
                    y = float(information [5]) / 100
                    d = information [9]
                except:
                    print 'error'
                finally:
                    try:
		                connection = sqlite3.connect(database_name)
		                cursor = connection.cursor()
		                cursor.execute('''INSERT INTO {tbn}( {ltn}, {longn}, {datum} ) VALUES (  {x1}, {y1}, {d1})'''\
			                .format(tbn = table_name, ltn = latitude_column, longn = longtitude_column, datum = data_column, x1 = x, y1 = y, d1 = d))
		                connection.commit()
		                
                    #except (sqlite3.Error):
		                #print (database_error_connection)
                        #print (sqlite3.Error)
                    except Exception as e:
                    # Roll back any change if something goes wrong
                        connection.rollback()
                        raise e
                    finally:
                    # Close the db connection
                        connection.close()
            except (ValueError):
                pass
    
