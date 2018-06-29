Ubuntu 16.04.4 LTS.
mysql  Ver 14.14 Distrib 5.7.22, for Linux (x86_64) using  EditLine wrapper

g++ -I/usr/include/mysql -I./include ./src/main.cpp -L/usr/lib/mysql -lmysqlclient -std=c++11 -o ./grade

5 tables;
1 view;

mysql> show tables;
| Tables_in_grade  |
|------------------|
| scores           |
| students         |
| teachers         |
| teaching_classes |
| time             |
| view1            |
6 rows in set (0.00 sec)

mysql> show columns from scores;
| Field        | Type        | Null | Key | Default | Extra |
|--------------|-------------|------|-----|---------|-------|
| course_id    | int(11)     | NO   | PRI | NULL    |       |
| student_id   | int(11)     | NO   | PRI | NULL    |       |
| contest_time | int(11)     | YES  |     | NULL    |       |
| name         | varchar(25) | YES  |     | NULL    |       |
| score        | int(11)     | NO   |     | NULL    |       |
| full_score   | int(11)     | YES  |     | NULL    |       |
6 rows in set (0.00 sec)

mysql> show columns from students;
| Field      | Type        | Null | Key | Default | Extra |
|------------|-------------|------|-----|---------|-------|
| name       | varchar(25) | YES  |     | NULL    |       |
| id         | int(11)     | NO   | PRI | NULL    |       |
| sex        | int(11)     | YES  |     | NULL    |       |
| admission  | int(11)     | YES  |     | NULL    |       |
| graduation | int(11)     | YES  |     | NULL    |       |
5 rows in set (0.00 sec)

mysql> show columns from teachers;
| Field | Type        | Null | Key | Default | Extra |
|-------|-------------|------|-----|---------|-------|
| name  | varchar(25) | YES  |     | NULL    |       |
| id    | int(11)     | NO   | PRI | NULL    |       |
| sex   | int(11)     | YES  |     | NULL    |       |
3 rows in set (0.00 sec)

mysql> show columns from teaching_classes;
| Field      | Type    | Null | Key | Default | Extra |
|------------|---------|------|-----|---------|-------|
| id         | int(11) | NO   | PRI | NULL    |       |
| teacher_id | int(11) | YES  | MUL | NULL    |       |
| student_id | int(11) | NO   | PRI | NULL    |       |
| course_id  | int(11) | NO   | PRI | NULL    |       |
4 rows in set (0.00 sec)

mysql> show columns from time;
| Field | Type     | Null | Key | Default | Extra |
|-------|----------|------|-----|---------|-------|
| time  | datetime | YES  |     | NULL    |       |
1 row in set (0.00 sec)

mysql> desc view1;
| Field        | Type    | Null | Key | Default | Extra |
|--------------|---------|------|-----|---------|-------|
| MAX(`score`) | int(11) | YES  |     | NULL    |       |
| student_id   | int(11) | NO   |     | NULL    |       |
2 rows in set (0.01 sec)

mysql> show create view view1;
| View  | Create View                                                                                                                                                                                                                    | character_set_client | collation_connection |
|-------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------------------|----------------------|
| view1 | CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `view1` AS select max(`scores`.`score`) AS `MAX(``score``)`,`scores`.`student_id` AS `student_id` from `scores` group by `scores`.`student_id` | latin1               | latin1_swedish_ci    |
1 row in set (0.00 sec)


####1. 初始化模块
(不进行登录验证, 程序中包含数据库登录密码)
#####1.1. 建立数据库
#####1.2. 创建表格:
#####1.3. 建立索引
#####1.3. 创建视图
#####1.5. 建立触发器
#####1.6. 随机填充

####2. 分数相关模块
#####2.1. 插入一条成绩
#####2.2. 查询成绩
######2.2.1. 查询某学号所有成绩
######2.2.2. 查询教师所有学生成绩
######2.2.3. 查询所有不及格的成绩
######2.2.4. 查询某学生的最高成绩(视图, 自动更新)
#####2.4. 删除一条成绩

####3. 学生相关模块
#####3.1. 根据学号查询学生信息
#####3.2. 根据学号删除学生信息
#####3.3. 根据学号更新学生信息
#####3.4. 根据学号插入学生信息

####4. 教师相关模块
#####4.1. 根据工号查询教师信息
#####4.2. 根据工号删除教师信息
#####4.3. 根据工号更新教师信息
#####4.4. 根据工号插入教师信息

####5. 后台管理模块
#####5.1. 查看每条成绩修改命令执行的时间


测试用例:
	terminal1:
		`mysql -u root -p`
	password:
		`qwert`
    空数据库

	terminal2:
		g++ -I/usr/include/mysql -I./include ./src/main.cpp -L/usr/lib/mysql -lmysqlclient -std=c++11 -o ./grade    

	 1. init the system? 	初始化数据库, create database, create tables
		y
	 2. function list		功能列表
		1					自动填入随机数据
	 3. function list
		2					成绩相关模块
	 4. score  list			成绩相关功能列表
		2					查询成绩
	 5. search list			查询功能列表
		1					按照学生id查询
	 6. input sid			输入学生学号
		15					查询学号为15学生的所有成绩
	 7. score  list
		3					删除一条成绩
	 8. input the sid		要删除的成绩对应的学生学号
		15					删除成绩的学号为15
	 9. input the cid		要删除的成绩对应的课程编号
		5					删除成绩的课程编号为5
	10. make sure			确认删除
		y
	11. score  list		
		2					查询验证已删除
	12. search list			
		1
	13. inupt the sid		验证学号15, 课程号5的成绩已经删除
		15
	14. score list
		2					继续验证查询功能
	15. search list 		
		2					验证按照教师编号查询
	16. input tid			输入教师编号
		5
	17. score list			
		2					继续验证查询功能
	18. search list			
		3					查询低于某一分值的成绩
	19. input the score		输入分值
		60					查询所有不及格成绩
	20. score list			
		2					
	21. search list			按照学号查询某一学生最高分
		4
	22. input sid			查询学生学号
		15
	23. score list		
		1					验证插入一条成绩
	24. sid			cid
		15			5
	26. ctime 		cname
		20180101	cname
	27.	score		fullscore
		100			100
	28. score list
		2					验证已插入
	29. search list			
		4
	30. input sid
		15					通过验证最高成绩验证成绩已经插入
