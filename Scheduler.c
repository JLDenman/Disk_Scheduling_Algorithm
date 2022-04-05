#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define m 15

int main(int argc, char* argv[])
{
	int trackSequence[m];

	// Write an input generator, which produces a file containing m random integers in the range [0 : 99], each representing a request to seek to the corresponding track. Generate a long input sequence of requests.
	for (int i = 0; i < m; i++) 
	{
		trackSequence[i] = rand() % 100;
		//printf("%d,", trackSequence[i]);
	}

	// Submit the input sequence to the different programs, record the numbers of tracks traversed, and compare the results.
	int FIFONumber = FIFOTracksTraversed(trackSequence);
	int CSCANNumber = CScanTracksTraversed(trackSequence);

	return 0;
}

// Implement 2 or more of the 4 scheduling algorithms. Each program reads the generated sequence of requests and returns the total number of tracks traversed by the r/w arm.
// Submit the input sequence to the different programs, record the numbers of tracks traversed, and compare the results.

// FIFO Algorithm
int FIFOTracksTraversed(int sequence[])
{
	int seekTimeCount = 0;

	printf("FIFO Order: \n");
	for (int i = 0; i < m; i++)
	{
		printf("-%d-", sequence[i]);
	}

	for  (int t = 1; t < m; t++)
	{
		int currentTrack = sequence[t];
		int previousTrack = sequence[t - 1];

		if (currentTrack > previousTrack)
		{
			seekTimeCount = seekTimeCount + (currentTrack - previousTrack);
		}
		else
		{
			seekTimeCount = seekTimeCount + (previousTrack - currentTrack);
		}
	}

	printf("\nSeek Time: %d\n", seekTimeCount);
}

// C-Scan Algorithm
int CScanTracksTraversed(int sequence[])
{
	int seekTimeCount = 0;
	int NullCounter = 0;
	int CScanElementCount = 0;
	int copy_sequence[m];
	int CScanSortedSequence[m];

	// Setting this variable to 0 means no new scan has started.
	int newiteration = 0;

	// Make copy of original sequence to replace with placeholders.
	for (int i = 0; i < m; i++) {
		copy_sequence[i] = sequence[i];
	}

	// Initialize very first as starting element for C-Scan Algorithm.
	int previousTrackToCompare = copy_sequence[0];
	CScanSortedSequence[CScanElementCount] = copy_sequence[CScanElementCount];
	copy_sequence[0] = 100;
	NullCounter++;


	// Sort the tracks based on CScan Algorithm.
	do
	{
		for (int i = 0; i < m; i++)
		{
			if (newiteration == 1)
			{
				if (copy_sequence[i] < 100)
				{
					CScanElementCount++;
					CScanSortedSequence[CScanElementCount] = copy_sequence[i];
					previousTrackToCompare = copy_sequence[i];
					// Setting elements that have been sorted to value out of 0:99 range for identification purposes.
					copy_sequence[i] = 100;
					NullCounter++;
					// Set this variable to 0 again after scan has started at first element that has not been sorted yet.
					newiteration--;
				}
			}

			if (previousTrackToCompare < copy_sequence[i+1] && copy_sequence[i + 1]<100)
			{
				CScanElementCount++;
				CScanSortedSequence[CScanElementCount] = copy_sequence[i + 1];
				previousTrackToCompare = copy_sequence[i + 1];
				copy_sequence[i + 1] = 100;
				NullCounter++;
			}


		}

		// Setting this variable to 1 means a new scan from the first element is starting. 
		newiteration = 1;
	} while (NullCounter < m);

	printf("CSCAN Order: \n");
	for (int i = 0; i < m; i++)
	{
		printf("-%d-", CScanSortedSequence[i]);
	}

	 //Calculate seek time of sorted track array.
	for (int t = 1; t < m; t++)
	{
		int currentTrack = CScanSortedSequence[t];
		int previousTrack = CScanSortedSequence[t - 1];

		if (currentTrack > previousTrack)
		{
			seekTimeCount = seekTimeCount + (currentTrack - previousTrack);
		}
		else
		{
			seekTimeCount = seekTimeCount + (previousTrack - currentTrack);
		}
	}

	printf("\nSeek Time: %d", seekTimeCount);
}