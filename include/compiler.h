#ifndef _UTIL_COMPILER_H_
#define _UTIL_COMPILER_H_

/**
 * @file compiler.h
 * @brief Generic compiler-specific macros.
 * @author James Hogan <james@albanarts.com>
 */

#ifdef __GNUC__

#define likely(X)    __builtin_expect(!!(X), 1)
#define unlikely(X)  __builtin_expect(!!(X), 0)

#else

#define likely(X)   (X)
#define unlikely(X) (X)

#endif

#endif // _UTIL_COMPILER_H_
