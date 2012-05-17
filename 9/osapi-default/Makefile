# Quick and very dirty!

# Which target? set default
ifndef TARGET
TARGET=host
endif

# Debug build? debug is default
ifdef DEBUG
CXXFLAGS=-g
DEST_DIR=lib/${TARGET}/debug
else
CXXFLAGS=-O2
DEST_DIR=lib/${TARGET}/release
endif
OBJ_DEST_DIR=build/${DEST_DIR}


COMMON=$(addprefix common/,Time.cpp Timer.cpp LogSystem.cpp LogOutputStdOut.cpp LogTypes.cpp Log.cpp Completion.cpp)
LINUX=$(addprefix linux/,ClockTime.cpp Mutex.cpp Conditional.cpp Thread.cpp Semaphore.cpp Utility.cpp)
SRC=${COMMON} ${LINUX}
OBJS=$(addprefix ${OBJ_DEST_DIR}/,$(notdir ${SRC:%.cpp=%.o}))

ifeq (${TARGET},host)
# Include host specific stuff
include compiler_setup.host
endif

ifeq (${TARGET},target)
# Include target specific stuff
include compiler_setup.target
endif

# Setting compiler flags
CXXFLAGS+= -Wall -Iinc  -D${OS}



${OBJ_DEST_DIR}/%.o: common/%.cpp
	@echo "Compiling "$<
	@${CXX} -c $< -o $@ ${CXXFLAGS}

${OBJ_DEST_DIR}/%.o: linux/%.cpp
	@echo "Compiling "$<
	@${CXX} -c $< -o $@ ${CXXFLAGS}

${DEST_DIR}:
	mkdir -p ${DEST_DIR}

${OBJ_DEST_DIR}:
	mkdir -p ${OBJ_DEST_DIR}

${DEST_DIR}/libOSApi.a: ${OBJ_DEST_DIR} ${DEST_DIR} ${OBJS} 
	${AR} cq $@ ${OBJS}

all: ${DEST_DIR}/libOSApi.a

clean:
	rm -f ${DEST_DIR}/libOSApi.a ${OBJS}
