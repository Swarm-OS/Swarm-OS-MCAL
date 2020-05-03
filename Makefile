#
# Makefile for the C demo
#
# Targets:
#   all         generates flash file
#   install     downloads elf file to mcu
#


FILENAME        = main

MCU             = STM32F411
MCU_CAPS        = $(shell echo $(MCU) | tr a-z A-Z)

local_src_dir   = ./mcal

ifndef MCU
$(error MCU is not set)
endif
	
ifndef OBJ_DIR
$(info OBJ_DIR not defined, local dir is used: ./obj/mcal)
	local_obj_dir= ./obj/mcal
else
	local_obj_dir= $(OBJ_DIR)
endif

local_srcs	+= $(wildcard $(local_src_dir)/*.c)

ifneq (,$(findstring STM32,$(MCU)))
	local_srcs	+= $(wildcard $(local_src_dir)/stm32/*.c)
	local_srcs	+= $(wildcard $(local_src_dir)/stm32/*/*.c)
#	local_srcs	+= $(wildcard $(local_src_dir)/stm32/*/startup_stm32f411xe.s)
$(info $$local_srcs is [${local_srcs}])
else
$(error Unknown MCU Vendor/Major architecture)
endif

local_objects_tmp	= $(local_srcs:$(local_src_dir)%.c=$(local_obj_dir)%.o)
local_objects		= $(local_objects_tmp:$(local_src_dir)%.s=$(local_obj_dir)%.o)
$(info $$local_objects is [${local_objects}])


AS 			= arm-none-eabi-as
ASFLAGS		= 

CC	        = arm-none-eabi-gcc
CCFLAGS		= -mcpu=cortex-m4 -DSTM32F411 -Wall -mthumb -ffunction-sections -fdata-sections
CCFLAGS	   += -I ./includes/ -I ./mcal/

LD        	= arm-none-eabi-gcc
LDFLAGS	    = -T ./mcal/swarm-os.ld
#LDFLAGS		= -T ./mcal/stm32/stm32f4xx/stm32f411.ld
LDFLAGS	   += --specs=nosys.specs -L ./includes

OBJCPY		= arm-none-eabi-objcopy
OBJCPY_FLAGS= -O binary 

PROG		= sudo dfu-util
PROG_FLAGS	= -d 0483:df11 -a 0 -s 0x08000000 
# $(local_obj_dir) $(local_objects)
all: $(FILENAME).bin

install: $(FILENAME).bin
	$(PROG) $(PROG_FLAGS) -D $<

$(FILENAME).bin: $(FILENAME).elf
	$(OBJCPY) $(OBJCPY_FLAGS) $< $@

$(FILENAME).elf: $(local_obj_dir)  $(local_objects) 
	$(LD) $(LDFLAGS) -o $@ $(local_objects) 

$(local_obj_dir)/%.o: $(local_src_dir)/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

$(local_obj_dir)/%.o: $(local_src_dir)/%.s
	$(AS) $(ASFLAGS) -o $@ $<

$(local_obj_dir):
	mkdir -p $(dir $(local_objects))