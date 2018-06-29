//Grade Design
//create the class CreateDb
//Tivility 2018.06.27

#include "application.h"

class CreateDb {
public: 
	void init() {
		MYSQL *conn = NULL;
		conn = mysql_init(NULL);
		if (conn == NULL) {
			printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		if (mysql_real_connect(conn, "localhost", "root", "qwert",
								NULL, 0, NULL, 0) == NULL) {
			printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		if (mysql_query(conn, "create database grade")) {
			printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		mysql_close(conn);
		return ;
	}
private:

};
