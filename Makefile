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
$(info $$local_srcs is [${local_srcs}])
else
$(error Unknown MCU Vendor/Major architecture)
endif

local_objects	= $(local_srcs:$(local_src_dir)%.c=$(local_obj_dir)%.o)
$(info $$local_objects is [${local_objects}])

CCLD        = arm-none-eabi-gcc
CCFLAGS		= -mcpu=cortex-m4 -DSTM32F411 -Wall -mthumb -I ./includes/ -I ./mcal/
LDFLAGS		= -T ./mcal/stm32/stm32f4xx/stm32f411.ld --specs=nosys.specs -L ./includes/

all: $(local_obj_dir) $(local_objects) $(FILENAME).elf

$(FILENAME).elf: $(local_objects)
	$(CCLD) $(LDFLAGS) -o $@ $(local_objects) 

$(local_obj_dir)/%.o: $(local_src_dir)/%.c
	$(CCLD) $(CCFLAGS) -c -o $@ $<

$(local_obj_dir):
	mkdir -p $(dir $(local_objects))