//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : 技术平台公共类库
//  @ File Name : mintcpio.cpp
//  @ Date : 2013/8/15
//  @ Author : disp
//
//


#include "mintcpio.h"

CMintcpio::CMintcpio()
{
	m_client_sd = -1;
}

CMintcpio::CMintcpio(int socke)
{
	m_client_sd = socke;
}

CMintcpio::~CMintcpio()
{
	Finish();
	
}

/*****************************************
** MINgetsbyte
** Fetch a single byte from the socket.
** RECV returns more than one byte so this call will read the
** buffer byte by byte and call recv every time the end is reached.
******************************************/
int CMintcpio::MINgetsbyte(byte *cbuf)
{
    int recv_len = recv( m_client_sd, cbuf, 1, 0 );
    if ( recv_len < 0 )
    {
        PERROR("Recv() call failed: %s\n", strerror(errno));
        Finish();
        return(-1);
    }
    else if ( recv_len == 0 )
    {
        PERROR("Client has closed the connection\n");
        //Finish();
        return(-1);
    }
    return(0);

}

/*****************************************
** MINputsbyte
** Write a single byte to the socket.
******************************************/
int CMintcpio::MINputsbyte(char msgbyte)
{
    int len;

    len = send( m_client_sd, &msgbyte, 1, 0 );
    if ( len < 0 )
    {
        PERROR("Send() call failed: %s\n", strerror(errno));
        //Finish();
        return(-1);
    }
    return(0);
}


int CMintcpio::Read(MINTCPIO_DATA *data,int* datalen)
{
	if(m_client_sd == -1)
		return -1;

    int index;
    TCP_HEADER tcp_hdr;
    int length;
    char temp[6];

    PDEBUG("MINTCPIO_READ\n");

    for (index=0; index<sizeof(TCP_HEADER); index++)
        if (MINgetsbyte( (byte*)(temp+index) )) return -1;

    temp[5] = '\0';
    length = atoi(temp+1);

    PDEBUG("tcp header is >%s<\n",temp);
    PDEBUG("data length is %d\n",length);

    for (index=0; index<length; index++)               /** Bancs Link **/
        if (MINgetsbyte( ((byte*)data)+index) ) return -1;

    //sprintf(temp,"%04d",INT_HEADER_SIZE+length);
    //memcpy(area->length,temp,4);
    
    //*datalen = INT_HEADER_SIZE+length;
    *datalen = length;
    
    PDEBUG("MINTCPIO_READ end\n");

    return 0;
}

int CMintcpio::Write(MINTCPIO_DATA *data,int datalen)
{
	if(m_client_sd == -1)
		return -1;
		
  	int size;
    int len;
    byte tmp_msg[sizeof(TCP_HEADER)+sizeof(MINTCPIO_DATA)];

    /* get length of message - convert from non-NUL terminated string */

    //memcpy(tmp_msg,length,4);
    //tmp_msg[4] = '\0';
    //size = atoi((char*)tmp_msg);
    size = datalen;

    PDEBUG("MINTCPIO_SEND - data length (%d bytes)\n",size);

    tmp_msg[0] = ' ';

    sprintf((char*)tmp_msg+1,"%04d",size);                      /** Bancs Link **/

    memcpy(tmp_msg+5,data, size);

    len = send(m_client_sd,tmp_msg,size+5, 0 );
    if ( len < 0 )
    {
        PERROR("Send() call failed: %s\n", strerror(errno));
        Finish();
        return -1;
    }

	PDEBUG("Sent complete message of %d bytes\n",len);
	PDEBUG("\t:%.*s:\n",len,(char *)tmp_msg);


    return 0;
}


int CMintcpio::ReadMsg(byte *msg,int* msglen)
{
	if(m_client_sd == -1)
		return -1;

    int index;
    TCP_HEADER tcp_hdr;
    int length;
    char temp[6];

    PDEBUG("MINTCPIO_READ\n");

    for (index=0; index<sizeof(TCP_HEADER); index++)
        if (MINgetsbyte( (byte*)(temp+index) )) return -1;

    temp[5] = '\0';
    length = atoi(temp+1);
    
    memcpy(msg,temp,5);
    *msglen = 5;

    PDEBUG("tcp header is >%s<\n",temp);
    PDEBUG("data length is %d\n",length);

    for (index=0; index<length; index++) 
        if (MINgetsbyte( msg+5+index) ) return -1;

    *msglen += length;
    PDEBUG("msg length is %d\n",*msglen);
        
    PDEBUG("MINTCPIO_READ end\n");

    return 0;
}

int CMintcpio::WriteMsg(byte *msg,int msglen)
{
	if(m_client_sd == -1)
		return -1;
		
    PDEBUG("MINTCPIO_SEND - msg length (%d bytes)\n",msglen);

    int len = send(m_client_sd,msg,msglen, 0 );
    if ( len < 0 )
    {
        PERROR("Send() call failed: %s\n", strerror(errno));
        Finish();
        return -1;
    }

	PDEBUG("Sent complete message of %d bytes\n",len);

    return 0;
}



void CMintcpio::Finish()
{
    /* Close the socket */
    if(m_client_sd != -1)
    {
    	close(m_client_sd);
    	m_client_sd = -1;
    	
	    PDEBUG("MINTCPIO_FINISH - socket closed\n");
	}

}


