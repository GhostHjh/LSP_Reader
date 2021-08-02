#include"LSP.h"

//int LSP_SQLite::NEW_TABLE()
//{
//	//创建不同的表用于储存需要的数据
//	string* NEW_TABLE_SQLite = new string[4];
//	NEW_TABLE_SQLite[0] = "CREATE TABLE 本子 ( ID INTEGER PRIMARY KEY NOT NULL, 作品名称 TEXT, 页数 INT, 汉化组 TEXT, 上次观看记录 TEXT, 是否显示 TEXT NOT NULL, 状态 TEXT );";
//	NEW_TABLE_SQLite[1] = "CREATE TABLE 视频 ( ID INTEGER PRIMAPY KEY NOT NULL, 作品名称 TEXT, 时长 INT, 汉化组 TEXT, 上次观看记录 TEXT, 是否显示 TEXT NOT NULL, 状态 TEXT );";
//	NEW_TABLE_SQLite[2] = "CREATE TABLE 合集 ( ID INTEGER PRIMAPY KEY NOT NULL, 作品名称 TEXT, 数量 INT, 汉化组 TEXT, 上次观看记录 TEXT, 是否显示 TEXT NOT NULL, 状态 TEXT );";
//	NEW_TABLE_SQLite[3] = "CREATE TABLE 数据库状态 ( 是否初始化	TEXT NOT NULL, 创建日期 TEXT NOT NULL, 最后保存日期 TEXT NOT NULL)";
//
//	//链接数据库
//	int sql_result = sqlite3_open_v2(LSP_SQLite_db, &LSP_SQL_SQLite, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);
//
//	//检测数据库是否打开成功
//	if (sql_result == SQLITE_OK)
//	{
//		cout << "数据库打开成功" << endl;
//	}
//	else
//	{
//		cout << "数据库打开失败" << endl;
//		return 0;
//	}
//
//	cout << "开始检测数据库是否完整" << endl;
//
//	//检测数据库是否完整
//	int int_sql = sqlite3_prepare_v2(LSP_SQL_SQLite, G2U((const char*)("SELECT 是否初始化 FROM 数据库状态")), -1, &LSP_SQL_Stmt, NULL);
//	if (int_sql == SQLITE_OK)
//	{
//		cout << "查询语句正常无误" << endl;
//		cout << sqlite3_column_text(LSP_SQL_Stmt, 0) << endl;
//
//		if ("yes" == U2G((char*)sqlite3_column_text(LSP_SQL_Stmt, 0)))
//		{
//			cout << endl << endl << "数据库已经完成了初始化" << endl;
//			SQL_NEW = 0;
//		}
//	}
//	else if (sqlite3_prepare_v2(LSP_SQL_SQLite, G2U("SELECT 是否初始化 FROM 数据库状态"), -1, &LSP_SQL_Stmt, NULL) != SQLITE_OK)
//	{
//		SQL_NEW = 1;
//	}
//	
//
//	if (SQL_NEW == 1)
//	{
//		cout << "开始对数据库进行初始化" << endl;
//
//		int int_tmp_re = sqlite3_prepare_v2(LSP_SQL_SQLite,G2U(NEW_TABLE_SQLite[0].data()), -1, &LSP_SQL_Stmt, NULL);
//
//		if (int_tmp_re == SQLITE_OK)
//			cout << endl << "数据库表 1 创建成功" << endl << endl;
//
//
//		sqlite3_finalize(LSP_SQL_Stmt);
//
//		for (int i = 1; i < 4 && int_tmp_re == SQLITE_OK; i++)
//		{
//			int_tmp_re = sqlite3_prepare_v2(LSP_SQL_SQLite, G2U(NEW_TABLE_SQLite[i].data()), -1, &LSP_SQL_Stmt, NULL);
//			
//
//			if (int_tmp_re == SQLITE_OK)
//				cout << "数据库表 " << i+1 << " 创建成功" << endl << endl;
//
//			sqlite3_finalize(LSP_SQL_Stmt);
//		}	
//	}
//
//	sqlite3_close(LSP_SQL_SQLite);
//	return 1;
//}
//返回系统时间给local_time结构变量

//本地时间初始化函数
string LSP_SQLite::time_level()
{
	time_t* now = new time_t;
	time(now);

	localtime_s(local_time, now);
	delete(now);

	return to_string(local_time->tm_year + 1900) + "_" + to_string(local_time->tm_mon + 1) + "_" + to_string(local_time->tm_mday) + "_" + to_string(local_time->tm_hour) + "_" + to_string(local_time->tm_min) + "_" + to_string(local_time->tm_sec);
}

//数据库是否完成初始化查询语句		成功: 0		失败: -1
int LSP_SQLite::LSP_SQLite_db_status()
{
	//SQL语句执行放回值
	int int_sql;

	//连接数据库
	if ((int_sql = sqlite3_open_v2(LSP_SQLite_db, &LSP_SQL_SQLite, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL)) == SQLITE_OK)
	{
		cout << "数据库\t\t连接成功" << endl;

		//判断数据库是否已经完成初始化一(保险)
		if ((int_sql = sqlite3_prepare_v2(LSP_SQL_SQLite, G2U("SELECT * FROM 数据库状态"), -1, &LSP_SQL_Stmt, NULL)) == SQLITE_OK)
		{
			cout << "数据库\t\t查询语句成功" << endl;

			//获取结果
			sqlite3_step(LSP_SQL_Stmt);
			LSP_SQLite_NEW_status = U2G((char*)sqlite3_column_text(LSP_SQL_Stmt, 0));

			//判断该数据库是否初始化结果是否为yes
			if ("yes" == LSP_SQLite_NEW_status)
			{
				cout << "数据库\t\t已经完成初始化" << endl << endl;

				//清除上一条SQL语句执行结果,  关闭SQLite句柄
				sqlite3_finalize(LSP_SQL_Stmt);
				sqlite3_close(LSP_SQL_SQLite);
				return 0;
			}
			//为初始化返回 0
			else
			{
				cout << "数据库\t\t未完成初始化" << endl << endl;

				LSP_SQLite_NEW_status = "no";
				//清除上一条SQL语句执行结果,  关闭SQLite句柄
				sqlite3_finalize(LSP_SQL_Stmt);
				sqlite3_close(LSP_SQL_SQLite);
				return -1;
			}		
		}
		//数据库查询失败返回 0
		else
		{
			cout << "数据库\t\t查询语句失败" << endl;

			//清除上一条SQL语句执行结果,  关闭SQLite句柄
			sqlite3_close(LSP_SQL_SQLite);
			return -1;
		}
	}		
	else
	{
		cout << "数据库\t\t连接失败" << endl;

		return -1;
	}

}


//数据库初始化语句
int LSP_SQLite::LSP_SQLite_db_NEW()
{
	//创建不同的表用于储存需要的数据
	string* NEW_TABLE_SQLite = new string[8];
	NEW_TABLE_SQLite[0] = "CREATE TABLE 本子 ( ID INTEGER PRIMARY KEY AUTOINCREMENT, 作品名称 TEXT, 页数 INT, 汉化组 TEXT, 上次观看记录 TEXT, 作品封面 TEXT, 是否显示 TEXT NOT NULL, 状态 TEXT );";
	NEW_TABLE_SQLite[1] = "CREATE TABLE 视频 ( ID INTEGER PRIMARY KEY AUTOINCREMENT, 作品名称 TEXT, 时长 INT, 分类 TEXT, 上次观看记录 TEXT, 作品封面 TEXT, 是否显示 TEXT NOT NULL, 状态 TEXT );";
	NEW_TABLE_SQLite[2] = "CREATE TABLE 合集 ( ID INTEGER PRIMARY KEY AUTOINCREMENT, 作品名称 TEXT, 数量 INT, 分类 TEXT, 上次观看记录 TEXT, 是否显示 TEXT NOT NULL, 状态 TEXT );";
	NEW_TABLE_SQLite[3] = "CREATE TABLE 游戏 ( ID INTEGER PRIMARY KEY AUTOINCREMENT, 作品名称 TEXT, 大小 INT, 汉化组 TEXT, 上次启动记录 TEXT, 作品封面 TEXT, 是否显示 TEXT NOT NULL, 状态 TEXT );";
	NEW_TABLE_SQLite[4] = "CREATE TABLE ASMR ( ID INTEGER PRIMARY KEY AUTOINCREMENT, 作品名称 TEXT, 时长 INT, 语言 TEXT, 上次观看记录 TEXT, 是否显示 TEXT NOT NULL, 状态 TEXT );";
	NEW_TABLE_SQLite[5] = "CREATE TABLE 数据库状态 ( 是否初始化	TEXT NOT NULL, 本子路径 TEXT, 视频路径 TEXT, 合集路径 TEXT, 游戏路径 TEXT, ASMR路径 TEXT, 创建日期 TEXT NOT NULL, 最后保存日期 TEXT NOT NULL)";
	NEW_TABLE_SQLite[6] = "INSERT INTO 数据库状态 (是否初始化, 创建日期, 最后保存日期) VALUES ( \'yes\', \'";
	NEW_TABLE_SQLite[6] += time_level();
	NEW_TABLE_SQLite[6] += "\', \'";
	NEW_TABLE_SQLite[6] += time_level();
	NEW_TABLE_SQLite[6] += "\');";
	NEW_TABLE_SQLite[7] = "INSERT INTO 数据库状态 ( 本子路径, 合集路径, 视频路径, 游戏路径, ASMR路径) VALUES ( \'";
	NEW_TABLE_SQLite[7] += LSP_path[0] + "\', \'" + LSP_path[1] + "\', \'" + LSP_path[2] + "\', \'" + LSP_path[3] + "\', \'" + LSP_path[4] + "\' )";
	//LSP_path = new string[5]{ "E:/英雄时刻/个人/本子", "E:/英雄时刻/个人/合集", "E:/英雄时刻/个人/视频", "E:/英雄时刻/个人/Game", "E:/英雄时刻/个人/ASMR" };
	
	//SQL语句执行放回值
	int int_sql;
	
	//显示数据库初始化状态 yes OR no
	//cout << endl << endl << LSP_SQLite_NEW_status << endl << endl;

	//连接数据库
	if ( (int_sql = sqlite3_open_v2(LSP_SQLite_db, &LSP_SQL_SQLite, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL) ) == SQLITE_OK)
	{
		//SQLite3_exec()函数运行错误信息
		char* no_log = new char[128];

		cout << "数据库连接成功" << endl;

		//判断数据库是否已经完成初始化(保险)
		if ("no" == LSP_SQLite_NEW_status)
		{
			for (int i = 0; i < 8 && int_sql == SQLITE_OK; i++)
			{
				int_sql = sqlite3_exec(LSP_SQL_SQLite, G2U(NEW_TABLE_SQLite[i].c_str()), NULL, NULL, &no_log);
				cout << "第\t" << i + 1 << "\t个建表语句运行成功" << endl;
				cout << NEW_TABLE_SQLite[i] << endl << endl;
			}
			//关闭数据库连接
			sqlite3_close(LSP_SQL_SQLite);
			return 0;
		}
		else if ("no" != LSP_SQLite_NEW_status)
		{
			//关闭数据库连接
			sqlite3_close(LSP_SQL_SQLite);
			return -1;
		}
		//释放SQLite3_exec()函数运行错误信息
		delete[](no_log);
	}	
	else
	{
		cout << "数据库连接失败" << endl;

		return -1;
	}
}

//临时使用
void LSP_SQLite::tmp()
{
	for (int i = 0; i < LSP_SQLite_db_vector_book.size(); i++)
	{
		cout << "文件夹名称为:\t" << LSP_SQLite_db_vector_book[i].name << endl;
	}
}

//获取指定目录下的所有 文件夹/文件 到一个vector中
int LSP_SQLite::get_files_Folder_goto_vector(string path, vector<_finddata_t>& folder)
{
	cout << "\n开始运行\t" << path << "\t文件夹下 文件/文件夹 查找程序\n";
	//临时路径存放字符串
	string* tmp = new string;
	
	/*_finddata_t 为<io.h>库自带数据结构
	struct _finddata_t
	{
		unsigned attrib;		文件属性的储存位置,存储一个unsigned单元
		time_t time_create;		文件从1970_1_1保存到现在的时间
		time_t time_access;		文件最后一次被访问的时间
		time_t time_write;		文件最后一次被修改的时间
		_fsize_t size;			文件大小
		char name[_MAX_FNAME];	文件名称
	};*/
	_finddata_t* fileinfo = new _finddata_t;
	

	//intptr_t和uintptr_t的类型:typedef long int； typedef unsigned long int 
	//assign()函数：先将原字符串清空，然后赋予新的值作替换, append()函数: 拼接字符串, c_str()函数: 以char*的方式放回string字符串
	//_findfirst()函数: 第一个参数为文件名称,第二个参数是 _finddate 结构体指针, 如果查找成功则放回文件句柄,失败返回-1
	intptr_t hFiles = _findfirst(tmp->assign(path).append("/*").c_str(), fileinfo);

	/*cout << "\n当前拼接字符串为\t:" << *tmp << endl
		<< "当前 _findfirst 运行代码:\t" << hFiles << endl << endl;*/

	if (hFiles != -1)
	{
		cout << "此文件夹是\t" << path << "\t文件夹\n\n";

		//_findnext()函数接受两个参数, 第一个为文件句柄(long类型), 第二个为 _finddata_t结构体指针, 成功返回 0 , 失败返回 -1
		while (_findnext(hFiles, fileinfo) == 0)
		{	
			//strcmp()函数用于比较两个字符串, str1<str2 则 值小于0, str1>str2 则 值>0, str1=str2 则 值=0
			//这里的if判断为判断现在的文件并不是 .. 或者 . 这两个文件
			if (strcmp(fileinfo->name, ".") != 0 && strcmp(fileinfo->name, "..") != 0)
			{
				folder.push_back(*fileinfo);
			}
		}

		delete(fileinfo);
		delete(tmp);

		return 0;
	}
	else
	{
		cout << "此文件夹不是\t" << path << "\t文件夹" << endl;
		delete(fileinfo);
		delete(tmp);

		return -1;
	}

	delete(tmp);
	delete(fileinfo);
	cout << "\n\n结束运行 文件/文件夹 查找" << endl;
	return 0;
}

//检测是为 文件夹 还是 文件
string LSP_SQLite::Folder_or_File(vector<_finddata_t>& tmp_vector, int tmp_int)
{
	if (tmp_vector[tmp_int].attrib == 32)
	{
		//cout << "\t视频时长为:";
		return "文件";
	}	
	else if (tmp_vector[tmp_int].attrib == 16)
		return "文件夹";
	else
		return "未知";
}


//从vector容器中将获取到的 文件/文件夹 信息存入SQLite数据库指定的表中
int LSP_SQLite::LSP_SQLite_db_vecot_goto_TABLE(vector<_finddata_t>& TABLE_vector, string TABLE_name)
{
	//连接数据库
	if (!(sqlite3_open_v2(LSP_SQLite_db, &LSP_SQL_SQLite, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL) == SQLITE_OK))
		return -1;

	//用于执行的SQL语句
	string* SQL = new string;

	//用于储存sqlite_exec()错误信息
	char* no_log = new char[1024];

	//用于临时存储存储文件夹内文件信息
	vector<_finddata_t> tmp_folder;

	
	//用于临时储存文件夹名称的string变量
	string tmp_path;

	//针对不同的参数运行不同的
	if ("本子" == TABLE_name)  
	{
		for (int i = 0; i < TABLE_vector.size(); i++)
		{
			//设置临时地址为指定地址
			tmp_path = LSP_path[0] + "/" + TABLE_vector[i].name;

			get_files_Folder_goto_vector(tmp_path, tmp_folder);
			*SQL = "INSERT INTO " + TABLE_name + " ( 作品名称, 页数, 汉化组, 作品封面, 是否显示, 状态 )" + " VALUES ( \'" + TABLE_vector[i].name + "\', " + to_string(tmp_folder.size()) + ", \'" + LSP_Chinese_localization(TABLE_vector[i].name) + "\', \'" + tmp_path + "/" + tmp_folder[0].name + "\', \'yes\', \'正常\' );";

			//显示运行的SQL语句
			//cout << *SQL << endl << endl;

			//运行sql语句
			if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
			{
				cout << endl << "SQL语句运行失败" << endl;
				cout << U2G(no_log) << endl;

				cout << "测试使用双引号运行SQL语句" << endl;
				*SQL = "INSERT INTO " + TABLE_name + " ( 作品名称, 页数, 汉化组, 是否显示, 状态 )" + " VALUES ( \"" + TABLE_vector[i].name + "\", " + to_string(tmp_folder.size()) + ", \'" + LSP_Chinese_localization(TABLE_vector[i].name) + "\', \"" + tmp_path + "/" + tmp_folder[0].name + "\", \'yes\', \'正常\' );";
				cout << *SQL << endl;

				if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
					cout << "依旧运行失败,请查看日志" << endl << endl;
				else
					cout << "使用双引号运行SQL语句成功" << endl << endl;
			}
		}
	}	
	else if ("合集" == TABLE_name)
	{
		for (int i = 0; i < LSP_SQLite_db_vector_set.size(); i++)
		{
			//设置临时地址为合集根目录+当前文件夹
			tmp_path = LSP_path[1] + "/" + LSP_SQLite_db_vector_set_sort[i] + "/" + TABLE_vector[i].name;

			//就行子文件夹查询
			if (get_files_Folder_goto_vector(tmp_path, tmp_folder) != 0)
			{
				cout << "运行子文件夹数量查询失败!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
					<< "子文件夹名称:\t" << tmp_path << endl;
			}

			*SQL = "INSERT INTO " + TABLE_name + " ( 作品名称, 数量, 分类, 是否显示, 状态 )" + " VALUES ( \'" + TABLE_vector[i].name + "\', " + to_string(tmp_folder.size()) + ", \'" + LSP_SQLite_db_vector_set_sort[i] + "合集\', \'yes\', \'正常\' );";

			//输出运行的SQL语句
			//cout << *SQL << endl << endl;

			//运行sql语句
			if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
			{
				cout << endl << "SQL语句运行失败" << endl;
				cout << U2G(no_log) << endl;

				cout << "测试使用双引号运行SQL语句" << endl;
				*SQL = "INSERT INTO " + TABLE_name + " ( 作品名称, 数量, 分类, 是否显示, 状态 )" + " VALUES ( \"" + TABLE_vector[i].name + "\", " + to_string(tmp_folder.size()) + ", \'" + LSP_SQLite_db_vector_set_sort[i] + "合集\', \'yes\', \'正常\' );";
				cout << *SQL << endl;

				if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
					cout << "依旧运行失败,请查看日志" << endl << endl;
				else
					cout << "使用双引号运行SQL语句成功" << endl << endl;
			}
			else
				cout << "作品:\t" << TABLE_vector[i].name << "\t存入数据库成功\n\n";
		}
	}
	else if ("视频" == TABLE_name)
	{
		for (int i = 0; i < TABLE_vector.size(); i++)
		{
			//判断当前要存入数据库的是不是文件夹,如果是改分类为 xxx分类合集,否则改为 xxx分类视频.
			if (Folder_or_File(TABLE_vector, i) == "文件夹")
			{
				//设置临时地址为合集根目录
				tmp_path = LSP_path[2] + "/" + LSP_SQLite_db_vector_video_sort[i] + "/" + TABLE_vector[i].name;

				//就行子文件夹查询
				if (get_files_Folder_goto_vector(tmp_path, tmp_folder) != 0)
				{
					cout << "运行子文件夹数量查询失败!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
						<< "子文件夹名称:\t" << tmp_path << endl;
				}

				//更改分类名称
				LSP_SQLite_db_vector_video_sort[i] += "视频合集";
			}
			else if (Folder_or_File(TABLE_vector, i) == "文件")
				LSP_SQLite_db_vector_video_sort[i] += "视频";
			else
				LSP_SQLite_db_vector_video_sort[i] += "未知";

			*SQL = "INSERT INTO " + TABLE_name + " ( 作品名称, 时长, 分类, 作品封面, 是否显示, 状态 )" + " VALUES ( \'" + TABLE_vector[i].name + "\', " + to_string(tmp_folder.size()) + ", \'" + string(LSP_SQLite_db_vector_video_sort[i]) + "\', \'" + tmp_path + "/" + tmp_folder[0].name + "\', \'yes\', \'正常\' );";

			//显示运行的SQL语句
			//cout << *SQL << endl << endl;

			//运行sql语句
			if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
			{
				cout << endl << "SQL语句运行失败" << endl;
				cout << U2G(no_log) << endl;

				cout << "测试使用双引号运行SQL语句" << endl;
				*SQL = "INSERT INTO " + TABLE_name + " ( 作品名称, 时长, 分类, 作品封面, 是否显示, 状态 )" + " VALUES ( \"" + TABLE_vector[i].name + "\", " + to_string(tmp_folder.size()) + ", \'" + string(LSP_SQLite_db_vector_video_sort[i]) + "\', \"" + tmp_path + "/" + tmp_folder[0].name + "\", \'yes\', \'正常\' );";
				cout << *SQL << endl;

				if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
					cout << "依旧运行失败,请查看日志" << endl << endl;
				else
					cout << "使用双引号运行SQL语句成功" << endl << endl;
			}
			else
				cout << "作品:\t" << TABLE_vector[i].name << "\t成功存入数据库" << endl;
		}
	}	
	else if ("游戏" == TABLE_name)
	{
		for (int i = 0; i < TABLE_vector.size(); i++)
		{
			//get_files_Folder_goto_vector(tmp_path, tmp_folder);
			*SQL = "INSERT INTO " + TABLE_name + " ( 作品名称, 大小, 作品封面, 是否显示, 状态 )" + " VALUES ( \'" + TABLE_vector[i].name + "\', " + to_string(TABLE_vector[i].size / MB) + ", \'" + LSP_path[3] + "/" + TABLE_vector[i].name + "\', \'yes\', \'正常\' );";

			//显示运行的SQL语句
			//cout << *SQL << endl << endl;

			//运行sql语句
			if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
			{
				cout << endl << "SQL语句运行失败" << endl;
				cout << U2G(no_log) << endl;

				cout << "测试使用双引号运行SQL语句" << endl;
				*SQL = "INSERT INTO "+ TABLE_name + " ( 作品名称, 大小, 作品封面, 是否显示, 状态 )" + " VALUES ( \"" + TABLE_vector[i].name + "\", " + to_string(TABLE_vector[i].size / MB) + ", \"" + LSP_path[3] + "/" + TABLE_vector[i].name + "\", \'yes\', \'正常\' );";
				cout << *SQL << endl;

				if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
					cout << "依旧运行失败,请查看日志" << endl << endl;
				else
					cout << "使用双引号运行SQL语句成功" << endl << endl;
			}
		}
	}
	else if ("ASMR" == TABLE_name)
		tmp_path = LSP_path[4];
	else
		return -1;			

	//释放内存
	delete[](no_log);//释放用于储存sqlite_exec()错误信息
	vector<_finddata_t>().swap(tmp_folder);//清空临时用于存储文件夹的vector容器

	//检测内存释放情况
	if (tmp_folder.size() == 0 && no_log == nullptr)
		return 0;
	else
	{
		if (tmp_folder.size() != 0)
		{
			cout << "储存临时文件夹vector容器释放失败!!!!!!!!!!!!!" << endl;
		}
		else if (no_log != nullptr)
		{
			cout << "用于存储SQLite_exec()运行的SQL语句错误信息释放失败!!!!!!!!" << endl;
		}

		return -1;
	}

	//断开数据库连接
	sqlite3_close(LSP_SQL_SQLite);
	delete(SQL);
	return 0;
}


//文件夹名称筛选出汉化组
string LSP_SQLite::LSP_Chinese_localization(string tmp_Folder_name)
{
	//getline(cin, tmp_Folder_name);
	string Folder_name = "暂无汉化组信息";

	//一号筛选规则
	regex tmp_regex_1("\\](.*?)(汉化|漢化|翻译|翻訳|日语社)(.*?)\\]");//有效  
	regex tmp_regex__1_1("\\[(.*?)(汉化|漢化|翻译|翻訳|日语社)(.*?)\\]");

	//二号筛选规则
	regex tmp_regex_2("\\)(.*?)(汉化|漢化|翻译|翻訳|日语社)(.*?)\\)");//有效  
	regex tmp_regex__2_1("\\((.*?)(汉化|漢化|翻译|翻訳|日语社)(.*?)\\)");

	//三号规则
	regex tmp_regex_3("\\[(.*?)(汉化|漢化|翻译|翻訳|日语社)(.*?)\\]");

	//四号规则
	regex tmp_regex_4("\\((.*?)(汉化|漢化|翻译|翻訳|日语社)(.*?)\\)");

	//临时存储正则完的名称
	smatch tmp_smatch_Folder_name;
	if (regex_search(tmp_Folder_name, tmp_smatch_Folder_name, tmp_regex_1) && Folder_name == "暂无汉化组信息")
	{
		Folder_name = tmp_smatch_Folder_name[0];
		//cout << "规则 1 运行成功,当前字符串:\t" << Folder_name << endl;

		if (regex_search(Folder_name, tmp_smatch_Folder_name, tmp_regex__1_1))
			Folder_name = tmp_smatch_Folder_name[0];
	}
	
	if (regex_search(tmp_Folder_name, tmp_smatch_Folder_name, tmp_regex_2) && Folder_name == "暂无汉化组信息")
	{
		Folder_name = tmp_smatch_Folder_name[0];
		//cout << "规则 2 运行成功,当前字符串:\t" << Folder_name << endl;

		if (regex_search(Folder_name, tmp_smatch_Folder_name, tmp_regex__2_1))
			Folder_name = tmp_smatch_Folder_name[0];
	}
	
	if (regex_search(tmp_Folder_name, tmp_smatch_Folder_name, tmp_regex_3) && Folder_name == "暂无汉化组信息")
		Folder_name = tmp_smatch_Folder_name[0];
		//cout << "规则 3 运行成功,当前字符串:\t" << Folder_name << endl;
	else if (regex_search(tmp_Folder_name, tmp_smatch_Folder_name, tmp_regex_4))
		Folder_name = tmp_smatch_Folder_name[0];
		//cout << "规则 4 运行成功,当前字符串:\t" << Folder_name << endl;
	

	return string(Folder_name);
}

//获取 视频文件 基本信息
//string LSP_SQLite::video_all(string tmp_video_string)
//{
//	char* tmp_char = new char[tmp_video_string.size()];
//	memcpy(tmp_char, tmp_video_string.c_str(), tmp_video_string.size());
//
//	MediaInfoDLL::MediaInfo MI;
//	MediaInfoDLL::String files_name;
//	MI.Open();
//
//	return string();
//}

//数据库 本子 表初始化
int LSP_SQLite::LSP_SQLtie_db_TABLE_book_NEW()
{
	//获取指定目录下的所有 文件夹/文件 到一个vector中
	if (get_files_Folder_goto_vector(LSP_path[0], LSP_SQLite_db_vector_book) == 0)
		LSP_SQLite_db_vecot_goto_TABLE(LSP_SQLite_db_vector_book, "本子"); 
	else
	{
		cout << "\n\n\n指定目录下 文件夹/文件 写入vector失败!!!!!!!\n\n\n";
		return -1;
	}
		
	
	return 0;
}


//数据库 视频 表初始化
//int LSP_SQLite::LSP_SQLite_db_TABLE_video_NEW()
//{
//	if (get_files_Folder_goto_vector(LSP_path[2], LSP_SQLite_db_vector_video) == 0)
//	{
//		int* Folder_2_3_yes = new int(0);
//
//		//判断文件夹结构是否是 视频----> 二次元&&三次元
//		for (int i = 0; i < LSP_SQLite_db_vector_video.size() && *Folder_2_3_yes != 2; i++)
//		{
//			if (strcmp(LSP_SQLite_db_vector_video[i].name, "二次元") || strcmp(LSP_SQLite_db_vector_video[i].name, "三次元"))
//				(*Folder_2_3_yes)++;
//
//			//如果文件夹结构是否是 视频----> 二次元&&三次元
//			if (*Folder_2_3_yes == 2)
//			{
//				//临时视频文件夹vector
//				vector<_finddata_t>().swap(LSP_SQLite_db_vector_video);
//
//				//临时视频文件夹路径
//				string tmp_Folder_path = LSP_path[2] + "/二次元";
//
//				cout << "临时视频文件夹路径为:" << tmp_Folder_path << endl;
//
//				//获取临时视频文件夹路径下的文件/文件夹到临时文件夹vector
//				if (get_files_Folder_goto_vector(tmp_Folder_path, LSP_SQLite_db_vector_video) != 0)
//					return -1;
//
//				//临时视频文件夹路径更改
//				tmp_Folder_path = LSP_path[2] + "/三次元";
//
//				//获取新的临时视频文件夹路径下的文件/文件夹到临时文件夹vector
//				if (get_files_Folder_goto_vector(tmp_Folder_path, LSP_SQLite_db_vector_video) != 0)
//					return -1;
//			}
//		}
//
//		if (*Folder_2_3_yes != 2)
//		{
//			if (get_files_Folder_goto_vector(LSP_path[2], LSP_SQLite_db_vector_video) != 0)
//				return -1;
//		}
//
//		delete(Folder_2_3_yes);
//	}
//	LSP_SQLite_db_vecot_goto_TABLE(LSP_SQLite_db_vector_video, "视频");
//	get_files_Folder_goto_vector(LSP_path[2], LSP_SQLite_db_vector_video);
//
//	
//	return 0;
//}

//数据库 视频 表初始化
int LSP_SQLite::LSP_SQLite_db_TABLE_video_NEW()
{
	//临时存储路径
	vector<_finddata_t> tmp_voide_path;

	//判断文件夹是否存放成功
	if (get_files_Folder_goto_vector(LSP_path[2], tmp_voide_path) == 0)
	{
		for (int i = 0; i < tmp_voide_path.size(); i++)
		{
			cout << "当前分类文件夹为:\t" << tmp_voide_path[i].name << endl;

			if (get_files_Folder_goto_vector(LSP_path[2] + "/" + tmp_voide_path[i].name, LSP_SQLite_db_vector_video) == 0)
			{	
				cout << "开始列出分类文件夹 " << tmp_voide_path[i].name << " 中的子文件夹" << endl;
				for (int o = 0; o < LSP_SQLite_db_vector_video.size(); o++)
				{
					//设置第 o 个 视频文件/文件夹 的类别
					LSP_SQLite_db_vector_video_sort.push_back(string(tmp_voide_path[i].name));

					//debug测试数据是否正常
					/*cout << "名称:\t" << LSP_SQLite_db_vector_video[o].name << endl
						<< "文件夹/文件 :\t" << Folder_or_File(LSP_SQLite_db_vector_video, o) << endl
						<< "类别为;\t" << LSP_SQLite_db_vector_video_sort[o] << endl << endl;	*/				
				}
			}
		}
	}
	else
	{
		cout << "运行获取 视频 文件夹下子文件夹失败" << endl;

		return -1;
	}

	if (LSP_SQLite_db_vecot_goto_TABLE(LSP_SQLite_db_vector_video, "视频") == 0)
	{
		if(tmp_voide_path.size() != 0)
			vector<_finddata_t>().swap(tmp_voide_path);

		return 0;
	}	
	else
	{
		cout << "视频类vector存入SQLite数据库失败" << endl;

		return -1;
	}
		
}


int LSP_SQLite::LSP_SQLite_db_TABLE_set_NEW()
{
	//临时存储路径
	vector<_finddata_t> tmp_set_path;

	if(get_files_Folder_goto_vector(LSP_path[1], tmp_set_path) == 0)
	{
		for (int i = 0; i < tmp_set_path.size(); i++)
		{
			cout << "当前文件夹为:\t" << tmp_set_path[i].name << endl << endl;

			if (get_files_Folder_goto_vector(LSP_path[1] + "/" + tmp_set_path[i].name, LSP_SQLite_db_vector_set) == 0)
			{
				for (int o = 0; o < LSP_SQLite_db_vector_set.size(); o++)
				{
					//输入类别
					LSP_SQLite_db_vector_set_sort.push_back(string(tmp_set_path[i].name));

					//debug测试数据是否正常
					/*cout << "名称:\t" << LSP_SQLite_db_vector_set[o].name << endl
						<< "文件夹/文件 :\t" << Folder_or_File(LSP_SQLite_db_vector_set, o) << endl
						<< "类别为;\t" << LSP_SQLite_db_vector_set_sort[o] << endl << endl;*/
				}
			}
		}
	}
	else
	{
		cout << "获取合集目录下文件夹出错" << endl;

		return -1;
	}

	if (LSP_SQLite_db_vecot_goto_TABLE(LSP_SQLite_db_vector_set, "合集") == 0)
	{
		if (tmp_set_path.size() != 0)
			vector<_finddata_t>().swap(tmp_set_path);

		return 0;
	}
	else
	{
		cout << "合集类vector存入SQLite数据库失败" << endl;

		return -1;
	}
}

//游戏表初始化
int LSP_SQLite::LSP_SQLite_db_TABLE_game_NEW()
{
	//获取指定目录下的 文件夹.文件 写入到一个vector中
	if (get_files_Folder_goto_vector(LSP_path[3], LSP_SQLite_db_vector_game) == 0)
		LSP_SQLite_db_vecot_goto_TABLE(LSP_SQLite_db_vector_game, "游戏");
	else
	{
		cout << "获取游戏文件夹下游戏失败" << endl;
		return - 1;
	}
		

	return 0;
}



//LSP_SQLite构造函数
LSP_SQLite::LSP_SQLite()
{
	MB = 1024 * 1024;
	GB = MB * 1024;
	LSP_SQLite_db = new char[] {"LSP.db"};
	LSP_SQLite_NEW_status = "no";
	LSP_SQL_SQLite = nullptr;
	LSP_SQL_Stmt = nullptr;
	local_time = new tm;

	LSP_path = new string[5]{ "E:/英雄时刻/个人/本子", "E:/英雄时刻/个人/合集", "E:/英雄时刻/个人/视频", "E:/英雄时刻/个人/Game", "E:/英雄时刻/个人/ASMR" };

	//校对时间
	time_level();

	//检测数据库初始化状态
	LSP_SQLite_db_status();	
}

//LSP_SQLite析构函数
LSP_SQLite::~LSP_SQLite()
{
	//释放存放数据库名称的内存地址
	if (LSP_SQLite_db != nullptr)
		delete(LSP_SQLite_db);
	
	//释放存放时间的内存地址
	if (local_time != nullptr)
		delete(local_time);
		
	//释放储存不同路径的内存地址
	if (LSP_path != nullptr)
		delete[](LSP_path);	

	//检测数据库是否依旧连接
	if (LSP_SQL_SQLite == nullptr)
		sqlite3_close(LSP_SQL_SQLite);
}

//UTF-8编码 转 GBK编码
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

//GBK编码 转 UTF-8编码
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