//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : ����ƽ̨�������
//  @ File Name : shmaccess.cpp
//  @ Date : 2013/7/23
//  @ Author : disp
//
//

#include <iostream>
#include <dlfcn.h>
#include "platspub.h"
#include "shmaccess.h"
#include "sysutil/arealock.h"

CShmAccess::CShmAccess()
{
	m_pMatAddress=NULL;
	m_pLock = new CAreaLock;
}

CShmAccess::CShmAccess(const char* pFilePath)
	:CShmBase(pFilePath)
{
	m_pMatAddress=NULL;
	m_pLock = new CAreaLock;
}

CShmAccess::~CShmAccess()
{
	if(m_pLock)
		delete m_pLock;
}

int CShmAccess::LoadDsexFn(const char* pFilePaht,DSEX_ACCESS* pDsexAccess)
{
	void *pHandle = dlopen(pFilePaht, RTLD_LOCAL|RTLD_LAZY);
	if(pHandle)
	{
		pDsexAccess->pvLibraryHandle 	= pHandle;
		pDsexAccess->pfnOpenSelect 		= (DA_OpenSelect*)	dlsym(pHandle,"DA_OpenSelect");
		pDsexAccess->pfnGetDataCount 	= (DA_GetDataCount*)dlsym(pHandle,"DA_GetDataCount");				
		pDsexAccess->pfnFetchData 		= (DA_FetchData*)	dlsym(pHandle,"DA_FetchData");
		pDsexAccess->pfnCloseSelect 	= (DA_CloseSelect*)	dlsym(pHandle,"DA_CloseSelect");	
		pDsexAccess->pfnUpdateData		= (DA_UpdateData*)	dlsym(pHandle,"DA_UpdateData");
		
															
		if(pDsexAccess->pfnOpenSelect == NULL 
		|| pDsexAccess->pfnGetDataCount == NULL 
		|| pDsexAccess->pfnFetchData == NULL
		|| pDsexAccess->pfnCloseSelect ==NULL
		|| pDsexAccess->pfnUpdateData ==NULL)		
		{
			printf("pDsexAccess->pfnxxx == NULL\n");
						
			FreeDsexFn(pDsexAccess);
			return -1;
		}
		
		return 0;					
	}		
	else
	{
		printf("pHandle == NULL\n");
		return -1;
	}
				
}

int CShmAccess::FreeDsexFn(DSEX_ACCESS* pDsexAccess)
{
	if(pDsexAccess->pvLibraryHandle)
	{
		 dlclose(pDsexAccess->pvLibraryHandle);
		 pDsexAccess->pvLibraryHandle = NULL;	
	}
	
	 return 0;
}

int CShmAccess::GetDsInfo(const char* pDataSource,key_t& dskey,CString& strSoPath)
{
					
	char szKey[255];
	CString strDsbinPath = GetCfgData("General","DSBINPATH");
	CString strDsmax = GetCfgData("General","DSMAX");
	int nDsmax = atoi(strDsmax);

	bool bFind=false;
	for(int n=1;n<=nDsmax;n++)
	{
		sprintf(szKey,"DS%03d",n);
		CString strDsName = GetCfgData("DateSource",szKey,0);		strDsName.Trim();
		
		//printf("%03d [%s], [%s]\n",n,pDataSource,strDsName.c_str());
		if(strDsName.Compare(pDataSource)==0)
		{
			bFind=true;
			break;
		}
	}
	if(!bFind)
		return -1;
	
	CString strDsName 		= GetCfgData("DateSource",szKey,0);		strDsName.Trim();				
	CString strDsFlag 		= GetCfgData("DateSource",szKey,1);		strDsFlag.Trim();
	CString strDsEnabled 	= GetCfgData("DateSource",szKey,2);		strDsEnabled.Trim();
	CString strDsFlush 		= GetCfgData("DateSource",szKey,3);		strDsFlush.Trim();
	CString strDsSo 		= GetCfgData("DateSource",szKey,4);		strDsSo.Trim();
	CString strReserve 		= GetCfgData("DateSource",szKey,5);		strReserve.Trim();	
	
			
	dskey = GetAreaKey(atoi(strDsFlag));
	
	strSoPath = strDsbinPath+strDsSo;
	
	return 0;		
		
}
	
int CShmAccess::OpenSelect(CDict* pDict)
{
	char	tran_code[20];
	char	data_source[20];
	pDict->GetDictString("#DataSource#",data_source,20);
	pDict->GetDictString("$TRAN_CODE$",tran_code,20);

	key_t dskey;
	CString strSoPath;
	if(GetDsInfo(data_source,dskey,strSoPath) == -1)
	{
	    PERROR("Can't Get DsInfo [DataSource:%s]\n",data_source);	
		printf("Can't Get DsInfo [DataSource:%s]\n",data_source);		
		return -1;
	}
	 
	memset(&m_dsex,0,sizeof(DSEX_ACCESS));
	if(LoadDsexFn(strSoPath,&m_dsex) == -1)
	{
		PERROR(" %-10s %10s (%s)\n",data_source,"Failed to load dsex",strSoPath.c_str());
		printf(" %-10s %10s (%s)\n",data_source,"Failed to load dsex",strSoPath.c_str());
		return -1; 				
	}
				
	int nRet=-1;

	if(m_pLock->Select(dskey) != -1)
	{
		int shmid = shmget(dskey,0,DSAREA_ACCESS);
		if(shmid != -1)
		{										
			m_pMatAddress = (char*)shmat(shmid,0,0);
			if(m_pMatAddress)
			{			
    			m_pLock->LockRead();
    			nRet = m_dsex.pfnOpenSelect(pDict,m_pMatAddress);
    			if(nRet != 0)
    			{
    			    PERROR("m_dsex.pfnOpenSelect failed \n");		
    				printf("m_dsex.pfnOpenSelect failed \n");
    							
    				m_pLock->UnlockRead();
    				if(m_pMatAddress)
    				{
    	                shmdt((const void *)m_pMatAddress);
    	                m_pMatAddress = NULL;
    	            }
    			}
		    }
		    
		}
		else
		{
		    PERROR("shmget failed \n");
			printf("shmget failed \n");			
		}

	}
	else
	{
	    PERROR("OpenSelect: m_pLock->Select failed \n" );
    	printf("OpenSelect: m_pLock->Select failed \n" );
	}
	
	if(nRet != 0)
	    FreeDsexFn(&m_dsex);    
	
	return nRet;

}

int CShmAccess::GetDataCount()
{
	//printf("m_dsex.pfnGetDataCount :%d\n",m_dsex.pfnGetDataCount());	
					
	if(m_dsex.pfnGetDataCount)
		return m_dsex.pfnGetDataCount();
	else
		return -1;
}

int CShmAccess::FetchData(CDict* pDict, int nIndex)
{
	if(m_dsex.pfnFetchData)
	{
		return m_dsex.pfnFetchData(pDict,nIndex);
	
	}
	else
		return -1;
		
}

void CShmAccess::CloseSelect()
{
	if(m_dsex.pfnCloseSelect)
		m_dsex.pfnCloseSelect();
	
	if(m_pMatAddress)
	{
		shmdt((const void *)m_pMatAddress);
		 m_pMatAddress = NULL;
    }
		
	if(m_pLock)
		m_pLock->UnlockRead();
	
	FreeDsexFn(&m_dsex);	

}

int CShmAccess::UpdateData(CDict* pDict)
{
	char	data_source[20];
	char	tran_code[20];

	pDict->GetDictString("#DataSource#",data_source,20);
	pDict->GetDictString("$TRAN_CODE$",tran_code,20);

	key_t dskey;
	CString strSoPath;
	if(GetDsInfo(data_source,dskey,strSoPath) == -1)
	{
	    PERROR("Can't Get DsInfo \n");
		printf("Can't Get DsInfo \n");			
		return -1;
	}
	
	
	DSEX_ACCESS  dsexUpdate; 
	memset(&dsexUpdate,0,sizeof(DSEX_ACCESS));
	if(LoadDsexFn(strSoPath,&dsexUpdate) == -1)
	{
		PERROR(" %-10s %10s (%s)\n",data_source,"Failed to load dsex",strSoPath.c_str());
		printf(" %-10s %10s (%s)\n",data_source,"Failed to load dsex",strSoPath.c_str());
		return -1; 				
	}
	
				
	int nRet=-1;

	if(m_pLock->Select(dskey) != -1)
	{
		int shmid = shmget(dskey,0,DSAREA_ACCESS);
		if(shmid != -1)
		{										
				char* pMatAddress = (char*)shmat(shmid,0,0);	
				if(pMatAddress)
				{				
    				m_pLock->LockUpdate();
    				nRet = dsexUpdate.pfnUpdateData(pDict,pMatAddress);
    				m_pLock->UnlockUpdate();
    				shmdt((const void *)pMatAddress);
			    }				
		}
		else
		{
		    PERROR("shmget failed \n");
			printf("shmget failed \n");			
		}

	}
	else
	{
	    PERROR("UpdateData: m_pLock->Select failed \n" );
    	printf("UpdateData: m_pLock->Select failed \n" );
	}		
		

	FreeDsexFn(&dsexUpdate);		
	
	
	return nRet;


}
