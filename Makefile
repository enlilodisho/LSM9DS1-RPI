CXX=g++
CPPFLAGS=-std=c++11
LIBS=

DEPS=

LSM9DS1.o: LSM9DS1.cpp I2CBase.hpp RasPi_I2C.hpp GPIOBase.hpp RasPi_GPIO.hpp LSM9DS1_Registers.h
	$(CXX) -c LSM9DS1.cpp $(DEPS) -o LSM9DS1.o $(CPPFLAGS) $(LIBS)

clean:
	rm *.o
