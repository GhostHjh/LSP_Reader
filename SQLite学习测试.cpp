#include<iostream>
#include<thread>
#include<windows.h>
#include"sqlite3.h"

using namespace std;

char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

char* G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

int main(int arge, char* argv[])
{
	//创建一个数据库实例
	sqlite3* sqlite_tmp = nullptr;
	
	//设置数据库文件路径
	const char* sql_db = new char[8]{ "LSP.db" };

	//设置SQL语句
	const char* SQLite_SQL = new char[26]{"SELECT * FROM 数据库状态"};
	
	//stmt语句句柄
	sqlite3_stmt* sqlite_stmt_tmp = nullptr;

	//根据文件路径打开数据库
	//数据库文件的路径必须以c的字符串(char)传入
	int sql_result = sqlite3_open_v2(sql_db, &sqlite_tmp, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);
	
	//如果数据库不存在,则创建
	if (sql_result == SQLITE_OK)
	{
		cout << "数据库打开成功" << endl;
	}
	else
	{
		cout << "数据库打开失败" << endl;
	}

	//运行SQL语句, -1为自动计算sql语句长度
	int sql_result_sql = sqlite3_prepare_v2(sqlite_tmp, G2U(SQLite_SQL),-1, &sqlite_stmt_tmp, NULL);

	cout << "sql_result:\t" << sql_result << endl;
	cout << "sql_result_sql:\t" << sql_result_sql << endl;
	//运行sql语句是否成功,成功显示结果,失败报错
	if (sql_result_sql == SQLITE_OK)
	{
		cout << "查询语句OK!" << endl;

		//每调用一次  sqlite3_step()  函数,stmt语句句柄就会指向下一条记录
		while(sqlite3_step(sqlite_stmt_tmp) == SQLITE_ROW)
		{
			char* char_tmp = U2G((char*)sqlite3_column_text(sqlite_stmt_tmp, 0));
			//取出第0列字段的值
			cout << "状态:\t" << char_tmp << endl;
		}
		/*sqlite3_step(sqlite_stmt_tmp);
		cout << "名字:\t" << sqlite3_column_text(sqlite_stmt_tmp, 0) << endl;*/
	}
	else
	{
		cout << "SQL语句有问题!" << endl;
	}

	cout << "程序结束" << endl;
	//清除语句句柄
	sqlite3_finalize(sqlite_stmt_tmp);

	return 0;
}
