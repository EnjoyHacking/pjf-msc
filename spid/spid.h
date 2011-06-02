/*
 * spid: Statistical Packet Inspection
 * Copyright (C) 2011 Paweł Foremski <pawel@foremski.pl>
 * This software is licensed under GNU GPL version 3
 */

#ifndef _SPID_H_
#define _SPID_H_

#include "settings.h"
#include "datastructures.h"

/** Initialize spid
 * Does initialization of struct spid and setups basic events
 * @param so         options to apply (may be NULL)
 * @retval NULL      failure
 */
struct spid *spid_init(struct spid_options *so);

/** Add traffic source
 * @param type       type of the source (SPI_SOURCE_PCAP, ...)
 * @param label      if not 0, use as learning source for protocol with such numeric ID
 * @param args       source-specific arguments to the source, parsed by relevant handler
 * @retval 0         success
 * @retval 1         failure
 * @retval <0        error specific to source
 */
int spid_source_add(struct spid *spid, spid_source_t type, label_t label, const char *args);

/** Make one iteration of the main spid loop
 * @retval  0        success
 * @retval -1        temporary error
 * @retval  1        permanent error
 */
int spid_loop(struct spid *spid);

/** Announce a spid event
 * @param evname     spid event name (referenced)
 * @param delay_ms   delay in miliseconds before delivering the event
 * @param arg        opaque data specific to given event
 * @param argfree    do mmatic_freeptr(arg) after event handling / ignoring
 */
void spid_announce(struct spid *spid, const char *evname, uint32_t delay_ms, void *arg, bool argfree);

/** Subscribe to given spid event
 * @param evname     spid event name (referenced)
 * @param cb         event handler - receives code and data from spid_announce()
 * @param aggregate  if true, ignore further events until the first one is handled
 */
void spid_subscribe(struct spid *spid, const char *evname, spid_event_cb_t *cb, bool aggregate);

/** Stop spid main loop
 * @param  0         success
 * @param -1         error occured
 */
int spid_stop(struct spid *spid);

/** Free spid memory, close all resources, etc */
void spid_free(struct spid *spid);

#endif
