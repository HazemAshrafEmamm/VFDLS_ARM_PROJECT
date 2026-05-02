#ifndef STD_TYPES_H_
#define STD_TYPES_H_

// Boolean Data Type
typedef unsigned char         boolean;

// Unsigned Data Types
typedef unsigned char         uint8;
typedef unsigned short        uint16;
typedef unsigned long         uint32;
typedef unsigned long long    uint64;

// Signed Data Types
typedef signed char           sint8;
typedef signed short          sint16;
typedef signed long           sint32;
typedef signed long long      sint64;

// Floating Point Data Types
typedef float                 float32;
typedef double                float64;

#ifndef TRUE
#define TRUE                  (1U)
#endif

#ifndef FALSE
#define FALSE                 (0U)
#endif

#endif /* STD_TYPES_H_ */