#include<iostream>
#include<thread>
#include<string>
#include<regex>
#include<time.h>
#include<io.h>
#include<vector>
#include<Windows.h>
#include"sqlite3.h"
#include"MediaInfoDLL.h"
#include"LSP.h"

using namespace std;

int main(int arge, char* argv[])
{
	//tm *time_t = new tm;
	/*tmp += time_t->tm_year + '_' + time_t->tm_mon + '_' + time_t->tm_mday + '_' + time_t->tm_hour + '_' + time_t->tm_min + '_' + time_t->tm_sec;*/
	LSP_SQLite* SQL_main = new LSP_SQLite;
	int tmp = SQL_main->LSP_SQLite_db_NEW();
	

	
	cout << "\n\n当前时间:\t" << SQL_main->time_level() << endl << endl;

	SQL_main->LSP_SQLtie_db_TABLE_book_NEW();
	SQL_main->LSP_SQLite_db_TABLE_video_NEW();
	SQL_main->LSP_SQLite_db_TABLE_game_NEW();
	SQL_main->LSP_SQLite_db_TABLE_set_NEW();
	SQL_main->LSP_SQLite_db_TABLE_asmr_NEW();

	//cout << SQL_main->ate_bug("cc'ccccc");


	getchar();
	delete(SQL_main);
	return 0;
}
