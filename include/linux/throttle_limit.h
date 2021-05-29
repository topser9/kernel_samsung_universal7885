/*
 *  linux/include/linux/throttle_limit.h
 *
 */

#ifndef __THROTTLE_LIMIT_H__
#define __THROTTLE_LIMIT_H__

extern unsigned int big_throttle_limit;
extern unsigned int little_throttle_limit;
extern unsigned int gpu_throttle_limit;

#ifdef CONFIG_ARM_EXYNOS_ACME
extern bool is_throttle_limit(unsigned int clipped_freq, int cpu);
#else
static inline bool is_throttle_limit(unsigned int clipped_freq, int cpu)
{
	return false;
}
#endif

#endif /* __THROTTLE_LIMIT_H__ */
