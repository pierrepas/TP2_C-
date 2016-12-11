LD=g++
CXX=g++ -g -c
EXEC_SRC=\
	testGrayLevelImage2D.cpp testColorImage2D.cpp invert-red-blue.cpp save-green-channel.cpp save-channels.cpp testCathodique.cpp histogramme.cpp
MODULE_SRC=\
MODULE_OBJ=${MODULE_SRC:.cpp=.o}
EXEC_OBJ=${EXEC_SRC:.cpp=.o}
EXEC_PRG=${EXEC_SRC:.cpp=}
all: ${EXEC_PRG} ${MODULE_OBJ} ${EXEC_OBJ}


invert-red-blue: invert-red-blue.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

testGrayLevelImage2D: testGrayLevelImage2D.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

testColorImage2D: testColorImage2D.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

save-green-channel: save-green-channel.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

save-channels: save-channels.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

testCathodique: testCathodique.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

histogramme: histogramme.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

.cpp.o: %.cpp %.hpp
	${CXX} $<

clean:
	rm -f ${EXEC_PRG} ${MODULE_OBJ} ${EXEC_OBJ}

