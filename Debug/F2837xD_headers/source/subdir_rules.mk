################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
F2837xD_headers/source/F2837xD_GlobalVariableDefs.obj: ../F2837xD_headers/source/F2837xD_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="F:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="F:/ti/workspace2/sci_testbench_alt/F2837xD_common/include" --include_path="F:/ti/workspace2/sci_testbench_alt/F2837xD_common/source" --include_path="F:/ti/workspace2/sci_testbench_alt/F2837xD_headers/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="F2837xD_headers/source/F2837xD_GlobalVariableDefs.pp" --obj_directory="F2837xD_headers/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


