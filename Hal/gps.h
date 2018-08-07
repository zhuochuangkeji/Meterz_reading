#ifndef __GPS_H_
#define __GPS_H_
#include "common.h"
#include "ringBuffer.h"

#define GPS_MAX_PACKAGE_LEN   800
#define GPS_MAX_LEN         400
typedef struct
	{
	uint8_t protocolBuf[GPS_MAX_PACKAGE_LEN];           ///< Protocol data handle buffer
}gpsProtocol_t;

static uint8_t gpsBuf[GPS_MAX_LEN];                       ///< Ring buffer data cache buffer
static int8_t gizGpsPacket(rb_t *rb,uint8_t *gizdata,uint16_t *len);
int32_t gpsHandle(void );
void gpsInit(void);


#endif
