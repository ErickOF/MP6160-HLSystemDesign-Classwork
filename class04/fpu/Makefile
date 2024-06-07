include ../Makefile

TARGET?=fpu

CXXFLAGS += -DTB_NAME="\"$(TARGET)\""
LFLAGS += -DTB_NAME="\"$(TARGET)\""

ifdef FPU_AC_MODEL
	CXXFLAGS += -DFPU_AC_MODEL
	LFLAGS += -DFPU_AC_MODEL
endif

ifdef FPU_AT_MODEL
	CXXFLAGS += -DFPU_AT_MODEL
	LFLAGS += -DFPU_AT_MODEL
endif

ifdef FPU_LT_MODEL
	CXXFLAGS += -DFPU_LT_MODEL
	LFLAGS += -DFPU_LT_MODEL
endif

ifdef FPU_PV_MODEL
	CXXFLAGS += -DFPU_PV_MODEL
	LFLAGS += -DFPU_PV_MODEL
endif

waveform:
	@gtkwave $(TARGET).vcd
