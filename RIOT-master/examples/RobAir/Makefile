# name of your application
APPLICATION = motor_control

# If no BOARD is found in the environment, use this default:
BOARD ?= nucleo-l1

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP
#USEMODULE+=vtimer

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

#INCLUDES+=-I/home/vivien/Documents/RICM4/Genie_Logiciel/RIOT/core/include -I/home/vivien/Documents/RICM4/Genie_Logiciel/RIOT
#INCLUDES+= -I../../drivers/include/periph/

include $(RIOTBASE)/Makefile.include
