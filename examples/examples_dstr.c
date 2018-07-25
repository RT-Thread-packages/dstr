/*
 * File      : examples_dstr.c
 * This file is the example code of dstr(dynamic string) package
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
 * 2018-07-25     never        add sample API
 */

#include <rtthread.h>
#include <finsh.h>
#include "dstr.h"
#include <dfs_posix.h>

void rt_dstr_print(rt_dstr_t *thiz)
{
    if (thiz == NULL)
        return;
    rt_kprintf("%s\n", thiz->str);
}

void dstr_test_new(void)
{
    rt_kprintf("\n");

    rt_dstr_t *p = NULL;

    p = rt_dstr_new("new dstr");
    rt_dstr_print(p);
    rt_dstr_del(p);
    rt_kprintf("\n");
}

void dstr_test_cat(void)
{
    rt_dstr_t *p1 = NULL, *p2 = NULL;
    const char *str = "cat ";

    p1 = rt_dstr_cat(p1, "cat sample1");

    rt_dstr_print(p1);

    rt_dstr_del(p1);

    p2 = rt_dstr_new(str);

    rt_dstr_cat(p2, "sample2");

    rt_dstr_print(p1);

    rt_dstr_del(p1);

    rt_kprintf("\n");
}

void dstr_test_ncat(void)
{
    rt_dstr_t *p1 = NULL, *p2 = NULL;
    const char *str = "ncat ";

    p1 = rt_dstr_ncat(p1, "ncat sample1", 12);

    rt_dstr_print(p1);

    rt_dstr_del(p1);

    p2 = rt_dstr_new(str);

    rt_dstr_ncat(p2, "sample2222", 7);

    rt_dstr_print(p1);

    rt_dstr_del(p1);

    rt_kprintf("\n");
}

void dstr_test_cmp(void)
{
    rt_dstr_t *p1 = NULL;
    rt_dstr_t *p2 = NULL;
    int res = 0;

    p1 = rt_dstr_new("helle");
    p2 = rt_dstr_new("hellc");

    res = rt_dstr_cmp(p1, p2);
    rt_kprintf("cmp result: %d\n", res);

    rt_dstr_del(p1);
    rt_dstr_del(p2);

    //  NULL
    p1 = rt_dstr_new("abc");
    res = rt_dstr_cmp(p1, NULL);
    rt_kprintf("s2:NULL result: %d\n", res);
    rt_dstr_del(p1);

    p1 = rt_dstr_new("efg");
    res = rt_dstr_cmp(NULL, p1);
    rt_kprintf("s1:NULL result: %d\n", res);
    rt_dstr_del(p1);

    res = rt_dstr_cmp(NULL, NULL);
    rt_kprintf("two NULL result: %d\n\n", res);
}

void dstr_test_ncmp(void)
{
    rt_dstr_t *p1 = NULL;
    rt_dstr_t *p2 = NULL;
    int res = 0;

    p1 = rt_dstr_new("hello");
    p2 = rt_dstr_new("hella");

    res = rt_dstr_ncmp(p1, p2, 5);
    rt_kprintf("ncmp result: %d\n", res);

    rt_dstr_del(p1);
    rt_dstr_del(p2);

    /* NULL */
    p1 = rt_dstr_new("abc");
    res = rt_dstr_ncmp(p1, NULL, 2);
    rt_kprintf("s2:NULL ncmp result: %d\n", res);
    rt_dstr_del(p1);

    p1 = rt_dstr_new("efg");
    res = rt_dstr_ncmp(NULL, p1, 3);
    rt_kprintf("s1:NULL ncmp result: %d\n", res);
    rt_dstr_del(p1);

    res = rt_dstr_ncmp(NULL, NULL, 4);
    rt_kprintf("two NULL ncmp result: %d\n\n", res);
}

void dstr_test_casecmp(void)
{
    rt_dstr_t *p1 = NULL;
    rt_dstr_t *p2 = NULL;
    int res = 0;

    p1 = rt_dstr_new("hello");
    p2 = rt_dstr_new("HELLO");

    res = rt_dstr_casecmp(p1, p2);
    rt_kprintf("casecmp result: %d\n", res);

    rt_dstr_del(p1);
    rt_dstr_del(p2);

    /* NULL */
    p1 = rt_dstr_new("abc");
    res = rt_dstr_casecmp(p1, NULL);
    rt_kprintf("s2:NULL casecmp result: %d\n", res);
    rt_dstr_del(p1);

    p1 = rt_dstr_new("efg");
    res = rt_dstr_casecmp(NULL, p1);
    rt_kprintf("s1:NULL casecmp result: %d\n", res);
    rt_dstr_del(p1);

    res = rt_dstr_casecmp(NULL, NULL);
    rt_kprintf("two NULL casecmp result: %d\n\n", res);
}

void dstr_test_strlen(void)
{
    rt_dstr_t *p1 = NULL;
    int res = 0;

    p1 = rt_dstr_new("hello strlen");

    res = rt_dstr_strlen(p1);

    if (res == -1)
        return;

    rt_kprintf("length: %d\n", res);

    rt_dstr_del(p1);

    rt_kprintf("\n");
}

void dstr_test_sprintf(void)
{
    const char *src = "sprintf";
    rt_dstr_t *p1 = NULL;
    rt_dstr_t *p2 = NULL;

    /* string format */
    p1 = rt_dstr_new("test");

    rt_dstr_sprintf(p1, "%s", src);

    rt_dstr_print(p1);

    rt_dstr_del(p1);

    /* hex format */
    p2 = rt_dstr_new("");

    rt_dstr_sprintf(p2, "%08x", 0x20180604);

    rt_dstr_print(p2);

    rt_dstr_del(p2);

    rt_kprintf("\n");
}

rt_dstr_t *path_cat(const char *path, const char *filename)
{
    rt_dstr_t *p = RT_NULL;

    p = rt_dstr_sprintf(p, "%s/%s", path, filename);

    return p;
}

rt_dstr_t *header_info_cat(char *send_buffer)
{
    rt_dstr_t *p = RT_NULL;
    const char *key = "header-key";

    /* build header for upload */
    p = rt_dstr_append_printf(p, "api-key: %s\r\n", key);
    rt_dstr_append_printf(p, "Content-Length: %d\r\n", strlen(send_buffer));
    rt_dstr_cat(p, "Content-Type: application/octet-stream\r\n");

    return p;
}

void dstr_test_append(void)
{
    char *buffer = "test of header";

    rt_dstr_print(path_cat("/home", "bsp/thread.c"));
    rt_dstr_del(path_cat("/home", "bsp/thread.c"));

    rt_kprintf("\n");

    rt_dstr_print(header_info_cat(buffer));
    rt_dstr_del(header_info_cat(buffer));

    rt_kprintf("\n");
}

void dstr_test(void)
{
    dstr_test_new();
    dstr_test_cat();
    dstr_test_ncat();
    dstr_test_cmp();
    dstr_test_ncmp();
    dstr_test_casecmp();
    dstr_test_strlen();
    dstr_test_sprintf();
    dstr_test_append();
}
MSH_CMD_EXPORT(dstr_test, dstr example);
