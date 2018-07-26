/**
 * This header implements macros for creating storage objects 
 * with 1 byte (8bit) packing across all supported platforms.
 *
 * Example use...
 *
 *     PACK_PREFIX
 *     typedef struct _nameOfType_t
 *     {
 *         uint8_t aByte;
 *         uint16_t aShort;
 *         uint32_t aWord;
 *     } PACK_ATTRIB nameOfType_t;
 *     PACK_SUFFIX
 *
 */
#pragma once

#ifdef __GNUC__
	/* All GCC versions supports packed attribute */
	#define PACK_PREFIX /* empty */
	#define PACK_SUFFIX /* empty */
	#define PACK_ATTRIB __attribute__ ((packed))
#else
	/* MSVC uses pragma's to being and end regions of code */
	#define PACK_PREFIX	__pragma(pack(push, 1))
	#define PACK_SUFFIX	__pragma(pack(pop))
	#define PACK_ATTRIB /* empty */
#endif
