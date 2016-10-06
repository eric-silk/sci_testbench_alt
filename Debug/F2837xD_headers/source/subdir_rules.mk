################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
F2837xD_headers/source/F2837xD_GlobalVariableDefs.obj: ../F2837xD_headers/source/F2837xD_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/home/eric/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="/home/eric/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/eric/Documents/delfino/sci_testbench_alt/F2837xD_common/include" --include_path="/home/eric/Documents/delfino/sci_testbench_alt/F2837xD_common/source" --include_path="/home/eric/Documents/delfino/sci_testbench_alt/F2837xD_headers/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="F2837xD_headers/source/F2837xD_GlobalVariableDefs.d" --obj_directory="F2837xD_headers/source" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


