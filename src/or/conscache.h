/* Copyright (c) 2017, The Tor Project, Inc. */
/* See LICENSE for licensing information */

#ifndef TOR_CONSCACHE_H
#define TOR_CONSCACHE_H

typedef struct consensus_cache_entry_t consensus_cache_entry_t;
typedef struct consensus_cache_t consensus_cache_t;

#define CC_LABEL_SHA512      "sha512-digest"
#define CC_LABEL_DOCTYPE     "doctype"
#define CC_LABEL_COMPRESSION "compression"
#define CC_LABEL_

consensus_cache_t *consensus_cache_open(const char *subdir, int max_entries);
void consensus_cache_free(consensus_cache_t *cache);
consensus_cache_entry_t *consensus_cache_add(consensus_cache_t *cache,
                                             const config_line_t *labels,
                                             const uint8_t *data,
                                             size_t datalen);

consensus_cache_entry_t *consensus_cache_find_first(
                                             consensus_cache_t *cache,
                                             const char *key,
                                             const char *value);

void consensus_cache_find_all(smartlist_t *out,
                              consensus_cache_t *cache,
                              const char *key,
                              const char *value);
void consensus_cache_filter_list(smartlist_t *lst,
                                 const char *key,
                                 const char *value);

const char *consensus_cache_entry_get_value(const consensus_cache_entry_t *ent,
                                            const char *key);
const config_line_t *consensus_cache_entry_get_labels(
                                          const consensus_cache_entry_t *ent);

void consensus_cache_entry_incref(consensus_cache_entry_t *ent);
void consensus_cache_entry_decref(consensus_cache_entry_t *ent);

void consensus_cache_entry_mark_for_removal(consensus_cache_entry_t *ent);
int consensus_cache_entry_get_body(const consensus_cache_entry_t *ent,
                                   const uint8_t **body_out,
                                   size_t *sz_out);

#endif