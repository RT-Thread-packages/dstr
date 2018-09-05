/*
 * File      : dstr.c
 * This file is part of dstr (dynamic string) package
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-07     never        the first version
 * 2018-07-25     never        add append_printf() and modify some APIs
 * 2018-08-30     never        add some APIs and modify some APIs
 */

#include <stdarg.h>
#include <string.h>
#ifdef __GNUC__
#include <strings.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include "dstr.h"

#define DBG_ENABLE
#undef  DBG_ENABLE
#define DBG_SECTION_NAME  "RTDSTR"
#define DBG_LEVEL         DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

typedef rt_dstr_t *(*save_t)(rt_dstr_t *thiz, const char *src, size_t n, size_t old_size);

/**
 * This function will create a dstr(dynamic string) object.
 *
 * @param str the string
 *
 * @return a new dstr thiz
 */
rt_dstr_t *rt_dstr_new(const char *str)
{
    rt_dstr_t *thiz = NULL;

    thiz = (rt_dstr_t *)malloc(sizeof(*thiz));
    if (thiz == NULL)
    {
        dbg_log(DBG_ERROR, "new.malloc error\n");
        goto err;
    }

    if (str == NULL)
        thiz->length = 1;
    else
        thiz->length = strlen(str) + 1;

    thiz->str = (char *)malloc(sizeof(thiz->length));
    if (thiz->str == NULL)
    {
        dbg_log(DBG_ERROR, "new.malloc error\n");
        goto err;
    }

    if (str == NULL)
        memcpy(thiz->str, "", thiz->length);
    else
        memcpy(thiz->str, str, thiz->length);

    return thiz;

err:
    rt_dstr_del(thiz);
    return NULL;
}

/**
 * This function will delete a dstr(dynamic string) object.
 *
 * @param thiz a dstr(dynamic string) thiz
 *
 * @return none
 */
void rt_dstr_del(rt_dstr_t *thiz)
{
    if (thiz == NULL)
        return;

    if (thiz->str != NULL)
    {
        free(thiz->str);
        thiz->str = NULL;
    }

    free(thiz);
}

static int _resize(rt_dstr_t *const thiz, size_t new_size)
{
    char *p = NULL;

    if (thiz == NULL)
    {
        dbg_log(DBG_ERROR, "_resize.thiz param error\n");
        goto err;
    }

    p = (char *)realloc(thiz->str, new_size);

    if (p == NULL)
    {
        dbg_log(DBG_ERROR, "_resize.realloc error\n");
        goto err;
    }
    else
    {
        thiz->length = new_size;
        dbg_log(DBG_INFO, "new_size:%d\n", thiz->length);
        thiz->str = p;
        return 0;
    }
err:
    return -1;
}

static rt_dstr_t *_ahead(rt_dstr_t *thiz, const char *src, size_t n, size_t old_size)
{
    memmove(thiz->str + n, thiz->str, n);
    memcpy(thiz->str, src, n);
    *(thiz->str + (old_size - 1) + n) = '\0';
    return thiz;
}

static rt_dstr_t *_behind(rt_dstr_t *thiz, const char *src, size_t n, size_t old_size)
{
    memcpy(thiz->str + (old_size - 1), src, n);
    *(thiz->str + (old_size - 1) + n) = '\0';
    return thiz;
}

static rt_dstr_t *_xcat(rt_dstr_t *thiz, const char *src, size_t n, save_t fun)
{
    int res = 0;
    size_t new_size = 0, old_size = 0;

    if (thiz == NULL)
        thiz = rt_dstr_new(NULL);

    if (src == NULL)
    {
        dbg_log(DBG_ERROR, "param error\n");
        goto err;
    }

    if (n > (strlen(src) + 1))
    {
        dbg_log(DBG_ERROR, "size error\n");
        goto err;
    }

    old_size = thiz->length;
    new_size = n + old_size;

    res = _resize(thiz, new_size);
    if (res == -1)
    {
        dbg_log(DBG_ERROR, "_resize error\n");
        goto err;
    }
    return fun(thiz, src, n, old_size);
err:
    return NULL;
}

/**
 * This function appends the src string to the dest object,
 * overwriting the terminating null byte '\0' at the end of the dest,
 * and then adds a terminating null byte.
 *
 * @param thiz the dstr(dynamic string)
 * @param src  the string
 *
 * @return the dest dstr
 */
rt_dstr_t *rt_dstr_cat(rt_dstr_t *thiz, const char *src)
{
    return rt_dstr_ncat(thiz, src, strlen(src));
}

/**
 * This function is similar, except that it will use at most n bytes from src,
 * and src does not need to be null-terminated if it contains n or more bytes.
 *
 * @param thiz the dstr(dynamic string)
 * @param src  the string
 * @param n it will use at most n bytes from src
 *
 * @return the dest dstr
 */
rt_dstr_t *rt_dstr_ncat(rt_dstr_t *thiz, const char *src, size_t n)
{
    return _xcat(thiz, src, n, _behind);
}

/**
 * This function prepends the src string to the dest object,
 * overwriting the terminating null byte '\0' at the end of the dest,
 * and then adds a terminating null byte.
 *
 * @param thiz the dstr(dynamic string)
 * @param src  the string
 *
 * @return the dest dstr
 */
rt_dstr_t *rt_dstr_precat(rt_dstr_t *thiz, const char *src)
{
    return _xcat(thiz, src, strlen(src), _ahead);
}

/**
 * This function is similar, except that it will use at most n bytes from src,
 * and src does not need to be null-terminated if it contains n or more bytes.
 *
 * @param thiz the dstr(dynamic string)
 * @param src  the string
 * @param n it will use at most n bytes from src
 *
 * @return the dest dstr
 */
rt_dstr_t *rt_dstr_prencat(rt_dstr_t *thiz, const char *src, size_t n)
{
    return _xcat(thiz, src, n, _ahead);
}

/**
 * This function appends the dstr to the dest object,
 * overwriting the terminating null byte '\0' at the end of the dest,
 * and then adds a terminating null byte.
 *
 * @param dst the dest dstr thiz
 * @param src the src dstr
 *
 * @return the dest dstr
 */
rt_dstr_t *rt_dstr_cat_dstr(rt_dstr_t *dst, rt_dstr_t *src)
{
    /* e.g.: src->str = "abc", src->length = 4 */
    return rt_dstr_ncat_dstr(dst, src, src->length - 1);
}

/**
 * This function is similar, except that it will use at most n bytes from src,
 * and src does not need to be null-terminated if it contains n or more bytes.
 *
 * @param n it will use at most n bytes from src
 *
 * @return the dest dstr
 */
rt_dstr_t *rt_dstr_ncat_dstr(rt_dstr_t *dst, rt_dstr_t *src, size_t n)
{
    return _xcat(dst, src->str, n, _behind);
}

/**
 * This function prepends the dstr to the dest object,
 * overwriting the terminating null byte '\0' at the end of the dest,
 * and then adds a terminating null byte.
 *
 * @param thiz the dstr(dynamic string) thiz
 * @param src  the string
 *
 * @return the dest dstr
 */
rt_dstr_t *rt_dstr_precat_dstr(rt_dstr_t *dst, rt_dstr_t *src)
{
    /* e.g.: src->str = "abc", src->length = 4 */
    return rt_dstr_prencat_dstr(dst, src, src->length - 1);
}

/**
 * This function is similar, except that it will use at most n bytes from src,
 * and src does not need to be null-terminated if it contains n or more bytes.
 *
 * @param thiz the dstr(dynamic string)
 * @param src  the string
 * @param n it will use at most n bytes from src
 *
 * @return the dest dstr
 */
rt_dstr_t *rt_dstr_prencat_dstr(rt_dstr_t *dst, rt_dstr_t *src, size_t n)
{
    return _xcat(dst, src->str, n, _ahead);
}

static void _param_process(rt_dstr_t *const d1, rt_dstr_t *const d2, char **s1, char **s2)
{
    if (d1 != NULL)
        *s1 = d1->str;
    else
        *s1 = NULL;

    if (d2 != NULL)
        *s2 = d2->str;
    else
        *s2 = NULL;
}

/**
 * This function compares dstr1 and dstr2.
 *
 * @param dstr1 the dstr to be compared
 * @param dstr2 the dstr to be compared
 *
 * @return the result
 */
int rt_dstr_cmp(rt_dstr_t *const dstr1, rt_dstr_t *const dstr2)
{
    char *s1 = NULL, *s2 = NULL;

    _param_process(dstr1, dstr2, &s1, &s2);
    return strcmp(s1, s2);
}

/**
 * This function compares dstr1 and dstr2.
 *
 * @param dstr1 the dstr to be compared
 * @param dstr2 the dstr to be compared
 * @param count the maximum compare length
 *
 * @return the result
 */
int rt_dstr_ncmp(rt_dstr_t *const dstr1, rt_dstr_t *const dstr2, size_t n)
{
    char *s1 = NULL, *s2 = NULL;

    _param_process(dstr1, dstr2, &s1, &s2);
    return strncmp(s1, s2, n);
}

/**
 * This function will compare two dstrs while ignoring differences in case.
 *
 * @param dstr1 the dstr to be compared
 * @param dstr2 the dstr to be compared
 *
 * @return the result
 */
int rt_dstr_casecmp(rt_dstr_t *const dstr1, rt_dstr_t *const dstr2)
{
    char *s1 = NULL, *s2 = NULL;

    _param_process(dstr1, dstr2, &s1, &s2);
    return strcasecmp(s1, s2);
}

/**
 * This function will return the length of a dstr, which terminate will
 * null character.
 *
 * @param thiz the dstr
 *
 * @return the length of dstr
 */
int rt_dstr_strlen(rt_dstr_t *const thiz)
{
    if (thiz == NULL)
        return -1;

    return strlen(thiz->str);
}

/**
 * This function will return the dest dstr, which terminate will
 * null character.
 *
 * @param thiz the dstr
 *
 * @return the dest dstr
 */
rt_dstr_t *rt_dstr_sprintf(rt_dstr_t *thiz, const char *fmt, ...)
{
    va_list  ap;
    int new_len = 0;

    if (thiz == NULL)
        thiz = rt_dstr_new(NULL);

    va_start(ap, fmt);

    new_len = vsnprintf(NULL, 0, fmt, ap);      /* strlen("test sprintf") = 12 */

    if (_resize(thiz, new_len + 1) == -1) /* allocated space */
    {
        va_end(ap);
        goto err;
    }

    vsnprintf(thiz->str, new_len + 1, fmt, ap);

    va_end(ap);

    return thiz;
err:
    return NULL;
}

/**
 * This function will return the dest dstr, which terminate will
 * null character.
 *
 * @param thiz the dstr
 *
 * @return the dest dstr
 */
rt_dstr_t *rt_dstr_append_printf(rt_dstr_t *thiz, const char *format, ...)
{
    va_list ap;
    char *dst = NULL;
    int old_len = 0, new_len = 0;

    if (thiz == NULL)
        thiz = rt_dstr_new(NULL);

    va_start(ap, format);

    old_len = thiz->length;

    new_len = vsnprintf(NULL, 0, format, ap);

    if (_resize(thiz, old_len + new_len) == -1)
    {
        va_end(ap);
        goto err;
    }

    dst = thiz->str + old_len - 1; /* remove '\0' */

    vsnprintf(dst, 1 + new_len, format, ap);

    va_end(ap);

    return thiz;
err:
    return NULL;
}
