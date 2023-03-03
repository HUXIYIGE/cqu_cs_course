#include <stdlib.h>
#include<iostream>
#include<stdio.h>
#include<cstring>
#include<map>
#include <fstream>
#include <unordered_map>
using namespace std; 

//------------------------词法分析的变量---------------------------
const int MAXN=2000;
//词法分析token序列
string token[MAXN];		
string val[MAXN];
int row[MAXN];
int col[MAXN];
int p = 0;
int cnmd =0;
int line=1;
int cur=0;

//------------------------词法分析的函数---------------------------
//看是否为数字
bool number(char A){
	if(A>='0'&&A<='9')
		return true;
	return false;
}
//看是否为字母或下划线 
bool letter(char A){
	if((A=='_')||(A>='A'&&A<='Z')||(A>='a'&&A<='z'))
		return true;
	return false;
}
//看是否是保留字或标识符 
bool reserved_word(string s){
	if(s=="const")
	{
		token[p++] = "CONSTTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="int"){
		token[p++] = "INTTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="char"){
		token[p++] = "CHARTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="void"){
		token[p++] = "VOIDTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="main"){
		token[p++] = "MAINTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="if"){
		token[p++] = "IFTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="else"){
		token[p++] = "ELSETK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="do"){
		token[p++] = "DOTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="while"){
		token[p++] = "WHILETK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="for"){
		token[p++] = "FORTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="scanf")
	{
		token[p++] = "SCANFTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="printf")
	{
		token[p++] = "PRINTFTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="return")
	{ 
		token[p++] = "RETURNTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="switch")
	{ 
		token[p++] = "SWITCHTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="case")
	{ 
		token[p++] = "CASETK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="default")
	{ 
		token[p++] = "DEFAULTTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="PRINTF")
	{ 
		token[p++] = "PRINTFTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="printF"){
		token[p++] = "PRINTFTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	return false;
}
void lexical_analysis(){
	//标识符、整数、字符、字符串、保留字、运算符、分界符
	FILE *f;
	char CHAR;
	f=fopen("testfile.txt","r"); 
	//读取文件并处理
	while((CHAR=fgetc(f))!=EOF){
		cur++;
		//除了空格和Tab全读取
		while(CHAR!=' '&&int(CHAR)!=9){
			//以字母或开头,要么是保留字，要么是标识符 
			if(letter(CHAR)){
				string s="";
				int k=0;
				do{
					s+=CHAR;
				}
				while((CHAR=fgetc(f))!=EOF&&CHAR!=' '&&(letter(CHAR)||number(CHAR)));
				fseek(f,-1,SEEK_CUR);
				if(!(reserved_word(s)))//判断标识符是保留字还是标识符 
				{
					token[p++] = "IDENFR";
					val[cnmd++] = s;
					row[p-1]=line;
					col[p-1]=cur;
				} 
				cur+=s.length();
			}
			//整数
			else if(number(CHAR)){
				string s="";
				int i=0;
				do{
					s+=CHAR;
		
				}
				while((CHAR=fgetc(f))!=EOF&&CHAR!=' '&&number(CHAR));
				fseek(f,-1,SEEK_CUR);
				token[p++] = "INTCON";
				val[cnmd++] = s;
				row[p-1]=line;
				col[p-1]=cur;
				cur+=s.length();
			}
			//运算符 
			else if(CHAR=='+'){
				token[p++] = "PLUS";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR=='-'){
				token[p++] = "MINU";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR=='*'){
				token[p++] = "MULT";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			//不用处理注释
			else if(CHAR=='/'){
				token[p++] = "DIV";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR=='='){
				//后一个符号也是等于
				if((CHAR=fgetc(f))!=EOF&&CHAR=='=')
				{
					token[p++] = "EQL";
					val[cnmd++] = "==";
					row[p-1]=line;
					col[p-1]=cur;
					cur+=1;
				}
				//直接标记等号，然后回退
				else{
					token[p++] = "ASSIGN";
					val[cnmd++] = "=";
					row[p-1]=line;
					col[p-1]=cur;
					fseek(f,-1,SEEK_CUR);
					break;
				}
			}
			else if(CHAR=='<'){
				//小于等于
				if((CHAR=fgetc(f))!=EOF&&CHAR=='='){
					token[p++] = "LEQ";
					val[cnmd++] = "<=";
					row[p-1]=line;
					col[p-1]=cur;
					cur+=1;
				}
				//小于，回退，因为向后读取了一个字符
				else {
					token[p++] = "LSS";
					val[cnmd++] = "<";
					row[p-1]=line;
					col[p-1]=cur;
					fseek(f,-1,SEEK_CUR);
				}
			}
			else if(CHAR=='>'){
				//大于等于
				if((CHAR=fgetc(f))!=EOF&&CHAR=='='){
					token[p++] = "GEQ";
					val[cnmd++] = ">=";
					row[p-1]=line;
					col[p-1]=cur;
					cur+=1;
				}
				//大于，回退，因为向后读取了一个字符
				else {
					token[p++] = "GRE";
					val[cnmd++] = ">";
					row[p-1]=line;
					col[p-1]=cur;
					fseek(f,-1,SEEK_CUR);
				}
			}
			else if(CHAR=='!'){
				//不等于
				if((CHAR=fgetc(f))!=EOF&&CHAR=='='){
					token[p++] = "NEQ";
					val[cnmd++] = "!=";
					row[p-1]=line;
					col[p-1]=cur;
					cur+=1;
				}
				//感叹号后只可能是等于
			}
			//分界符
			else if(CHAR=='('){
				token[p++] = "LPARENT";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR==')'){
				token[p++] = "RPARENT";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR=='['){
				token[p++] = "LBRACK";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR==']'){
				token[p++] = "RBRACK";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR=='{'){
				token[p++] = "LBRACE";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR=='}'){
				token[p++] = "RBRACE";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			//标点符号
			else if(CHAR==':'){
				token[p++] = "COLON";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR==';'){
				token[p++] = "SEMICN";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR==','){
				token[p++] = "COMMA";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			//判断字符和字符串
			//如果是单影号，字符
			else if(CHAR=='\''){
				string s = ""; 
				while((CHAR=fgetc(f))!=EOF&&CHAR!='\'')
				{
					s+=CHAR;
				
				}
				token[p++] = "CHARCON";
				val[cnmd++] = s;
				row[p-1]=line;
				col[p-1]=cur+1;
				cur+=s.length()+1;
			}
			//如果是双赢号，字符串
			else if(CHAR=='"'){
				string s = ""; 
				while((CHAR=fgetc(f))!=EOF&&CHAR!='"')
				{
					s+=CHAR;	
				}
				token[p++] = "STRCON";
				val[cnmd++] = s;
				row[p-1]=line;
				col[p-1]=cur+1;
				cur+=s.length()+1;
			}
			else if(CHAR=='\n'){
				line++;
				cur=0;
			}
			else{
				//错误处理接口
				cout<<"\""<<CHAR<<"\""<<" in line "<<line<<" , column "<<cur<<endl;
				throw "illegal input";
			}
			break;
		}
	}
	fclose(f);
	for(int i=0;i<p;i++){
		cout<<token[i]<<" "<<val[i]<<" "<<row[i]<<" "<<col[i]<<endl;
	}
}


//-------------------------语法分析--------------------------
class yufafenxi{
private:
	string curtok="";
	string unregonized="";
	int toknum=0;
	int curindex=0;
	unordered_map<string, bool> has_retval;
	ofstream fout;
public:
	void nexttoken(){
	if(curindex<toknum){
		curtok=token[curindex++];
		fout<<token[curindex-1]<<" "<<val[curindex-1]<<endl;
	}
	else{
		curtok=unregonized;
	}
}
	string seek(int step){
		if(step+curindex>=0&&curindex+step-1<toknum){
			return token[curindex+step-1];
		}
		else{
			return unregonized;
		}
	}

	//无符号整数
	void unsigned_integer(){
		if(curtok=="INTCON"){
			fout << "<无符号整数>" << endl;
		}
	}

	//整数
	void integer(){
		if(curtok=="PLUS"||curtok=="MINU"){
			nexttoken();
			unsigned_integer();
		}
		else if(curtok=="INTCON"){
			unsigned_integer();
		}
		fout << "<整数>" << endl;
	}

	//常量定义
	void constant_def(){
		if(curtok=="INTTK"){
			nexttoken();
			nexttoken();
			nexttoken();
			integer();
			while (seek(1)=="COMMA"){
				nexttoken();
				nexttoken();
				nexttoken();
				nexttoken();
				integer();
			}
		}
		if(curtok=="CHARTK"){
			nexttoken();
			nexttoken();
			nexttoken();
			while (seek(1)=="COMMA"){
				nexttoken();
				nexttoken();
				nexttoken();
				nexttoken();
			}
		}
		fout << "<常量定义>" << endl;
	}

	//常量说明
	void constant_desc(){
		nexttoken();
		constant_def();
		nexttoken();
		while (seek(1)=="CONSTTK"){
			nexttoken();
			nexttoken();
			constant_def();
			nexttoken();
		}
		fout<< "<常量说明>" << endl;
	}

	// 变量定义
	void variable_def(){
		cout<<"variable_def"<<endl;
		if(seek(2)=="ASSIGN"||(seek(4)=="RBRACK"&&seek(5)=="ASSIGN")||(seek(4)=="RBRACK"&&seek(7)=="RBRACK"&&seek(8)=="ASSIGN")){
			nexttoken();
			if(seek(1)=="ASSIGN"){
				nexttoken();
				if(seek(1)=="CHARCON"){
					nexttoken();
				}
				else{
					nexttoken();
					integer();
				}
				fout<<"<常量>"<<endl;
			}
			else if(seek(4)=="ASSIGN"){
				nexttoken();//[
				nexttoken();//ui
				unsigned_integer();
				nexttoken();//]
				nexttoken();//=
				nexttoken();//{
				if(seek(1)=="CHARCON"){
					nexttoken();
				}
				else{
					nexttoken();
					integer();
				}
				fout<<"<常量>"<<endl;
				while (seek(1)=="COMMA")
				{
					nexttoken();
					if(seek(1)=="CHARCON"){
						nexttoken();
					}
					else{
						nexttoken();
						integer();
					}
					fout<<"<常量>"<<endl;
				}
				nexttoken();//{
			}
			else if(seek(7)=="ASSIGN"){
				nexttoken();//[
				nexttoken();//ui
				unsigned_integer();
				nexttoken();//]
				nexttoken();//[
				nexttoken();
				unsigned_integer();
				nexttoken();//]
				nexttoken();//=
				nexttoken();//{
				nexttoken();//{
				if(seek(1)=="CHARCON"){
					nexttoken();
				}
				else{
					nexttoken();
					integer();
				}
				fout<<"<常量>"<<endl;
				while (seek(1)=="COMMA")
				{
					nexttoken();
					if(seek(1)=="CHARCON"){
						nexttoken();
					}
					else{
						nexttoken();
						integer();
					}
					fout<<"<常量>"<<endl;
				}	
				nexttoken();//}
				while (seek(1)=="COMMA")
				{
					nexttoken();
					nexttoken();
					if(seek(1)=="CHARCON"){
						nexttoken();
					}
					else{
						nexttoken();
						integer();
					}
					fout<<"<常量>"<<endl;
					while (seek(1)=="COMMA"){
						nexttoken();
						if(seek(1)=="CHARCON"){
							nexttoken();
						}
						else{
							nexttoken();
							integer();
						}
						fout<<"<常量>"<<endl;
					}
					nexttoken();
				}
				nexttoken();//}
			}
			fout << "<变量定义及初始化>" << endl;
		}
		else{
			nexttoken();
			if(seek(1)=="LBRACK"){
				nexttoken();
				nexttoken();
				unsigned_integer();
				nexttoken();
				if(seek(1)=="LBRACK"){
					nexttoken();
					nexttoken();
					unsigned_integer();
					nexttoken();
				}
			}
			while (seek(1)=="COMMA"){
				nexttoken();
				nexttoken();
				if(seek(1)=="LBRACK"){
					nexttoken();
					nexttoken();
					unsigned_integer();
					nexttoken();
					if(seek(1)=="LBRACK"){
						nexttoken();
						nexttoken();
						unsigned_integer();
						nexttoken();
					}
				}
			}
			fout << "<变量定义无初始化>" << endl;
		}
		fout << "<变量定义>" << endl;
	}
	//变量说明
	void variable_desc(){
		cout<<"variable_desc"<<endl;
		variable_def();
		nexttoken();
		while ((seek(1)=="INTTK"||seek(1)=="CHARTK")&&(seek(3)=="SEMICN"||\
		seek(3)=="COMMA"||seek(3)=="ASSIGN"||seek(3)=="LBRACK")){
			nexttoken();
			variable_def();
			nexttoken();
		}
		fout <<"<变量说明>" << endl;
	}

	//声明头部
	void declaration_header(){
		nexttoken();
		has_retval.insert(pair<string,bool>(val[curindex-1],true));
		fout << "<声明头部>" << endl;
	}
	//参数表
	void parameters_table(){
	if (curtok == "INTTK" || curtok == "CHARTK") {
        nexttoken();//eat 类型标识符
        while (seek(1)== "COMMA") {
            nexttoken();//eat 类型标识符
			nexttoken();
			nexttoken();
        }
    }
	fout << "<参数表>" << endl;
}
	//＜因子＞ ::= ＜标识符＞
//          ｜＜标识符＞'['＜表达式＞']'
//			｜＜标识符＞'['＜表达式＞']''['＜表达式＞']'
//          |'('＜表达式＞')'
//          ｜＜整数＞
//          |＜字符＞
//          ｜＜有返回值函数调用语句＞
	void factor(){
		cout<<"factor"<<endl;
		if(curtok=="IDENFR"){
			if(has_retval[val[curindex-1]]){
				funcall();
			}
			else if(seek(1)=="LBRACK"){
				nexttoken();
				nexttoken();
				express();
				nexttoken();
				if(seek(1)=="LBRACK"){
					nexttoken();
					nexttoken();
					express();
					nexttoken();
				}
			}
		}
		else if(curtok=="LPARENT"){
			nexttoken();
			express();
			nexttoken();
		}
		else if(curtok=="INTCON"||curtok=="PLUS"||curtok=="MINU"){
			integer();
		}
		else if(curtok=="CHARCON"){
			//do nothing
		}
		fout<<"<因子>"<<endl;
	}

	//item
	void item(){
		cout<<"item"<<endl;
		factor();
		while (seek(1)=="MULT"||seek(1)=="DIV"){
			nexttoken();
			nexttoken();
			factor();
		}
		fout << "<项>" << endl;
	}

	//express
	void express(){
		cout<<"express"<<endl;
		if(curtok=="PLUS"||curtok=="MINU"){
			nexttoken();
		}
		item();
		while(seek(1)=="PLUS"||seek(1)=="MINU"){
			nexttoken();
			nexttoken();
			item();
		}
		fout << "<表达式>" << endl;
	}

	//condition
	void conditon(){
		cout<<"conditon"<<endl;
		express();
		
		if(seek(1)=="LSS"||seek(1)=="LEQ"||seek(1)=="GRE"||seek(1)=="GEQ"||seek(1)=="EQL"||seek(1)=="NEQ"){
			nexttoken();
			nexttoken();
			express();
		}
		fout << "<条件>" << endl;	
	}
	//condition statement
	void condition_statement(){
		nexttoken();
		nexttoken();
		conditon();
		nexttoken();
		nexttoken();
		statement();
		if(seek(1)=="ELSETK"){
			nexttoken();
			nexttoken();
			statement();
		}
		fout << "<条件语句>" << endl;
	}
	//Value parameter table
	void value_par_table(){
		express();
		while (seek(1)=="COMMA")
		{
			nexttoken();
			nexttoken();
			express();
		}
		fout << "<值参数表>" << endl;
	}
	//funcall
	void funcall(){
		nexttoken();
		if(seek(1)!="RPARENT"){
			nexttoken();
			value_par_table();
			nexttoken();
		}
		else{
			fout<<"<值参数表>"<<endl;
			nexttoken();
		}
		fout<< "<有返回值函数调用语句>" << endl;
	}
	//
	void voidfuncall(){
		nexttoken();
		if(seek(1)!="RPARENT"){
			nexttoken();
			value_par_table();
			nexttoken();
		}
		else{
			fout<<"<值参数表>"<<endl;
			nexttoken();
		}
		fout<< "<无返回值函数调用语句>" << endl;

	}
	//＜赋值语句＞ ::= ＜标识符＞＝＜表达式＞
	//              |＜标识符＞'['＜表达式＞']'=＜表达式＞
	//              |＜标识符＞'['＜表达式＞']''['＜表达式＞']'=＜表达式＞
	void assign_statement(){
		cout<<"assign_statement"<<endl;
		nexttoken();
		if(curtok=="ASSIGN"){
			nexttoken();
			express();
		}
		else{
			nexttoken();
			express();
			nexttoken();
			if(seek(1)=="ASSIGN"){
				nexttoken();
				nexttoken();
				express();
			}
			else{//seek(1)="["
				nexttoken();
				nexttoken();
				express();
				nexttoken();
				nexttoken();
				nexttoken();
				express();
			}
		}
		fout<<"<赋值语句>"<<endl;
	}

	//step
	void step(){
		unsigned_integer();
		fout << "<步长>" << endl;
	}
	//＜循环语句＞ ::= while '('＜条件＞')'＜语句＞
	//        | do＜语句＞while '('＜条件＞')'
	//        |for'('＜标识符＞＝＜表达式＞;＜条件＞;＜标识符＞＝＜标识符＞(+|-)＜步长＞')'＜语句＞
	void loop_statement(){
		if(curtok=="WHILETK"){
			nexttoken();
			nexttoken();
			conditon();
			nexttoken();
			nexttoken();
			statement();
		}
		else if(curtok=="FORTK"){
			nexttoken();
			nexttoken();
			nexttoken();
			nexttoken();
			express();
			nexttoken();
			nexttoken();
			conditon();
			nexttoken();
			nexttoken();
			nexttoken();
			nexttoken();
			nexttoken();
			nexttoken();
			step();
			nexttoken();
			nexttoken();
			statement();
		}
		fout << "<循环语句>" << endl;
	}

	//read statement
	void read_statement(){
		nexttoken();
		nexttoken();
		nexttoken();
		fout << "<读语句>" << endl;
	}

	//string
	void str(){
		if(curtok=="STRCON"){
			fout<< "<字符串>" << endl;
		}
	}

	//write statement
	void write_statement(){
		nexttoken();
		nexttoken();
		if(curtok=="STRCON"){
			if(seek(1)=="COMMA"){
				str();
				nexttoken();
				nexttoken();
				express();
				nexttoken();
			}
			else{
				str();
				nexttoken();
			}
		}
		else{
			express();
			nexttoken();
		}
		fout << "<写语句>" << endl;

	}

	//＜返回语句＞ ::= return['('＜表达式＞')']
	void return_statement(){
		if(seek(1)=="LPARENT"){
			nexttoken();
			nexttoken();
			express();
			nexttoken();
		}
		else{
			//do nothing
		}
		fout<<"<返回语句>"<<endl;
	}

	//case clause
	void case_clause(){
		cout<<"case_clause"<<endl;
		nexttoken();
		if(curtok=="PLUS"||curtok=="MINU"||curtok=="INTCON"||curtok=="CHARCON"){
			if(curtok!="CHARCON"){
				integer();
			}
			fout<<"<常量>"<<endl;
		}
		nexttoken();
		nexttoken();
		statement();
		fout<<"<情况子语句>"<<endl;
	}
	//Fact Sheet
	void fact_sheet(){
		cout<<"fact_sheet"<<endl;
		case_clause();
		if(seek(1)=="CASETK"){
			nexttoken();
			case_clause();
		}
		fout<<"<情况表>"<<endl;
	}
	void deft(){
		nexttoken();
		nexttoken();
		statement();
		fout<<"<缺省>"<<endl;
	}
	//case statement
	void case_statement(){
		nexttoken();
		nexttoken();
		express();
		nexttoken();
		nexttoken();
		nexttoken();
		fact_sheet();
		nexttoken();
		deft();
		nexttoken();
		fout<<"<情况语句>"<<endl;
	}

	//语句
	void statement(){
		cout<<"statement"<<endl;
		if(curtok=="IFTK"){
			condition_statement();
		}
		else if(curtok=="WHILETK"||curtok=="FORTK"){
			loop_statement();
		}
		else if(curtok=="LBRACE"){
			if(seek(1)=="RBRACE"){
				fout << "<语句列>" << endl;
				nexttoken();
			}
			else{
				nexttoken();
				statement_column();
				nexttoken();
			}
		}
		else if(curtok=="IDENFR"){
			if(has_retval[val[curindex-1]]){
				funcall();
				nexttoken();
			}
			else if(seek(1)=="ASSIGN"||seek(1)=="LBRACK"){
				assign_statement();
				nexttoken();
			}
			else if(!has_retval[val[curindex-1]]){
				voidfuncall();
				nexttoken();
			}
			
		}
		else if(curtok=="SCANFTK"){
			read_statement();
			nexttoken();
		}
		else if(curtok=="PRINTFTK"){
			write_statement();
			nexttoken();
		}
		else if(curtok=="RETURNTK"){
			return_statement();
			nexttoken();
		}
		else if(curtok=="SWITCHTK"){
			case_statement();
		}
		else if(curtok=="SEMICN"){
			//nothing
		}
		fout<< "<语句>" << endl;
	}

	//语句列
	void statement_column(){
		cout<<"statement_column"<<endl;
		if (curtok!= "RBRACE") {
			while (seek(1)!= "RBRACE"&&curindex<toknum||curtok=="SEMICN") {
				statement();
				if (seek(1)!= "RBRACE"&&curindex<toknum) {
					nexttoken();
				}
				else if(seek(1)== "RBRACE"){
					break;
				}

			}
		}
		fout << "<语句列>" << endl;
	}

	//复合语句
	void compound_statement(){
		cout<<"compound_statement"<<endl;
		if(curtok=="CONSTTK"){
			constant_desc();
			nexttoken();
		}
		if(curtok=="CHARTK"||curtok=="INTTK"){
			variable_desc();
			nexttoken();
		}
		statement_column();
		fout << "<复合语句>" << endl;
	}

	//有返回值函数定义
	void func_def(){
		declaration_header();
		nexttoken();
		if (seek(1)!="RPARENT"){
			nexttoken();
			parameters_table();
			nexttoken();
		}else{
			fout << "<参数表>" << endl;
			nexttoken();
		}
		nexttoken();
		nexttoken();
		compound_statement();
		nexttoken();
		fout << "<有返回值函数定义>" << endl;
	}

	//无返回值函数定义
	void void_func_def(){
		nexttoken();
		has_retval.insert(pair<string, bool>(val[curindex-1], false));
		nexttoken();
		if (seek(1)!="RPARENT"){
			nexttoken();
			parameters_table();
			nexttoken();
		}else{
			fout << "<参数表>" << endl;
			nexttoken();
		}
		nexttoken();
		nexttoken();
		compound_statement();
		nexttoken();
		fout << "<无返回值函数定义>" << endl;
	}
	//main
	void mainfun(){
		cout<<"mainfun"<<endl;
		nexttoken();
		nexttoken();
		nexttoken();
		nexttoken();
		nexttoken();
		compound_statement();
		nexttoken();
		fout << "<主函数>" << endl;
	}
	void program(){
		cout<<"program"<<endl;
		nexttoken();
		if(curtok=="CONSTTK"){
			constant_desc();
			nexttoken();
		}
		if((curtok=="INTTK"||curtok=="CHARTK")&&(seek(2)=="SEMICN"||\
		seek(2)=="COMMA"||seek(2)=="ASSIGN"||seek(2)=="LBRACK")){
			variable_desc();
			nexttoken();
		}
		//函数定义
		while(((curtok=="INTTK"||curtok=="CHARTK")&&seek(2)=="LPARENT")\
		||(curtok=="VOIDTK"&&seek(2)=="LPARENT"&&seek(1)!="MAINTK")){
			if((curtok=="INTTK"||curtok=="CHARTK")&&seek(2)=="LPARENT"){
				func_def();
				nexttoken();
			}
			else{
				void_func_def();
				nexttoken();
			}
		}
		mainfun();
		fout << "<程序>" << endl;
	}
	//语法分析
	void start(){
		fout=ofstream("output.txt");
		toknum=p;
		program();
	}
};

int main(){
	try{
		lexical_analysis();
		yufafenxi yffx;
		yffx.start();
	}
	catch(const char * msg){
		cerr <<msg<<endl;
	}
	return 0;
}
