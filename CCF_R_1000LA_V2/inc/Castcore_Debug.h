/**
  ******************************************************************************
  * @file    Castcore_Debug.h
  * @author  Castcore Telecom. Institute for the next generation of broadcast technology
  * @version V1.0.0
  * @brief
  ******************************************************************************
   Version v 1.0.0. 2014/03/13
     - By. Yoo Seung Ki : Creating new


  ******************************************************************************
*/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CASTCORE_DEBUG_H_
#define _CASTCORE_DEBUG_H_

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define DEBUG_ON 		1
#define DEBUG_OFF		0

#define DEBUG_MODE							DEBUG_ON

#define MCU_DEBUG_ON_OFF					DEBUG_ON

/************************************************************************************
			                                Don`t Touch!!!!!!!!!!!!!!!
**************************************************************************************/
#define PLATFORM_DIAG printf

#if MCU_DEBUG_ON_OFF
	#define MCU_DEBUG		1
#else
	#define MCU_DEBUG		0
#endif


/***********************************************************************************/

#define DEBUGF(debug, Message) do { \
									if ( \
										((debug) & DEBUG_MODE) && \
										((debug) & 1))  \
									{ \
										PLATFORM_DIAG Message;\
									} \
								} while(0)
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif /* _CASTCORE_DEBUG_H_ */


