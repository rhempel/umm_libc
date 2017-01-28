long random( void )
{

  static long seed = 1;
  
  // Compute x = (7^5 * x) mod (2^31 - 1)
  // wihout overflowing 31 bits:
  //      (2^31 - 1) = 127773 * (7^5) + 2836
  // From "Random number generators: good ones are hard to find",
  // Park and Miller, Communications of the ACM, vol. 31, no. 10,
  // October 1988, p. 1195.

  // long hi, lo, x;
  // hi = seed / 127773L;
  // lo = seed % 127773L;
  
  seed = 16807L * (seed % 127773L) - 2836L * (seed / 127773L);
  	 
  if (seed <= 0)
     seed += 0x7fffffffL;
     
  return( seed );
}

