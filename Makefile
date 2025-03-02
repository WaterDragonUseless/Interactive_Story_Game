CFCLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
all:cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
cyoa-step1: page.o story.o cyoa-step1.o
	g++ $(CFCLAGS) -o cyoa-step1 page.o story.o cyoa-step1.o

cyoa-step2: page.o story.o cyoa-step2.o
	g++ $(CFCLAGS) -o cyoa-step2 page.o story.o cyoa-step2.o

cyoa-step3: page.o story.o cyoa-step3.o
	g++ $(CFCLAGS) -o cyoa-step3 page.o story.o cyoa-step3.o

cyoa-step4: page_s4.o story_s4.o cyoa-step4.o
	g++ $(CFCLAGS) -o cyoa-step4 page_s4.o story_s4.o cyoa-step4.o

%.o: %.cpp page.h story.h page_s4.h story_s4.h
	g++ $(CFCLAGS) -c $<
