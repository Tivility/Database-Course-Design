//Grade Design
//create the class: UpdateScore
//Tivility 2018.06.27

#include "defclass.h"
#include "application.h"


class UpdateScore {

public: 
	int init() {
		conn = mysql_init(NULL);
		mysql_real_connect(conn, "localhost", "root", "qwert", "grade", 0, NULL, 0);
		
		int tar = 0;

		while (tar = getin()) {
			if (tar == 1) {								// insert score
				if (create()) {
					cout << "insert success" << endl;
				}
				else {
					cout << "insert failed" << endl;
				}
			}
			else if (tar == 2) {						// query score
				search();
			}
			else if (tar == 3) {						// delete score
				delete_sco();
			}
			else {
				puts("**********************************************************");
				puts("* exit the function model                                *");
				puts("* EXIT!!!!!                                              *");
				break;
			}
		}
		mysql_close(conn);

		return 0;

	}

private: 

	Score score;
	//course_id, student_id, contest_time, contest_name, score, full_score

	MYSQL *conn;
	MYSQL_ROW *row;
	MYSQL_FIELD *field;
	MYSQL_RES *result;

	string title[6] = {
		"name",
		"course_id",
		"student_id",
		"contest_time",
		"score",
		"full_score"
	};

	int getin() {
		puts("**********************************************************");
		puts("*   please input the function id :                       *");
		puts("*--------------------------------------------------------*");
		puts("*   1. insert score                                      *");
		puts("*   2. query score                                       *");
		puts("*   3. delete score                                      *");
		puts("*   4. exit                                              *");

		int tmp, ret;
		ret = (bool)(cin >> tmp);

		score.init();

		return ret ? tmp : ret;

	}

	bool search() {

		/***************************************************************
		*                                                              *
		*	select * from scores where student_id = ######             *
		*                                                              *
		*	select scores.* from scores, teaching_classes              *
		*	where(                                                     *
		*	`scores`.`student_id`=`teaching_classes`.`student_id` and  *
		*	`scores`.`course_id`=`teaching_classes`.`course_id` and    *
		*	`teaching_classes`.`teacher_id` = ######                   *
		*	);                                                         *
		*                                                              *
		*	select * from scores where score > #####                   *
		*                                                              *
		***************************************************************/

		
		puts("**********************************************************");
		puts("*    please input the function you want                  *");
		puts("*--------------------------------------------------------*");
		puts("*  1. search by student id                               *");
		puts("*  2. search by teacher id                               *");
		puts("*  3. search by student score below                      *");
		puts("*  4. search the max score by student id                 *");
		puts("*  5. exit                                               *");

		MYSQL_RES   *result  = NULL;
		MYSQL_FIELD *field   = NULL; 
		MYSQL_ROW    row     = NULL;

		int num_fields = 0, cnt = 0;

		bool ret = false;
		int tmp = 0, inid = 0;
		//cout << "tmp = " << tmp << endl;
		while (tmp < 1 || tmp > 5) {
			cin >> tmp;
			//cout << "tmp = " << tmp << endl;
		}

		//string s = "SELECT * FROM `scores` WHERE `` = " + to_string(student.id);
		//string sc = "SELECT COUNT(*) FROM `students` WHERE `id` = " + to_string(student.id);

		string st          = "SELECT ";
		string midstar     = "scores.* ";
		string midcnt      = "COUNT(*) ";
		string midwhere    = "FROM `scores` WHERE ";
		string midwhere_1  = "FROM `scores`, `teaching_classes` WHERE(";
		string fun1        = "`student_id`=";
		string fun2        = "`scores`.`student_id`=`teaching_classes`.";
			   fun2       += "`student_id` and `scores`.`course_id`=`teaching_classes`.";
			   fun2       += "`course_id` and `teaching_classes`.`teacher_id`=";
		string fun3        = "`score`<";
		string ed          = ")";
		string s           = st + midstar;
		string sc          = st + midcnt;

		if (tmp == 1) {
			inid = 0;
			puts("**********************************************************");
			while (inid == 0) {
				puts("*   please input the student id :                        *");
				cin >> inid;
			}
			s += (midwhere + fun1 + to_string(inid));
			sc += (midwhere + fun1 + to_string(inid));
		}
		else if (tmp == 2) {
			inid = 0;
			puts("**********************************************************");
			while (inid == 0) {
				puts("*   please input the teacher id :                        *");
				cin >> inid;
			}
			s += (midwhere_1 + fun2 + to_string(inid) + ed);
			sc += (midwhere_1 + fun2 + to_string(inid) + ed);
		}
		else if (tmp == 3) {
			inid = 0;
			puts("**********************************************************");
			while (inid == 0) {
				puts("*   please input the score :                             *");
				cin >> inid;
			}
			s += (midwhere + fun3 + to_string(inid));
			sc += (midwhere + fun3 + to_string(inid));
		}
		else if (tmp == 4) {
			inid = 0;
			puts("**********************************************************");
			while (inid == 0) {
				puts("*   please input the student id :                        *");
				cin >> inid;
			}
			s  = "SELECT * FROM `view1` WHERE `student_id`=" + to_string(inid);
			sc = "SELECT COUNT(*) FROM `view1` WHERE `student_id`=" + to_string(inid);
		}
		else {
			puts("exit search function!");
			return false;
		}

		//cout << "s = " << s << endl << "sc = " << sc << endl;

		mysql_query(conn, sc.c_str());

		result     = mysql_store_result(conn);
		num_fields = mysql_num_fields(result);
		string tmpres = mysql_fetch_row(result)[0];
		if (tmpres[0] == '0') { //not exist
			puts("    !!!! NOT FOUND !!!!    ");
			mysql_free_result(result);
			return false;
		}
		else { //free the count search 
			cout << "found " << tmpres << " data" << endl;
			mysql_free_result(result);
		}

		mysql_query(conn, s.c_str());
		result     = mysql_store_result(conn);
		num_fields = mysql_num_fields(result);

		while (field = mysql_fetch_field(result)) {
			printf ("%s\t", field->name);
		}
		puts("");
		while (row = mysql_fetch_row(result)) {
			string tmps[10];
			for (int i = 0; i < num_fields; ++i) {
				if (i == 1 || i == 2 || i == 3) 
					putchar('\t');
				printf ("%s\t", row[i] ? row[i] : "null");
				if (row[i]) //row[i] == NULL 
					tmps[i] = row[i];
			}
			puts("");
		}
		mysql_free_result(result);
		return true;
	}

	bool cknu(string s) {
		return s != "NULL";
	}

	bool create() {
		/**************************************
		*     create a score in databases;    *
		*        to use this function,         *
		* make sure the student do not exist!! *
		* course_id       int                  *
		* student_id      int                  *
		* contest_time    int                  *
		* name            string               *
		* score           int                  *
		* full_score      int                  *
		***************************************/
		string tmps;
		puts ("**********************************************************");
		puts ("*                     please input                       *");

		puts ("* student_id :                                           *");
		cin >> tmps;  
		if (tmps != "NULL")
			score.student_id = stoi(tmps);
		puts ("* course_id :                                            *");
		cin >> tmps;  
		if (tmps != "NULL")
			score.course_id = stoi(tmps);
		puts ("* contest_time :                                         *");
		cin >> tmps;  
		if (tmps != "NULL")
			score.contest_time = stoi(tmps);
		puts ("* name :  (contest name)                                 *");
		cin >> tmps;  
		if (tmps != "NULL")
			score.name = tmps;      
		puts ("* score :                                                *");
		cin >> tmps;  
		if (tmps != "NULL")
			score.score = stoi(tmps);
		puts ("* full_score :                                           *");
		cin >> tmps;  
		if (tmps != "NULL")
			score.full_score = stoi(tmps);
		puts ("**********************************************************");


		string s = ""; 			s += "INSERT INTO `scores`(`course_id`, `student_id`";
		if (score.contest_time)	s += ", `contest_time`";
		if (cknu(score.name))	s += ", `name`";
		if (score.score)      	s += ", `score`";     
		if (score.full_score)   s += ", `full_score`";
								s += ") VALUES(";
								s += to_string(score.course_id);
								s += ", ";
								s += to_string(score.student_id);
		if (score.contest_time)	s += (", " + to_string(score.contest_time));
		if (cknu(score.name))  	s += (", '"+ score.name + '\'');
		if (score.score)		s += (", " + to_string(score.score));
		if (score.full_score)   s += (", " + to_string(score.full_score));  
								s += ")";
		//cout << "s = " << s << endl;
		return !mysql_query(conn, s.c_str());
	}

	bool ck_c() {
		char c = 0;
		puts ("(y or n)");
		while (c != 'y' && c != 'n') {
			c = getchar();
		}
		return c == 'y';
	}

	bool delete_sco() {
		//DELETE FROM `students` WHERE(
		//    `student_id` = stuid and
		//    `course_id`  = curid)
		int stuid, curid;
		puts("**********************************************************");
		puts("*  please input the student id and the course id         *");
		puts("*--------------------------------------------------------*");
		puts("*  student id :                                          *");
		cin >> stuid;
		puts("*  course id :                                           *");
		cin >> curid;
		puts("**********************************************************");
		puts("*             make sure to delete this score             *");
		if (!ck_c())
			return false;
		string s  = "DELETE FROM `scores` WHERE (`student_id`=";
			   s += to_string(stuid);
			   s += " and `course_id`=";
			   s += to_string(curid);
			   s += ")";
		//cout << "s = " << s << endl;
		if (!mysql_query(conn, s.c_str())) {
			puts("delete success!");
			return true;
		}
		else {
			puts("delete failed!");
			return false;
		}

	}


};
