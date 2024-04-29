#ifndef UBEE_GB_TO_UTF8_H
#define UBEE_GB_TO_UTF8_H

#include <string>

namespace uBEE {
void gb18030_to_utf8(char *inbuf, char *outbuf, size_t outLen);
void utf8_to_gb18030(char *inbuf, char *outbuf, size_t outLen);
}  // namespace uBEE

#endif  // UBEE_GB_TO_UTF8_H