#ifndef ETHC_BLOOM_H
#define ETHC_BLOOM_H
#include <stddef.h>
#include <stdint.h>

struct eth_bloom {
  uint64_t bitsets[32];
};

int eth_bloom_create(struct eth_bloom *bloom);
int eth_bloom_from_bytes(struct eth_bloom *bloom, const uint8_t *bytes, size_t len);
int eth_bloom_and(const struct eth_bloom *bloom1, const struct eth_bloom *bloom2);
int eth_bloom_or(struct eth_bloom *dest_bloom, const struct eth_bloom *src_bloom);
int eth_bloom_copy(struct eth_bloom *dest_bloom, const struct eth_bloom *src_bloom);

#endif
