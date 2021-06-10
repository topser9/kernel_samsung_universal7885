dtb-$(CONFIG_ARCH_EXYNOS7) += exynos7-espresso.dtb

dtb-$(CONFIG_SOC_EXYNOS8890) += exynos8890-maestro.dtb
dtb-$(CONFIG_SOC_EXYNOS8895) += exynos8895-smdk8895.dtb
dtb-$(CONFIG_SOC_EMULATOR7872) += exynos7872-emulator7872.dtb
dtb-$(CONFIG_SOC_EXYNOS7872) += exynos7872-smdk7872.dtb
dtb-$(CONFIG_SOC_EXYNOS7872) += exynos7872-maestro7872.dtb

ifneq ($(CONFIG_SOC_EXYNOS7885_ANDROID_VERSION_P),y)
ifneq ($(CONFIG_SOC_EXYNOS7885_ANDROID_VERSION_Q_MR),y)
ifeq ($(CONFIG_SOC_EXYNOS7883),y)
dtb-y += exynos7883-universal7883.dtb
dtb-y += exynos7883-universal7883_FHD.dtb
else
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7885-smdk7885.dtb
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7885-universal7885.dtb
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7885-universal7885_FHD.dtb
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7885-universal7885_O_Treble.dtb
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7885-universal7885_FHD_O_Treble.dtb
endif
endif
endif

ifeq ($(CONFIG_SOC_EXYNOS7885_ANDROID_VERSION_P_MR),y)
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7885-universal7885_FHD_P_MR.dtb
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7885-universal7885_P_MR.dtb
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7885-universal7885_FHD_P_MR_Treble.dtb
dtb-$(CONFIG_SOC_EXYNOS7885) += exynos7885-universal7885_P_MR_Treble.dtb
ifeq ($(CONFIG_SOC_EXYNOS7884),y)
dtb-y += exynos7884-universal7884_FHD_P_MR_Treble.dtb
dtb-y += exynos7884-universal7884_P_MR_Treble.dtb
endif
ifeq ($(CONFIG_SOC_EXYNOS7884A),y)
dtb-y += exynos7884a-universal7884a_FHD_P_MR_Treble.dtb
dtb-y += exynos7884a-universal7884a_P_MR_Treble.dtb
endif
always		:= $(dtb-y)
subdir-y	:= $(dts-dirs)
clean-files	:= *.dtb
else
ifeq ($(CONFIG_SOC_EXYNOS7885_ANDROID_VERSION_P),y)
dts-dirs := dtbo
endif
ifeq ($(CONFIG_SOC_EXYNOS7885_ANDROID_VERSION_Q_MR),y)
dts-dirs := dtbo
endif

ifeq ($(CONFIG_SOC_EXYNOS7885_ANDROID_VERSION_P),y)
always		:= $(dtb-y) $(dtbo-y)
subdir-y	:= $(dts-dirs)
clean-files	:= *.dtb *.dtbo
endif
ifeq ($(CONFIG_SOC_EXYNOS7885_ANDROID_VERSION_Q_MR),y)
always		:= $(dtb-y) $(dtbo-y)
subdir-y	:= $(dts-dirs)
clean-files	:= *.dtb *.dtbo
else
always		:= $(dtb-y)
subdir-y	:= $(dts-dirs)
clean-files	:= *.dtb
endif
endif
