run: Filesystem.jar
	java -jar $< Main

Filesystem.jar: src/*.java classes/*.class
	javac -g src/*.java
	mv src/*.class classes
	jar -cfe $@ main -C classes .
	
compil: src/*.java
	javac -g src/*.java
	mv src/*.class classes
	java -cp classes main
	

