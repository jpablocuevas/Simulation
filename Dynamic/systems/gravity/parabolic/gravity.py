import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm


def print_matrix (X : list [list [float] ]) -> None:
	
	for i in range (0, len (X), 1):
		
		for j in range (0, len (X[i]), 1):
			
			print (str(X[i][j]) + " ");
		
		print ("\n");
		
def read_data (stop : int , step : int) -> list [list [list [float] ] ]:
	
	positions : list [list [list [float] ] ] = [];
	
	X : list [list[float]] = [];
	
	x : list [float] = [];
	
	for k in range (0, stop, step):

		string = "positions" + str (k) + ".txt";
		
		f = open (string, "r");
		
		data = f.readlines ();
		
		X = [];
		
		for i in range (0, len (data), 1):
			
			x = [];
			
			temp = data[i].split ();
			
			for j in range (0, len (temp), 1):
				
				x.append (float (temp[j]));
			
			X.append (x);
			
			x = [];
		
		f.close ();
		
		positions.append (X);
	
	return positions;
	


def main (stop : int, step : int) -> None:
	
	positions : list [list[list[float]]] = [];
	
	positions = read_data (stop, step);
	
	print (positions);
	
	'''for i in range (0, len (positions), 1):
		
		fig = plt.figure ();
		
		ax = fig.add_subplot (projection='3d');

		ax.scatter(positions[i][0][0], positions[i][0][1], positions[i][0][2], marker="*", color = "rebeccapurple");
			
		ax.scatter(positions[i][1][0], positions[i][1][1], positions[i][1][2], marker="*", color = "gold");
		
		#ax.scatter(positions[i][2][0], positions[i][2][1], positions[i][2][2], marker="*", color = "forestgreen");
		
		#ax.scatter(positions[i][3][0], positions[i][3][1], positions[i][3][2], marker="*", color = "darkblue");

		ax.set_xlabel('x');
		
		ax.set_ylabel('y');
		
		ax.set_zlabel('z');
		
		fig.savefig ("position" + str (i) + ".jpg");
		
		plt.close ();'''
		
	fig = plt.figure ();
	
	ax = fig.add_subplot (projection='3d');
	
	
	for i in range (0, len (positions), 1):
	
		ax.scatter(positions[i][0][0], positions[i][0][1], positions[i][0][2], marker="*", color = "rebeccapurple");
		
		ax.scatter(positions[i][1][0], positions[i][1][1], positions[i][1][2], marker="*", color = "gold");
		
		ax.scatter(positions[i][2][0], positions[i][2][1], positions[i][2][2], marker="*", color = "darkblue");
	

	ax.set_xlabel('x');
	
	ax.set_ylabel('y');
	
	ax.set_zlabel('z');
	
	fig.savefig ("full_trajectory.jpg");
	
	plt.close ();


if ( __name__ == "__main__"):
	
	stop : int = 120;
	
	step : int = 20;
	
	main (stop, step);
	
	
