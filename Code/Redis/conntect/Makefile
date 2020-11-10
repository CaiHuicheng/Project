target: redisConntect

redisConntect: redis_password.h redis_password.cpp
ifdef WINDIR
	g++ -std=c++11 -pthread -DXG_MINGW -o redis redis_password.cpp -lws2_32 -lpsapi -lm
else
	g++ -std=c++11 -pthread -o redis redis_password.cpp -lutil -ldl -lm
endif
	
clean:
	@rm redis