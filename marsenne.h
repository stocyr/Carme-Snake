#ifndef MARSENNE_H_
#define MARSENNE_H_


void init_genrand(unsigned long s);
void init_by_array(unsigned long init_key[], int key_length);
unsigned long genrand_int32(void);
double genrand_real2(void);


#endif /* MARSENNE_H_ */
