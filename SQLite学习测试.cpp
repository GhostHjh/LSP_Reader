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
	//����һ�����ݿ�ʵ��
	sqlite3* sqlite_tmp = nullptr;
	
	//�������ݿ��ļ�·��
	const char* sql_db = new char[8]{ "LSP.db" };

	//����SQL���
	const char* SQLite_SQL = new char[26]{"SELECT * FROM ���ݿ�״̬"};
	
	//stmt�����
	sqlite3_stmt* sqlite_stmt_tmp = nullptr;

	//�����ļ�·�������ݿ�
	//���ݿ��ļ���·��������c���ַ���(char)����
	int sql_result = sqlite3_open_v2(sql_db, &sqlite_tmp, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);
	
	//������ݿⲻ����,�򴴽�
	if (sql_result == SQLITE_OK)
	{
		cout << "���ݿ�򿪳ɹ�" << endl;
	}
	else
	{
		cout << "���ݿ��ʧ��" << endl;
	}

	//����SQL���, -1Ϊ�Զ�����sql��䳤��
	int sql_result_sql = sqlite3_prepare_v2(sqlite_tmp, G2U(SQLite_SQL),-1, &sqlite_stmt_tmp, NULL);

	cout << "sql_result:\t" << sql_result << endl;
	cout << "sql_result_sql:\t" << sql_result_sql << endl;
	//����sql����Ƿ�ɹ�,�ɹ���ʾ���,ʧ�ܱ���
	if (sql_result_sql == SQLITE_OK)
	{
		cout << "��ѯ���OK!" << endl;

		//ÿ����һ��  sqlite3_step()  ����,stmt������ͻ�ָ����һ����¼
		while(sqlite3_step(sqlite_stmt_tmp) == SQLITE_ROW)
		{
			char* char_tmp = U2G((char*)sqlite3_column_text(sqlite_stmt_tmp, 0));
			//ȡ����0���ֶε�ֵ
			cout << "״̬:\t" << char_tmp << endl;
		}
		/*sqlite3_step(sqlite_stmt_tmp);
		cout << "����:\t" << sqlite3_column_text(sqlite_stmt_tmp, 0) << endl;*/
	}
	else
	{
		cout << "SQL���������!" << endl;
	}

	cout << "�������" << endl;
	//��������
	sqlite3_finalize(sqlite_stmt_tmp);

	return 0;
}
