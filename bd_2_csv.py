import sqlite3

conn = sqlite3.connect('DataBase.db')
cursor = conn.cursor()

#создание таблиц + наполнение
'''
cursor.executescript("""
		    BEGIN TRANSACTION;
		    CREATE TABLE "user" (
				`id`    INTEGER PRIMARY KEY AUTOINCREMENT,
				`name`    TEXT,
				`id_lang`    INTEGER,
				`changed`    TEXT
			);

			INSERT INTO `user`  (name, id_lang, changed)  
			VALUES('Егор',1, DATETIME('now'));
			INSERT INTO `user`  (name, id_lang, changed)  
			VALUES('Иван',2, DATETIME('now'));

			CREATE TABLE "lang" (
				`id`    INTEGER PRIMARY KEY AUTOINCREMENT,
				`name`    TEXT,
				`changed`    TEXT
			);

			INSERT INTO `lang`  (name, changed)  
			VALUES('python',DATETIME('now'));
			INSERT INTO `lang`  (name, changed)  
			VALUES('c++',DATETIME('now'));

			COMMIT;
		""")'''
s = ''
k = 0
f = open("DataBase.csv","w+")
for row in cursor.execute('SELECT * FROM students_table'):
#for row in cursor.execute('SELECT * FROM user'):
	print(row)
	for i in row:
		if k!= 0:
			s=s+','
		s = s+ str(i)
		k= k+1	
	f.write(s + '\n')
	s = ''	
	k=0
            