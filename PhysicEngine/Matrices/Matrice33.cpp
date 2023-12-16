#include "Matrice33.h"
#include <iostream>


Matrice33::Matrice33()
{
	for (int i = 0; i < 9; i++)
		values[i] = 0;
}

Matrice33::Matrice33(float newVal[9])
{
	for (int i = 0; i < 9; i++)
		values[i] = newVal[i];

}

Matrice33::~Matrice33()
{
}

//combinaison de transformation lineaire
Matrice33 Matrice33::operator*(const Matrice33& m) const
{
	Matrice33 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) 
		{
			for (int k = 0; k < 3; k++) {
				result.values[3 * i + j] += this->values[3*i + k] * m.values[3*k +j];
			}
		}
	}
	return result;
}

Vector3D Matrice33::operator*(const Vector3D& v) const
{
	Vector3D result = Vector3D(0,0,0);
	for (int i = 0; i < 3; i++) {
		//std::cout << result.getX() << " " << values[i] << " " << v.getX()  << " | " << v.getVector()[i] << "\n";
		result.setX(result.getX() + this->values[i] * v.getVector()[i]);
		
		//std::cout << result.getY() << " " << values[i+3] << " " << v.getX() << " | " << v.getVector()[i] << "\n";
		result.setY(result.getY() + this->values[i+3] * v.getVector()[i]);

		//std::cout << result.getZ() << " " << values[i+6] << " " << v.getX() << " | " << v.getVector()[i] << "\n";
		result.setZ(result.getZ() + this->values[i+6] * v.getVector()[i]);
	}
	return result;
}

Matrice33 Matrice33::operator*(const float& f) const
{
	Matrice33 result;
	for (int i = 0; i < 9; i++) {
		result.values[i] = this->values[i] * f;
	}
	return result;
}

Matrice33 Matrice33::Inverse()
{
	Matrice33 result;
	Matrice33 adjointe = this->getAdjointe();
	float determinant = this->getDeterminant(this->values, 9);
//	printf("determinant : %f\n", determinant);
	if (determinant != 0) {
		
		result =  adjointe * (1 / determinant);
	}
	return result;
}

Matrice33 Matrice33::Transpose()
{
	Matrice33 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			result.values[i*3+j] = this->values[j*3+i];
		}
	}
	return result;
}


void Matrice33::setOrientation(const Quaternion& q)
{
	float wx, wy, wz, xx, xy, xz, yy, yz, zz;
	wx = q.getW() * q.getX();
	wy = q.getW() * q.getY();
	wz = q.getW() * q.getZ();
	xx = q.getX() * q.getX();
	xy = q.getX() * q.getY();
	xz = q.getX() * q.getZ();
	yy = q.getY() * q.getY();
	yz = q.getY() * q.getZ();
	zz = q.getZ() * q.getZ();
	

	this->values[0] = 1 - 2 * (yy + zz);
	this->values[1] = 2 * (xy - wz);
	this->values[2] = 2 * (xz + wy);
	this->values[3] = 2 * (xy + wz);
	this->values[4] = 1 - 2 * (xx + zz);
	this->values[5] = 2 * (yz - wx);
	this->values[6] = 2 * (xz - wy);
	this->values[7] = 2 * (yz + wx);
	this->values[8] = 1 - 2 * (xx + yy);


}

float Matrice33::getDeterminant(float *tab, int n)
{
	float result = 0;
	float subtab[4];
	if (n == 4)
		return ((tab[0] * tab[3] ) - (tab[2] * tab[1]));
	else {
		for (int x = 0; x < 3; x++) {
			int subi = 0;
			for (int i = 1; i < 3; i++) {
				int subj = 0;
				for (int j = 0; j < 3; j++) {
					if (j == x)
						continue;
					subtab[subi*2 + subj] = tab[i*3+j];
					subj++;
				}
				subi++;
			}
			result += (pow(-1, x) * tab[x] * getDeterminant(subtab, n - 5));
		}
	}
	return result;
}

Matrice33 Matrice33::getAdjointe() const 
{
	Matrice33 adjointe;
	Matrice33 temp;
	Matrice33 vec;
	for (int i = 0; i < 9; i++) {
		vec.getValues(i) = this->values[i];
	}
	vec.Transpose();
		
	int sign = 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			getCofactor(vec, temp, i, j);

			sign = ((i + j) % 2 == 0) ? 1 : -1;
			// Interchanging rows and columns to get the transpose of the cofector Matrix
			adjointe.getValues(i*3+j) = (sign) * (temp.getDeterminant(&temp.getValues(0), 4));
		}
	}

	return adjointe;
}

void Matrice33::getCofactor(Matrice33& vec, Matrice33& temp, int p, int q) const{
	//std::vector<std::vector<int>> temp(3, std::vector<int>(3));
	int i = 0;
	int j = 0;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++)
		{
			//copying into temporary matix only those element which are not given row and column
			if (row != p && col != q) {
				switch (3*i+j)
				{
				case 2:
					temp.getValues(3) = vec.getValues(row + 3 * col);
					break;
				case 3:
					temp.getValues(2) = vec.getValues(row + 3 * col);
					break;
				case 4:
					temp.getValues(3) = vec.getValues(row + 3 * col);
					break;
				default:
					temp.getValues(3 * i + j) = vec.getValues(row + 3 * col);
					break;
				}
				
				j++;
			}

			if (j == 3 - 1) {
				j = 0;
				i++;
			}
		}

	}

}
