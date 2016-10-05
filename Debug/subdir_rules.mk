################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
77D_sci.obj: ../77D_sci.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"E:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="E:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="E:/Users/Eric/Documents/Senior Design/sci_testbench_alt/F2837xD_common/include" --include_path="E:/Users/Eric/Documents/Senior Design/sci_testbench_alt/F2837xD_common/source" --include_path="E:/Users/Eric/Documents/Senior Design/sci_testbench_alt/F2837xD_headers/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="77D_sci.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sci_api.obj: ../sci_api.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"E:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="E:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="E:/Users/Eric/Documents/Senior Design/sci_testbench_alt/F2837xD_common/include" --include_path="E:/Users/Eric/Documents/Senior Design/sci_testbench_alt/F2837xD_common/source" --include_path="E:/Users/Eric/Documents/Senior Design/sci_testbench_alt/F2837xD_headers/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="sci_api.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sci_testbench.obj: ../sci_testbench.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"E:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="E:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="E:/Users/Eric/Documents/Senior Design/sci_testbench_alt/F2837xD_common/include" --include_path="E:/Users/Eric/Documents/Senior Design/sci_testbench_alt/F2837xD_common/source" --include_path="E:/Users/Eric/Documents/Senior Design/sci_testbench_alt/F2837xD_headers/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="sci_testbench.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


