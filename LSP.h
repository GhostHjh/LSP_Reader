#pragma once
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

using namespace std;

//UTF-8 ת GBK����
char* U2G(const char* utf8);

//GBK���� ת UTF-8����
char* G2U(const char* gb2312);


//LSP���ݿ���ؿ�
class LSP_SQLite
{
public:
	LSP_SQLite();
	~LSP_SQLite();

	//ϵͳʱ��ṹ����
	tm* local_time;

	//ʱ��У��
	string time_level();

	//���ݿ��Ƿ��ʼ����״̬
	int LSP_SQLite_db_status();

	//��ʼ��������
	int LSP_SQLite_db_NEW();

	//Ϊ ���� ���ʼ��
	int LSP_SQLtie_db_TABLE_book_NEW();

	//Ϊ �ϼ� ���ʼ��
	int LSP_SQLite_db_TABLE_set_NEW();

	//Ϊ ��Ƶ ���ʼ��
	int LSP_SQLite_db_TABLE_video_NEW();

	//Ϊ ��Ϸ ���ʼ��
	int LSP_SQLite_db_TABLE_game_NEW();

	//Ϊ ASMR ���ʼ��
	int LSP_SQLite_db_TABLE_asmr_NEW();

	//��ʱ
	void tmp();

	//���ַ����еĵ����ż�һ��������
	string ate_bug(string bug);
	

private:
	// MB/GB ��С
	int MB;
	int GB;

	//LSP������ļ���Ĭ�ϵ�·��
	string* LSP_path;

	//�����ļ����� �ļ�/�ļ��� ����
	vector<_finddata_t> LSP_SQLite_db_vector_book;
	
	//�ϼ��ļ����� �ļ�/�ļ��� ����
	vector<_finddata_t> LSP_SQLite_db_vector_set;
	vector<string> LSP_SQLite_db_vector_set_sort; //�ϼ� �ļ�/�ļ��� �����

	//��Ƶ�ļ����� �ļ�/�ļ��� ����
	vector<_finddata_t> LSP_SQLite_db_vector_video;
	vector<string> LSP_SQLite_db_vector_video_sort; //��Ƶ �ļ�/�ļ��� �����

	//��Ϸ�ļ����� �ļ�/�ļ��� ����
	vector<_finddata_t> LSP_SQLite_db_vector_game;

	//ASMR�ļ����� �ļ�/�ļ��� ����
	vector<_finddata_t> LSP_SQLite_db_vector_asmr;

	//��vector�����н���ȡ���� �ļ�/�ļ��� ��Ϣ����SQLite���ݿ�ָ���ı���
	int LSP_SQLite_db_vecot_goto_TABLE(vector<_finddata_t>& TABLE_vector, string TABLE_name);

	//��SQLite���ݿ�ָ���ı��л�ȡ���� �ļ�/�ļ��� ��Ϣ����vector����
	//int LSP_SQLite_db_TABLE_goto_TABLE(vector<_finddata_t>& TABLE_vector);

	//�ļ�������ɸѡ��������
	string LSP_Chinese_localization(string Folder_name);

	//��ʾ ��Ƶ�ļ� ������Ϣ
	//string video_all(string tmp_video_string);

	//���ݿ��Ƿ��ʼ��
	string LSP_SQLite_NEW_status;

	//SQLite���ݿ��ļ�����
	char* LSP_SQLite_db;

	//SQLite���ݿ�ʵ��
	sqlite3* LSP_SQL_SQLite;

	//SQLite���ݿ���
	sqlite3_stmt* LSP_SQL_Stmt;


	//��ȡָ��Ŀ¼�µ����� �ļ���/�ļ� ��һ��vector��
	int get_files_Folder_goto_vector(string path, vector<_finddata_t>& folder);

	//�����Ϊ �ļ��� ���� �ļ�
	string Folder_or_File(vector<_finddata_t>& tmp_vector, int tmp_int);
};
