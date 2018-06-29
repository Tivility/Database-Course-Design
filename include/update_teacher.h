//Grade Design
//create the class UpdateTeacher
//Tivility 2018.06.25

#include "defclass.h"
#include "application.h"


class UpdateTeacher {

public: 
	int init() {
		conn = mysql_init(NULL);
		mysql_real_connect(conn, "localhost", "root", "qwert", "grade", 0, NULL, 0);
		while (getin()) {
			if (search()) {
				puts ("**********************************************************");
				puts ("*        the teacher is already existed, delete?         *");
				if (ck_c()) {
					delete_thr();
					if (ck_break_update())
						break;
					else 	
						continue;
				}
				puts ("*        the teacher is already existed, update?         *");
				if (!ck_c()) {
					puts ("* not update!                                            *");
					if (ck_break_update())
						break;
					else 	
						continue;
				}
				if (update()) {
					puts ("* update finished                                        *");
				}
				else {
					puts ("* update failed                                          *");
				}
			}
			else {
				puts ("**********************************************************");
				puts ("*          the teacher is not in system, create?         *");
				if (!ck_c()) {
					puts ("* not create!                                            *");
					if (ck_break_update())
						break;
					else 	
						continue;
				}
				if (create()) {
					puts ("* create success!                                        *");
				}
				else {
					puts ("* create failed!                                         *");
				}
			}
			if (ck_break_update())
				break;
		}
		mysql_close(conn);
		puts ("**********************************************************");
		puts ("*                                                        *");
		puts ("*   TEACHER MODEL EXIT!!!!                               *");
		puts ("*                                                        *");
		puts ("**********************************************************");
		return 0;
	}

private: 
	Teacher teacher;

	MYSQL *conn;
	MYSQL_ROW *row;
	MYSQL_FIELD *field;
	MYSQL_RES *result;

	string title[5] = {
		"name",
		"id",
		"sex",
	};

	bool ck_break_update() {
		puts ("**********************************************************");
		puts ("*                   end this model?                      *");
		if (ck_c()) {
			return true;
		}
		puts ("**********************************************************");
		return false;
	}

	bool getin() {
		puts ("**********************************************************");
		puts ("*              movements of the teachers                 *");
		puts ("*  functions include query, creat, update, and delate    *");
		puts ("*--------------------------------------------------------*");
		puts ("*    please input the id of teachers you wanna check     *");
		puts ("*        (input 0 to exit this function model)           *");
		puts ("*--------------------------------------------------------*");
		teacher.init();
		bool ret = scanf("%d", &teacher.id);
		getchar();
		return ret;
	}

	bool search() {
		/**********
		SELECT `id` FROM `teacher` WHERE `id` = 3
		(result == NULL) means not exist
		**********/

		MYSQL_RES   *result  = NULL;
		MYSQL_FIELD *field   = NULL; 
		MYSQL_ROW    row     = NULL;

		int num_fields = 0, cnt = 0;
		bool ret = false;
		
		string s   = "SELECT * FROM `teachers` WHERE `id` = ";
		       s  += to_string(teacher.id);
		string sc  = "SELECT COUNT(*) FROM `teachers` WHERE `id` = ";
			   sc += to_string(teacher.id);

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
		puts ("");
		while (row = mysql_fetch_row(result)) {
			string tmps[10];
			for (int i = 0; i < num_fields; ++i) {
				printf ("%s\t", row[i] ? row[i] : "null");
				if (row[i]) //row[i] == NULL 
					tmps[i] = row[i];
			}
			puts ("");

			teacher.name			= tmps[0];
			if (tmps[2] != "")
				teacher.sex			= stoi(tmps[2]);
		}
		mysql_free_result(result);
		return true;
	}

	bool update() {
		/**********************************
		* update the teacher in databases *
		*  first use search to make sure  * 
		*  the teacher is already exist!  *
		***********************************/

		int fun = 0;
		string tmps = "";
		while (true) {
			string s = "";
			puts ("**********************************************************");
			puts ("*                   select the element                   *");
			puts ("*    1. name    3. sex   4. exit                         *");
			puts ("*--------------------------------------------------------*");
			scanf("%d", &fun);
			if (fun == 4) {
				puts ("exit update!");
				break;
			}
			if (fun < 1 || fun > 3 || fun == 2) continue;
			fun--;
			cout << "input the " << title[fun] << endl;
			cin >> tmps;

			//UPDATE `teachers` set `title` = `tmps` where `id` = teacher.id
			s += "UPDATE `teachers` SET `";
			s += title[fun];
			s += "` = ";
			if (fun == 0) s += '\'';
			s += tmps;
			if (fun == 0) s += '\'';
			s += " WHERE `id` = ";
			s += to_string(teacher.id);
			//cout << s << endl;
			if (!mysql_query(conn, s.c_str())) {
				puts ("update success!");
			}
			else {
				puts ("update failed!");
			}

		}
		return true;
	}

	bool cknu(string s) {
		return s != "NULL" && s != "null";
	}

	bool create() {
		/**************************************
		*    create a teacher in databases;    *
		*        to use this function,         *
		* make sure the teacher do not exist!! *
		***************************************/
		string tmps;
		puts ("**********************************************************");
		puts ("*                     please input                       *");
		puts ("* name:                                                  *");
		cin >> tmps; 	teacher.name = tmps;
		puts ("* sex :                                                  *");
		puts ("* 1. male   2.female                                     *");
		cin >> tmps;  
		if (tmps != "NULL")
			teacher.sex = stoi(tmps);
		puts ("**********************************************************");
		string thrname = teacher.name;
		//to_string(teacher.id);
		//`name`, `id`, `sex`, `admission`, `graduation`;

		string s = ""; 			s += "INSERT INTO `teachers`(`id`";
		if (cknu(teacher.name))	s += ", `name`";
		if (teacher.sex)		s += ", `sex`";
								s += ") VALUES(";
								s += to_string(teacher.id);
		if (cknu(teacher.name))	s += (", '"+ thrname + '\'');
		if (teacher.sex)		s += (", " + to_string(teacher.sex));
								s += ")";
		return !mysql_query(conn, s.c_str());
	}

	bool ck_c() {
		char c = 0;
		puts ("*                    (y or n)                            *");
		puts ("*--------------------------------------------------------*");
		while (c != 'y' && c != 'n') {
			c = getchar();
		}
		return c == 'y';
	}

	bool delete_thr() {
		//DELETE FROM `teachers` WHERE `id` = thr.id;
		puts ("**********************************************************");
		puts ("*             make sure to delete the teacher            *");
		if (!ck_c())
			return false;
		string s = "DELETE FROM `teachers` WHERE `id` = ";
		s += to_string(teacher.id);
		if (!mysql_query(conn, s.c_str())) {
			puts ("delete success!");
			return true;
		}
		else {
			puts ("delete failed!");
			return false;
		}

	}

};
