#ifndef DELAY_H_
#define DELAY_H_

#include "std_types.h"

// الدالة المسؤولة عن التأخير بالمللي ثانية
void Delay_ms(uint32 milliseconds);

// الدالة المسؤولة عن التأخير بالمايكرو ثانية
void Delay_us(uint32 microseconds);

#endif /* DELAY_H_ */