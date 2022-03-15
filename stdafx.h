#ifndef STDAFX_H
#define STDAFX_H

#include <assert.h>

#ifdef NDEBUG
#define assert(_Expression) ((void)0)
#else /* !defined (NDEBUG) */
#if defined(_UNICODE) || defined(UNICODE)
#define assertMsg(_Expression, MSG)                               \
  (void)((!!(_Expression)) ||                                     \
         (_wassert(_CRT_WIDE(#_Expression " => " _CRT_WIDE(MSG)), \
                   _CRT_WIDE(__FILE__), __LINE__),                \
          0))
#else /* not unicode */
#define assertMsg(_Expression) \
  (void)((!!(_Expression)) ||  \
         (_assert(#_Expression " => " _CRT_WIDE(MSG), __FILE__, __LINE__), 0))
#endif /* _UNICODE||UNICODE */
#endif /* !defined (NDEBUG) */

#endif
