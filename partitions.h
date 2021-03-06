#ifndef PARTITIONS_H
#define PARTITIONS_H

#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>

/* amount of partitions */
#define PARTITIONS_MAX_COUNT 4
#define PARTITION_MAX_NAME_LENGTH 16

#define ERASE_ON_CREATION true
#define NO_ERASE_ON_CREATION false

/* partition descriptor */
typedef struct {
	/* partition name */
	char name[PARTITION_MAX_NAME_LENGTH];
	/* flash memory start address */
	uint32_t origin_addr;
	/* size of partition; should be multiple to flash page size */
	size_t size;
	/* 0 - keep flash data; 1- erase on creation */
	bool erase_data;
} prtn_desc_t;

typedef struct {
	ssize_t (*copy)(void *dest, void *src, size_t n);
	ssize_t (*erase_page)(void *addr);
	/* can be NULL */
	void (*flash_unlock)(void);
	/* can be NULL */
	void (*flash_lock)(void);
	/* can be NULL */
	void (*critical_section_start)(void);
	/* can be NULL */
	void (*critical_section_end)(void);
} prtn_callbacks_t;

typedef struct {
	uint32_t flash_page_size;
	uint32_t flash_start;
	uint32_t flash_size;
} prtn_flash_params;

typedef struct {
	prtn_flash_params flash_params;
	prtn_desc_t partitions[PARTITIONS_MAX_COUNT];
} prtn_table_t;

void partitions_register_callbacks(prtn_callbacks_t *cb);
void partition_table_init(prtn_table_t *table);
int partition_copy(char *dest, char *src);
bool partition_erase(char *name);
bool partition_is_empty(char *name);
void partitions_test(void);
prtn_desc_t *partition_get_by_name(char *name);



#endif /* PARTITIONS_H */
