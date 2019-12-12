CXX=g++
CFLAGS=-Wall -O2 -fPIC -std=c++14
LIBS=-lwiringPi -pthread -lrt -lcrypt
#LIBS=-Wl,-rpath=/usr/local/lib/libwiringPi.so -pthread -lrt -lcrypt
AR=ar
ARFLAGS=-rcs

LIB_NAME=libTM1637Controller
LIB_CFLAGS=-DPLATFORM_RASPBERRY_PI
DIR_TM1637_CORE=../src
DIR_TM1637_INCLUDE=${DIR_TM1637_CORE}
DIR_TM1637_SOURCE=${DIR_TM1637_CORE}
SWIG_INTERFACE=TM1637Controller.i
SWIG_OUTPUT=TM1637Controller_wrap
CORE_OBJECTS:=TM1637Controller.o TM1637_7SegmentLEDController_SegmentAddressing.o ${SWIG_OUTPUT}.o

DIR_BINDING_CSHARP=./csharp/Smdn.Devices.TM1637Controller

TM1637Controller.o:
	${CXX} ${CFLAGS} ${LIB_CFLAGS} -I${DIR_TM1637_INCLUDE} -c ${DIR_TM1637_SOURCE}/TM1637Controller.cpp -o TM1637Controller.o

TM1637_7SegmentLEDController_SegmentAddressing.o:
	${CXX} ${CFLAGS} ${LIB_CFLAGS} -I${DIR_TM1637_INCLUDE} -c ${DIR_TM1637_SOURCE}/TM1637_7SegmentLEDController_SegmentAddressing.cpp -o TM1637_7SegmentLEDController_SegmentAddressing.o

${SWIG_OUTPUT}.o:
	${CXX} ${CFLAGS} ${LIB_CFLAGS} -I${DIR_TM1637_INCLUDE} -c ${SWIG_OUTPUT}.cpp -o ${SWIG_OUTPUT}.o

${LIB_NAME}.so: ${CORE_OBJECTS}
	${CXX} -shared -I${DIR_TM1637_INCLUDE} ${LIBS} -o ${LIB_NAME}.so ${CORE_OBJECTS}

all: binding-csharp

clean: clean-binding-csharp
	rm -f ${CORE_OBJECTS}
	rm -f ${DIR_TM1637_INCLUDE}/*.h.gch
	rm -f ${SWIG_OUTPUT}.cpp
	rm -f ${SWIG_OUTPUT}.o
	rm -f ${LIB_NAME}.a
	rm -f ${LIB_NAME}.so
	rm -f *.o

binding-csharp-lib:
	swig -csharp -c++ -o ${SWIG_OUTPUT}.cpp -outdir ${DIR_BINDING_CSHARP}/src/Smdn.Devices.TM1637Controller.Bindings/ -dllimport ${LIB_NAME} -namespace 'Smdn.Devices.TM1637Controller.Bindings' ${SWIG_INTERFACE}
	$(MAKE) ${LIB_NAME}.so
	cp -f ${LIB_NAME}.so ${DIR_BINDING_CSHARP}/src/Smdn.Devices.TM1637Controller.Bindings/

binding-csharp: __find-dotnet binding-csharp-lib
	${DOTNET_BUILD} ${DIR_BINDING_CSHARP}/src/Smdn.Devices.TM1637Controller.csproj

clean-binding-csharp: __find-dotnet
	rm -f -r ${DIR_BINDING_CSHARP}/src/Smdn.Devices.TM1637Controller.Bindings/*.cs
	rm -f -r ${DIR_BINDING_CSHARP}/src/Smdn.Devices.TM1637Controller.Bindings/*.so
	rm -f ${LIB_NAME}.so
	-$(DOTNET_CLEAN) ${DIR_BINDING_CSHARP}/src/Smdn.Devices.TM1637Controller.csproj

__find-dotnet: FORCE
ifeq (, $(shell which dotnet))
ifeq (, $(shell which msbuild))
	$(error requires dotnet or msbuild)
else
DOTNET_BUILD=msbuild /t:Build
DOTNET_CLEAN=msbuild /t:Clean
endif
else
DOTNET_BUILD=dotnet build
DOTNET_CLEAN=dotnet clean
endif

FORCE:
.PHONY: clean clean-binding-csharp __find-dotnet
