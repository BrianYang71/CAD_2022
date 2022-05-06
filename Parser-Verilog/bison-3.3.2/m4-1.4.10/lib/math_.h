/* A GNU-like <math.h>.

   Copyright (C) 2002-2003, 2007 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */

#ifndef _GL_MATH_H

/* The include_next requires a split double-inclusion guard.  */
#@INCLUDE_NEXT@ @NEXT_MATH_H@

#ifndef _GL_MATH_H
#define _GL_MATH_H


/* The definition of GL_LINK_WARNING is copied here.  */


#ifdef __cplusplus
extern "C" {
#endif


/* Write x as
     x = mantissa * 2^exp
   where
     If x finite and nonzero: 0.5 <= |mantissa| < 1.0.
     If x is zero: mantissa = x, exp = 0.
     If x is infinite or NaN: mantissa = x, exp unspecified.
   Store exp and return mantissa.  */
#if @GNULIB_FREXP@
# if @REPLACE_FREXP@
#  define frexp rpl_frexp
extern double frexp (double x, int *exp);
# endif
#elif defined GNULIB_POSIXCHECK
# undef frexp
# define frexp(x,e) \
    (GL_LINK_WARNING ("frexp is unportable - " \
                      "use gnulib module frexp for portability"), \
     frexp (x, e))
#endif


#if @GNULIB_MATHL@ || !@HAVE_DECL_ACOSL@
extern long double acosl (long double x);
#endif
#if !@GNULIB_MATHL@ && defined GNULIB_POSIXCHECK
# undef acosl
# define acosl(x) \
    (GL_LINK_WARNING ("acosl is unportable - " \
                      "use gnulib module mathl for portability"), \
     acosl (x))
#endif

#if @GNULIB_MATHL@ || !@HAVE_DECL_ASINL@
extern long double asinl (long double x);
#endif
#if !@GNULIB_MATHL@ && defined GNULIB_POSIXCHECK
# undef asinl
# define asinl(x) \
    (GL_LINK_WARNING ("asinl is unportable - " \
                      "use gnulib module mathl for portability"), \
     asinl (x))
#endif

#if @GNULIB_MATHL@ || !@HAVE_DECL_ATANL@
extern long double atanl (long double x);
#endif
#if !@GNULIB_MATHL@ && defined GNULIB_POSIXCHECK
# undef atanl
# define atanl(x) \
    (GL_LINK_WARNING ("atanl is unportable - " \
                      "use gnulib module mathl for portability"), \
     atanl (x))
#endif

#if @GNULIB_MATHL@ || !@HAVE_DECL_CEILL@
extern long double ceill (long double x);
#endif
#if !@GNULIB_MATHL@ && defined GNULIB_POSIXCHECK
# undef ceill
# define ceill(x) \
    (GL_LINK_WARNING ("ceill is unportable - " \
                      "use gnulib module mathl for portability"), \
     ceill (x))
#endif

#if @GNULIB_MATHL@ || !@HAVE_DECL_COSL@
extern long double cosl (long double x);
#endif
#if !@GNULIB_MATHL@ && defined GNULIB_POSIXCHECK
# undef cosl
# define cosl(x) \
    (GL_LINK_WARNING ("cosl is unportable - " \
                      "use gnulib module mathl for portability"), \
     cosl (x))
#endif

#if @GNULIB_MATHL@ || !@HAVE_DECL_EXPL@
extern long double expl (long double x);
#endif
#if !@GNULIB_MATHL@ && defined GNULIB_POSIXCHECK
# undef expl
# define expl(x) \
    (GL_LINK_WARNING ("expl is unportable - " \
                      "use gnulib module mathl for portability"), \
     expl (x))
#endif

#if @GNULIB_MATHL@ || !@HAVE_DECL_FLOORL@
extern long double floorl (long double x);
#endif
#if !@GNULIB_MATHL@ && defined GNULIB_POSIXCHECK
# undef floorl
# define floorl(x) \
    (GL_LINK_WARNING ("floorl is unportable - " \
                      "use gnulib module mathl for portability"), \
     floorl (x))
#endif

/* Write x as
     x = mantissa * 2^exp
   where
     If x finite and nonzero: 0.5 <= |mantissa| < 1.0.
     If x is zero: mantissa = x, exp = 0.
     If x is infinite or NaN: mantissa = x, exp unspecified.
   Store exp and return mantissa.  */
#if @GNULIB_FREXPL@ && @REPLACE_FREXPL@
# define frexpl rpl_frexpl
#endif
#if (@GNULIB_FREXPL@ && @REPLACE_FREXPL@) || !@HAVE_DECL_FREXPL@
extern long double frexpl (long double x, int *exp);
#endif
#if !@GNULIB_FREXPL@ && defined GNULIB_POSIXCHECK
# undef frexpl
# define frexpl(x,e) \
    (GL_LINK_WARNING ("frexpl is unportable - " \
                      "use gnulib module frexpl for portability"), \
     frexpl (x, e))
#endif

/* Return x * 2^exp.  */
#if @GNULIB_LDEXPL@ && @REPLACE_LDEXPL@
# define ldexpl rpl_ldexpl
#endif
#if (@GNULIB_LDEXPL@ && @REPLACE_LDEXPL@) || !@HAVE_DECL_LDEXPL@
extern long double ldexpl (long double x, int exp);
#endif
#if !@GNULIB_LDEXPL@ && defined GNULIB_POSIXCHECK
# undef ldexpl
# define ldexpl(x,e) \
    (GL_LINK_WARNING ("ldexpl is unportable - " \
                      "use gnulib module ldexpl for portability"), \
     ldexpl (x, e))
#endif

#if @GNULIB_MATHL@ || !@HAVE_DECL_LOGL@
extern long double logl (long double x);
#endif
#if !@GNULIB_MATHL@ && defined GNULIB_POSIXCHECK
# undef logl
# define logl(x) \
    (GL_LINK_WARNING ("logl is unportable - " \
                      "use gnulib module mathl for portability"), \
     logl (x))
#endif

#if @GNULIB_MATHL@ || !@HAVE_DECL_SINL@
extern long double sinl (long double x);
#endif
#if !@GNULIB_MATHL@ && defined GNULIB_POSIXCHECK
# undef sinl
# define sinl(x) \
    (GL_LINK_WARNING ("sinl is unportable - " \
                      "use gnulib module mathl for portability"), \
     sinl (x))
#endif

#if @GNULIB_MATHL@ || !@HAVE_DECL_SQRTL@
extern long double sqrtl (long double x);
#endif
#if !@GNULIB_MATHL@ && defined GNULIB_POSIXCHECK
# undef sqrtl
# define sqrtl(x) \
    (GL_LINK_WARNING ("sqrtl is unportable - " \
                      "use gnulib module mathl for portability"), \
     sqrtl (x))
#endif

#if @GNULIB_MATHL@ || !@HAVE_DECL_TANL@
extern long double tanl (long double x);
#endif
#if !@GNULIB_MATHL@ && defined GNULIB_POSIXCHECK
# undef tanl
# define tanl(x) \
    (GL_LINK_WARNING ("tanl is unportable - " \
                      "use gnulib module mathl for portability"), \
     tanl (x))
#endif


#if @GNULIB_SIGNBIT@
# if @REPLACE_SIGNBIT@
#  undef signbit
extern int gl_signbitf (float arg);
extern int gl_signbitd (double arg);
extern int gl_signbitl (long double arg);
#  if __GNUC__ >= 2 && !__STRICT_ANSI__
#   if defined FLT_SIGNBIT_WORD && defined FLT_SIGNBIT_BIT
#    define gl_signbitf(arg) \
       ({ union { float _value;						\
                  unsigned int _word[(sizeof (float) + sizeof (unsigned int) - 1) / sizeof (unsigned int)]; \
                } _m;							\
          _m._value = (arg);						\
          (_m._word[FLT_SIGNBIT_WORD] >> FLT_SIGNBIT_BIT) & 1;		\
        })
#   endif
#   if defined DBL_SIGNBIT_WORD && defined DBL_SIGNBIT_BIT
#    define gl_signbitd(arg) \
       ({ union { double _value;						\
                  unsigned int _word[(sizeof (double) + sizeof (unsigned int) - 1) / sizeof (unsigned int)]; \
                } _m;							\
          _m._value = (arg);						\
          (_m._word[DBL_SIGNBIT_WORD] >> DBL_SIGNBIT_BIT) & 1;		\
        })
#   endif
#   if defined LDBL_SIGNBIT_WORD && defined LDBL_SIGNBIT_BIT
#    define gl_signbitl(arg) \
       ({ union { long double _value;					\
                  unsigned int _word[(sizeof (long double) + sizeof (unsigned int) - 1) / sizeof (unsigned int)]; \
                } _m;							\
          _m._value = (arg);						\
          (_m._word[LDBL_SIGNBIT_WORD] >> LDBL_SIGNBIT_BIT) & 1;		\
        })
#   endif
#  endif
#  define signbit(x) \
   (sizeof (x) == sizeof (long double) ? gl_signbitl (x) : \
    sizeof (x) == sizeof (double) ? gl_signbitd (x) : \
    gl_signbitf (x))
# endif
#elif defined GNULIB_POSIXCHECK
  /* How to override a macro?  */
#endif


#ifdef __cplusplus
}
#endif

#endif /* _GL_MATH_H */
#endif /* _GL_MATH_H */
