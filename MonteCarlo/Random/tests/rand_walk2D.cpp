# include <iostream>
# include <iomanip>
# include <cstdlib>
# include <fstream>

int main (void) {
	
	std:: ofstream file;
	
	file << std:: fixed << std:: setprecision (6);
	
	file.open ("rand_walk2D.txt");
	
	srand ( (unsigned) time (NULL));
	
	uint n = 100;
	
	double x0, y0, x, y, l = 0.5;
	
	x0 = (double) rand () / RAND_MAX;
	y0 = (double) rand () / RAND_MAX;
	
	for (int i = 0; i < n; i++) {
		
		/*if (rand () % 2 == 0) {
			
			x = - (double) rand () / RAND_MAX;
			y = (double) rand () / RAND_MAX;
		}
		
		else {
			
			x = (double) rand () / RAND_MAX;
			y = - (double) rand () / RAND_MAX;
		}*/
		x = (double) rand () / RAND_MAX;
		y = (double) rand () / RAND_MAX;
		
		file << x0 + l*x << ' ' << y0 + l*y << '\n';
		
		x0 = x;
		y0 = y;
	}
	
	file.close ();

	return 0;
}




