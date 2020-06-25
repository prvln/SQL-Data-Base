import pyodbc

conn = pyodbc.connect("DRIVER={SQLite3 ODBC Driver};SERVER=localhost;DATABASE=F:\\QT_MYSQL_CLIENT\\DataBaseODBC.db;Trusted_connection=yes")
cnxn = pyodbc.connect('DRIVER={CData ODBC Driver for CSV};Location=F:\\QT_MYSQL_CLIENT\\Schema.ini;')

cursor = conn.cursor()
curxor = cnxn.cursor()


s = ''
k = 0
#f = open("F:\\QT_MYSQL_CLIENT\\DataBaseODBC.csv","w+") # ПОЛНЫЙ ПУТЬ
for row in cursor.execute('SELECT * FROM students_table'):
	print(row)
	curxor.execute('INSERT INTO DataBaseO(ID, "Имя", "Фамилия", "Группа", "Индекс", "Возраст", "Кафедра", "Факультет") VALUES ("' + str(row[0]) + '", "' + str(row[1]) + '", "' + str(row[2]) + '", "' + str(row[3]) + '", "' + str(row[4]) + '", "' + str(row[5]) + '", "' + str(row[6]) + '", "' + str(row[7]) + '")')
	curxor.commit()
conn.close()
cnxn.close()