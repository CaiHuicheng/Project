//BKDHash 千万个string在内存怎么高速查找
unsigned int BKDRHash(char *str) { 
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc.. 
	unsigned inthash = 0;   
	while (*str) { 
		hash = hash * seed + (*str++); 
		}   
	return (hash & 0x7FFFFFFF); 
}