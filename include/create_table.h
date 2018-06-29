//Grade Design
//set the class CreateTable
//Tivility 2018.06.27

#include "application.h"

class CreateTable {
public: 
	void init() {
		string s_student = "";
		s_student += "CREATE TABLE `students`( ";
		s_student += "`name` VARCHAR(25), ";
		s_student += "`id` INT NOT NULL UNIQUE, ";
		s_student += "`sex` INT, ";
		s_student += "`admission` INT, ";
		s_student += "`graduation` INT, ";
		s_student += "KEY(`id`))";

		string s_teacher = "";
		s_teacher += "CREATE TABLE `teachers`( ";
		s_teacher += "`name` VARCHAR(25), ";
		s_teacher += "`id` INT NOT NULL UNIQUE, ";
		s_teacher += "`sex` INT, ";
		s_teacher += "KEY(`id`))";

		string s_course = "";
		s_course += "CREATE TABLE `courses`( ";
		s_course += "`name` VARCHAR(25), ";
		s_course += "`id` INT NOT NULL UNIQUE, ";
		s_course += "KEY(`id`))";

		string s_time = "";
		s_time += "CREATE TABLE `time`(";
		s_time += "`time` datetime)";

		string s_class = "";
		s_class += "CREATE TABLE `teaching_classes`( ";
		s_class += "`id` INT NOT NULL, ";
		s_class += "`teacher_id` INT, ";
		s_class += "`student_id` INT, ";
		s_class += "`course_id` INT, ";
		s_class += "PRIMARY KEY(`id`, `student_id`, `course_id`), ";
		s_class += "UNIQUE KEY(`id`, `student_id`, `course_id`), ";
		s_class += "FOREIGN KEY(`teacher_id`) REFERENCES `teachers`(`id`) ";
		s_class += "ON UPDATE CASCADE ON DELETE CASCADE, ";
		s_class += "FOREIGN KEY(`student_id`) REFERENCES `students`(`id`) ";
		s_class += "ON UPDATE CASCADE ON DELETE CASCADE)";
	//	s_class += "FOREIGN KEY(`course_id`) REFERENCES `courses`(`id`))";

		string s_score = "";
		s_score += "CREATE TABLE `scores`( ";
		s_score += "`course_id` INT NOT NULL, ";
		s_score += "`student_id` INT, ";
		s_score += "`contest_time` INT, ";
		s_score += "`name` VARCHAR(25), ";
		s_score += "`score` INT NOT NULL, ";
		s_score += "`full_score` INT, ";
		s_score += "PRIMARY KEY(`course_id`, `student_id`), ";
		s_score += "UNIQUE KEY(`course_id`, `student_id`), ";
		s_score += "FOREIGN KEY(`student_id`) REFERENCES `students`(`id`)";
		s_score += "ON UPDATE CASCADE ON DELETE CASCADE)";

		string ins_class = "";
		ins_class += "INSERT INTO `teaching_classes`";
		ins_class += "(`id`, `teacher_id`, `student_id`, `course_id`) ";
		ins_class += "VALUES(55, 55, 55, 55)";

		string ins_score = "";
		ins_score += "INSERT INTO `scores`";
		ins_score += "(`course_id`, `student_id`, `score`) ";
		ins_score += "VALUES(55, 55, 55)";

		string s_trig1 = "";
		s_trig1 += "CREATE TRIGGER `trig1` AFTER INSERT ";
		s_trig1 += "ON `scores` FOR EACH ROW ";
		s_trig1 += "INSERT INTO `time` VALUES(NOW())";

		string s_view1 = "";
		s_view1 += "CREATE VIEW `view1` AS SELECT MAX(`score`), ";
		s_view1 += "`student_id` FROM `scores` ";
		s_view1 += "GROUP BY `scores`.`student_id`";

		MYSQL *conn;
		conn = mysql_init(NULL);
		mysql_real_connect(conn, "localhost", "root", "qwert", "grade", 0, NULL, 0);

		//cout << s_student << endl;
		mysql_query(conn, s_student.c_str());
		//cout << s_teacher << endl;
		mysql_query(conn, s_teacher.c_str());
	//	cout << s_course << endl;
	//	mysql_query(conn, s_course.c_str());
		//cout << s_class << endl;
		mysql_query(conn, s_class.c_str());
		//cout << s_score << endl;
		mysql_query(conn, s_score.c_str());
		//cout << s_time << endl;
		mysql_query(conn, s_time.c_str());

		mysql_query(conn, s_trig1.c_str());
		mysql_query(conn, s_view1.c_str());
		
		mysql_query(conn, "INSERT INTO `students`(`id`, `name`) VALUES(55, 'Test')");
		mysql_query(conn, "INSERT INTO `teachers`(`id`, `name`) VALUES(55, 'Test')");
	//	mysql_query(conn, "INSERT INTO `courses`(`id`, `name`) VALUES(55, 'Test')");
		mysql_query(conn, ins_class.c_str());
		mysql_query(conn, ins_score.c_str());

		mysql_close(conn);;

		return ;
	}
private: 

};
