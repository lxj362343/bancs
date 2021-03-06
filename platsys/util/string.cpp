//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : 通用工具 字符串处理类 
//  @ File Name : string.cpp
//  @ Date : 2013/5/13
//  @ Author : disp
//
//


#include "util/string.h"
#include "util/utilmisc.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

CString::CString()
{
	init(-1);
}

CString::CString(const CString& strSrc)
{
    assign(strSrc.c_str());

}

CString::CString(const char* pSrc)
{
    assign(pSrc);
}

CString::CString(const char ch)
{
	char sz[2];
	sz[0]=ch;
	sz[1]='\0';
    assign(sz);
}


CString::~CString(void)
{
	if(m_pstring)
        delete [] m_pstring;
    
   m_pstring=NULL;
}

void CString::init(int size)
{
    m_size            = (size > 0) ? size : 0;
    m_pstring         = new char [m_size+1];
    m_pstring[0]      = '\0';
    m_pstring[m_size] = '\0';
}

void CString::assign(const char* pstr)
{
	m_size = strlen(pstr);
	init(m_size);
	memcpy(m_pstring, pstr, m_size);
	m_pstring[m_size] = '\0';

}

int CString::GetLength()
{
	return strlen(m_pstring);
}

bool CString::IsEmpty()
{
	return (strlen(m_pstring)<=0)? true : false;
}

bool CString::IsNumeric()
{
    bool bNumeric = true;

    int nLen = GetLength();
    if(nLen <= 0)
        return false;

    for(int idx = 0; idx < nLen; idx++)
    {
        if(m_pstring[idx] < '0' || m_pstring[idx] > '9') 
        {
            if(m_pstring[idx]!= '.' && m_pstring[idx] != '+' && m_pstring[idx] != '-') 
            {
                bNumeric = false;
                break;
            }
        }
    }
     
    //判断+ - . 的位置以及出现数量，按照Bancs的格式，+/-可以出现在尾部
    if(bNumeric)
    {
        int nPoint = CountCh('.');
        int nPlus  = CountCh('+');
        int nMinus = CountCh('-');
        if( nPoint > 1 || nPlus > 1 || nMinus > 1 || (nPlus==1 && nMinus==1) )
            bNumeric = false;           
        else if(nPlus==1 && (m_pstring[0] != '+' || m_pstring[nLen-1]!='+'))
            bNumeric = false; 
        else if(nMinus==1 && (m_pstring[0] != '-' || m_pstring[nLen-1]!='-'))
            bNumeric = false;     
    
    }

    return bNumeric;
}

bool CString::IsDigit()
{
    bool bDigit = true;

    int nLen = GetLength();
    if(nLen <= 0)
        return false;

    for(int idx = 0; idx < nLen; idx++)
    {
        if(m_pstring[idx] < '0' || m_pstring[idx] > '9')  //(!isdigit(m_pstring[idx]))
        {
            bDigit = false;
            break;
        }
     }

    return bDigit;    
}

bool CString::IsUpper()
{
    bool bUpper = true;

    int nLen = GetLength();
    if(nLen <= 0)
        return false;

    for(int idx = 0; idx < nLen; idx++)
    {
        if(m_pstring[idx] < 'A' || m_pstring[idx] > 'Z')  //(!isupper(m_pstring[idx]))
        {
            bUpper = false;
            break;
        }
     }

    return bUpper;     
}

bool CString::IsLower()
{
    bool bLower = true;

    int nLen = GetLength();
    if(nLen <= 0)
        return false;

    for(int idx = 0; idx < nLen; idx++)
    {
        if(m_pstring[idx] < 'a' || m_pstring[idx] > 'z')  //(!islower(m_pstring[idx]))
        {
            bLower = false;
            break;
        }
     }

    return bLower;      
}

bool CString::IsZeros()
{
    bool b = true;

    int nLen = GetLength();
    for(int idx = 0; idx < nLen; idx++)
    {
        if(m_pstring[idx] != '0')
        {
            b = false;
            break;
        }
     }

    return b;      
}
    
bool CString::IsSpaces()
{
    bool b = true;

    int nLen = GetLength();
    for(int idx = 0; idx < nLen; idx++)
    {
        if(m_pstring[idx] != ' ' && m_pstring[idx] != '\t')
        {
            b = false;
            break;
        }
     }

    return b; 
}    

int CString::CountCh(char ch)
{
    int nCount = 0;
    int nLen = GetLength();
    for (int idx = 0; idx < nLen; idx++)
    {
        if(m_pstring[idx] == ch)
            nCount++;

     }

    return nCount;     
    
}

void CString::MakeReverse()
{
    char * pnew = new char[m_size+1];
		
	for(int n=0;n<m_size;n++)
	{
		pnew[n] = m_pstring[m_size-1-n];
	}
	pnew[m_size] = '\0';

    delete [] m_pstring;
    m_pstring = pnew;
}

void CString::MakeUpper()
{
    for (int i = 0; i < GetLength(); i++)
        m_pstring[i] = toupper(m_pstring[i]);
}

void CString::MakeLower()
{
    for (int i = 0; i < GetLength(); i++)
        m_pstring[i] = tolower(m_pstring[i]);
}

int CString::Compare(const char* pStr)
{
	return strcmp(c_str(),pStr);   //stricmp strcasecmp
}

int CString::Delete(int nIndex, int nCount)
{
	if(nIndex<0 || nIndex > GetLength()-1 || nCount<1)
		return -1;
		
	char *p = new char[GetLength()+1];
	memset(p,0,GetLength()+1);
	
	int nIdx=0,nCountTemp=0;
	
	for(int n=0;n<GetLength();n++)
	{
		if(n>=nIndex && nCountTemp<nCount)
		{
				nCountTemp++;
				continue;
		}
		else
		{
			p[nIdx++] = m_pstring[n];				
			
		}
		
	}
		
	char * pold = m_pstring;
    assign(p);
    delete [] pold;	
		
	delete [] p;
	
	return GetLength();
}

int CString::Insert(int nIndex, char* pStr)
{
	if(nIndex<0 || nIndex > GetLength()-1 || pStr==NULL)
		return -1;

	int len = strlen(pStr);
	int newlen  = strlen(pStr) + GetLength();

	char * pold = m_pstring;

	init(newlen);
	
	int nIdx=0;
	for(int n=0;n<newlen;n++)
	{
		if(n<nIndex)
			m_pstring[n] = pold[n];
		else if(n>=nIndex && n<(nIndex+len)) //插入内容的位置
			m_pstring[n] = pStr[nIdx++];			
		else
				m_pstring[n] = pold[n-len];			
		
	}


	delete [] pold;
			
    return GetLength();
}

int CString::Remove(char chRemove)
{
    char *p = new char[GetLength()+1];
    memset(p,0,GetLength()+1);
    
    int nIdx=0;
    for(int n=0;n<GetLength();n++)
    {
    	if(m_pstring[n] != chRemove)
    		p[nIdx++] = m_pstring[n];
    	
    }
    
    char * pold = m_pstring;
    assign(p);
    delete [] pold;	
		
    delete [] p;
    
    return GetLength();
}

int CString::Replace(char chOld, char chNew)
{
	for(int n=0;n<GetLength();n++)
	{
		if(m_pstring[n] == chOld)
			m_pstring[n] = chNew;
	}
	
	return GetLength();
}

void CString::Trim()
{
	TrimLeft();
	TrimRight();

}

void CString::TrimLeft()
{
	
    char* p = NULL;
    for(int n=0;n<GetLength();n++)
    {
    	if(m_pstring[n] != ' ' && m_pstring[n] != '\t')
    	{
    		p = &(m_pstring[n]);
    		break;
    	}
    }
		
	char * pold = m_pstring;
    assign(p);
    delete [] pold;
    		
   
}

void CString::TrimRight()
{
    for(int n = GetLength()-1; n >= 0; n--)
    {
    	if(m_pstring[n] == ' ' || m_pstring[n] == '\t')
    		m_pstring[n] = '\0';
    	else
    		break;
    }
    
    char * pold = m_pstring;
    assign(m_pstring);
    delete [] pold;
    	
	
}
int CString::Find(const char* pFind, int nStart)
{
	if(nStart > GetLength()-1)
		return -1;
		
	if(nStart < 0)
		nStart = 0;
		
	char* pStart = (char*)&m_pstring[nStart];
    const char * pfound = strstr(pStart, pFind);
    if (!pfound)
        return -1;

    //return pfound - pStart;	
    return pfound - pStart + nStart;    //2014.11.3	    
}

int CString::Find(char chFind, int nStart)
{
	if(nStart < 0)
		nStart = 0;

	int nIdx=-1;
    for(int n = nStart; n < GetLength(); n++)
    {
        if((*this)[n] == chFind)
        {
        	nIdx =  n;
        	break;
        }
	}

    return nIdx;
}

int CString::ReverseFind(char chFind)
{
	int nIdx=-1;
    for(int n = GetLength()-1; n >= 0; n--)
    {
    	if((*this)[n] == chFind)
        {
        	nIdx =  n;
        	break;
        }
	}

    return nIdx;
}

CString CString::Left(int nCount)
{
	char *pLeft = new char[GetLength()+1];
	memset(pLeft,0,GetLength()+1);
	
	if(nCount<0 || nCount>GetLength())
		nCount = GetLength();
	
	for(int n=0;n<GetLength() && n<nCount;n++)
	{
		pLeft[n] = m_pstring[n];
		
	}
		
	CString strTemp(pLeft);
    
    delete[] pLeft;
    		
    return strTemp;
}

CString CString::Right(int nCount)
{
    char *pRight = new char[GetLength()+1];
    memset(pRight,0,GetLength()+1);
    
    if(nCount<0 || nCount>GetLength())
    	nCount = GetLength();
    			
    int nIdx=0;
    for(int n=GetLength()-nCount;n<GetLength() && nIdx<nCount;n++)
    {
    	pRight[nIdx++] = m_pstring[n];
    	
    }
		
	CString strTemp(pRight);
    
    delete[] pRight;
    		
    return strTemp;
}

CString CString::Mid(int nFirst, int nCount)
{
    char *pMid = new char[GetLength()+1];
    memset(pMid,0,GetLength()+1);
    
    if(nFirst<0)
    	nFirst = 0;
    if(nCount<0 || nCount>GetLength())
    	nCount = GetLength();
    			
    int nIdx=0;
    for(int n=nFirst;n<GetLength() && nIdx<nCount;n++)
    {
    	pMid[nIdx++] = m_pstring[n];
    	
    }
		
	CString strTemp(pMid);
    
    delete[] pMid;
    		
    return strTemp;
}

char* CString::c_str() const
{
	return m_pstring;
}

CString& CString::operator =(const CString& strSrc)
{
    char * pold = m_pstring;
    assign(strSrc.c_str());
    delete [] pold;

    return *this;
}

CString& CString::operator =(const char* pSrc)
{
    char * pold = m_pstring;
    assign(pSrc);
    delete [] pold;

    return *this;
}

CString& CString::operator=(char chSrc)
{
    delete [] m_pstring;

    init(1);
    m_pstring[0] = chSrc;

    return *this;
}

void CString::operator+=(const char* pAdd)
{
	int len     = strlen(pAdd);
	int newlen  = len + GetLength();
    int oldsize = GetLength();

	char * pold = m_pstring;

	init(newlen);

	memcpy(m_pstring, pold, oldsize);
	memcpy(&m_pstring[oldsize], pAdd, len);

	delete [] pold;
	
}

void CString::operator+=(char chAdd)
{
    char str[2];
    str[0] = chAdd;
    str[1] = '\0';

    CString::operator+=(str);
}

void CString::operator+=(const CString& strAdd)
{
    CString::operator+=(strAdd.c_str());
}

bool CString:: operator==(const char* s)
{
    int len = strlen(s);
    if (len != GetLength())
        return false;

    return memcmp(m_pstring, s, len) == 0;
}

bool CString::operator==(const CString& str)
{
    return operator==(str.c_str());
}

bool CString:: operator!=(const char* s)
{
    return !(operator==(s));
}

bool CString::operator!=(const CString& str)
{
    return operator!=(str.c_str());
}


bool CString:: operator<(const char* s) const
{
    /*
        int strcmp(s1,s2); //自左向右逐个字符按ASCII值大小比较
        当s1<s2时，返回为负数 注意不是-1
        当s1=s2时，返回值= 0
        当s1>s2时，返回正数 注意不是1
    */
    
    return strcmp(m_pstring, s)<0; //map中key使用，是降序
    
}

bool CString::operator<(const CString& str) const
{
    return operator<(str.c_str());
}

char& CString::operator[](int nIdx)
{
    //若非引用，则仅能获取不能修改
    if (nIdx < 0)
        nIdx = 0;
    if (nIdx >= GetLength())
        nIdx = GetLength()-1;

    return m_pstring[nIdx];
}

CString operator+(const CString& s1, const CString&s2)
{
	CString strTemp(s1);
	strTemp += s2;
    		
    return strTemp;
}


CString::operator const char *() const
{

    return m_pstring;
}

// format a string
void CString::Format(char *fmt, ...)
{
	const int BUF_SIZE = 8*1024;
	char TmpBuffer[BUF_SIZE]; // TODO, should calculate this size dynamically.
	
	va_list argList;
	va_start(argList, fmt);
	vsnprintf(TmpBuffer, BUF_SIZE, fmt, argList);
	//vsprintf(TmpBuffer, fmt, argList);
	va_end(argList);
	
    char * pold = m_pstring;
    assign(TmpBuffer);
    delete [] pold;	

}