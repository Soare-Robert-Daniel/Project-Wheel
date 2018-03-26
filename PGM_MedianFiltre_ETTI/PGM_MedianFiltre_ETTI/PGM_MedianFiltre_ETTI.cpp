// PGM_MedianFiltre_ETTI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
char FileIn[50], FileOut[50], choice[50], type[4];
int dim, width, height, maxLight;
int **m, * t;

void init()
{
	cin >> choice >> dim >> FileIn >> FileOut;
}

/*
	DO: Read the data from the image. Assign the header info to global variables
	and create a matrix with value of each pixel 
*/
void readFile()
{
	cout << "Reading the file...\n";
	ifstream in(FileIn);
	in >> type; // read the file type 
	in >> width >> height >> maxLight;
	// create a matrix
	m = new int*[height]; // initialize the rows
	for (int i = 0; i < width; ++i) m[i] = new int[width]; // initialize the columns
	for (int i = 0; i < height; ++i) // read the value
		for (int j = 0; j < width; ++j)
			in >> m[i][j];
	in.close();
}

/*
	DO: Write the data to a new image. 
*/

void writeFile()
{
	cout << "Writing the file...\n";
	ofstream out(FileOut);
	out << type << '\n'; 
	out <<  width << " " << height << "\n" << maxLight << "\n";
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
			out << m[i][j] << " ";
		if( i + 2 != height) // this will prevent the appearing of black line at bottom of the image
			out << "\n";
	}
	out.close();
}

void showMatrix(int** a)
{
	cout << "#\n";
	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			cout << a[i][j] <<" ";
		}
		cout << "\n";
	}
	cout << "%\n";
}

// DO: Deal with the edge
void bording(int** &a)
{
	int dir_x = 0, dir_y = 0;
	if ((a[0][0] == -1) && (a[0][dim - 1] == -1))
		dir_x = 1;
	else if ((a[dim - 1][0] == -1) && (a[dim - 1][dim - 1] == -1))
		dir_x = -1;

	if ((a[0][0] == -1) && (a[dim - 1][0] == -1))
		dir_y = -1;
	else if ((a[0][dim - 1] == -1) && (a[dim - 1][dim - 1] == -1))
		dir_y = 1;

	if (dir_x == 0 && dir_y == 0)
		return;
	
	if (dir_x == 1)
	{
		// from south to north
		for (int row = dim - 1; row > 0; --row)
		{
			for (int col = 0; col < dim; ++col)
			{
				if (a[row][col] > -1)
				{
					// check the upper value
					if (a[row - 1][col] == -1)
					{
						a[row - 1][col] = a[row][col];
					}
				}
			}
		}
	}
	else if (dir_x == -1)
	{
		// from north to south
		for (int row = 0; row < dim-1; ++row)
		{
			for (int col = 0; col < dim; ++col)
			{
				if (a[row][col] > -1)
				{
					// check the lower value
					if (a[row + 1][col] == -1)
					{
						a[row + 1][col] = a[row][col];
					}
				}
			}
		}
	}
	
	if (dir_y == 1)
	{
		// from east to west
		
		for (int col = 0; col < dim-1; ++col)
		{
			for (int row = 0; row < dim; ++row)
			{
				if (a[row][col] > -1)
				{
					// check the upper value
					if (a[row][col+1] == -1)
					{
						a[row][col+1] = a[row][col];
					}
				}
			}
		}
	}
	else if (dir_y == -1)
	{
		// from west to east

		for (int col = dim-1; col > 0; --col)
		{
			for (int row = 0; row < dim; ++row)
			{
				if (a[row][col] > -1)
				{
					// check the upper value
					if (a[row][col-1] == -1)
					{
						a[row][col-1] = a[row][col];
					}
				}
			}
		}
	}
	
}

/*
	DO: Create the window which will gone be sorted
*/

void win(int x, int y)
{
	//cout << "Creating the window "<< x << " " << y << "\n";
	// create a matrix
	int** a = new int*[dim]; // initialize the rows
	for (int i = 0; i < dim; ++i) a[i] = new int[dim]; // initialize the columns
	int xoff = x - dim/2, yoff = y - dim/2; // offsets
	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			if ((xoff + i) < 0 || (yoff + j) < 0 || (xoff + i) >= height || (yoff + j) >= width)
			{
				a[i][j] = -1;
			}
			else a[i][j] = m[xoff + i][yoff + j];
		}
	}

	/*
	TODO:
	*/
	bording(a);
	
	//cout << "Creating the vector\n";
	int k = 0;
	t = new int[dim * dim];
	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			t[k] = a[i][j];
			k++;
		}
	}

	// delete the matrix
	for (int i = 0; i < dim; ++i) delete a[i];
	delete a;
}

/*
	DO: Sort the vector
*/

void bubble(int *& v)
{
	//cout << "Applying bubble sort...\n";
	bool ok = true;
	do {
		for (int i = 0; i < dim * dim - 1; ++i)
		{
			if (v[i] > v[i + 1])
			{
				// swap
				int tmp = v[i];
				v[i] = v[i+1];
				v[i + 1] = tmp;
			}
		}

		// check if is sorted
		ok = true;
		for (int i = 0; i < dim * dim -1; ++i)
		{
			if (v[i] > v[i + 1])
			{
				ok = false;
				break;
			}
		}
	} while (!ok);
}

/*
	Testing function
*/
/*
	DO: Merge two vector
*/

void merge_vector(int *&v, int left, int right, int mid)
{
	int i = left, j = mid + 1, k = 0;
	int *tmp_v = new int[right - left + 1];

	while (i <= mid && j <= right)
	{
		if (v[i] < v[j])
			tmp_v[k++] = v[i++];
		else
			tmp_v[k++] = v[j++];
	}

	// Check if we took all the values from i -> mid. Otherwise put them in tmp_v
	while (i <= mid)
		tmp_v[k++] = v[i++];

	// Check if we took all the values from j -> left. Otherwise put them in tmp_v
	while (j <= right)
		tmp_v[k++] = v[j++];

	// The sorting is done. Now, we put the sorted value back to 'v'
	for (i = left; i <= right; i++)
		v[i] = tmp_v[i - left];

	// Delete the vector
	delete tmp_v;
}

/*
DO: Sort the vector
*/

void merge(int *&v, int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;
		// Split the data into two half.
		merge(v, left, mid);
		merge(v, mid + 1, right);

		// Merge them to get sorted output.
		merge_vector(v, left, right, mid);
	}
}

int main()
{
	init();
	readFile();
	for (int i = 0; i < height ; ++i)
	{
		for (int j = 0; j < width ; ++j)
		{
			win(i, j);
			if (strcmp(choice, "merge"))
				merge(t, 0, dim * dim - 1);
			else bubble(t);
			m[i][j] = t[dim * dim / 2];
			if(t != NULL) delete t;
			t = NULL;
		}
	}
	writeFile();
	cout << "Done!\n";
	while (true);
	// merge 3 lena_noise.pgm test.pgm
    return 0;
}

