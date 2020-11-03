EXE=rabbitmq_consumer
SUBDIR=src
 
#CXXFLAGS:编译选项, LDFLAGS:链接选项
CXXFLAGS += 
LDFLAGS += -L/usr/local/lib -lrabbitmq
 
CXX_SOURCES =$(foreach dir,$(SUBDIR), $(wildcard $(dir)/*.cpp))
CXX_OBJECTS=$(patsubst  %.cpp, %.o, $(CXX_SOURCES))
DEP_FILES  =$(patsubst  %.o,  %.d, $(CXX_OBJECTS))
 
$(EXE): $(CXX_OBJECTS)
	g++  $(CXX_OBJECTS) -o $(EXE) $(LDFLAGS)
	
%.o: %.cpp
	g++  -c  $(CXXFLAGS) -MMD $<  -o  $@
 
-include $(DEP_FILES)
 
clean: 
	rm  -rf  $(CXX_OBJECTS)  $(DEP_FILES)  $(EXE)
 
test:
	echo $(CXX_OBJECTS)
 
initlib:
	ln -s lib/librabbitmq.so.4.2.0 /usr/local/lib/librabbitmq.so
	ln -s lib/librabbitmq.so.4.2.0 /usr/lib64/librabbitmq.so.4