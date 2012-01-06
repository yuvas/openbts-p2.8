/*
* Copyright 2008 Free Software Foundation, Inc.
*
*
* This software is distributed under the terms of the GNU Affero Public License.
* See the COPYING file in the main directory for details.
*
* This use of this software may be subject to additional restrictions.
* See the LEGAL file in the main directory for details.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Affero General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Affero General Public License for more details.

	You should have received a copy of the GNU Affero General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "BitVector.h"
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <sys/time.h>

static int in_len = 224;

void fill_random(BitVector &b, int n)
{
	int i;
	for (i=0; i<n; i++)
		b[i] = random() & 1;
}

int main(int argc, char *argv[])
{
	int i, n;
	BitVector v1(in_len);
	BitVector v2(in_len * 2);
	BitVector v3(v1.size());

	ViterbiR2O4 vCoder;
	struct timespec ts0, ts1;

	clock_gettime(CLOCK_MONOTONIC, &ts0);

	printf("[.] Random vector checks: len %i\n", in_len);

	n = 100000;
	for (i=0; i<n; i++) {
		if (!(i % 10000))
			printf("[..] Encoding / Decoding cycle : %i of %i\n", i, n);

		fill_random(v1, in_len);
		v1.encode(vCoder,v2);

		SoftVector sv2(v2);
		sv2.decode(vCoder, v3);
	}

	clock_gettime(CLOCK_MONOTONIC, &ts1);

	struct timeval tv0, tv1;
	tv0.tv_sec = ts0.tv_sec;
	tv0.tv_usec = ts0.tv_nsec / 1000;
	tv1.tv_sec = ts1.tv_sec;
	tv1.tv_usec = ts1.tv_nsec / 1000;

	timersub(&tv1, &tv0, &tv0);
	printf("Finished in %li.%06li secs\n", tv0.tv_sec, tv0.tv_usec);
}
