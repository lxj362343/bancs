//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : 日期跨度处理类
//  @ File Name : datetimespan.h
//  @ Date : 2014/5/6
//  @ Author : disp
//
//


#if !defined(_CDateTimeSpan_H)
#define _CDateTimeSpan_H


//=============================================================================
// Includes
//=============================================================================

#include <math.h>
#include <time.h>
#include "datetime.h"


//=============================================================================
// Classes
//=============================================================================

class CDateTimeSpan
{
// Constructors and destructor
public:
    CDateTimeSpan();
    CDateTimeSpan(const CDateTimeSpan & dtsSrc);
    CDateTimeSpan(const CDateTime & dtStart , const CDateTime & dtEnd);
    virtual ~CDateTimeSpan();
    
public:  
    CDateTime GetDTStart() const { return m_dtStart;   };
    CDateTime GetDTEnd()   const { return m_dtEnd;     };
    void SetDTStart(const CDateTime & dtStart) { m_dtStart  = dtStart;  };
    void SetDTEnd(const CDateTime & dtEnd)     { m_dtEnd    = dtEnd;    };    
    
public:  
    int GetYMDDetail(int& nYear,int& nMonth,int& nDay);	    //以年月日的方式表示时间跨度期
    int GetTotalYears(int& nYears);	                        //以年方式表示时间跨度
    int GetTotalMonths(int& nMonths);	                    //以月方式表示时间跨度
    int GetTotalDays(int& nDays);	                        //以日方式表示时间跨度 
    
// Data
private:
    CDateTime m_dtStart,m_dtEnd;

};


#endif  //_CDateTimeSpan_H

/*
//首先构造两个时间
CDateTime dtStart = CDateTime::FromText("20130401","YYYYMMDD");
//CDateTime dtStart(2013,4,1);
CDateTime dtEnd   = CDateTime::FromText("20140506");    //缺省格式："YYYYMMDD"
    
//然后构造span并进行计算
CDateTimeSpan dtSpan(dtStart,dtEnd);
//CDateTimeSpan dtSpan(CDateTime(2013,4,1),CDateTime::FromText("20140506")); //另一种构造方法
int nYear,nMonth,nDay;
int nYears;
if(dtSpan.GetYMDDetail(nYear,nMonth,nDay) == 0)
{
    //计算成功
}
if(dtSpan.GetTotalYears(nYears)==0)
{
    //计算成功    
}
*/

