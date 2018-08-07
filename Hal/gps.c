#include "gps.h"

rb_t pGps;                         ///< Ring buffer structure variable
gpsProtocol_t gpsProtocol;
static int8_t gizGpsPacket(rb_t *rb,uint8_t *gpsdata,uint16_t *len)
{
    int32_t ret = 0;
    int32_t i = 0;
    uint8_t tmpData;
    uint8_t tmpLen = 0;
		uint8_t packetLen=0;
		uint8_t protocolFlag=0;
		uint8_t Assignment_data=0;
	  uint8_t *packetData=gpsdata;
		
    if(NULL == rb|| NULL==gpsdata ||len==NULL)
    {
        GIZWITS_LOG("gizProtocolGetOnePacket Error , Illegal Param\n");
        return -1;
    }
		
    tmpLen = rbCanRead(rb);
    if(0 == tmpLen)
    {
        return -2;//没有数据
    }
		if(tmpLen>=200)
		{		
			for(i=0; i<tmpLen; i++)
				{
        ret = rbRead(rb, &tmpData, 1);
        if(0 != ret)
        {
					if(tmpData=='$')
					{
						protocolFlag=1;

					}
					else
					{
						;
						
					}
					if((protocolFlag==1)&&(tmpData!=0x0D))
					{
						// 数据多了就会越界的风险
					//	GIZWITS_LOG("The head of a data zhong ******\n");
						packetData[packetLen] = tmpData;
						packetLen++;
						*len=packetLen;
						
					}
					if((protocolFlag==1)&&(tmpData==0x0D))
					{
						Assignment_data=tmpData;
					}
					if((Assignment_data==0x0D)&&(tmpData==0X0A))
					{
					return 0;
					}
					
				}
				
				
		}
	}
}



/**@} */

/**
* @brief Write data to the ring buffer
* @param [in] buf        : buf adress
* @param [in] len        : byte length
* @return   correct : Returns the length of the written data
            failure : -1
*/
int32_t gizGpsPutData(uint8_t *buf, uint32_t len)
{
    int32_t count = 0;

    if(NULL == buf)
    {
        GIZWITS_LOG("ERR: gizGpsPutData buf is empty \n");
        return -1;
    }

    count = rbWrite(&pGps, buf, len);
    if(count != len)
    {
        GIZWITS_LOG("ERR: Failed to rbWrite \n");
        return -1;
    }

    return count;
}


 int32_t gpsHandle(void )
{
	int32_t gpsret=0;
	uint16_t gpsProtocolLen = 0;
	uint32_t i=0;
	gpsret=	gizGpsPacket(&pGps,gpsProtocol.protocolBuf,&gpsProtocolLen);
	for(i=0;i<gpsProtocolLen;i++)
	{
		GIZWITS_LOG("%c",gpsProtocol.protocolBuf[i]);
	}
	if(gpsret==0)
		{
			GIZWITS_LOG("gpsret One Packet!\n");
		}
	return 0;
	
}





 void gpsInit(void)
 {
	  pGps.rbCapacity =GPS_MAX_LEN;
		pGps.rbBuff = gpsBuf;
    if(0 == rbCreate(&pGps))
			{
			GIZWITS_LOG("pGps rbCreate Success \n");
			}
		else
			{
			GIZWITS_LOG("pGps rbCreate Faild \n");
			}
			
		}

