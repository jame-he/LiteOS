
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#ifndef u8_t
#define u8_t   unsigned char    
#endif
#ifndef u16_t
#define u16_t  unsigned short    
#endif
#ifndef u32_t
#define u32_t  unsigned  int   
#endif
#ifndef s8_t
#define s8_t   signed char    
#endif
#ifndef s16_t
#define s16_t  signed short    
#endif
#ifndef s32_t
#define s32_t  signed int   
#endif

//we need nothing here except the standard struct here
//kernel port here
//create a task:return the task handle here while -1 means create failed
typedef void *(*fnTaskEntry)(u32_t arg);
s32_t task_create(const char *name,fnTaskEntry fnTask,s32_t stackisize,void *stack,void *args,s32_t prior);
//task sleep here:unit ms
void task_sleepms(s32_t ms);

//ring buffer implement here:used for the driver
typedef struct
{
    u8_t          *buf;  //which means the buffer
    s32_t          buflen; //which means the buffer limit
    s32_t          datalen; //which means how many data in the buffer
    s32_t          dataoff; //which means the valid data offset in the buffer
}tagRingBuf;
//ring:which to be initialized
//buf:you supplied for the ring
//len:the buf length
//return:0 means ok while -1 failed
s32_t ring_init(tagRingBuf *ring,u8_t *buf, s32_t buflen,s32_t offset,s32_t datalen);
//write len bytes data to the ring
//return:how many bytes has been written while -1 means something err
//write only changes the datalen and  data in  the ring
s32_t ring_write(tagRingBuf *ring,u8_t *buf,s32_t len);
//read len bytes data from the ring
//return:how many bytes has been read while -1 means something err
//read effect the offset datalen and data in the ring
s32_t ring_read(tagRingBuf *ring,u8_t *buf,s32_t len);
s32_t ring_reset(tagRingBuf *ring);  //clear the ring data
s32_t ring_datalen(tagRingBuf *ring);//show me how many data in the ring
//io device for some component ported
s32_t iodev_open(const char *name,s32_t flags,s32_t mode);
s32_t iodev_read(s32_t fd,u8_t *buf,s32_t len,s32_t timeout);
s32_t iodev_write(s32_t fd,u8_t *buf,s32_t len,s32_t timeout);
s32_t iodev_close(s32_t fd);
s32_t iodev_flush(s32_t fd);
void  iodev_debugmode(s32_t rxtx,u32_t mode);  //rxtx:0 rx while 1tx 2 rxtx mode 0 nodebug 1 ascii 2 hex




