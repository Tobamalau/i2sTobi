#include <stdio.h>
#include <nrf.h>
#include "sdk_config.h"
#include "sound.h"



//#define PIN_MCK    (13)
//#define PIN_SCK    (30)
//#define PIN_LRCK   (31)
//#define PIN_SDOUT  (29)

int main(void)
{
  // Sine table (stereo, so every value is duplicated)
  
  
  // Enable transmission
  NRF_I2S->CONFIG.TXEN = (I2S_CONFIG_TXEN_TXEN_ENABLE << I2S_CONFIG_TXEN_TXEN_Pos);
  
  // Enable MCK generator
  NRF_I2S->CONFIG.MCKEN = (I2S_CONFIG_MCKEN_MCKEN_ENABLE << I2S_CONFIG_MCKEN_MCKEN_Pos);
  
  // MCKFREQ
  NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV21  << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
  
  // Ratio = 96 
  NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_96X << I2S_CONFIG_RATIO_RATIO_Pos;
    
  // Master mode, 16Bit, left aligned
  NRF_I2S->CONFIG.MODE = I2S_CONFIG_MODE_MODE_MASTER << I2S_CONFIG_MODE_MODE_Pos;
  NRF_I2S->CONFIG.SWIDTH = I2S_CONFIG_SWIDTH_SWIDTH_16BIT << I2S_CONFIG_SWIDTH_SWIDTH_Pos;
  NRF_I2S->CONFIG.ALIGN = I2S_CONFIG_ALIGN_ALIGN_LEFT << I2S_CONFIG_ALIGN_ALIGN_Pos;
  
  // Format = I2S
  NRF_I2S->CONFIG.FORMAT = I2S_CONFIG_FORMAT_FORMAT_I2S << I2S_CONFIG_FORMAT_FORMAT_Pos;
  
  // Use stereo 
  //NRF_I2S->CONFIG.CHANNELS = I2S_CONFIG_CHANNELS_CHANNELS_STEREO << I2S_CONFIG_CHANNELS_CHANNELS_Pos;
  NRF_I2S->CONFIG.CHANNELS = I2S_CONFIG_CHANNELS_CHANNELS_Left << I2S_CONFIG_CHANNELS_CHANNELS_Pos;
  
  // Configure pins
  NRF_I2S->PSEL.MCK = (I2S_CONFIG_MCK_PIN << I2S_PSEL_MCK_PIN_Pos);
  NRF_I2S->PSEL.SCK = (I2S_CONFIG_SCK_PIN << I2S_PSEL_SCK_PIN_Pos); 
  NRF_I2S->PSEL.LRCK = (I2S_CONFIG_LRCK_PIN << I2S_PSEL_LRCK_PIN_Pos); 
  NRF_I2S->PSEL.SDOUT = (I2S_SDOUT_PIN << I2S_PSEL_SDOUT_PIN_Pos);
  
  NRF_I2S->ENABLE = 1;

  printf("Start\n");

  // Configure data pointer
  NRF_I2S->TXD.PTR = (uint32_t)&m_musik_table[0];
  NRF_I2S->RXTXD.MAXCNT = leftChannelSize;//sizeof(sine_table) / sizeof(uint32_t);//
  //printf("NRF_I2S->RXTXD.MAXCNT:%d,%d,%d", NRF_I2S->RXTXD.MAXCNT,  sizeof(sine_table), sizeof(uint32_t));
  // Start transmitting I2S data
  NRF_I2S->TASKS_START = 1;
  
  
  // Since we are not updating the TXD pointer, the sine wave will play over and over again.
  // The TXD pointer can be updated after the EVENTS_TXPTRUPD arrives.
  while (1)
  {
    __WFE();
    
  }
}