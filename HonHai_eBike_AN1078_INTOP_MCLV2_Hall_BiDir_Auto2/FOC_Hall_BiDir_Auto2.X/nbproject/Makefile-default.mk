#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FOC_Hall_BiDir_Auto2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FOC_Hall_BiDir_Auto2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../CalcRef.s ../clrkpark.s ../InvPark.s ../pi.s ../ReadADC0.s ../SVGEN.S ../trig.s ../MeasCurr.s ../PMSM.c ../initdspic.c ../smc.s ../atan2CORDIC.s ../FdWeak.c ../RTDM.c ../SpeedCalc.s

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/CalcRef.o ${OBJECTDIR}/_ext/1472/clrkpark.o ${OBJECTDIR}/_ext/1472/InvPark.o ${OBJECTDIR}/_ext/1472/pi.o ${OBJECTDIR}/_ext/1472/ReadADC0.o ${OBJECTDIR}/_ext/1472/SVGEN.o ${OBJECTDIR}/_ext/1472/trig.o ${OBJECTDIR}/_ext/1472/MeasCurr.o ${OBJECTDIR}/_ext/1472/PMSM.o ${OBJECTDIR}/_ext/1472/initdspic.o ${OBJECTDIR}/_ext/1472/smc.o ${OBJECTDIR}/_ext/1472/atan2CORDIC.o ${OBJECTDIR}/_ext/1472/FdWeak.o ${OBJECTDIR}/_ext/1472/RTDM.o ${OBJECTDIR}/_ext/1472/SpeedCalc.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/CalcRef.o.d ${OBJECTDIR}/_ext/1472/clrkpark.o.d ${OBJECTDIR}/_ext/1472/InvPark.o.d ${OBJECTDIR}/_ext/1472/pi.o.d ${OBJECTDIR}/_ext/1472/ReadADC0.o.d ${OBJECTDIR}/_ext/1472/SVGEN.o.d ${OBJECTDIR}/_ext/1472/trig.o.d ${OBJECTDIR}/_ext/1472/MeasCurr.o.d ${OBJECTDIR}/_ext/1472/PMSM.o.d ${OBJECTDIR}/_ext/1472/initdspic.o.d ${OBJECTDIR}/_ext/1472/smc.o.d ${OBJECTDIR}/_ext/1472/atan2CORDIC.o.d ${OBJECTDIR}/_ext/1472/FdWeak.o.d ${OBJECTDIR}/_ext/1472/RTDM.o.d ${OBJECTDIR}/_ext/1472/SpeedCalc.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/CalcRef.o ${OBJECTDIR}/_ext/1472/clrkpark.o ${OBJECTDIR}/_ext/1472/InvPark.o ${OBJECTDIR}/_ext/1472/pi.o ${OBJECTDIR}/_ext/1472/ReadADC0.o ${OBJECTDIR}/_ext/1472/SVGEN.o ${OBJECTDIR}/_ext/1472/trig.o ${OBJECTDIR}/_ext/1472/MeasCurr.o ${OBJECTDIR}/_ext/1472/PMSM.o ${OBJECTDIR}/_ext/1472/initdspic.o ${OBJECTDIR}/_ext/1472/smc.o ${OBJECTDIR}/_ext/1472/atan2CORDIC.o ${OBJECTDIR}/_ext/1472/FdWeak.o ${OBJECTDIR}/_ext/1472/RTDM.o ${OBJECTDIR}/_ext/1472/SpeedCalc.o

# Source Files
SOURCEFILES=../CalcRef.s ../clrkpark.s ../InvPark.s ../pi.s ../ReadADC0.s ../SVGEN.S ../trig.s ../MeasCurr.s ../PMSM.c ../initdspic.c ../smc.s ../atan2CORDIC.s ../FdWeak.c ../RTDM.c ../SpeedCalc.s


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/FOC_Hall_BiDir_Auto2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP256MC506
MP_LINKER_FILE_OPTION=,--script=p33EP256MC506.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/PMSM.o: ../PMSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/PMSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/PMSM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../PMSM.c  -o ${OBJECTDIR}/_ext/1472/PMSM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/PMSM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -no-legacy-libc  -O0 -I".." -msmart-io=1 -msfr-warn=off   -finline
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/PMSM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/initdspic.o: ../initdspic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/initdspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/initdspic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../initdspic.c  -o ${OBJECTDIR}/_ext/1472/initdspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/initdspic.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -no-legacy-libc  -O0 -I".." -msmart-io=1 -msfr-warn=off   -finline
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/initdspic.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/FdWeak.o: ../FdWeak.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/FdWeak.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/FdWeak.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../FdWeak.c  -o ${OBJECTDIR}/_ext/1472/FdWeak.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/FdWeak.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -no-legacy-libc  -O0 -I".." -msmart-io=1 -msfr-warn=off   -finline
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/FdWeak.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/RTDM.o: ../RTDM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RTDM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RTDM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../RTDM.c  -o ${OBJECTDIR}/_ext/1472/RTDM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/RTDM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -no-legacy-libc  -O0 -I".." -msmart-io=1 -msfr-warn=off   -finline
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/RTDM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1472/PMSM.o: ../PMSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/PMSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/PMSM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../PMSM.c  -o ${OBJECTDIR}/_ext/1472/PMSM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/PMSM.o.d"      -mno-eds-warn  -g -omf=elf -no-legacy-libc  -O0 -I".." -msmart-io=1 -msfr-warn=off   -finline
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/PMSM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/initdspic.o: ../initdspic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/initdspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/initdspic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../initdspic.c  -o ${OBJECTDIR}/_ext/1472/initdspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/initdspic.o.d"      -mno-eds-warn  -g -omf=elf -no-legacy-libc  -O0 -I".." -msmart-io=1 -msfr-warn=off   -finline
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/initdspic.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/FdWeak.o: ../FdWeak.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/FdWeak.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/FdWeak.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../FdWeak.c  -o ${OBJECTDIR}/_ext/1472/FdWeak.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/FdWeak.o.d"      -mno-eds-warn  -g -omf=elf -no-legacy-libc  -O0 -I".." -msmart-io=1 -msfr-warn=off   -finline
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/FdWeak.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/RTDM.o: ../RTDM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RTDM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RTDM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../RTDM.c  -o ${OBJECTDIR}/_ext/1472/RTDM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/RTDM.o.d"      -mno-eds-warn  -g -omf=elf -no-legacy-libc  -O0 -I".." -msmart-io=1 -msfr-warn=off   -finline
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/RTDM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/CalcRef.o: ../CalcRef.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CalcRef.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CalcRef.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../CalcRef.s  -o ${OBJECTDIR}/_ext/1472/CalcRef.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/CalcRef.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/CalcRef.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/clrkpark.o: ../clrkpark.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/clrkpark.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/clrkpark.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../clrkpark.s  -o ${OBJECTDIR}/_ext/1472/clrkpark.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/clrkpark.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/clrkpark.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/InvPark.o: ../InvPark.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/InvPark.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/InvPark.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../InvPark.s  -o ${OBJECTDIR}/_ext/1472/InvPark.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/InvPark.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/InvPark.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/pi.o: ../pi.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/pi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/pi.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../pi.s  -o ${OBJECTDIR}/_ext/1472/pi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/pi.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/pi.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/ReadADC0.o: ../ReadADC0.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ReadADC0.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ReadADC0.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../ReadADC0.s  -o ${OBJECTDIR}/_ext/1472/ReadADC0.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/ReadADC0.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/ReadADC0.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/trig.o: ../trig.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/trig.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/trig.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../trig.s  -o ${OBJECTDIR}/_ext/1472/trig.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/trig.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/trig.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/MeasCurr.o: ../MeasCurr.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MeasCurr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MeasCurr.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../MeasCurr.s  -o ${OBJECTDIR}/_ext/1472/MeasCurr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/MeasCurr.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MeasCurr.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/smc.o: ../smc.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/smc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/smc.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../smc.s  -o ${OBJECTDIR}/_ext/1472/smc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/smc.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/smc.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/atan2CORDIC.o: ../atan2CORDIC.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/atan2CORDIC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/atan2CORDIC.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../atan2CORDIC.s  -o ${OBJECTDIR}/_ext/1472/atan2CORDIC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/atan2CORDIC.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/atan2CORDIC.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/SpeedCalc.o: ../SpeedCalc.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/SpeedCalc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SpeedCalc.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SpeedCalc.s  -o ${OBJECTDIR}/_ext/1472/SpeedCalc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/SpeedCalc.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/SpeedCalc.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1472/CalcRef.o: ../CalcRef.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CalcRef.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CalcRef.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../CalcRef.s  -o ${OBJECTDIR}/_ext/1472/CalcRef.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/CalcRef.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/CalcRef.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/clrkpark.o: ../clrkpark.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/clrkpark.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/clrkpark.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../clrkpark.s  -o ${OBJECTDIR}/_ext/1472/clrkpark.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/clrkpark.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/clrkpark.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/InvPark.o: ../InvPark.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/InvPark.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/InvPark.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../InvPark.s  -o ${OBJECTDIR}/_ext/1472/InvPark.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/InvPark.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/InvPark.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/pi.o: ../pi.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/pi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/pi.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../pi.s  -o ${OBJECTDIR}/_ext/1472/pi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/pi.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/pi.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/ReadADC0.o: ../ReadADC0.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ReadADC0.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ReadADC0.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../ReadADC0.s  -o ${OBJECTDIR}/_ext/1472/ReadADC0.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/ReadADC0.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/ReadADC0.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/trig.o: ../trig.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/trig.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/trig.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../trig.s  -o ${OBJECTDIR}/_ext/1472/trig.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/trig.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/trig.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/MeasCurr.o: ../MeasCurr.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MeasCurr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MeasCurr.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../MeasCurr.s  -o ${OBJECTDIR}/_ext/1472/MeasCurr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/MeasCurr.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MeasCurr.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/smc.o: ../smc.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/smc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/smc.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../smc.s  -o ${OBJECTDIR}/_ext/1472/smc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/smc.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/smc.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/atan2CORDIC.o: ../atan2CORDIC.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/atan2CORDIC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/atan2CORDIC.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../atan2CORDIC.s  -o ${OBJECTDIR}/_ext/1472/atan2CORDIC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/atan2CORDIC.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/atan2CORDIC.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/SpeedCalc.o: ../SpeedCalc.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/SpeedCalc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SpeedCalc.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SpeedCalc.s  -o ${OBJECTDIR}/_ext/1472/SpeedCalc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/SpeedCalc.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/SpeedCalc.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/SVGEN.o: ../SVGEN.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/SVGEN.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SVGEN.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SVGEN.S  -o ${OBJECTDIR}/_ext/1472/SVGEN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/SVGEN.o.d"  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -no-legacy-libc  -I".." -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/SVGEN.o.asm.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/SVGEN.o.d" "${OBJECTDIR}/_ext/1472/SVGEN.o.asm.d"  -t $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1472/SVGEN.o: ../SVGEN.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/SVGEN.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SVGEN.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SVGEN.S  -o ${OBJECTDIR}/_ext/1472/SVGEN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/SVGEN.o.d"  -omf=elf -no-legacy-libc  -I".." -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/SVGEN.o.asm.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/SVGEN.o.d" "${OBJECTDIR}/_ext/1472/SVGEN.o.asm.d"  -t $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/FOC_Hall_BiDir_Auto2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../HallAutoScan.X.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/FOC_Hall_BiDir_Auto2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    ../HallAutoScan.X.a  -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -no-legacy-libc   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library=q,--library-path="..",--no-force-link,--smart-io,--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/FOC_Hall_BiDir_Auto2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../HallAutoScan.X.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/FOC_Hall_BiDir_Auto2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    ../HallAutoScan.X.a  -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -no-legacy-libc  -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library=q,--library-path="..",--no-force-link,--smart-io,--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/FOC_Hall_BiDir_Auto2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
