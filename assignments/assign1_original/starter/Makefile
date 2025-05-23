# This will run by default with command 'make'
larson.bin: larson.s
	arm-none-eabi-as larson.s -o larson.o
	arm-none-eabi-objcopy larson.o -O binary larson.bin

# upload to the Pi
install: larson.bin
	rpi-install.py larson.bin

# Remove binary files with 'make clean'
clean:
	rm -rf *.o *.bin
