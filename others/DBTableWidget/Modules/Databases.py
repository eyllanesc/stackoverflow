import sqlite3


class DatabaseManager(object):
    def __init__(self, database, table):
        self.db = database
        self.table = table

        self.con = sqlite3.connect('students.db')
        self.cursor = self.con.cursor()

        self.cursor.execute('''CREATE TABLE IF NOT EXISTS`{}` (`s_id` INTEGER PRIMARY KEY AUTOINCREMENT,`name` TEXT NOT NULL,`mid` INTEGER,
        `lec` INTEGER,`res` INTEGER,`term` INTEGER,`final`  INTEGER,`end` INTEGER);'''.format(self.table))

        self.con.commit()

    def gettable(self):
        self.cursor.execute("SELECT * FROM {}".format(self.table))
        return self.cursor.fetchall()

    def getcols(self):
        self.cursor.execute("SELECT * FROM {}".format(self.table))
        return [description[0] for description in self.cursor.description]

    def addentry(self, message):
        name, mid, lec, res, term, final, end = message
        cmd = "INSERT INTO {} (name, mid, lec, res, term, final, end) VALUES((?), (?), (?), (?), (?), (?), (?));".format(
            self.table)
        self.cursor.execute(cmd, (name, mid, lec, res, term, final, end))
        self.con.commit()

    def __del__(self):
        self.con.commit()
        self.cursor.close()
        self.con.close()


if __name__ == '__main__':
    dbu = DatabaseManager('students.db', 'degrees')
    dbu.addentry(('nn', 10, 11, 12, 13, 14, 15))
    print(dbu.gettable())
