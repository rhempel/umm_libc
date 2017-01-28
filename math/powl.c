/*  powlong.c:  Computes x**y where x and y are 32-bit longs.
             
    Copyright (C) 2006  Ralph Hempel

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA */

/* Version 1.0 - Initial release */

long powlong(long x, long y)
{
    long res = x;
	
    if(y == 0.0) return 1.0;
    if(y == 1.0) return res;
    if(x <= 0.0) return 0.0;
    while( --y )	
      res *= x;
      
    return( res );
}
