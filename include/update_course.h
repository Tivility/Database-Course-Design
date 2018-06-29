//Grade Design
//create the class UpdateCourse
//Tivility 2018.06.27

#include "defclass.h"
#include "application.h"


class UpdateCourse {

public: 
	int init() {
		conn = mysql_init(NULL);
		mysql_real_connect(conn, "localhost", "root", "qwert", "grade", 0, NULL, 0);
		while (getin()) {
			if (search()) {
				puts("**********************************************************");
				puts("*         the course is already existed, delete?         *");
				if (ck_c()) {
					delete_thr();
					continue;
				}
				puts("*         the course is already existed, update?         *");
				if (!ck_c()) {
					puts("* not update!                                            *");
					continue;
				}
				if (update()) {
					puts("* update finished                                        *");
				}
			}
			else {
				puts("**********************************************************");
				puts("*           the course is not in system, create?         *");
				if (!ck_c()) {
					puts("* not create!                                            *");
					continue;
				}
				if (create()) {
					puts("* create success!                                        *");
				}
				else {
					puts("* create failed!                                         *");
				}
			}
			puts("**********************************************************");
			puts("*                       end update?                      *");
			if (ck_c()) {
				puts("**********************************************************");
				puts("*                   FUNCTIN EXIT!                        *"); 
				puts("**********************************************************");
				break;
			}
			puts("**********************************************************");
		}
		mysql_close(conn);
		return 0;
	}

private: 
	Course course;
	//id, name

	MYSQL *conn;
	MYSQL_ROW *row;
	MYSQL_FIELD *field;
	MYSQL_RES *result;

	string title[5] = {
		"name",
		"id",
	};

	bool getin() {
		puts("**********************************************************");
		puts("*               movements of the courses                 *");
		puts("*  functions include query, creat, update, and delate    *");
		puts("**********************************************************");
		puts("*     please input the id of courses you wanna check     *");
		course.init();
		bool ret = scanf("%d", &course.id);
		getchar();
		return ret;
	}

	bool search() {
		/**********
		SELECT `id` FROM `course` WHERE `id` = 3
		(result == NULL) means not exist
		**********/

		MYSQL_RES   *result  = NULL;
		MYSQL_FIELD *field   = NULL; 
		MYSQL_ROW    row     = NULL;

		int num_fields = 0, cnt = 0;
		bool ret = false;
		
		string s = "SELECT * FROM `courses` WHERE `id` = " + to_string(course.id);
		string sc = "SELECT COUNT(*) FROM `courses` WHERE `id` = " + to_string(course.id);

		mysql_query(conn, sc.c_str());
		
		result     = mysql_store_result(conn);
		num_fields = mysql_num_fields(result);

		if (mysql_fetch_row(result)[0][0] == '0') { //not exist
			mysql_free_result(result);
			return false;
		}
		else { //free the count search 
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
				printf ("%s\t", row[i] ? row[i] : "null");
				if (row[i]) //row[i] == NULL 
					tmps[i] = row[i];
			}
			puts("");

			course.name			= tmps[0];
		}
		mysql_free_result(result);
		return true;
	}

	bool update() {
		/**********************************
		* update the course in databases  *
		*  first use search to make sure  * 
		*  the course is already exist!   *
		***********************************/

		int fun = 0;
		string tmps = "";
		while (true) {
			string s = "";
			puts("**********************************************************");
			puts("*                   select the element                   *");
			puts("*    1. name             2. exit                         *");
			puts("**********************************************************");
			scanf("%d", &fun);
			if (fun == 2) {
				puts("exit update!");
				break;
			}
			if (fun < 1 || fun > 2) continue;
			fun--;
			cout << "input the " << title[fun] << endl;
			cin >> tmps;

			//UPDATE `courses` set `title` = `tmps` where `id` = teacher.id
			s += "UPDATE `courses` SET `";
			s += title[fun];
			s += "` = ";
			if (fun == 0) s += '\'';
			s += tmps;
			if (fun == 0) s += '\'';
			s += " WHERE `id` = ";
			s += to_string(course.id);
			if (!mysql_query(conn, s.c_str())) {
				puts("update success!");
			}
			else {
				puts("update failed!");
			}

		}
		return true;
	}

	bool cknu(string s) {
		return s != "NULL" && s != "null";
	}

	bool create() {
		/**************************************
		*    create a course in databases;    *
		*        to use this function,        *
		* make sure the course do not exist!! *
		***************************************/
		string tmps;
		puts ("**********************************************************");
		puts ("*                     please input                       *");
		puts ("* name:                                                  *");
		cin >> tmps; 	course.name = tmps;
		puts ("**********************************************************");
		string corname = course.name;
		//to_string(course.id);
		//`name`, `id`, `sex`, `admission`, `graduation`;

		string s = ""; 			s += "INSERT INTO `courses`(`id`";
		if (cknu(course.name))	s += ", `name`";
								s += ") VALUES(";
								s += to_string(course.id);
		if (cknu(course.name))	s += (", '"+ corname + '\'');
								s += ")";
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

	bool delete_thr() {
		//DELETE FROM `courses` WHERE `id` = thr.id;
		puts("**********************************************************");
		puts("*              make sure to delete the course            *");
		if (!ck_c())
			return false;
		string s = "DELETE FROM `courses` WHERE `id` = ";
		s += to_string(course.id);
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
