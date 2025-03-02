producer:
	gcc producer.c -o producer

consumer:
	gcc consumer.c -o consumer

build: producer consumer

clean:
	rm producer consumer

run:
	./producer

all: clean build run
