/*
   Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.










   The lines above are intentionally left blank
*/

#ifndef MYSQL_STAGE_H
#define MYSQL_STAGE_H

/**
  @file mysql/psi/mysql_stage.h
  Instrumentation helpers for stages.
*/

#include "mysql/psi/psi.h"

/**
  @defgroup Stage_instrumentation Stage Instrumentation
  @ingroup Instrumentation_interface
  @{
*/

/**
  @def mysql_stage_register(P1, P2, P3)
  Stage registration.
*/
#ifdef HAVE_PSI_STAGE_INTERFACE
#define mysql_stage_register(P1, P2, P3) \
  inline_mysql_stage_register(P1, P2, P3)
#else
#define mysql_stage_register(P1, P2, P3) \
  do {} while (0)
#endif

#ifdef HAVE_PSI_STAGE_INTERFACE
  #define MYSQL_SET_STAGE(K, F, L) \
    inline_mysql_set_stage(K, F, L)
#else
  #define MYSQL_SET_STAGE(K, F, L) \
    do {} while (0)
#endif

#ifdef HAVE_PSI_STAGE_INTERFACE
static inline void inline_mysql_stage_register(
  const char *category, PSI_stage_info **info, int count)
{
  PSI_STAGE_CALL(register_stage)(category, info, count);
}
#endif

#ifdef HAVE_PSI_STAGE_INTERFACE
static inline void
inline_mysql_set_stage(PSI_stage_key key,
                       const char *src_file, int src_line)
{
  PSI_STAGE_CALL(start_stage)(key, src_file, src_line);
}
#endif

/** @} (end of group Stage_instrumentation) */

#endif

