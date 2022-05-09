#ifndef MASTER_CONFIG_H_
#define MASTER_CONFIG_H_

#include "custom_board.h"

#define THIS_DEVICE_ROWS 5
#define THIS_DEVICE_COLS 14

#define MATRIX_ROW_PINS { GPIO(1,13),GPIO(0,2),GPIO(0,29),GPIO(0,31),GPIO(0,30) } // Dummy
#define MATRIX_COL_PINS { GPIO(0,6),GPIO(0,5),GPIO(0,8),GPIO(0,12),GPIO(0,7),GPIO(0,15),GPIO(0,17),GPIO(0,20),GPIO(0,22),GPIO(0,24),GPIO(1,0),GPIO(1,4),GPIO(0,9),GPIO(1,6)}
#define IS_LEFT_HAND  true
#define ENABLE_STARTUP_ADV_NOLIST

#endif /* MASTER_CONFIG_H_ */
