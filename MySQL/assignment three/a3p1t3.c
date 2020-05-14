#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>

/*This program updates uid=48*/

int j = 0; //counter

static int callback(void *data, int argc, char **argv, char **azColName){
	
	/*file pointer*/
	FILE *fp;
	
	/*doesn't append if first line*/
	if(j==0)
		fp=fopen("a3p1task2.txt", "w");
   	else
		fp=fopen("a3p1task2.txt", "a");   

	int i;
   	fprintf(stderr, "%s: ", (const char*)data);
   
	
	//printf("\n\nRecord %d\n", j);
	//j++;

   	/*for each arg print column name and its value each on new line*/
	for(i = 0; i<argc; i++) {
      		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }

	fclose(fp);  
	printf("\n");
   	return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Entry Successful";

   /* Open database */
   rc = sqlite3_open("passwd", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
	
	/*first line selects entry with uid=48*/
	/*second line sends to callback for output*/
	sql = "SELECT * from pwtable where uid='48'";
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

   	/* Create merged SQL statement */
	/*updates gecos with string for uid=48*/
	/*then selects uid=48 to be sent to callback*/
   	sql = "UPDATE pwtable set gecos='My Apache Server for cs3377' where uid='48';"
        "SELECT * from pwtable where uid='48'";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   return 0;
}