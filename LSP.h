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

//UTF-8 转 GBK编码
char* U2G(const char* utf8);

//GBK编码 转 UTF-8编码
char* G2U(const char* gb2312);


//LSP数据库相关库
class LSP_SQLite
{
public:
	LSP_SQLite();
	~LSP_SQLite();

	//系统时间结构变量
	tm* local_time;

	//时间校对
	string time_level();

	//数据库是否初始化的状态
	int LSP_SQLite_db_status();

	//初始化创建表
	int LSP_SQLite_db_NEW();

	//为 本子 表初始化
	int LSP_SQLtie_db_TABLE_book_NEW();

	//为 合集 表初始化
	int LSP_SQLite_db_TABLE_set_NEW();

	//为 视频 表初始化
	int LSP_SQLite_db_TABLE_video_NEW();

	//为 游戏 表初始化
	int LSP_SQLite_db_TABLE_game_NEW();

	//为 ASMR 表初始化
	int LSP_SQLite_db_TABLE_asmr_NEW();

	//临时
	void tmp();

	//将字符串中的单引号加一个单引号
	string ate_bug(string bug);
	

private:
	// MB/GB 大小
	int MB;
	int GB;

	//LSP软件各文件夹默认的路径
	string* LSP_path;

	//本子文件夹下 文件/文件夹 属性
	vector<_finddata_t> LSP_SQLite_db_vector_book;
	
	//合集文件夹下 文件/文件夹 属性
	vector<_finddata_t> LSP_SQLite_db_vector_set;
	vector<string> LSP_SQLite_db_vector_set_sort; //合集 文件/文件夹 的类别

	//视频文件夹下 文件/文件夹 属性
	vector<_finddata_t> LSP_SQLite_db_vector_video;
	vector<string> LSP_SQLite_db_vector_video_sort; //视频 文件/文件夹 的类别

	//游戏文件夹下 文件/文件夹 属性
	vector<_finddata_t> LSP_SQLite_db_vector_game;

	//ASMR文件夹下 文件/文件夹 属性
	vector<_finddata_t> LSP_SQLite_db_vector_asmr;

	//从vector容器中将获取到的 文件/文件夹 信息存入SQLite数据库指定的表中
	int LSP_SQLite_db_vecot_goto_TABLE(vector<_finddata_t>& TABLE_vector, string TABLE_name);

	//从SQLite数据库指定的表中获取到的 文件/文件夹 信息存入vector容器
	//int LSP_SQLite_db_TABLE_goto_TABLE(vector<_finddata_t>& TABLE_vector);

	//文件夹名称筛选出汉化组
	string LSP_Chinese_localization(string Folder_name);

	//显示 视频文件 基础信息
	//string video_all(string tmp_video_string);

	//数据库是否初始化
	string LSP_SQLite_NEW_status;

	//SQLite数据库文件名称
	char* LSP_SQLite_db;

	//SQLite数据库实例
	sqlite3* LSP_SQL_SQLite;

	//SQLite数据库句柄
	sqlite3_stmt* LSP_SQL_Stmt;


	//获取指定目录下的所有 文件夹/文件 到一个vector中
	int get_files_Folder_goto_vector(string path, vector<_finddata_t>& folder);

	//检测是为 文件夹 还是 文件
	string Folder_or_File(vector<_finddata_t>& tmp_vector, int tmp_int);
};
