/* ce-compatibility.c */

#include <windows.h>
#include "ce-compatibility.h"

int errno = 0;

int winerror_to_errno(int winerror)
{
    switch(winerror) {
        case 2: return 2;
        case 3: return 2;
        case 4: return 24;
        case 5: return 13;
        case 6: return 9;
        case 7: return 12;
        case 8: return 12;
        case 9: return 12;
        case 10: return 7;
        case 11: return 8;
        case 15: return 2;
        case 16: return 13;
        case 17: return 18;
        case 18: return 2;
        case 19: return 13;
        case 20: return 13;
        case 21: return 13;
        case 22: return 13;
        case 23: return 13;
        case 24: return 13;
        case 25: return 13;
        case 26: return 13;
        case 27: return 13;
        case 28: return 13;
        case 29: return 13;
        case 30: return 13;
        case 31: return 13;
        case 32: return 13;
        case 33: return 13;
        case 34: return 13;
        case 35: return 13;
        case 36: return 13;
        case 53: return 2;
        case 65: return 13;
        case 67: return 2;
        case 80: return 17;
        case 82: return 13;
        case 83: return 13;
        case 89: return 11;
        case 108: return 13;
        case 109: return 32;
        case 112: return 28;
        case 114: return 9;
        case 128: return 10;
        case 129: return 10;
        case 130: return 9;
        case 132: return 13;
        case 145: return 41;
        case 158: return 13;
        case 161: return 2;
        case 164: return 11;
        case 167: return 13;
        case 183: return 17;
        case 188: return 8;
        case 189: return 8;
        case 190: return 8;
        case 191: return 8;
        case 192: return 8;
        case 193: return 8;
        case 194: return 8;
        case 195: return 8;
        case 196: return 8;
        case 197: return 8;
        case 198: return 8;
        case 199: return 8;
        case 200: return 8;
        case 201: return 8;
        case 202: return 8;
        case 206: return 2;
        case 215: return 11;
        case 1816: return 12;
        default: return EINVAL;
    }
}

char* strerror(long err)
{
  return "Unknown Error";
}

int isatty(int fd)
{
  return 1;
}

HANDLE _get_osfhandle(FILE* f)
{
  return ((long) f);
}


#define CHAR_MAX 255

struct lconv lc;

struct lconv* localeconv()
{
  lc.decimal_point	=	"."; //	Decimal-point separator used for non-monetary quantities.
  lc.thousands_sep	=	""; //	Separators used to delimit groups of digits to the left of the decimal point for non-monetary quantities.
  lc.grouping		=	""; //	Specifies the amount of digits that form each of the groups to be separated by thousands_sep separator for non-monetary quantities. This is a zero-terminated sequence of char values that may contain different grouping sizes for each successive group starting from the right, each number indicating the amount of digits for the group; the last number before the ending zero in this string is used for the remaining groups. For example, assuming thousand_sep is set to "," and the number to represent is one million (1000000):
  lc.int_curr_symbol	=	""; //	International currency symbol. This is formed by the three-letter ISO-4217 entry code for the currency, like "USD" for U.S.-Dollar or "GBP" for Pound Sterling, followed by the character used to separate this symbol from the monetary quantity
  lc.currency_symbol	=	""; //	Local currency symbol, like "$".
  lc.mon_decimal_point	=	""; //	Decimal-point separator used for monetary quantities.
  lc.mon_thousands_sep	=	""; //	Separators used to delimit groups of digits to the left of the decimal point for monetary quantities.
  lc.mon_grouping	=	""; //	Specifies the amount of digits that form each of the groups to be separated by mon_thousands_sep separator for monetary quantities. See grouping description above.
  lc.positive_sign	=	""; //	Sign to be used for nonnegative (positive or zero) monetary quantities.
  lc.negative_sign	=	""; //	Sign to be used for negative monetary quantities.
  lc.frac_digits	=	CHAR_MAX; //	Amount of fractional digits to the right of the decimal point for monetary quantities in the local format.
  lc.p_cs_precedes	=	CHAR_MAX; //	Whether the currency symbol should precede nonnegative (positive or zero) monetary quantities. If this value is 1, the currency symbol should precede; if it is 0, it should follow.
  lc.n_cs_precedes	=	CHAR_MAX; //	Whether the currency symbol should precede negative monetary quantities. If this value is 1, the currency symbol should precede; if it is 0 it should follow.
  lc.p_sep_by_space	=	CHAR_MAX; //	Whether a space should appear between the currency symbol and nonnegative (positive or zero) monetary quantities. If this value is 1, a space should appear; if it is 0 it should not.
  lc.n_sep_by_space	=	CHAR_MAX; //	Whether a space should appear between the currency symbol and negative monetary quantities. If this value is 1, a space should appear; if it is 0 it should not.
  lc.p_sign_posn	=	CHAR_MAX; //	Position of the sign for nonnegative (positive or zero) monetary quantities:
  lc.n_sign_posn	=	CHAR_MAX; //	Position of the sign for negative monetary quantities. See p_sign_posn above.
  lc.int_frac_digits	=	CHAR_MAX; //	Same as frac_digits, but for the international format (instead of the local format).
//  lc.int_p_cs_precedes	=	CHAR_MAX; //	Same as p_cs_precedes, but for the international format.
//  lc.int_n_cs_precedes	=	CHAR_MAX; //	Same as n_cs_precedes, but for the international format.
//  lc.int_p_sep_by_space	=	CHAR_MAX; //	Same as p_sep_by_space, but for the international format.
//  lc.int_n_sep_by_space	=	CHAR_MAX; //	Same as n_sep_by_space, but for the international format.
//  lc.int_p_sign_posn	=	CHAR_MAX; //	Same as p_sign_posn, but for the international format.
//  lc.int_n_sign_posn	=	CHAR_MAX; //
  return &lc;
}

UINT WINAPI SetErrorMode(UINT uMode)
{
  return 0;
}

int getpid()
{
  return (int)GetCurrentProcessId();
}

__p_sig_fn_t signal(int signum, __p_sig_fn_t handler)
{
  return SIG_ERR;
}

int raise(int sig)
{
  return 0;
}

