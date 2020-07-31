
#include <fstream>
#include <string>
#include <iostream>
#include <math.h>


using namespace std;
static int brcvorova;

int ** napravi_graf(int m,int n)
{

	int **matrix = new int*[n*m];
	for (int i = 0; i < n*m; i++)
	{
		matrix[i] = new int[n*m]();
	}
	brcvorova = n * m;
	return matrix;

}

int ** napravi_lavirint(int m, int n)
{

	int **matrix = new int*[m];
	for (int i = 0; i < m; i++)
	{
		matrix[i] = new int[n]();
	}
	return matrix;

}

int** Floyd(int **a)
{
	int **R = new int*[brcvorova];
	for (int i = 0; i <brcvorova; i++)
	{
		R[i] = new int[brcvorova]();
	}


	for (int i = 0; i < brcvorova; i++)
	{
		for (int j = 0; j < brcvorova; j++)
		{
			if (a[i][j] == 0) a[i][j] = 1000; 
			R[i][j] = 0;
		}
		a[i][i] = 0;
	}
	for (int k = 0; k < brcvorova; k++)
		for (int i = 0; i < brcvorova; i++)
			for (int j = 0; j < brcvorova; j++)
				if (a[i][j]>a[i][k] + a[k][j])
				{
					a[i][j] = a[i][k] + a[k][j]; R[i][j] = k;
				}
	return R;
}



int** Floydwarshall(int **a)// Odredjuje duzine najkracih puteva izmedju svaka dva cvora
{
	int i, j, k;
	for (k = 0; k<brcvorova; k++)
		for (i = 0; i<brcvorova; i++)
			if (a[i][k])
				for (j = 0; j<brcvorova; j++)
					if (a[k][j]) { a[i][j] = 1; }
	return a;
}

int odabericvor(int m_vrsta_lavirint1, int n_kolona_lavirint1, int i1, int j1)
{
	return (i1*(n_kolona_lavirint1)+j1);
}

bool proveridesni(int x, int y, int**matrix, int**graf, int m, int n) //dal da pise zid;
{
	if (y+1>=n) return true;
	else if (graf[odabericvor(m, n, x, y)][odabericvor(m, n, x, y + 1)] == 0) return true;
	else return false;

}

bool proveridonji(int x, int y, int**matrix, int**graf, int m, int n) //dal da pise zid;
{
	if (x+1>=m) return true;
	else if (graf[odabericvor(m, n, x, y)][odabericvor(m, n, x + 1, y)] == 0) return true;
	else return false;

}

void ispislavirinta(int **matrix,int **graf,int m, int n)
{ 
	cout << "LAVIRINT" << endl<<endl;
	for (int i = 0; i < 2*n+1; i++)
	{
		cout << "%";
	}
	cout << endl;
	for (int i = 0; i < 2*m; i++)
	{

		for (int j = 0; j < n; j++)
		{ 
			if (j == 0) cout << "%";
			if (i % 2 == 0)
			{
				cout << "C";
				if (proveridesni(i/2, j, matrix, graf, m, n))
					cout << "%";
				else cout << "S";
			}
			else {
			
				if (proveridonji( abs((i-1)) / 2, j, matrix, graf, m, n)) cout << "%%";
				else cout << "S%";

			}

		}
		cout << endl;
	}
	
}



int ** fajl_napravi_graf(int **A, int n)
{
	ifstream f("matrix.txt");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			f >> A[i][j];
	brcvorova = n;
	return A;
}

void obrisigraf(int ** matrix, int rows)
{
	for (int i = 0; i < rows; ++i)
		delete[] matrix[i];
	delete[] matrix;
	brcvorova = 0;
}

int** dodaj_cvor(int** m1)
{
	int **matrix = new int*[brcvorova + 1];
	for (int i = 0; i < brcvorova + 1; i++)
	{
		matrix[i] = new int[brcvorova + 1]();
	}
	for (int i = 0; i < brcvorova; i++)
	{
		for (int j = 0; j < brcvorova; j++)
		{
			matrix[i][j] = m1[i][j];
		}
	}
	brcvorova++;

	return matrix;
}

int ** obrisi_cvor(int ** m, int br)
{
	if (brcvorova != br)
	{
		for (int i = 0; i < brcvorova; i++)
		{
			for (int j = br + 1; j < brcvorova; j++)
			{
				m[i][j - 1] = m[i][j];
			}
		}
		for (int i = br + 1; i < brcvorova; i++)
		{
			for (int j = 0; j < brcvorova; j++)
			{
				m[i - 1][j] = m[i][j];
			}
		}

	}
	delete[] m[brcvorova - 1];
	brcvorova--;
	return m;

}

void dodajgranu(int ** m, int pocetni, int krajnji)
{
	if (pocetni < 0 || krajnji < 0 || pocetni >= brcvorova || krajnji >= brcvorova) cout << "Nemoguce je dodati granu jer zadati cvor ne postoji" << endl;
	else m[pocetni][krajnji] = m[krajnji][pocetni] = 1;

}

void ispisgrafa(int ** m)
{
	cout << "GRAF-Matricna reprezentacija" << endl << endl;
	if (brcvorova == 0) cout << "Graf ne postoji" << endl;
	else
		for (int i = 0; i < brcvorova; i++)
		{
			for (int j = 0; j < brcvorova; j++)
			{
				cout << m[i][j] << " ";
			}
			cout << endl;
		}
	cout << endl;
}

void ispismatrice_susednosti(int ** m)
{
	cout << "Matrica doseznosti:" << endl << endl;
	if (brcvorova == 0) cout << "Matrica susednosti ne postoji" << endl;
	else
		for (int i = 0; i < brcvorova; i++)
		{
			for (int j = 0; j < brcvorova; j++)
			{
				cout << m[i][j] << " ";
			}
			cout << endl;
		}
	cout << endl;
}


void ispisimatricu(int **matrix, int m,int n)
{   
	for (int i = 0; i <m ; i++)
	{	
		for (int j = 0; j < n; j++)
		{
			cout << matrix[i][j]<<" ";

		}
		cout << endl;
	}
}

void printPath(int **put,int**lavirint,int i, int j,int m,int n) //i pocetak j kraj
{
	int xkoordinata;
	int ykoordinata;
	if (put[i][j])
	{
		
		int brojacx = 0;
		printPath(put, lavirint, i, put[i][j], m, n);
		
		for (int p = 0; p < m; p++)
		{
			for (int k = 0; k < n; k++)
			{
				
				if (brojacx++ == put[i][j])
				{
					xkoordinata = p;
					ykoordinata = k;
				}
						

			}
		}
		cout << "(" << xkoordinata << ", " << ykoordinata << ")-> ";
	//	cout << put[i][j] << "->";
		printPath(put,lavirint, put[i][j], j,m,n);
	}
}

void kopirajmatricu(int **matrix,int**graf )
{
	for (int i = 0; i < brcvorova; i++)
	{
		for (int j = 0; j < brcvorova; j++)
		{
			matrix[i][j] = graf[i][j];
		}
	}
}

int** otvoriput(int x, int y, int **graf)
{
	graf[x][y] = graf[y][x] = 1;
	return graf;
}
int** zatvoriput(int x, int y, int **graf)
{
	graf[x][y] = graf[y][x] = 0;
	return graf;
}

bool moguceizaci(int x, int y, int **matrica_susednosti)
{
	if (matrica_susednosti[x][y]) return true;
	else return false;
}

int main()
{
	int x1, x2, y1, y2;
	int ulaz_x, ulaz_y, izlaz_x, izlaz_y;
	int k,brojacx=0;
	int m_vrsta_lavirint, n_kolona_lavirint;
	cout << "Unesite velicinu lavirinta; m vrsta n kolona" << endl;
	cin >> m_vrsta_lavirint >> n_kolona_lavirint;
	int	**graf = napravi_graf(m_vrsta_lavirint, n_kolona_lavirint);
	int **put = napravi_graf(m_vrsta_lavirint, n_kolona_lavirint);
	int **matrica_susednosti = napravi_lavirint(brcvorova, brcvorova);
	int **matrix = napravi_lavirint(m_vrsta_lavirint, n_kolona_lavirint);
	//graf = fajl_napravi_graf(graf, m_vrsta_lavirint*n_kolona_lavirint);
	ispisgrafa(graf);	
	ispisimatricu(matrix, m_vrsta_lavirint, n_kolona_lavirint);
	cout << endl;
	ispislavirinta(matrix, graf, m_vrsta_lavirint, n_kolona_lavirint);

	while (1)
	{
		cout << "Unos iz konzole:" << endl;
		cout << "Pritisnite 1 ako zelite da otvorite put" << endl;
		cout << "Pritisnite 2 ako zelite da zatvorite put" << endl;
		cout << "Pritisnite 3 za zadavanje pocetka i kraja lavirinta" << endl;
		cout << "Pritisnite 0 za kraj prorgama" << endl;
		cin >> k;

		switch (k)
		{
		case 1:
			cout << "Unesite koji put hocete da otvorite kao koordinate" << endl;
			cout << "x1:->"; cin >> x1; cout << "y1:->"; cin >> y1; cout << endl;
			cout << "x2:->"; cin >> x2; cout << "y2:->"; cin >> y2; cout << endl;
			graf = otvoriput(odabericvor(m_vrsta_lavirint, n_kolona_lavirint, x1, y1), odabericvor(m_vrsta_lavirint, n_kolona_lavirint, x2, y2), graf);
			ispisgrafa(graf);
			ispislavirinta(matrix, graf, m_vrsta_lavirint, n_kolona_lavirint);
			break;
		case 2:
			cout << "Unesite koji put hocete da zatvorite kao koordinate" << endl;
			cout << "x1:->"; cin >> x1; cout << "y1:->"; cin >> y1; cout << endl;
			cout << "x2:->"; cin >> x2; cout << "y2:->"; cin >> y2; cout << endl;
			graf = zatvoriput(odabericvor(m_vrsta_lavirint, n_kolona_lavirint, x1, y1), odabericvor(m_vrsta_lavirint, n_kolona_lavirint, x2, y2), graf);
			ispisgrafa(graf);
			ispislavirinta(matrix, graf, m_vrsta_lavirint, n_kolona_lavirint);
			break;
		case 3:
			cout << "Unesite koji ulaz i izlaz kao koordinate" << endl;
			cout << "ulaz x:->"; cin >> ulaz_x; cout << "ulaz y:->"; cin >> ulaz_y; cout << endl;
			cout << "izlaz x:->"; cin >> izlaz_x; cout << "izlaz y:->"; cin >> izlaz_y; cout << endl;
			kopirajmatricu(matrica_susednosti,graf);
			//ispisgrafa(graf);
			//ispismatrice_susednosti(matrica_susednosti);
			matrica_susednosti = Floydwarshall(matrica_susednosti);
			//ispisgrafa(graf);
			//ispismatrice_susednosti(matrica_susednosti);
			if (moguceizaci(odabericvor(m_vrsta_lavirint, n_kolona_lavirint, ulaz_x, ulaz_y), odabericvor(m_vrsta_lavirint, n_kolona_lavirint, izlaz_x, izlaz_y), matrica_susednosti))
			{
				cout << "Moguce je stici od ulaza do izlaza" << endl;
				//ispisgrafa(graf);
				put = Floyd(graf);
				//ispismatrice_susednosti(put);
				int i = odabericvor(m_vrsta_lavirint, n_kolona_lavirint, ulaz_x, ulaz_y);
				int j = odabericvor(m_vrsta_lavirint, n_kolona_lavirint, izlaz_x, izlaz_y);
				int xkoordinata, ykoordinata;
				brojacx = 0;
				for (int p = 0; p <m_vrsta_lavirint; p++)
				{
					for (int k = 0; k < n_kolona_lavirint; k++)
					{
						
						if (brojacx++ == i)
						{
							xkoordinata = p;
							ykoordinata = k ;
						}


					}
				}
				cout << "(" << xkoordinata << ", " << ykoordinata << ")-> ";
				
				brojacx = 0;
				printPath(put, matrix, i, j, m_vrsta_lavirint, n_kolona_lavirint);

				for (int p = 0; p <m_vrsta_lavirint; p++)
				{
					for (int k = 0; k < n_kolona_lavirint; k++)
					{

						if (brojacx++ == j)
						{
							xkoordinata = p;
							ykoordinata = k ;
						}


					}
				}
				cout << "(" << xkoordinata << ", " << ykoordinata << ")-> " << endl;


				//cout << j<<endl;
				;
			
			}

			else cout << "Nije moguce izaci iz lavirinta" << endl;
			break;

		case 0:
			exit(14);

		}
	}
	
	system("pause");
	
	

}