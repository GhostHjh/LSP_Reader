#include"LSP.h"

//int LSP_SQLite::NEW_TABLE()
//{
//	//������ͬ�ı����ڴ�����Ҫ������
//	string* NEW_TABLE_SQLite = new string[4];
//	NEW_TABLE_SQLite[0] = "CREATE TABLE ���� ( ID INTEGER PRIMARY KEY NOT NULL, ��Ʒ���� TEXT, ҳ�� INT, ������ TEXT, �ϴιۿ���¼ TEXT, �Ƿ���ʾ TEXT NOT NULL, ״̬ TEXT );";
//	NEW_TABLE_SQLite[1] = "CREATE TABLE ��Ƶ ( ID INTEGER PRIMAPY KEY NOT NULL, ��Ʒ���� TEXT, ʱ�� INT, ������ TEXT, �ϴιۿ���¼ TEXT, �Ƿ���ʾ TEXT NOT NULL, ״̬ TEXT );";
//	NEW_TABLE_SQLite[2] = "CREATE TABLE �ϼ� ( ID INTEGER PRIMAPY KEY NOT NULL, ��Ʒ���� TEXT, ���� INT, ������ TEXT, �ϴιۿ���¼ TEXT, �Ƿ���ʾ TEXT NOT NULL, ״̬ TEXT );";
//	NEW_TABLE_SQLite[3] = "CREATE TABLE ���ݿ�״̬ ( �Ƿ��ʼ��	TEXT NOT NULL, �������� TEXT NOT NULL, ��󱣴����� TEXT NOT NULL)";
//
//	//�������ݿ�
//	int sql_result = sqlite3_open_v2(LSP_SQLite_db, &LSP_SQL_SQLite, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);
//
//	//������ݿ��Ƿ�򿪳ɹ�
//	if (sql_result == SQLITE_OK)
//	{
//		cout << "���ݿ�򿪳ɹ�" << endl;
//	}
//	else
//	{
//		cout << "���ݿ��ʧ��" << endl;
//		return 0;
//	}
//
//	cout << "��ʼ������ݿ��Ƿ�����" << endl;
//
//	//������ݿ��Ƿ�����
//	int int_sql = sqlite3_prepare_v2(LSP_SQL_SQLite, G2U((const char*)("SELECT �Ƿ��ʼ�� FROM ���ݿ�״̬")), -1, &LSP_SQL_Stmt, NULL);
//	if (int_sql == SQLITE_OK)
//	{
//		cout << "��ѯ�����������" << endl;
//		cout << sqlite3_column_text(LSP_SQL_Stmt, 0) << endl;
//
//		if ("yes" == U2G((char*)sqlite3_column_text(LSP_SQL_Stmt, 0)))
//		{
//			cout << endl << endl << "���ݿ��Ѿ�����˳�ʼ��" << endl;
//			SQL_NEW = 0;
//		}
//	}
//	else if (sqlite3_prepare_v2(LSP_SQL_SQLite, G2U("SELECT �Ƿ��ʼ�� FROM ���ݿ�״̬"), -1, &LSP_SQL_Stmt, NULL) != SQLITE_OK)
//	{
//		SQL_NEW = 1;
//	}
//	
//
//	if (SQL_NEW == 1)
//	{
//		cout << "��ʼ�����ݿ���г�ʼ��" << endl;
//
//		int int_tmp_re = sqlite3_prepare_v2(LSP_SQL_SQLite,G2U(NEW_TABLE_SQLite[0].data()), -1, &LSP_SQL_Stmt, NULL);
//
//		if (int_tmp_re == SQLITE_OK)
//			cout << endl << "���ݿ�� 1 �����ɹ�" << endl << endl;
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
//				cout << "���ݿ�� " << i+1 << " �����ɹ�" << endl << endl;
//
//			sqlite3_finalize(LSP_SQL_Stmt);
//		}	
//	}
//
//	sqlite3_close(LSP_SQL_SQLite);
//	return 1;
//}
//����ϵͳʱ���local_time�ṹ����

//����ʱ���ʼ������
string LSP_SQLite::time_level()
{
	time_t* now = new time_t;
	time(now);

	localtime_s(local_time, now);
	delete(now);

	return to_string(local_time->tm_year + 1900) + "_" + to_string(local_time->tm_mon + 1) + "_" + to_string(local_time->tm_mday) + "_" + to_string(local_time->tm_hour) + "_" + to_string(local_time->tm_min) + "_" + to_string(local_time->tm_sec);
}

//���ݿ��Ƿ���ɳ�ʼ����ѯ���		�ɹ�: 0		ʧ��: -1
int LSP_SQLite::LSP_SQLite_db_status()
{
	//SQL���ִ�зŻ�ֵ
	int int_sql;

	//�������ݿ�
	if ((int_sql = sqlite3_open_v2(LSP_SQLite_db, &LSP_SQL_SQLite, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL)) == SQLITE_OK)
	{
		cout << "���ݿ�\t\t���ӳɹ�" << endl;

		//�ж����ݿ��Ƿ��Ѿ���ɳ�ʼ��һ(����)
		if ((int_sql = sqlite3_prepare_v2(LSP_SQL_SQLite, G2U("SELECT * FROM ���ݿ�״̬"), -1, &LSP_SQL_Stmt, NULL)) == SQLITE_OK)
		{
			cout << "���ݿ�\t\t��ѯ���ɹ�" << endl;

			//��ȡ���
			sqlite3_step(LSP_SQL_Stmt);
			LSP_SQLite_NEW_status = U2G((char*)sqlite3_column_text(LSP_SQL_Stmt, 0));

			//�жϸ����ݿ��Ƿ��ʼ������Ƿ�Ϊyes
			if ("yes" == LSP_SQLite_NEW_status)
			{
				cout << "���ݿ�\t\t�Ѿ���ɳ�ʼ��" << endl << endl;

				//�����һ��SQL���ִ�н��,  �ر�SQLite���
				sqlite3_finalize(LSP_SQL_Stmt);
				sqlite3_close(LSP_SQL_SQLite);
				return 0;
			}
			//Ϊ��ʼ������ 0
			else
			{
				cout << "���ݿ�\t\tδ��ɳ�ʼ��" << endl << endl;

				LSP_SQLite_NEW_status = "no";
				//�����һ��SQL���ִ�н��,  �ر�SQLite���
				sqlite3_finalize(LSP_SQL_Stmt);
				sqlite3_close(LSP_SQL_SQLite);
				return -1;
			}		
		}
		//���ݿ��ѯʧ�ܷ��� 0
		else
		{
			cout << "���ݿ�\t\t��ѯ���ʧ��" << endl;

			//�����һ��SQL���ִ�н��,  �ر�SQLite���
			sqlite3_close(LSP_SQL_SQLite);
			return -1;
		}
	}		
	else
	{
		cout << "���ݿ�\t\t����ʧ��" << endl;

		return -1;
	}

}


//���ݿ��ʼ�����
int LSP_SQLite::LSP_SQLite_db_NEW()
{
	//������ͬ�ı����ڴ�����Ҫ������
	string* NEW_TABLE_SQLite = new string[8];
	NEW_TABLE_SQLite[0] = "CREATE TABLE ���� ( ID INTEGER PRIMARY KEY AUTOINCREMENT, ��Ʒ���� TEXT, ҳ�� INT, ������ TEXT, �ϴιۿ���¼ TEXT, ��Ʒ���� TEXT, �Ƿ���ʾ TEXT NOT NULL, ״̬ TEXT );";
	NEW_TABLE_SQLite[1] = "CREATE TABLE ��Ƶ ( ID INTEGER PRIMARY KEY AUTOINCREMENT, ��Ʒ���� TEXT, ʱ�� INT, ���� TEXT, �ϴιۿ���¼ TEXT, ��Ʒ���� TEXT, �Ƿ���ʾ TEXT NOT NULL, ״̬ TEXT );";
	NEW_TABLE_SQLite[2] = "CREATE TABLE �ϼ� ( ID INTEGER PRIMARY KEY AUTOINCREMENT, ��Ʒ���� TEXT, ���� INT, ���� TEXT, �ϴιۿ���¼ TEXT, �Ƿ���ʾ TEXT NOT NULL, ״̬ TEXT );";
	NEW_TABLE_SQLite[3] = "CREATE TABLE ��Ϸ ( ID INTEGER PRIMARY KEY AUTOINCREMENT, ��Ʒ���� TEXT, ��С INT, ������ TEXT, �ϴ�������¼ TEXT, ��Ʒ���� TEXT, �Ƿ���ʾ TEXT NOT NULL, ״̬ TEXT );";
	NEW_TABLE_SQLite[4] = "CREATE TABLE ASMR ( ID INTEGER PRIMARY KEY AUTOINCREMENT, ��Ʒ���� TEXT, ʱ�� INT, ���� TEXT, �ϴιۿ���¼ TEXT, �Ƿ���ʾ TEXT NOT NULL, ״̬ TEXT );";
	NEW_TABLE_SQLite[5] = "CREATE TABLE ���ݿ�״̬ ( �Ƿ��ʼ��	TEXT NOT NULL, ����·�� TEXT, ��Ƶ·�� TEXT, �ϼ�·�� TEXT, ��Ϸ·�� TEXT, ASMR·�� TEXT, �������� TEXT NOT NULL, ��󱣴����� TEXT NOT NULL)";
	NEW_TABLE_SQLite[6] = "INSERT INTO ���ݿ�״̬ (�Ƿ��ʼ��, ��������, ��󱣴�����) VALUES ( \'yes\', \'";
	NEW_TABLE_SQLite[6] += time_level();
	NEW_TABLE_SQLite[6] += "\', \'";
	NEW_TABLE_SQLite[6] += time_level();
	NEW_TABLE_SQLite[6] += "\');";
	NEW_TABLE_SQLite[7] = "INSERT INTO ���ݿ�״̬ ( ����·��, �ϼ�·��, ��Ƶ·��, ��Ϸ·��, ASMR·��) VALUES ( \'";
	NEW_TABLE_SQLite[7] += LSP_path[0] + "\', \'" + LSP_path[1] + "\', \'" + LSP_path[2] + "\', \'" + LSP_path[3] + "\', \'" + LSP_path[4] + "\' )";
	//LSP_path = new string[5]{ "E:/Ӣ��ʱ��/����/����", "E:/Ӣ��ʱ��/����/�ϼ�", "E:/Ӣ��ʱ��/����/��Ƶ", "E:/Ӣ��ʱ��/����/Game", "E:/Ӣ��ʱ��/����/ASMR" };
	
	//SQL���ִ�зŻ�ֵ
	int int_sql;
	
	//��ʾ���ݿ��ʼ��״̬ yes OR no
	//cout << endl << endl << LSP_SQLite_NEW_status << endl << endl;

	//�������ݿ�
	if ( (int_sql = sqlite3_open_v2(LSP_SQLite_db, &LSP_SQL_SQLite, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL) ) == SQLITE_OK)
	{
		//SQLite3_exec()�������д�����Ϣ
		char* no_log = new char[128];

		cout << "���ݿ����ӳɹ�" << endl;

		//�ж����ݿ��Ƿ��Ѿ���ɳ�ʼ��(����)
		if ("no" == LSP_SQLite_NEW_status)
		{
			for (int i = 0; i < 8 && int_sql == SQLITE_OK; i++)
			{
				int_sql = sqlite3_exec(LSP_SQL_SQLite, G2U(NEW_TABLE_SQLite[i].c_str()), NULL, NULL, &no_log);
				cout << "��\t" << i + 1 << "\t������������гɹ�" << endl;
				cout << NEW_TABLE_SQLite[i] << endl << endl;
			}
			//�ر����ݿ�����
			sqlite3_close(LSP_SQL_SQLite);
			return 0;
		}
		else if ("no" != LSP_SQLite_NEW_status)
		{
			//�ر����ݿ�����
			sqlite3_close(LSP_SQL_SQLite);
			return -1;
		}
		//�ͷ�SQLite3_exec()�������д�����Ϣ
		delete[](no_log);
	}	
	else
	{
		cout << "���ݿ�����ʧ��" << endl;

		return -1;
	}
}

//��ʱʹ��
void LSP_SQLite::tmp()
{
	for (int i = 0; i < LSP_SQLite_db_vector_book.size(); i++)
	{
		cout << "�ļ�������Ϊ:\t" << LSP_SQLite_db_vector_book[i].name << endl;
	}
}

//��ȡָ��Ŀ¼�µ����� �ļ���/�ļ� ��һ��vector��
int LSP_SQLite::get_files_Folder_goto_vector(string path, vector<_finddata_t>& folder)
{
	cout << "\n��ʼ����\t" << path << "\t�ļ����� �ļ�/�ļ��� ���ҳ���\n";
	//��ʱ·������ַ���
	string* tmp = new string;
	
	/*_finddata_t Ϊ<io.h>���Դ����ݽṹ
	struct _finddata_t
	{
		unsigned attrib;		�ļ����ԵĴ���λ��,�洢һ��unsigned��Ԫ
		time_t time_create;		�ļ���1970_1_1���浽���ڵ�ʱ��
		time_t time_access;		�ļ����һ�α����ʵ�ʱ��
		time_t time_write;		�ļ����һ�α��޸ĵ�ʱ��
		_fsize_t size;			�ļ���С
		char name[_MAX_FNAME];	�ļ�����
	};*/
	_finddata_t* fileinfo = new _finddata_t;
	

	//intptr_t��uintptr_t������:typedef long int�� typedef unsigned long int 
	//assign()�������Ƚ�ԭ�ַ�����գ�Ȼ�����µ�ֵ���滻, append()����: ƴ���ַ���, c_str()����: ��char*�ķ�ʽ�Ż�string�ַ���
	//_findfirst()����: ��һ������Ϊ�ļ�����,�ڶ��������� _finddate �ṹ��ָ��, ������ҳɹ���Ż��ļ����,ʧ�ܷ���-1
	intptr_t hFiles = _findfirst(tmp->assign(path).append("/*").c_str(), fileinfo);

	/*cout << "\n��ǰƴ���ַ���Ϊ\t:" << *tmp << endl
		<< "��ǰ _findfirst ���д���:\t" << hFiles << endl << endl;*/

	if (hFiles != -1)
	{
		cout << "���ļ�����\t" << path << "\t�ļ���\n\n";

		//_findnext()����������������, ��һ��Ϊ�ļ����(long����), �ڶ���Ϊ _finddata_t�ṹ��ָ��, �ɹ����� 0 , ʧ�ܷ��� -1
		while (_findnext(hFiles, fileinfo) == 0)
		{	
			//strcmp()�������ڱȽ������ַ���, str1<str2 �� ֵС��0, str1>str2 �� ֵ>0, str1=str2 �� ֵ=0
			//�����if�ж�Ϊ�ж����ڵ��ļ������� .. ���� . �������ļ�
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
		cout << "���ļ��в���\t" << path << "\t�ļ���" << endl;
		delete(fileinfo);
		delete(tmp);

		return -1;
	}

	delete(tmp);
	delete(fileinfo);
	cout << "\n\n�������� �ļ�/�ļ��� ����" << endl;
	return 0;
}

//�����Ϊ �ļ��� ���� �ļ�
string LSP_SQLite::Folder_or_File(vector<_finddata_t>& tmp_vector, int tmp_int)
{
	if (tmp_vector[tmp_int].attrib == 32)
	{
		//cout << "\t��Ƶʱ��Ϊ:";
		return "�ļ�";
	}	
	else if (tmp_vector[tmp_int].attrib == 16)
		return "�ļ���";
	else
		return "δ֪";
}


//��vector�����н���ȡ���� �ļ�/�ļ��� ��Ϣ����SQLite���ݿ�ָ���ı���
int LSP_SQLite::LSP_SQLite_db_vecot_goto_TABLE(vector<_finddata_t>& TABLE_vector, string TABLE_name)
{
	//�������ݿ�
	if (!(sqlite3_open_v2(LSP_SQLite_db, &LSP_SQL_SQLite, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL) == SQLITE_OK))
		return -1;

	//����ִ�е�SQL���
	string* SQL = new string;

	//���ڴ���sqlite_exec()������Ϣ
	char* no_log = new char[1024];

	//������ʱ�洢�洢�ļ������ļ���Ϣ
	vector<_finddata_t> tmp_folder;

	
	//������ʱ�����ļ������Ƶ�string����
	string tmp_path;

	//��Բ�ͬ�Ĳ������в�ͬ��
	if ("����" == TABLE_name)  
	{
		for (int i = 0; i < TABLE_vector.size(); i++)
		{
			//������ʱ��ַΪָ����ַ
			tmp_path = LSP_path[0] + "/" + TABLE_vector[i].name;

			get_files_Folder_goto_vector(tmp_path, tmp_folder);
			*SQL = "INSERT INTO " + TABLE_name + " ( ��Ʒ����, ҳ��, ������, ��Ʒ����, �Ƿ���ʾ, ״̬ )" + " VALUES ( \'" + TABLE_vector[i].name + "\', " + to_string(tmp_folder.size()) + ", \'" + LSP_Chinese_localization(TABLE_vector[i].name) + "\', \'" + tmp_path + "/" + tmp_folder[0].name + "\', \'yes\', \'����\' );";

			//��ʾ���е�SQL���
			//cout << *SQL << endl << endl;

			//����sql���
			if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
			{
				cout << endl << "SQL�������ʧ��" << endl;
				cout << U2G(no_log) << endl;

				cout << "����ʹ��˫��������SQL���" << endl;
				*SQL = "INSERT INTO " + TABLE_name + " ( ��Ʒ����, ҳ��, ������, �Ƿ���ʾ, ״̬ )" + " VALUES ( \"" + TABLE_vector[i].name + "\", " + to_string(tmp_folder.size()) + ", \'" + LSP_Chinese_localization(TABLE_vector[i].name) + "\', \"" + tmp_path + "/" + tmp_folder[0].name + "\", \'yes\', \'����\' );";
				cout << *SQL << endl;

				if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
					cout << "��������ʧ��,��鿴��־" << endl << endl;
				else
					cout << "ʹ��˫��������SQL���ɹ�" << endl << endl;
			}
		}
	}	
	else if ("�ϼ�" == TABLE_name)
	{
		for (int i = 0; i < LSP_SQLite_db_vector_set.size(); i++)
		{
			//������ʱ��ַΪ�ϼ���Ŀ¼+��ǰ�ļ���
			tmp_path = LSP_path[1] + "/" + LSP_SQLite_db_vector_set_sort[i] + "/" + TABLE_vector[i].name;

			//�������ļ��в�ѯ
			if (get_files_Folder_goto_vector(tmp_path, tmp_folder) != 0)
			{
				cout << "�������ļ���������ѯʧ��!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
					<< "���ļ�������:\t" << tmp_path << endl;
			}

			*SQL = "INSERT INTO " + TABLE_name + " ( ��Ʒ����, ����, ����, �Ƿ���ʾ, ״̬ )" + " VALUES ( \'" + TABLE_vector[i].name + "\', " + to_string(tmp_folder.size()) + ", \'" + LSP_SQLite_db_vector_set_sort[i] + "�ϼ�\', \'yes\', \'����\' );";

			//������е�SQL���
			//cout << *SQL << endl << endl;

			//����sql���
			if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
			{
				cout << endl << "SQL�������ʧ��" << endl;
				cout << U2G(no_log) << endl;

				cout << "����ʹ��˫��������SQL���" << endl;
				*SQL = "INSERT INTO " + TABLE_name + " ( ��Ʒ����, ����, ����, �Ƿ���ʾ, ״̬ )" + " VALUES ( \"" + TABLE_vector[i].name + "\", " + to_string(tmp_folder.size()) + ", \'" + LSP_SQLite_db_vector_set_sort[i] + "�ϼ�\', \'yes\', \'����\' );";
				cout << *SQL << endl;

				if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
					cout << "��������ʧ��,��鿴��־" << endl << endl;
				else
					cout << "ʹ��˫��������SQL���ɹ�" << endl << endl;
			}
			else
				cout << "��Ʒ:\t" << TABLE_vector[i].name << "\t�������ݿ�ɹ�\n\n";
		}
	}
	else if ("��Ƶ" == TABLE_name)
	{
		for (int i = 0; i < TABLE_vector.size(); i++)
		{
			//�жϵ�ǰҪ�������ݿ���ǲ����ļ���,����Ǹķ���Ϊ xxx����ϼ�,�����Ϊ xxx������Ƶ.
			if (Folder_or_File(TABLE_vector, i) == "�ļ���")
			{
				//������ʱ��ַΪ�ϼ���Ŀ¼
				tmp_path = LSP_path[2] + "/" + LSP_SQLite_db_vector_video_sort[i] + "/" + TABLE_vector[i].name;

				//�������ļ��в�ѯ
				if (get_files_Folder_goto_vector(tmp_path, tmp_folder) != 0)
				{
					cout << "�������ļ���������ѯʧ��!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
						<< "���ļ�������:\t" << tmp_path << endl;
				}

				//���ķ�������
				LSP_SQLite_db_vector_video_sort[i] += "��Ƶ�ϼ�";
			}
			else if (Folder_or_File(TABLE_vector, i) == "�ļ�")
				LSP_SQLite_db_vector_video_sort[i] += "��Ƶ";
			else
				LSP_SQLite_db_vector_video_sort[i] += "δ֪";

			*SQL = "INSERT INTO " + TABLE_name + " ( ��Ʒ����, ʱ��, ����, ��Ʒ����, �Ƿ���ʾ, ״̬ )" + " VALUES ( \'" + TABLE_vector[i].name + "\', " + to_string(tmp_folder.size()) + ", \'" + string(LSP_SQLite_db_vector_video_sort[i]) + "\', \'" + tmp_path + "/" + tmp_folder[0].name + "\', \'yes\', \'����\' );";

			//��ʾ���е�SQL���
			//cout << *SQL << endl << endl;

			//����sql���
			if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
			{
				cout << endl << "SQL�������ʧ��" << endl;
				cout << U2G(no_log) << endl;

				cout << "����ʹ��˫��������SQL���" << endl;
				*SQL = "INSERT INTO " + TABLE_name + " ( ��Ʒ����, ʱ��, ����, ��Ʒ����, �Ƿ���ʾ, ״̬ )" + " VALUES ( \"" + TABLE_vector[i].name + "\", " + to_string(tmp_folder.size()) + ", \'" + string(LSP_SQLite_db_vector_video_sort[i]) + "\', \"" + tmp_path + "/" + tmp_folder[0].name + "\", \'yes\', \'����\' );";
				cout << *SQL << endl;

				if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
					cout << "��������ʧ��,��鿴��־" << endl << endl;
				else
					cout << "ʹ��˫��������SQL���ɹ�" << endl << endl;
			}
			else
				cout << "��Ʒ:\t" << TABLE_vector[i].name << "\t�ɹ��������ݿ�" << endl;
		}
	}	
	else if ("��Ϸ" == TABLE_name)
	{
		for (int i = 0; i < TABLE_vector.size(); i++)
		{
			//get_files_Folder_goto_vector(tmp_path, tmp_folder);
			*SQL = "INSERT INTO " + TABLE_name + " ( ��Ʒ����, ��С, ��Ʒ����, �Ƿ���ʾ, ״̬ )" + " VALUES ( \'" + TABLE_vector[i].name + "\', " + to_string(TABLE_vector[i].size / MB) + ", \'" + LSP_path[3] + "/" + TABLE_vector[i].name + "\', \'yes\', \'����\' );";

			//��ʾ���е�SQL���
			//cout << *SQL << endl << endl;

			//����sql���
			if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
			{
				cout << endl << "SQL�������ʧ��" << endl;
				cout << U2G(no_log) << endl;

				cout << "����ʹ��˫��������SQL���" << endl;
				*SQL = "INSERT INTO "+ TABLE_name + " ( ��Ʒ����, ��С, ��Ʒ����, �Ƿ���ʾ, ״̬ )" + " VALUES ( \"" + TABLE_vector[i].name + "\", " + to_string(TABLE_vector[i].size / MB) + ", \"" + LSP_path[3] + "/" + TABLE_vector[i].name + "\", \'yes\', \'����\' );";
				cout << *SQL << endl;

				if (sqlite3_exec(LSP_SQL_SQLite, G2U(SQL->c_str()), NULL, NULL, &no_log) != SQLITE_OK)
					cout << "��������ʧ��,��鿴��־" << endl << endl;
				else
					cout << "ʹ��˫��������SQL���ɹ�" << endl << endl;
			}
		}
	}
	else if ("ASMR" == TABLE_name)
		tmp_path = LSP_path[4];
	else
		return -1;			

	//�ͷ��ڴ�
	delete[](no_log);//�ͷ����ڴ���sqlite_exec()������Ϣ
	vector<_finddata_t>().swap(tmp_folder);//�����ʱ���ڴ洢�ļ��е�vector����

	//����ڴ��ͷ����
	if (tmp_folder.size() == 0 && no_log == nullptr)
		return 0;
	else
	{
		if (tmp_folder.size() != 0)
		{
			cout << "������ʱ�ļ���vector�����ͷ�ʧ��!!!!!!!!!!!!!" << endl;
		}
		else if (no_log != nullptr)
		{
			cout << "���ڴ洢SQLite_exec()���е�SQL��������Ϣ�ͷ�ʧ��!!!!!!!!" << endl;
		}

		return -1;
	}

	//�Ͽ����ݿ�����
	sqlite3_close(LSP_SQL_SQLite);
	delete(SQL);
	return 0;
}


//�ļ�������ɸѡ��������
string LSP_SQLite::LSP_Chinese_localization(string tmp_Folder_name)
{
	//getline(cin, tmp_Folder_name);
	string Folder_name = "���޺�������Ϣ";

	//һ��ɸѡ����
	regex tmp_regex_1("\\](.*?)(����|�h��|����|���U|������)(.*?)\\]");//��Ч  
	regex tmp_regex__1_1("\\[(.*?)(����|�h��|����|���U|������)(.*?)\\]");

	//����ɸѡ����
	regex tmp_regex_2("\\)(.*?)(����|�h��|����|���U|������)(.*?)\\)");//��Ч  
	regex tmp_regex__2_1("\\((.*?)(����|�h��|����|���U|������)(.*?)\\)");

	//���Ź���
	regex tmp_regex_3("\\[(.*?)(����|�h��|����|���U|������)(.*?)\\]");

	//�ĺŹ���
	regex tmp_regex_4("\\((.*?)(����|�h��|����|���U|������)(.*?)\\)");

	//��ʱ�洢�����������
	smatch tmp_smatch_Folder_name;
	if (regex_search(tmp_Folder_name, tmp_smatch_Folder_name, tmp_regex_1) && Folder_name == "���޺�������Ϣ")
	{
		Folder_name = tmp_smatch_Folder_name[0];
		//cout << "���� 1 ���гɹ�,��ǰ�ַ���:\t" << Folder_name << endl;

		if (regex_search(Folder_name, tmp_smatch_Folder_name, tmp_regex__1_1))
			Folder_name = tmp_smatch_Folder_name[0];
	}
	
	if (regex_search(tmp_Folder_name, tmp_smatch_Folder_name, tmp_regex_2) && Folder_name == "���޺�������Ϣ")
	{
		Folder_name = tmp_smatch_Folder_name[0];
		//cout << "���� 2 ���гɹ�,��ǰ�ַ���:\t" << Folder_name << endl;

		if (regex_search(Folder_name, tmp_smatch_Folder_name, tmp_regex__2_1))
			Folder_name = tmp_smatch_Folder_name[0];
	}
	
	if (regex_search(tmp_Folder_name, tmp_smatch_Folder_name, tmp_regex_3) && Folder_name == "���޺�������Ϣ")
		Folder_name = tmp_smatch_Folder_name[0];
		//cout << "���� 3 ���гɹ�,��ǰ�ַ���:\t" << Folder_name << endl;
	else if (regex_search(tmp_Folder_name, tmp_smatch_Folder_name, tmp_regex_4))
		Folder_name = tmp_smatch_Folder_name[0];
		//cout << "���� 4 ���гɹ�,��ǰ�ַ���:\t" << Folder_name << endl;
	

	return string(Folder_name);
}

//��ȡ ��Ƶ�ļ� ������Ϣ
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

//���ݿ� ���� ���ʼ��
int LSP_SQLite::LSP_SQLtie_db_TABLE_book_NEW()
{
	//��ȡָ��Ŀ¼�µ����� �ļ���/�ļ� ��һ��vector��
	if (get_files_Folder_goto_vector(LSP_path[0], LSP_SQLite_db_vector_book) == 0)
		LSP_SQLite_db_vecot_goto_TABLE(LSP_SQLite_db_vector_book, "����"); 
	else
	{
		cout << "\n\n\nָ��Ŀ¼�� �ļ���/�ļ� д��vectorʧ��!!!!!!!\n\n\n";
		return -1;
	}
		
	
	return 0;
}


//���ݿ� ��Ƶ ���ʼ��
//int LSP_SQLite::LSP_SQLite_db_TABLE_video_NEW()
//{
//	if (get_files_Folder_goto_vector(LSP_path[2], LSP_SQLite_db_vector_video) == 0)
//	{
//		int* Folder_2_3_yes = new int(0);
//
//		//�ж��ļ��нṹ�Ƿ��� ��Ƶ----> ����Ԫ&&����Ԫ
//		for (int i = 0; i < LSP_SQLite_db_vector_video.size() && *Folder_2_3_yes != 2; i++)
//		{
//			if (strcmp(LSP_SQLite_db_vector_video[i].name, "����Ԫ") || strcmp(LSP_SQLite_db_vector_video[i].name, "����Ԫ"))
//				(*Folder_2_3_yes)++;
//
//			//����ļ��нṹ�Ƿ��� ��Ƶ----> ����Ԫ&&����Ԫ
//			if (*Folder_2_3_yes == 2)
//			{
//				//��ʱ��Ƶ�ļ���vector
//				vector<_finddata_t>().swap(LSP_SQLite_db_vector_video);
//
//				//��ʱ��Ƶ�ļ���·��
//				string tmp_Folder_path = LSP_path[2] + "/����Ԫ";
//
//				cout << "��ʱ��Ƶ�ļ���·��Ϊ:" << tmp_Folder_path << endl;
//
//				//��ȡ��ʱ��Ƶ�ļ���·���µ��ļ�/�ļ��е���ʱ�ļ���vector
//				if (get_files_Folder_goto_vector(tmp_Folder_path, LSP_SQLite_db_vector_video) != 0)
//					return -1;
//
//				//��ʱ��Ƶ�ļ���·������
//				tmp_Folder_path = LSP_path[2] + "/����Ԫ";
//
//				//��ȡ�µ���ʱ��Ƶ�ļ���·���µ��ļ�/�ļ��е���ʱ�ļ���vector
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
//	LSP_SQLite_db_vecot_goto_TABLE(LSP_SQLite_db_vector_video, "��Ƶ");
//	get_files_Folder_goto_vector(LSP_path[2], LSP_SQLite_db_vector_video);
//
//	
//	return 0;
//}

//���ݿ� ��Ƶ ���ʼ��
int LSP_SQLite::LSP_SQLite_db_TABLE_video_NEW()
{
	//��ʱ�洢·��
	vector<_finddata_t> tmp_voide_path;

	//�ж��ļ����Ƿ��ųɹ�
	if (get_files_Folder_goto_vector(LSP_path[2], tmp_voide_path) == 0)
	{
		for (int i = 0; i < tmp_voide_path.size(); i++)
		{
			cout << "��ǰ�����ļ���Ϊ:\t" << tmp_voide_path[i].name << endl;

			if (get_files_Folder_goto_vector(LSP_path[2] + "/" + tmp_voide_path[i].name, LSP_SQLite_db_vector_video) == 0)
			{	
				cout << "��ʼ�г������ļ��� " << tmp_voide_path[i].name << " �е����ļ���" << endl;
				for (int o = 0; o < LSP_SQLite_db_vector_video.size(); o++)
				{
					//���õ� o �� ��Ƶ�ļ�/�ļ��� �����
					LSP_SQLite_db_vector_video_sort.push_back(string(tmp_voide_path[i].name));

					//debug���������Ƿ�����
					/*cout << "����:\t" << LSP_SQLite_db_vector_video[o].name << endl
						<< "�ļ���/�ļ� :\t" << Folder_or_File(LSP_SQLite_db_vector_video, o) << endl
						<< "���Ϊ;\t" << LSP_SQLite_db_vector_video_sort[o] << endl << endl;	*/				
				}
			}
		}
	}
	else
	{
		cout << "���л�ȡ ��Ƶ �ļ��������ļ���ʧ��" << endl;

		return -1;
	}

	if (LSP_SQLite_db_vecot_goto_TABLE(LSP_SQLite_db_vector_video, "��Ƶ") == 0)
	{
		if(tmp_voide_path.size() != 0)
			vector<_finddata_t>().swap(tmp_voide_path);

		return 0;
	}	
	else
	{
		cout << "��Ƶ��vector����SQLite���ݿ�ʧ��" << endl;

		return -1;
	}
		
}


int LSP_SQLite::LSP_SQLite_db_TABLE_set_NEW()
{
	//��ʱ�洢·��
	vector<_finddata_t> tmp_set_path;

	if(get_files_Folder_goto_vector(LSP_path[1], tmp_set_path) == 0)
	{
		for (int i = 0; i < tmp_set_path.size(); i++)
		{
			cout << "��ǰ�ļ���Ϊ:\t" << tmp_set_path[i].name << endl << endl;

			if (get_files_Folder_goto_vector(LSP_path[1] + "/" + tmp_set_path[i].name, LSP_SQLite_db_vector_set) == 0)
			{
				for (int o = 0; o < LSP_SQLite_db_vector_set.size(); o++)
				{
					//�������
					LSP_SQLite_db_vector_set_sort.push_back(string(tmp_set_path[i].name));

					//debug���������Ƿ�����
					/*cout << "����:\t" << LSP_SQLite_db_vector_set[o].name << endl
						<< "�ļ���/�ļ� :\t" << Folder_or_File(LSP_SQLite_db_vector_set, o) << endl
						<< "���Ϊ;\t" << LSP_SQLite_db_vector_set_sort[o] << endl << endl;*/
				}
			}
		}
	}
	else
	{
		cout << "��ȡ�ϼ�Ŀ¼���ļ��г���" << endl;

		return -1;
	}

	if (LSP_SQLite_db_vecot_goto_TABLE(LSP_SQLite_db_vector_set, "�ϼ�") == 0)
	{
		if (tmp_set_path.size() != 0)
			vector<_finddata_t>().swap(tmp_set_path);

		return 0;
	}
	else
	{
		cout << "�ϼ���vector����SQLite���ݿ�ʧ��" << endl;

		return -1;
	}
}

//��Ϸ���ʼ��
int LSP_SQLite::LSP_SQLite_db_TABLE_game_NEW()
{
	//��ȡָ��Ŀ¼�µ� �ļ���.�ļ� д�뵽һ��vector��
	if (get_files_Folder_goto_vector(LSP_path[3], LSP_SQLite_db_vector_game) == 0)
		LSP_SQLite_db_vecot_goto_TABLE(LSP_SQLite_db_vector_game, "��Ϸ");
	else
	{
		cout << "��ȡ��Ϸ�ļ�������Ϸʧ��" << endl;
		return - 1;
	}
		

	return 0;
}



//LSP_SQLite���캯��
LSP_SQLite::LSP_SQLite()
{
	MB = 1024 * 1024;
	GB = MB * 1024;
	LSP_SQLite_db = new char[] {"LSP.db"};
	LSP_SQLite_NEW_status = "no";
	LSP_SQL_SQLite = nullptr;
	LSP_SQL_Stmt = nullptr;
	local_time = new tm;

	LSP_path = new string[5]{ "E:/Ӣ��ʱ��/����/����", "E:/Ӣ��ʱ��/����/�ϼ�", "E:/Ӣ��ʱ��/����/��Ƶ", "E:/Ӣ��ʱ��/����/Game", "E:/Ӣ��ʱ��/����/ASMR" };

	//У��ʱ��
	time_level();

	//������ݿ��ʼ��״̬
	LSP_SQLite_db_status();	
}

//LSP_SQLite��������
LSP_SQLite::~LSP_SQLite()
{
	//�ͷŴ�����ݿ����Ƶ��ڴ��ַ
	if (LSP_SQLite_db != nullptr)
		delete(LSP_SQLite_db);
	
	//�ͷŴ��ʱ����ڴ��ַ
	if (local_time != nullptr)
		delete(local_time);
		
	//�ͷŴ��治ͬ·�����ڴ��ַ
	if (LSP_path != nullptr)
		delete[](LSP_path);	

	//������ݿ��Ƿ���������
	if (LSP_SQL_SQLite == nullptr)
		sqlite3_close(LSP_SQL_SQLite);
}

//UTF-8���� ת GBK����
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

//GBK���� ת UTF-8����
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