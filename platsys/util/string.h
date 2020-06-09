//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : 通用工具 字符串处理类
//  @ File Name : string.h
//  @ Date : 2013/5/13
//  @ Author : disp
//
//


#if !defined(_CSTRING_H)
#define _CSTRING_H


class CString
{
	
// Constructors, destructor
public:
	CString();
	CString(const CString& strSrc);
	CString(const char* pSrc);
	CString(const char ch);	
	~CString();
	
// Methods	
	int GetLength();					//获取字符串长度
	int CountCh(char ch);                               	//统计指定字符出现的次数	
	void MakeReverse();					//反转字符串的顺序
	void MakeUpper();					//将小写字母转为大写字母
	void MakeLower();					//将大写字母转换为小写字母
	int Compare(const char* pStr);				//区分大小写比较两个字符串
	int Delete(int nIndex, int nCount = 1);			//删除指定内容
	int Insert(int nIndex, char* pStr);			//插入指定内容
	int Remove(char chRemove);				//删除指定的字符
	int Replace(char chOld, char chNew);			//用指定的新字符替代旧字符
	void Trim();						//剔除字符串前后空格
	void TrimLeft();					//剔除字符串前面的空格
	void TrimRight();					//剔除字符串后面的空格
	int Find(const char* pFind, int nStart = 0);		//查找指定字符串的首次出现位置
	int Find(char chFind, int nStart = 0);			//查找指定字符的首次出现位置
	int ReverseFind(char chFind);				//查找指定字符的最后出现位置
	CString Left(int nCount);				//从左侧提取指定长度的字符串内容
	CString Right(int nCount);				//从右侧提取指定长度的字符串内容
	CString Mid(int nFirst, int nCount);			//提取指定位置和长度的字符串内容
	char* c_str() const;					//获取c类型的字符串
	void Format(char *fmt, ...);				//类似sprintf的格式化输出

// Methods 	
	bool IsEmpty();                                     //是否为空
	bool IsNumeric();				    //检测是否全部由数字0~9，+/-及小数点.组成
	bool IsDigit();                                     //检测是否全部由数字0~9组成
	bool IsUpper();                                     //检测是否全部由大写字母组成
	bool IsLower();                                     //检测是否全部由小写字母组成	
	bool IsZeros();                                     //检测是否全部由'0'组成，或为空
	bool IsSpaces();                                    //检测是否全部由' ' 或'\t'组成，或为空

	
// Operators
	CString& operator =(const CString& strSrc);				//重载运算符 =
	CString& operator =(const char* pSrc);					//重载运算符 =
	CString& operator =(char chSrc);					//重载运算符 =
	void operator+=(const char* pAdd);					//重载运算符 +=
    void operator+=(const CString& strAdd);					//重载运算符 +=
    void operator+=(char chAdd);						//重载运算符 +=
	bool operator==(const char* s);						//重载运算符 ==
	bool operator==(const CString& str);					//重载运算符 ==
	bool operator!=(const char* s);						//重载运算符 !=
	bool operator!=(const CString& str);					//重载运算符 !=	
	bool operator<(const char* s) const;					//重载运算符 <
	bool operator<(const CString& str) const;				//重载运算符 <	
	char& operator[](int nIdx);						//重载运算符 []													//重载运算符 []
	friend CString operator+(const CString& s1, const CString& s2);		//重载运算符 +
	operator const char *() const;						//重载运算符 (const char*)
	
// Data
protected:
    int   m_size;
    char* m_pstring;
    
// Private methods
private:
    void init(int size);  
    void assign(const char* pstr);  	
};

#endif  //_CSTRING_H
