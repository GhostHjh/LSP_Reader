# 代码结构

## 核心代码:

> LSP.cpp---------->main函数  
> LSP.h------------>和数据库交互，数据结构头文件(后续想要对其中功能做分离)   
> LSP.cpp---------->实现和数据库的交互以及数据筛选等工作  



## 依赖项

> ## sqlite依赖项:
> > shell.c--------->Sqlite数据库shell实现代码 
> > sqlite3.c------->Sqlite数据库接口代码  
> > sqlite3.h------->sqlite数据库接口头文件(使用中)   
> > sqlite3ext.h---->sqlite数据库接口头文件(暂时没有被使用)  
> > sqlite3.dll----->sqlite数据库动态链接库(def, exp, lib)  



## 其他

> sqlite_cs.db---->项目临时sqlite数据库  

