
ifeq ($(CONFIG_SOC_EXYNOS7885_ANDROID_VERSION_P),y)
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7885-universal7885_FHD_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7885-universal7885_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7905-universal7905_FHD_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7905-universal7905_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7884) += exynos7904-universal7904_FHD_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7884) += exynos7904-universal7904_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7884) += exynos7884-universal7884_FHD_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7884) += exynos7884-universal7884_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7884A) += exynos7884b-universal7884b_FHD_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7884A) += exynos7884b-universal7884b_P_Treble.dtbo
dtb-y += exynos7885.dtb
endif

ifeq ($(CONFIG_SOC_EXYNOS7885_ANDROID_VERSION_Q_MR),y)
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7885-universal7885_FHD_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7885-universal7885_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7905-universal7905_FHD_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7905-universal7905_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7884) += exynos7904-universal7904_FHD_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7884) += exynos7904-universal7904_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7884) += exynos7884-universal7884_FHD_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7884) += exynos7884-universal7884_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7884A) += exynos7884b-universal7884b_FHD_P_Treble.dtbo
dtb-$(CONFIG_SOC_EXYNOS7884A) += exynos7884b-universal7884b_P_Treble.dtbo
dtb-y += exynos7885.dtb
endif

ifeq ($(CONFIG_SOC_EXYNOS7885_ANDROID_VERSION_P),y)
always         := $(dtb-y) $(dtbo-y)
subdir-y       := $(dts-dirs)
clean-files    := *.dtb *.dtbo
endif

ifeq ($(CONFIG_SOC_EXYNOS7885_ANDROID_VERSION_Q_MR),y)
always         := $(dtb-y) $(dtbo-y)
subdir-y       := $(dts-dirs)
clean-files    := *.dtb *.dtbo
endif
