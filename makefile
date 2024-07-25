build:
	rm -rf dist/*
	gcc -o dist/keygen src/keygen.c 
	gcc -o dist/encrypt src/encrypt.c  -lm -lgmp
	gcc -o dist/decrypt src/decrypt.c  -lm -lgmp

	