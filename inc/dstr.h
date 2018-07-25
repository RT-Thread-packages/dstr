/*
 * File      : dstr.h
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
 */

#ifndef __DSTR_H__
#define __DSTR_H__

#include <rtthread.h>

struct rt_dstr
{
    char *str;
    size_t length;  /* allocated space. e.g.: "abc" + '\0' */
};
typedef struct rt_dstr rt_dstr_t;

rt_dstr_t *rt_dstr_new(const char *str);
void rt_dstr_del(rt_dstr_t *thiz);

rt_dstr_t *rt_dstr_cat(rt_dstr_t *thiz, const char *src);
rt_dstr_t *rt_dstr_ncat(rt_dstr_t *thiz, const char *src, size_t n);

int rt_dstr_cmp(rt_dstr_t *const dstr1, rt_dstr_t *const dstr2);
int rt_dstr_ncmp(rt_dstr_t *const dstr1, rt_dstr_t *const dstr2, size_t n);

int rt_dstr_casecmp(rt_dstr_t *const dstr1, rt_dstr_t *const dstr2);
int rt_dstr_strlen(rt_dstr_t *const thiz);

rt_dstr_t *rt_dstr_sprintf(rt_dstr_t *thiz, const char *fmt, ...);
rt_dstr_t *rt_dstr_append_printf(rt_dstr_t *thiz, const char *format, ...);
#endif /* __DSTR_H__ */
