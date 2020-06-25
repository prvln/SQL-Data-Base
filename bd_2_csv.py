import sqlite3

conn = sqlite3.connect('DataBase.db')
cursor = conn.cursor()
s = ''
k = 0
f = open("DataBase.csv","w+")
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
            
