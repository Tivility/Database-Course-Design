#include "application.h"
#include "create_db.h"
#include "create_table.h"
#include "defclass.h"
#include "update_course.h"
#include "update_score.h"
#include "update_student.h"
#include "update_teacher.h"
#include "rand_insert.h"


CreateDb		createDb;
CreateTable		createTable;
//UpdateCourse	updateCourse;
UpdateScore		updateScore;
UpdateStudent	updateStudent;
UpdateTeacher	updateTeacher;
Randinsert		randInsert;

bool ck_c() {
	char c = 0;
	puts ("*                    (y or n)                            *");
	puts ("*--------------------------------------------------------*");
	while (c != 'y' && c != 'n') {
		c = getchar();
	}
	return c == 'y';
}

void initSystem() {
	createDb.init();
	createTable.init();
	return ;
}

int main() {
	puts("**********************************************************");
	puts("*  SYSTEM START !!!!                                     *");
	puts("*  init the system?                                      *");
	puts("*  if you first in this system                           *");
	puts("*  please init the whole system                          *");
	if (ck_c()) {
		initSystem();
	}
	while (true) {
		puts("**********************************************************");
		puts("*  please input the function you want                    *");
		puts("*--------------------------------------------------------*");
		puts("*  1. auto insert random datas                           *");
		puts("*  2. movement of scores                                 *");
		puts("*  3. movement of students                               *");
		puts("*  4. movement of teachers                               *");
		puts("*  5. exit the system                                    *");
		int tmp1 = 0;
		while (tmp1 < 1 || tmp1 > 5) {
			cin >> tmp1;
		}
		/************************************
		if (tmp1 == 1) {
			updateCourse.init();
		}
		************************************/
		if (tmp1 == 1) {
			randInsert.init();
		}
		if (tmp1 == 2) {
			updateScore.init();
		}
		else if (tmp1 == 3) {
			updateStudent.init();
		}
		else if (tmp1 == 4) {
			updateTeacher.init();
		}
		else if (tmp1 == 5) {
			puts("**********************************************************");
			puts("*                                                        *");
			puts("*  SYSTEM END!!!!                                        *");
			puts("*                                                        *");
			puts("**********************************************************");
			break;
		}
	}
	return 0;
}
