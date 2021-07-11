/*
 *  linux/include/linux/throttle_limit.h
 *
 */

#ifndef __THROTTLE_LIMIT_H__
#define __THROTTLE_LIMIT_H__

#ifdef CONFIG_ARM_EXYNOS_ACME
extern int get_big_throttle_limit(void);
extern int get_little_throttle_limit(void);
extern int get_gpu_throttle_limit(void);
extern bool is_throttle_limit(unsigned int clipped_freq, int cpu);
#else
	int get_big_throttle_limit(void)
{
	return 0;
}
int get_little_throttle_limit(void)
{
	return 0;
}
int get_gpu_throttle_limit(void)
{
	return 0;
}
static inline bool is_throttle_limit(unsigned int clipped_freq, int cpu)
{
	return false;
}
#endif

#endif /* __THROTTLE_LIMIT_H__ */
