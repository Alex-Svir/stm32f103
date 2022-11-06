/*
 * startup.cpp
 *
 *  Created on: 20 окт. 2022 г.
 *      Author: shurik
 */
//	.init
//	.ctors
//	.preinit_array
//	.init_array			+
//	.fini
//	.fini_array
//	.dtors

void main();

__attribute__(( section("._start") ))
void __reset()  {
	extern void (*__startup_init_array_start[])();
	extern void (*__startup_init_array_end[])();
	int sz = __startup_init_array_end - __startup_init_array_start;
	while (sz--) {
		__startup_init_array_start[sz]();
	}

	main();

	while(1);
}
