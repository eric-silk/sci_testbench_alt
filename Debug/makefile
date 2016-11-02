################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /home/eric/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./77D_sci.obj" \
"./sci_api.obj" \
"./sci_testbench.obj" \
"./F2837xD_common/source/F2837xD_CodeStartBranch.obj" \
"./F2837xD_common/source/F2837xD_CpuTimers.obj" \
"./F2837xD_common/source/F2837xD_DefaultISR.obj" \
"./F2837xD_common/source/F2837xD_Gpio.obj" \
"./F2837xD_common/source/F2837xD_Ipc.obj" \
"./F2837xD_common/source/F2837xD_PieCtrl.obj" \
"./F2837xD_common/source/F2837xD_PieVect.obj" \
"./F2837xD_common/source/F2837xD_SysCtrl.obj" \
"./F2837xD_common/source/F2837xD_usDelay.obj" \
"./F2837xD_headers/source/F2837xD_GlobalVariableDefs.obj" \
"../2837x_FLASH_lnk_cpu1.cmd" \
"../F2837xD_headers/cmd/F2837xD_Headers_nonBIOS_cpu1.cmd" \
$(GEN_CMDS__FLAG) \
-lrts2800_fpu32.lib \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include F2837xD_common/source/subdir_vars.mk
-include F2837xD_headers/cmd/subdir_vars.mk
-include F2837xD_headers/source/subdir_vars.mk
-include subdir_rules.mk
-include F2837xD_common/source/subdir_rules.mk
-include F2837xD_headers/cmd/subdir_rules.mk
-include F2837xD_headers/source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
sci_testbench_alt.out \

EXE_OUTPUTS__QUOTED += \
"sci_testbench_alt.out" \

BIN_OUTPUTS += \
sci_testbench_alt.hex \

BIN_OUTPUTS__QUOTED += \
"sci_testbench_alt.hex" \


# All Target
all: sci_testbench_alt.out

# Tool invocations
sci_testbench_alt.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"/home/eric/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 -g --define=CPU1 --diag_warning=225 --display_error_number --diag_wrap=off -z -m"sci_testbench_alt.map" --stack_size=0x200 --warn_sections -i"/home/eric/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/lib" -i"/home/eric/Documents/delfino/sci_testbench_alt/F2837xD_common" -i"/home/eric/Documents/delfino/sci_testbench_alt/F2837xD_headers" -i"/home/eric/Documents/delfino/sci_testbench_alt/F2837xD_headers/include" -i"/home/eric/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="sci_testbench_alt_linkInfo.xml" --rom_model -o "sci_testbench_alt.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

sci_testbench_alt.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"/home/eric/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/hex2000"  -o "sci_testbench_alt.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "77D_sci.d" "sci_api.d" "sci_testbench.d" "F2837xD_common/source/F2837xD_CpuTimers.d" "F2837xD_common/source/F2837xD_DefaultISR.d" "F2837xD_common/source/F2837xD_Gpio.d" "F2837xD_common/source/F2837xD_Ipc.d" "F2837xD_common/source/F2837xD_PieCtrl.d" "F2837xD_common/source/F2837xD_PieVect.d" "F2837xD_common/source/F2837xD_SysCtrl.d" "F2837xD_headers/source/F2837xD_GlobalVariableDefs.d" 
	-$(RM) "77D_sci.obj" "sci_api.obj" "sci_testbench.obj" "F2837xD_common/source/F2837xD_CodeStartBranch.obj" "F2837xD_common/source/F2837xD_CpuTimers.obj" "F2837xD_common/source/F2837xD_DefaultISR.obj" "F2837xD_common/source/F2837xD_Gpio.obj" "F2837xD_common/source/F2837xD_Ipc.obj" "F2837xD_common/source/F2837xD_PieCtrl.obj" "F2837xD_common/source/F2837xD_PieVect.obj" "F2837xD_common/source/F2837xD_SysCtrl.obj" "F2837xD_common/source/F2837xD_usDelay.obj" "F2837xD_headers/source/F2837xD_GlobalVariableDefs.obj" 
	-$(RM) "F2837xD_common/source/F2837xD_CodeStartBranch.d" "F2837xD_common/source/F2837xD_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

