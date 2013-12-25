/* $Id: letocl.h,v 1.1.2.7 2013/12/25 10:09:12 alkresin Exp $ */

/*
 * Harbour Project source code:
 * Header file for Leto RDD
 *
 * Copyright 2013 Alexander S. Kresin <alex / at / kresin.ru>
 * www - http://www.kresin.ru
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA (or visit the web site http://www.gnu.org/).
 *
 * As a special exception, the Harbour Project gives permission for
 * additional uses of the text contained in its release of Harbour.
 *
 * The exception is that, if you link the Harbour libraries with other
 * files to produce an executable, this does not by itself cause the
 * resulting executable to be covered by the GNU General Public License.
 * Your use of that executable is in no way restricted on account of
 * linking the Harbour library code into it.
 *
 * This exception does not however invalidate any other reasons why
 * the executable file might be covered by the GNU General Public License.
 *
 * This exception applies only to the code released by the Harbour
 * Project under the name Harbour.  If you copy code from other
 * Harbour Project or Free Software Foundation releases into a copy of
 * Harbour, as the General Public License permits, the exception does
 * not apply to the code that you add in this way.  To avoid misleading
 * anyone as to the status of such modified files, you must delete
 * this exception notice from them.
 *
 * If you write modifications of your own for Harbour, it is your choice
 * whether to permit this exception to apply to your modifications.
 * If you do not wish that, delete this exception notice.
 *
 */

#include "hbdefs.h"

#if !defined (HB_SOCKET_T)
   #if defined( HB_OS_WIN_32 ) || defined( HB_OS_WIN )
      #define HB_SOCKET_T SOCKET
      #ifndef HB_SOCKET_H_
         #include <winsock2.h>
      #endif
   #else
      #define HB_SOCKET_T int
   #endif
#endif

#define HB_MAX_FILE_EXT       10

/* Field types from hbapirdd.h */

#define HB_FT_NONE            0
#define HB_FT_STRING          1     /* "C" */
#define HB_FT_LOGICAL         2     /* "L" */
#define HB_FT_DATE            3     /* "D" */
#define HB_FT_LONG            4     /* "N" */
#define HB_FT_FLOAT           5     /* "F" */
#define HB_FT_INTEGER         6     /* "I" */
#define HB_FT_DOUBLE          7     /* "B" */
#define HB_FT_TIME            8     /* "T" */
#if !( defined( HB_FT_DATETIME ) )
#define HB_FT_DATETIME        8
#endif
#define HB_FT_TIMESTAMP       9     /* "@" */
#if !( defined( HB_FT_DAYTIME ) )
#define HB_FT_DAYTIME         9
#endif
#if !( defined( HB_FT_MODTIME ) )
#define HB_FT_MODTIME         10    /* "=" */
#endif
#define HB_FT_ROWVER          11    /* "^" */
#define HB_FT_AUTOINC         12    /* "+" */
#define HB_FT_CURRENCY        13    /* "Y" */
#define HB_FT_CURDOUBLE       14    /* "Z" */
#define HB_FT_VARLENGTH       15    /* "Q" */
#define HB_FT_MEMO            16    /* "M" */
#define HB_FT_ANY             17    /* "V" */
#define HB_FT_IMAGE           18    /* "P" */
#if !( defined( HB_FT_PICTURE ) )
   #define HB_FT_PICTURE         18
#endif
#define HB_FT_BLOB            19    /* "W" */
#define HB_FT_OLE             20    /* "G" */

HB_EXTERN_BEGIN

typedef struct _CDPSTRU
{
   char *      szClientCdp;
   char *      szServerCdp;
   struct _CDPSTRU * pNext;
} CDPSTRU, *PCDPSTRU;

typedef struct _LETOBUFFER_
{
   BYTE *      pBuffer;          /* Buffer for records */
   ULONG       ulBufLen;         /* allocated buffer length */
   ULONG       ulBufDataLen;     /* data length in buffer */
   BOOL        bSetDeleted;      /* current _SET_DELETED flag */
   ULONG       ulDeciSec;        /* buffer time in 1/100 seconds */
   USHORT      uiShoots;         /* using statistic */
} LETOBUFFER;

typedef struct _LETOFIELD
{
   char       szName[12];
   unsigned int  uiType;
   unsigned int  uiLen;
   unsigned int  uiDec;
} LETOFIELD;

typedef struct _LETOTABLE
{
   unsigned long hTable;
   unsigned int  uiDriver;
   unsigned int  uiConnection;

   unsigned int  uiFieldExtent;
   LETOFIELD *   pFields;
   unsigned int * pFieldUpd;           /* Pointer to updated fields array */
   unsigned int * pFieldOffset;        /* Pointer to field offset array */

   unsigned int  uiOrders;
   char *        szTags;

   char     szMemoExt[HB_MAX_FILE_EXT + 1];    /* MEMO file extension */
   unsigned char bMemoType;           /* MEMO type used in DBF memo fields */
   unsigned int  uiMemoVersion;       /* MEMO file version */

   unsigned int  fBof;                /* HB_TRUE if "bof" */
   unsigned int  fEof;                /* HB_TRUE if "eof" */
   unsigned int  fFound;              /* HB_TRUE if "found" */
   unsigned int  fDeleted;            /* Deleted record */
   unsigned int  fRecLocked;          /* TRUE if record is locked */

   unsigned int  uiRecordLen;         /* Size of record */
   unsigned long ulRecNo;
   unsigned long ulRecCount;          /* Count of records */
   unsigned char * pRecord;           /* Buffer of record data */

   LETOBUFFER  Buffer;                /* skip buffer */
   unsigned char *  ptrBuf;
   unsigned int  uiRecInBuf;
   signed char BufDirection;

   long          lLastUpdate;         /* from dbf header: last update */

} LETOTABLE;

typedef struct _LETOCONNECTION_
{
   HB_SOCKET_T hSocket;
   char *      pAddr;
   int         iPort;
   int         iTimeOut;
   char *      szPath;
   char        szVersion[24];
   unsigned int uiMajorVer;
   unsigned int uiMinorVer;
   char        szVerHarbour[80];
   char        szAccess[8];
   char        cDopcode[2];
   HB_BOOL     bCrypt;
   HB_BOOL     bCloseAll;
   PCDPSTRU    pCdpTable;

   HB_BOOL     bTransActive;
   BYTE *      szTransBuffer;
   ULONG       ulTransBuffLen;
   ULONG       ulTransDataLen;
   ULONG       ulRecsInTrans;
   ULONG       ulTransBlockLen;

   HB_BOOL     bRefreshCount;

   char *      pBufCrypt;
   ULONG       ulBufCryptLen;

/* uiBufRefreshTime defines the time interval in 0.01 sec. After this 
   time is up, the records buffer must be refreshed, 100 by default */
   USHORT      uiBufRefreshTime;

   USHORT      uiDriver;
   USHORT      uiMemoType;

   USHORT      uiProto;
   USHORT      uiTBufOffset;

} LETOCONNECTION;

HB_EXTERN_END

char * leto_getRcvBuff( void );
char * leto_firstchar( void );
void leto_setCallback( void( *fn )( void ) );
void LetoInit( void );
void LetoExit( unsigned int uiFull );
void LetoSetDateFormat( const char * szDateFormat );
void LetoSetCentury( char cCentury );
void LetoSetCdp( const char * szCdp );
void LetoSetModName( char * szModule );
int LetoGetConnectRes( void );
int LetoGetCmdItem( char ** pptr, char * szDest );
LETOCONNECTION * LetoConnectionNew( const char * szAddr, int iPort, const char * szUser, const char * szPass, int iTimeOut );
int LetoCloseAll( LETOCONNECTION * pConnection );
void LetoConnectionClose( LETOCONNECTION * pConnection );
char * LetoGetServerVer( LETOCONNECTION * pConnection );
void LetoSetPath( LETOCONNECTION * pConnection, const char * szPath );

int LetoDbClose( LETOTABLE * pTable );
LETOTABLE * LetoDbCreate( LETOCONNECTION * pConnection, char * szFile, char * szAlias, char * szFields, unsigned int uiArea );
LETOTABLE * LetoDbOpen( LETOCONNECTION * pConnection, char * szFile, char * szAlias, int iShared, int iReadOnly, char * szCdp, unsigned int uiArea );
unsigned int LetoDbBof( LETOTABLE * pTable );
unsigned int LetoDbEof( LETOTABLE * pTable );
unsigned int LetoDbGetField( LETOTABLE * pTable, unsigned int uiIndex, char * szRet, unsigned int * uiLen );
unsigned int LetoDbRecCount( LETOTABLE * pTable, unsigned long * ulCount );
unsigned int LetoDbFieldCount( LETOTABLE * pTable, unsigned int * uiCount );
unsigned int LetoDbFieldName( LETOTABLE * pTable, unsigned int uiIndex, char * szName );
unsigned int LetoDbFieldType( LETOTABLE * pTable, unsigned int uiIndex, unsigned int * uiType );
unsigned int LetoDbFieldLen( LETOTABLE * pTable, unsigned int uiIndex, unsigned int * uiLen );
unsigned int LetoDbFieldDec( LETOTABLE * pTable, unsigned int uiIndex, unsigned int * uiDec );

long int leto_RecvFirst( LETOCONNECTION * pConnection );
long int leto_Recv( LETOCONNECTION * pConnection );
long int leto_DataSendRecv( LETOCONNECTION * pConnection, const char * sData, unsigned long ulLen );
LETOCONNECTION * leto_getConnectionPool( void );
LETOCONNECTION * leto_ConnectionFind( const char * szAddr, int iPort );
const char * leto_GetServerCdp( LETOCONNECTION * pConnection, const char *szCdp );
int LetoCheckServerVer( LETOCONNECTION * pConnection, USHORT uiVer );
const char * leto_RemoveIpFromPath(const char * szPath);
int leto_getIpFromPath( const char * sSource, char * szAddr, int * piPort, char * szPath, BOOL bFile );
void leto_getFileFromPath( const char * sSource, char * szFile );
char * leto_DecryptBuf( LETOCONNECTION * pConnection, const char * ptr, ULONG * pulLen );
char * leto_DecryptText( LETOCONNECTION * pConnection, ULONG * pulLen );

char * LetoMgGetInfo( LETOCONNECTION * pConnection );
char * LetoMgGetUsers( LETOCONNECTION * pConnection, const char * szTable );
char * LetoMgGetTables( LETOCONNECTION * pConnection, const char * szUser );
void LetoMgKillUser( LETOCONNECTION * pConnection, const char * szUserId );
char * LetoMgGetTime( LETOCONNECTION * pConnection );

int LetoGetError( void );
void LetoSetError( int iErr );
int LetoVarSet( LETOCONNECTION * pConnection, char * szGroup, char * szVar, char cType, char * szValue, unsigned int uiFlags, char ** pRetValue );
char * LetoVarGet( LETOCONNECTION * pConnection, char * szGroup, char * szVar );
long LetoVarIncr( LETOCONNECTION * pConnection, char * szGroup, char * szVar, unsigned int uiFlags );
long LetoVarDecr( LETOCONNECTION * pConnection, char * szGroup, char * szVar, unsigned int uiFlags );
int LetoVarDel( LETOCONNECTION * pConnection, char * szGroup, char * szVar );
char * LetoVarGetList( LETOCONNECTION * pConnection, const char * szGroup, unsigned int uiMaxLen );

int LetoIsFileExist( LETOCONNECTION * pConnection, char * szFile );
int LetoFileErase( LETOCONNECTION * pConnection, char * szFile );
int LetoFileRename( LETOCONNECTION * pConnection, char * szFile, char * szFileNew );
char * LetoMemoRead( LETOCONNECTION * pConnection, char * szFile, unsigned long * ulMemoLen );
int LetoMemoWrite( LETOCONNECTION * pConnection, char * szFile, char * szValue, unsigned long ulLen );
char * LetoFileRead( LETOCONNECTION * pConnection, char * szFile, unsigned long ulStart, unsigned long * ulLen );
int LetoFileWrite( LETOCONNECTION * pConnection, char * szFile, char * szValue, unsigned long ulStart, unsigned long ulLen );
long int LetoFileSize( LETOCONNECTION * pConnection, char * szFile );
char * LetoDirectory( LETOCONNECTION * pConnection, char * szDir, char * szAttr );
int LetoMakeDir( LETOCONNECTION * pConnection, char * szFile );

unsigned int leto_IsBinaryField( unsigned int uiType, unsigned int uiLen );
void leto_SetBlankRecord( LETOTABLE * pTable, unsigned int uiAppend );
int leto_ParseRecord( LETOTABLE * pTable, const char * szData, unsigned int uiCrypt );

