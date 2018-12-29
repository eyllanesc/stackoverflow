def create_connection(db_file):
    try:
        connection = sqlite3.connection(db_file)
        return connection
    except Error as database_error_connection:
        print (database_error_connection)
    return None

def create_coordinates_table(connection, create_table_sql):
    try:
        c = connection.cursor()
        c.execute(create_table_sql)
    except Error as database_error_connection:
        print (database_error_connection)

def main():
    database = '/home/dragoncoder/Schreibtisch/praca_semestralna/Navigation/datenbank/facharbeit.sqlite'
    sql_create_coordinate_table = ('''CREATE TABLE IF NOT EXISTS coordinates (id INTEGER PRIMARY KEY,
																				latitude real NOT NULL,
																				longtitude real NOT NULL);''')	
    connection = create_connection (database)
    if connection is not None:
        create_coordinates_table(connection, sql_create_coordinate_table)
    else:
        print ("Probleme aufgetreten! Die Tabelle kann nicht hinzugefuegt werden.")
if__name__ == '__main__'
    main()
