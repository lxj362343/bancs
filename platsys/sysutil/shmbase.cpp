//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : 技术平台公共类库
//  @ File Name : cshmbase.cpp
//  @ Date : 2013/7/17
//  @ Author : disp
//
//

#include "platspub.h"
#include "shmbase.h"

CIniConfig  CShmBase::m_config;
    
CShmBase::CShmBase()
{
	InitCfg(NULL);

}

CShmBase::CShmBase(const char* pFilePath)
{
	InitCfg(pFilePath);
}

CShmBase::~CShmBase()
{
	//UninitCfg();

}

int CShmBase::InitCfg(const char* pFilePath)
{
    if(m_config.IsInit())   //已经初始化
        return 0;
        
	if(pFilePath && strlen(pFilePath) >0)
		return m_config.Init(pFilePath);
	else
	{
		char szFilePath[255];
		sprintf(szFilePath,"%s/etc/shm.cfg",getenv("NCBS_HOME") );
		return m_config.Init(szFilePath);	
		
	}
		
		
}

void CShmBase::UninitCfg()
{
	m_config.Uninit();
}

CString CShmBase::GetCfgData(const char* pSection,const char* pKey)
{
	CString strData;
	char szData[1024]="";
	if(m_config.GetData(pSection,pKey,szData)==0)
	{
		strData = szData;
	}
	
	return strData;
}

CString CShmBase::GetCfgData(const char* pSection,const char* pKey,int nIndex)
{
	CString strData;
	char szData[1024]="";
	if(m_config.GetData(pSection,pKey,szData)==0)
	{
		strData = CUtilMisc::GetArgWithBreak(szData,nIndex);;
		strData.Trim();
	}
				
	return strData;
}
      
    
key_t CShmBase::GetAreaKey(int dsflag,char chSysNum)
{
	//shm_key  =  SHM_FLAGMASK  |  GetEnvKey()  |  GetDsKey() ;  
	if(dsflag < 0 || dsflag >= 4096)
	{
			fprintf(stderr,"Invalid valid ,dsflag = %d\n",dsflag);
			return 0;
	}
    
    key_t retval = (key_t)0;
    key_t regionid=(key_t)0,systemid=(key_t)0;
    char *env;
    if (!(env = getenv(REGION_ENV)))
	{
			fprintf(stderr,"environment variable not defined");
			return 0;
	}

	if (*env<'0' || *env>'9'){   
		if (*env<'A' || *env>'Z'){
			if (*env<'a' || *env>'z'){
				fprintf(stderr,"Invalid valid in environmental variable %s = %c\n",REGION_ENV,*env);
				return 0;
			}
		}
	}
	
	if ('A' <= *env && 'Z' >= *env )
			regionid = (key_t)(10+(*env - 'A'));
	else if ('a' <= *env && 'z' >= *env )
			regionid = (key_t)(36+(*env - 'a'));
	else if ('0' <= *env && '9' >= *env ) 
			regionid = (key_t)(*env - '0');
    
    
    if(chSysNum >='0' && chSysNum<='9')
        env = &chSysNum;
    else
        env = getenv(SYS_NUM_ENV);

   if (!(env))
	{
			fprintf(stderr,"environment variable not defined");
			return 0;
	}
	if (*env<'0' || *env>'9')
	{   
			fprintf(stderr,"Invalid valid in environmental variable %s = %c\n",SYS_NUM_ENV,*env);
			return 0;
	}

	systemid = (key_t)(*env - '0');

/*		
	key_t shm_flagmask;	
	CString str = GetCfgData("General","FLAGMASK");
	sscanf(str.c_str(), "%x", &shm_flagmask);
*/
	
	retval = SHM_FLAGMASK | systemid<<20 | regionid<<12 | dsflag;

    return(retval);		
		
}


