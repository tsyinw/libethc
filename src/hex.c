#include <ethc/hex.h>
#include <strings.h>

#if defined(_MSC_VER)
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

#define HEXCHARS "0123456789abcdef"

int eth_is_hex(const char *str, size_t len, int strict) {
  int prefix = 0;
  size_t i;

  len = len == -1 ? strlen(str) : len;

  if (!str || len == 0)
    return 0;

  if (strncasecmp(str, "0x", 2) == 0)
    prefix = 1;

  if (strict && !prefix)
    return 0;

  if (prefix) {
    str += 2;
    len -= 2;
  }

  for (i = 0; i < len; i++) {
    char ch = str[i];
    if (((ch < 'A' || ch > 'F') && (ch < 'a' || ch > 'f')) &&
        (ch < '0' || ch > '9'))
      return 0;
  }

  return 1;
}

int eth_hex_pad_left(char *rstr, const char *str, size_t len, size_t width) {
  size_t fill_len = 0;

  len = len == -1 ? strlen(str) : len;

  if(!str || !rstr)
    return 0;

  if (len > width || !eth_is_hex(str, len, 0))
    return 0;

  fill_len = width - len;
  memset(rstr, '0', fill_len);
  memcpy(rstr + fill_len, str, len);
  rstr[width] = '\0';

  return 1;
}

int eth_hex_pad_right(char *rstr, const char *str, size_t len, size_t width) {
  size_t fill_len = 0;

  len = len == -1 ? strlen(str) : len;

  if(!rstr || !str)
    return 0;

  if (!str || len > width || !eth_is_hex(str, len, 0))
    return 1;

  strncpy(rstr, str, len);
  fill_len = width - len;
  memset(rstr + len, '0', fill_len);
  rstr[width] = '\0';

  return 1;
}

int eth_hex_from_bytes(char *rstr, const uint8_t *bytes, size_t len) {
  size_t i = 0, j = 0;

  if(!rstr || !bytes || len < 1)
    return 0;

  while(i < len) {
    rstr[j++] = HEXCHARS[((bytes[i] & 0xFF) >> 4) & 0xF];
    rstr[j++] = HEXCHARS[(bytes[i] & 0xFF) & 0xF];
    i++;
  }

  rstr[j] = '\0';

  return 1;
};

