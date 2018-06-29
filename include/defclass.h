//Grade Design
//define the class
//Person : all people is person
//Student: students of classes
//Teacher: teachers of classes
//Tivility 2018.06.21
//course: 
//class;
//score;


#ifndef DB_DEFCLASS
#define DB_DEFCLASS

class Person {
public: 
	string name;
	int id;
	int sex;
	void init() {
		name = "";
		id = sex = 0;
		return ;
	}
private:

};

class Student : public Person {
public:
	int admission;
	int graduation;
	void init() {
		name = "";
		id = sex = admission = graduation = 0;
		return ;
	}
private: 

};

class Teacher : public Person {
public:
private:

};

class Course {
public: 
	int id;
	string name;
	void init() {
		id = 0;
		name = "";
		return ;
	}
private: 

};

class Teaching_class {
public: 
	int id;
	int teacher_id;
	int student_id;
	int start_time;
	int course_id;
	void init() {
		id = teacher_id = student_id = start_time = course_id = 0;
		return ;
	}
private: 

};

class Score {
public: 
	string name;
	int course_id;
	int student_id;
	int contest_time;
	int score;
	int full_score;
	void init() {
		course_id = student_id = contest_time = score = full_score = 0;
		name = "";
		return ;
	}
private:

};

#endif
