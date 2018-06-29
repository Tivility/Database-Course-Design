//Grade Design
//create the class UpdateStudent
//Tivility 2018.06.27

#include "defclass.h"
#include "application.h"

class UpdateStudent {

public: 
	int init() {
		conn = mysql_init(NULL);
		mysql_real_connect(conn, "localhost", "root", "qwert", "grade", 0, NULL, 0);
		while (getin()) {
			if (search()) {
				puts ("**********************************************************");
				puts ("*        the student is already existed, delete?         *");
				if (ck_c()) {
					delete_stu();
					if (ck_break_update()) 
						break;
					else 
						continue;
				}
				puts ("*        the student is already existed, update?         *");
				if (!ck_c()) {
					puts ("* not update!                                            *");
					if (ck_break_update()) 
						break;
					else 
						continue;
				}
				else ; //update mpdel
				if (update()) {
					puts ("* update finished                                        *");
				}
				else {
					puts ("* update failed                                          *");
				}
			}
			else {
				puts ("**********************************************************");
				puts ("*          the student is not in system, create?         *");
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
		puts ("*   STUDENT MODEL EXIT!!!!                               *");
		puts ("*                                                        *");
		puts ("**********************************************************");

		return 0;
	}

private: 
	Student student;

	MYSQL *conn;
	MYSQL_ROW *row;
	MYSQL_FIELD *field;
	MYSQL_RES *result;

	string title[5] = {
		"name",
		"id",
		"sex",
		"admission",
		"graduation",
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
		puts ("*              movements of the students                 *");
		puts ("*  functions include query, creat, update, and delate    *");
		puts ("*--------------------------------------------------------*");
		puts ("*    please input the id of students you wanna check     *");
		puts ("*        (input 0 to exit this function model)           *");
		puts ("*--------------------------------------------------------*");
		student.init();
		bool ret = scanf("%d", &student.id);
		getchar();
		return ret && student.id;
	}

	bool search() {
		/**********
		SELECT `id` FROM `students` WHERE `id` = 3
		(result == NULL) means not exist
		**********/

		MYSQL_RES   *result  = NULL;
		MYSQL_FIELD *field   = NULL; 
		MYSQL_ROW    row     = NULL;

		int num_fields = 0, cnt = 0;
		bool ret = false;
		
		string s   = "SELECT * FROM `students` WHERE `id` = ";
			   s  += to_string(student.id);
		string sc  = "SELECT COUNT(*) FROM `students` WHERE `id` = ";
			   sc += to_string(student.id);

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
				if (i == 4) putchar('\t');
				printf ("%s\t", row[i] ? row[i] : "null");
				if (row[i]) //row[i] == NULL 
					tmps[i] = row[i];
			}
			puts ("");

			student.name			= tmps[0];
			if (tmps[2] != "")
				student.sex			= stoi(tmps[2]);
			if (tmps[3] != "")
				student.admission	= stoi(tmps[3]);
			if (tmps[4] != "")
				student.graduation	= stoi(tmps[4]);
		}
		mysql_free_result(result);
		return true;
	}

	bool update() {
		/**********************************
		* update the student in databases *
		*  first use search to make sure  * 
		*  the student is already exist!  *
		***********************************/

		int fun = 0;
		string tmps = "";
		while (true) {
			string s = "";
			puts ("**********************************************************");
			puts ("*                   select the element                   *");
			puts ("*  1. name  3. sex  4. admission  5. graduation  6. exit *");
			puts ("*--------------------------------------------------------*");
			scanf("%d", &fun);
			if (fun == 6) {
				puts ("exit update!");
				break;
			}
			if (fun < 1 || fun > 5 || fun == 2) continue;
			fun--;
			cout << "input the " << title[fun] << endl;
			cin >> tmps;

			//UPDATE `students` set `title` = `tmps` where `id` = student.id
			s += "UPDATE `students` SET `";
			s += title[fun];
			s += "` = ";
			if (fun == 0) s += '\'';
			s += tmps;
			if (fun == 0) s += '\'';
			s += " WHERE `id` = ";
			s += to_string(student.id);
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
		return s != "NULL";
	}

	bool create() {
		/**************************************
		*    create a student in databases;    *
		*        to use this function,         *
		* make sure the student do not exist!! *
		***************************************/
		string tmps;
		puts ("**********************************************************");
		puts ("*                     please input                       *");
		puts ("* name:                                                  *");
		cin >> tmps; 	student.name = tmps;
		puts ("* sex :                                                  *");
		puts ("* 1. male   2.female                                     *");
		cin >> tmps;  
		if (tmps != "NULL")
			student.sex = stoi(tmps);
		puts ("* admission year :                                       *");
		cin >> tmps;  
		if (tmps != "NULL")
			student.admission = stoi(tmps);
		puts ("* graduation year :                                      *");
		cin >> tmps;  
		if (tmps != "NULL")
			student.admission = stoi(tmps);
		puts ("**********************************************************");
		string stuname = student.name;
		//to_string(student.id);
		//`name`, `id`, `sex`, `admission`, `graduation`;

		string s = ""; 			s += "INSERT INTO `students`(`id`";
		if (cknu(student.name))	s += ", `name`";
		if (student.sex)		s += ", `sex`";
		if (student.admission)	s += ", `admission`";
		if (student.graduation) s += ", `graduation`";
								s += ") VALUES(";
								s += to_string(student.id);
		if (cknu(student.name))	s += (", '"+ stuname + '\'');
		if (student.sex)		s += (", " + to_string(student.sex));
		if (student.admission)	s += (", " + to_string(student.admission));
		if (student.graduation) s += (", " + to_string(student.graduation));
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

	bool delete_stu() {
		//DELETE FROM `students` WHERE `id` = stu.id;
		puts ("**********************************************************");
		puts ("*             make sure to delete the student            *");
		if (!ck_c())
			return false;
		string s = "DELETE FROM `students` WHERE `id` = ";
		s += to_string(student.id);
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
