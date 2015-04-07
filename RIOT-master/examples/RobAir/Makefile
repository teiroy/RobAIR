# name of your application
APPLICATION = motor_contorl

# If no BOARD is found in the environment, use this default:
BOARD ?= nucleo-l1

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

INCLUDES+=-I/home/jeremy/Documents/RICM4/S2/Projet/RIOT-master/core/include -I/home/jeremy/Documents/RICM4/S2/Projet/RIOT-master/drivers/include -I/home/jeremy/Documents/RICM4/S2/Projet/RIOT-master/drivers/include/periph/

include $(RIOTBASE)/Makefile.include
