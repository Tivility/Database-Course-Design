//Grade Design
//randinsert for all table;
//Tivility 2018.06.28

#include "application.h"

class Randinsert {
public: 	
	void init() {

		srand(time(NULL));

		conn = mysql_init(NULL);
		mysql_real_connect(conn, "localhost", "root", "qwert", "grade", 0, NULL, 0);

		insert_student();
		insert_teacher();
		insert_class();
		insert_score();

		mysql_close(conn);
		return ;
	}

private:
	MYSQL *conn;

	void insert_student() {
		for (int i = 1; i <= 30; ++i) {
			string ins = "";
			ins += "INSERT INTO `students`";
			ins += "(`name`, `id`) ";
			ins += "VALUES(";
			ins += "'sname";
			ins += to_string(i);
			ins += "', ";
			ins += to_string(i);
			ins += ")";
			//cout << ins << endl;
			mysql_query(conn, ins.c_str());
		}
		return ;
	}
	void insert_teacher() {
		for (int i = 1; i <= 10; ++i) {
			string ins = "";
			ins += "INSERT INTO `teachers`";
			ins += "(`name`, `id`) ";
			ins += "VALUES(";
			ins += "'tname";
			ins += to_string(i);
			ins += "', ";
			ins += to_string(i);
			ins += ")";
			//cout << ins << endl;
			mysql_query(conn, ins.c_str());
		}
		return ;
		
	}
	void insert_class() {
		int id = 0;
		for (int i = 1; i <= 10; ++i) {
			for (int j = 1; j <= 30; ++j) {
				string ins = "";
				ins += "INSERT INTO `teaching_classes`";
				ins += "(`id`, `teacher_id`, `student_id`, `course_id`) ";
				ins += "VALUES(";
				ins += to_string(id++);
				ins += ", ";
				ins += to_string(i);
				ins += ", ";
				ins += to_string(j);
				ins += ", ";
				ins += to_string(i);
				ins += ")";
				//cout << ins << endl;
				mysql_query(conn, ins.c_str());
			}
		}
		return ;
	}
	void insert_score() {
		for (int i = 1; i <= 10; ++i) {
			for (int j = 1; j < 50; ++j) {
				string ins_score = "";
				ins_score += "INSERT INTO `scores`";
				ins_score += "(`course_id`, `student_id`, `score`) ";
				ins_score += "VALUES(";
				ins_score += to_string(i);
				ins_score += ", ";
				ins_score += to_string(j);
				ins_score += ", ";
				ins_score += to_string(55 + ((rand()&1) ? rand() % 30 : -(rand() % 20)));
				ins_score += ")";
				//cout << ins_score << endl;
				mysql_query(conn, ins_score.c_str());
			}
		}
	}



};
