import pyodbc

conn = pyodbc.connect("DRIVER={SQLite3 ODBC Driver};SERVER=localhost;DATABASE=F:\\QT_MYSQL_CLIENT\\DataBaseODBC.db;Trusted_connection=yes")
cursor = conn.cursor()

s = ''
k = 0
f = open("F:\\QT_MYSQL_CLIENT\\DataBaseODBC.csv","w+") # ПОЛНЫЙ ПУТЬ
for row in cursor.execute('SELECT * FROM students_table'):
	print(row)
	for i in row:
		if k!= 0:
			s=s+','
		s = s+ str(i)
		k= k+1	
	f.write(s + '\n')
	s = ''	
	k=0