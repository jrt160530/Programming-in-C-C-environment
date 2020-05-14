#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
/*This program writes sqlite3 table "passwd" to a file, formatted*/


int j = 0;		//for record #

/*callback takes each line from sqlite db and list each column on a new line and writes to file */
static int callback(void *data, int argc, char **argv, char **azColName){
  
	//file pointer
 	FILE *fp;
	
	//do not append if first line
	if(j==0)
		fp=fopen("a3p1task2.txt", "w");
   	else
		fp=fopen("a3p1task2.txt", "a");
  	
	int i;
 	fprintf(stderr, "%s: ", (const char*)data);
   
	//writes record # to file
	fprintf(fp,"\n\nRecord %d\n", j);
	//increment counter
	j++;

   	/*for each argument write column name and its value*/
	for(i = 0; i<argc; i++){
      	fprintf(fp, "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 	//write to file
  	 }

	fclose(fp);		//close file
  	printf("\n");
  	return 0;
	}	



int main(int argc, char* argv[]) {
	sqlite3 *db;			//points to sqlite3 database
   	char *zErrMsg = 0;
   	int rc;				//check return value 
   	char *sql;			
   	const char* data = "Entry successful";



   /* Open database */
   rc = sqlite3_open("passwd", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "SELECT * from pwtable";

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