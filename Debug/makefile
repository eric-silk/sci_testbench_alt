################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := F:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./sci_testbench.obj" \
"./F2837xD_headers/source/F2837xD_GlobalVariableDefs.obj" \
"./F2837xD_common/source/F2837xD_CodeStartBranch.obj" \
"./F2837xD_common/source/F2837xD_CpuTimers.obj" \
"./F2837xD_common/source/F2837xD_DefaultISR.obj" \
"./F2837xD_common/source/F2837xD_Gpio.obj" \
"./F2837xD_common/source/F2837xD_Ipc.obj" \
"./F2837xD_common/source/F2837xD_PieCtrl.obj" \
"./F2837xD_common/source/F2837xD_PieVect.obj" \
"./F2837xD_common/source/F2837xD_Sci.obj" \
"./F2837xD_common/source/F2837xD_SysCtrl.obj" \
"./F2837xD_common/source/F2837xD_sci_io.obj" \
"./F2837xD_common/source/F2837xD_usDelay.obj" \
"../2837x_FLASH_lnk_cpu1.cmd" \
"../F2837xD_headers/cmd/F2837xD_Headers_nonBIOS_cpu1.cmd" \
$(GEN_CMDS__FLAG) \
-l"rts2800_fpu32.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include F2837xD_headers/source/subdir_vars.mk
-include F2837xD_headers/cmd/subdir_vars.mk
-include F2837xD_common/source/subdir_vars.mk
-include subdir_rules.mk
-include F2837xD_headers/source/subdir_rules.mk
-include F2837xD_headers/cmd/subdir_rules.mk
-include F2837xD_common/source/subdir_rules.mk
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
	"F:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -mt -ml --vcu_support=vcu2 --cla_support=cla1 --tmu_support=tmu0 --float_support=fpu32 -g --define=CPU1 --diag_warning=225 --diag_wrap=off --display_error_number -z -m"sci_testbench_alt.map" --stack_size=0x200 --warn_sections -i"F:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/lib" -i"F:/ti/workspace2/sci_testbench_alt/F2837xD_common" -i"F:/ti/workspace2/sci_testbench_alt/F2837xD_headers" -i"F:/ti/workspace2/sci_testbench_alt/F2837xD_headers/include" -i"F:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="sci_testbench_alt_linkInfo.xml" --rom_model -o "sci_testbench_alt.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

sci_testbench_alt.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"F:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/hex2000"  -o "sci_testbench_alt.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "sci_testbench.pp" "F2837xD_headers\source\F2837xD_GlobalVariableDefs.pp" "F2837xD_common\source\F2837xD_CpuTimers.pp" "F2837xD_common\source\F2837xD_DefaultISR.pp" "F2837xD_common\source\F2837xD_Gpio.pp" "F2837xD_common\source\F2837xD_Ipc.pp" "F2837xD_common\source\F2837xD_PieCtrl.pp" "F2837xD_common\source\F2837xD_PieVect.pp" "F2837xD_common\source\F2837xD_Sci.pp" "F2837xD_common\source\F2837xD_SysCtrl.pp" "F2837xD_common\source\F2837xD_sci_io.pp" 
	-$(RM) "sci_testbench.obj" "F2837xD_headers\source\F2837xD_GlobalVariableDefs.obj" "F2837xD_common\source\F2837xD_CodeStartBranch.obj" "F2837xD_common\source\F2837xD_CpuTimers.obj" "F2837xD_common\source\F2837xD_DefaultISR.obj" "F2837xD_common\source\F2837xD_Gpio.obj" "F2837xD_common\source\F2837xD_Ipc.obj" "F2837xD_common\source\F2837xD_PieCtrl.obj" "F2837xD_common\source\F2837xD_PieVect.obj" "F2837xD_common\source\F2837xD_Sci.obj" "F2837xD_common\source\F2837xD_SysCtrl.obj" "F2837xD_common\source\F2837xD_sci_io.obj" "F2837xD_common\source\F2837xD_usDelay.obj" 
	-$(RM) "F2837xD_common\source\F2837xD_CodeStartBranch.pp" "F2837xD_common\source\F2837xD_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

