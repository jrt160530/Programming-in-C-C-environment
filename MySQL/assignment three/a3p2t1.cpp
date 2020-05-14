#include <iostream> 
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
using namespace std; 
  
class Passwd { 
 string user, pass, uid, gid, gecos, home, shell;
	int rec;
public: 

void setEntry(string u, string p, string ui, string gi, 
				string g, string h, string s, int j){
	user = u;
	pass = p;
	uid = ui;
	gid = gi;
	gecos = g;
	home = h;
	shell = s;
	rec = j;
		
				}

string printEntry(){
	ofstream myfile;
  	if(rec==0)
  		myfile.open ("a3p2task1.txt");	
	else 
		myfile.open ("a3p2task1.txt", std::ofstream::out | std::ofstream::app);
	myfile << "\nRecord " << rec;
	myfile << "\nuser: " << user;
	myfile << "\nuid: " << uid;
	myfile << "\ngid: " << gid;
	myfile << "\ngecos: " << gecos;
	myfile << "\nhome: " << home;
	myfile << "\nshell: " << shell << "\n";

	myfile.close();
	}
 
}; 

int j = 0;

static int callback(void *data, int argc, char **argv, char **azColName){
  	
	Passwd pwArray[58]; 

	ofstream myfile;

	int i = 0;
 	fprintf(stderr, "%s: ", (const char*)data);
   	
	pwArray[j].setEntry(argv[i],argv[i++],argv[i++],argv[i++],
      			argv[i++],argv[i++],argv[i++], j);
	
	
	pwArray[j].printEntry();
	j++;

  	printf("\n");
  	return 0;
	}	




int main(int argc, char* argv[]) {
	sqlite3 *db;			//points to sqlite3 database
   	char *zErrMsg = 0;
   	int rc;				//check return value 
   	const char *sql;			
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
cout << "test before";
  rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   cout << "test after";
  
  
  
  
  
  if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   return 0;
}