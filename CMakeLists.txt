cmake_minimum_required(VERSION 3.28)

# set(CXX_SCAN_FOR_MODULES ON)

project(rccar LANGUAGES CXX)

#set(MCU atmega16)
set(MCU attiny2313a)
set(F_CPU 8000000)
set(BAUD 9600)
set(PROG_TYPE stk500v2)
set(PORT /dev/ttyACM0)

if(${MCU} EQUAL atmega16)
    # fuses for atmega16
    set(FUSES "-U lfuse:w:0xe2:m -U hfuse:w:0x99:m")
elseif(${MCU} EQUAL attiny2313a)
    set(FUSES "-U lfuse:w:0xE4:m -U hfuse:w:0xDF:m")
endif()

add_definitions(-DF_CPU=${F_CPU})

set(AVRCPP   avr-g++)
set(AVRC     avr-gcc)
set(AVRSTRIP avr-strip)
set(OBJCOPY  avr-objcopy)
set(OBJDUMP  avr-objdump)
set(AVRSIZE  avr-size)
set(AVRDUDE  avrdude)


set(CMAKE_SYSTEM_NAME  Generic)
set(CMAKE_CXX_COMPILER ${AVRCPP})
set(CMAKE_C_COMPILER   ${AVRC})
set(CMAKE_ASM_COMPILER   ${AVRC})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CDEBUG    "-gstabs -g -ggdb")
set(CWARN     "-Wall -Wstrict-prototypes -Wl,--gc-sections -Wl,--relax")
set(CTUNING   "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections")
set(COPT      "-Os -lm -lprintf_flt")
set(CMCU      "-mmcu=${MCU}")
#set(CDEFS     "-DF_CPU=${F_CPU} -DBAUD=${BAUD}")

set(CFLAGS   "${CMCU} ${CDEBUG} ${CDEFS} ${COPT} ${CWARN} ${CSTANDARD} ${CTUNING}")
set(CXXFLAGS "${CMCU} ${CDEBUG} ${CDEFS} ${COPT} ${CTUNING}")

set(CMAKE_C_FLAGS   "${CFLAGS}")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")
set(CMAKE_ASM_FLAGS   "${CFLAGS}")

# set(HEADERS include/test.hh
#             include/i2c.hh
#             include/use_cases.hh
#             include/pwm_output_repository.hh
#             include/timer1.hh

#             include/data/pwm_engine_repository.hh
#             include/data/sg90_servo_repository.hh
#             include/data/uart_repository.hh
#             include/data/uart_service.hh

#             include/domain/engine_repository.hh
#             include/domain/servo_repository.hh
#             include/domain/communication_repository.hh
#             include/domain/message.hh
# )

# set(SOURCE src/i2c.cc
# )

# add_executable(${PROJECT_NAME} main.cc ${HEADERS} ${SOURCE})

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
  PRIVATE
    FILE_SET HEADERS
      BASE_DIRS
        include
      FILES

        include/data/timer1.hh
        include/data/pwm_engine_repository.hh
        include/data/sg90_servo_repository.hh
        include/data/uart_repository.hh
        include/data/uart_service.hh

        include/domain/engine_repository.hh
        include/domain/servo_repository.hh
        include/domain/communication_repository.hh
        include/domain/message.hh
        include/domain/use_cases.hh

  PRIVATE
    main.cc
)

# target_include_directories(${PROJECT_NAME} PRIVATE include)
# target_include_directories(${PROJECT_NAME} PRIVATE "/home/dtr/repos/avr-libstdcpp/include/")

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")

add_custom_target(strip ALL     ${AVRSTRIP} "${PROJECT_NAME}.elf" DEPENDS ${PROJECT_NAME})
add_custom_target(hex   ALL     ${OBJCOPY} -R .eeprom -O ihex "${PROJECT_NAME}.elf" "${PROJECT_NAME}.hex" DEPENDS strip)
add_custom_target(eeprom        ${OBJCOPY} -j .eeprom --change-section-lma .eeprom=0 -O ihex "${PROJECT_NAME}.elf" "${PROJECT_NAME}.eeprom" DEPENDS strip)

add_custom_target(flash ${AVRDUDE} -B 125kHz -c ${PROG_TYPE} -p ${MCU} -P ${PORT} $FUSES -U flash:w:${PROJECT_NAME}.hex DEPENDS hex)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_NAME}.hex;${PROJECT_NAME}.eeprom;${PROJECT_NAME}.lst")
