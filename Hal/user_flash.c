#include "user_flash.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h"

uint32_t writeFlashData = 0x55555555;
uint32_t addr = 0x08007000;
//FLASH??????
void writeFlashTest(void)
{
    //flash 写入数据测试
  HAL_FLASH_Unlock();

    //擦出flash
      //初始化电脑
    FLASH_EraseInitTypeDef f;
    f.TypeErase = FLASH_TYPEERASE_PAGES;
    f.PageAddress = addr;
    f.NbPages = 1;
    //设置PageError
    uint32_t PageError = 0;
    //调用擦出flash
    HAL_FLASHEx_Erase(&f, &PageError);

    //3对flash烧写
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, writeFlashData);

    //4锁住flash
  HAL_FLASH_Lock();
}

//FLASH??????
void printFlashTest(void)
{
  uint32_t temp = *(__IO uint32_t*)(addr);

    printf("addr:0x%x, data:0x%x\r\n", addr, temp);
}


