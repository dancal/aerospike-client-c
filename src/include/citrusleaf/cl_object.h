/*
 * Copyright 2008-2014 Aerospike, Inc.
 *
 * Portions may be licensed to Aerospike, Inc. under one or more contributor
 * license agreements.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */
#pragma once

#include <stdlib.h>

/******************************************************************************
 * TYPES
 ******************************************************************************/


typedef enum cl_type_e { 
    CL_NULL         = 0x00,
    CL_INT          = 0x1,
    CL_FLOAT        = 2,
    CL_STR          = 0x03,
    CL_BLOB         = 0x04,
    CL_TIMESTAMP    = 5,
    CL_DIGEST       = 6,
    CL_JAVA_BLOB    = 7,
    CL_CSHARP_BLOB  = 8,
    CL_PYTHON_BLOB  = 9,
    CL_RUBY_BLOB    = 10,
    CL_PHP_BLOB     = 11,
    CL_ERLANG_BLOB  = 12,
    CL_APPEND       = 13,
    CL_RTA_LIST     = 14,
    CL_RTA_DICT     = 15,
    CL_RTA_APPEND_DICT = 16,
    CL_RTA_APPEND_LIST = 17,
    CL_LUA_BLOB     = 18,
    CL_MAP          = 19,
    CL_LIST         = 20,
    CL_UNKNOWN      = 666666
} cl_type;

/**
 * An object is the value in a bin, or it is used as a key
 * The object is typed according to the citrusleaf typing system
 * These are often stack allocated, and are assigned using the 'wrap' calls
 */
typedef struct cl_object_s {
    cl_type         type;
    size_t          sz; 
    union {
        char *      str;    // note for str: sz is strlen (not strlen+1 
        void *      blob;
        int64_t     i64;    // easiest to have one large int type
    } u;
    void *          free;   // if this is set, this must be freed on destructuion   
} cl_object;

/******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

void citrusleaf_object_init(cl_object * o);
void citrusleaf_object_init_str(cl_object * o, char const * str);
void citrusleaf_object_init_str2(cl_object * o, char const * str, size_t str_len);
void citrusleaf_object_init_blob(cl_object * o, void const * buf, size_t buf_len);
void citrusleaf_object_init_blob2(cl_object * o, void const * buf, size_t buf_len, cl_type type);
void citrusleaf_object_init_blob_handoff(cl_object *o, void *blob, size_t len, cl_type t);
void citrusleaf_object_init_int(cl_object * o, int64_t i);
void citrusleaf_object_init_null(cl_object * o);
void citrusleaf_object_free(cl_object * o);
int citrusleaf_copy_object(cl_object * destobj, cl_object * srcobj);
