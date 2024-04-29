#include "gb_x_utf8.h"

#include <errno.h>
#include <iconv.h>
#include <stdio.h>
#include <string.h>

#include <string>
namespace uBEE {
void gb18030_to_utf8(char *inbuf, char *outbuf, size_t outLen) {
    char *pinbuf = inbuf;
    size_t inLen = strlen(inbuf) + 1;
    iconv_t ct = iconv_open("utf-8", "gb18030");
    if (ct == (iconv_t)-1) {
        printf("\033[1;31miconv_open error!!!\n\033[0m");
        return;
    }
    memset(outbuf, 0, outLen);
    size_t ret = iconv(ct, &pinbuf, (size_t *)&inLen, &outbuf, (size_t *)&outLen);
    if (ret == (size_t)-1) {
        switch (errno) {
            case E2BIG:
                printf("\033[1;31merrno:E2BIG(outbuf空间不够)\n\033[0m");
                break;
            case EILSEQ:
                printf("\033[1;31merrno:EILSEQ(inbuf多字节序无效)\n\033[0m");
                break;
            case EINVAL:
                printf("\033[1;31merrno:EINVAL(有残余的字节未转换)\n\033[0m");
                break;
            default:
                break;
        }
    }
    iconv_close(ct);
}

void utf8_to_gb18030(char *inbuf, char *outbuf, size_t outLen) {
    char *pinbuf = inbuf;
    size_t inLen = strlen(inbuf) + 1;
    iconv_t ct = iconv_open("gb18030", "utf-8");
    if (ct == (iconv_t)-1) {
        printf("\033[1;31miconv_open error!!!\n\033[0m");
        return;
    }
    memset(outbuf, 0, outLen);
    size_t ret = iconv(ct, &pinbuf, (size_t *)&inLen, &outbuf, (size_t *)&outLen);
    if (ret == (size_t)-1) {
        switch (errno) {
            case E2BIG:
                printf("\033[1;31merrno:E2BIG(outbuf空间不够)\n\033[0m");
                break;
            case EILSEQ:
                printf("\033[1;31merrno:EILSEQ(inbuf多字节序无效)\n\033[0m");
                break;
            case EINVAL:
                printf("\033[1;31merrno:EINVAL(有残余的字节未转换)\n\033[0m");
                break;
            default:
                break;
        }
    }
    iconv_close(ct);
}
}  // namespace uBEE