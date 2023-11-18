#include "Matrice34.h"

Matrice34::Matrice34()
{
	for (int i = 0; i < 12; i++)
		values[i] = 0;
}

Matrice34::Matrice34(float newVal[12])
{
	for (int i = 0; i < 12; i++)
		values[i] = newVal[i];
}

Matrice34::Matrice34(Matrice33 mat)
{

	values[0] = mat.getValues(0);
	values[1] = mat.getValues(1);
	values[2] = mat.getValues(2);
	values[3] = 0;
	
	values[4] = mat.getValues(3);
	values[5] = mat.getValues(4);
	values[6] = mat.getValues(5);
	values[7] = 0;

	values[8] = mat.getValues(6);
	values[9] = mat.getValues(7);
	values[10] = mat.getValues(8);
	values[11] = 0;
	

}

Matrice34::~Matrice34()
{
}

Matrice34 Matrice34::operator*(const Matrice34& m) const
{
	float tab[12] = {0,0,0,0,0,0,0,0,0,0,0,0 };
	Matrice34 result = Matrice34(tab);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				if (k == 3) {
					if(j == 3)
						result.values[4*i + j] += this->values[4*i + k] * 1;
				}
				else {
					result.values[4*i + j] += this->values[4*i + k] * m.values[4*k + j];
				}
			}
		}
	}

	return result;
}

Vector3D Matrice34::operator*(const Vector3D& v) const
{
	Vector3D result;
	float tab[3] = { 0,0,0 };
	for (int i = 0; i < 3; i++)
	{
		tab[i] = this->values[4 * i + 0] * v.getX() + this->values[4 * i + 1] * v.getY() + this->values[4 * i + 2] * v.getZ() + this->values[4 * i + 3] * 1;
	}
	result.setX(tab[0]);
	result.setY(tab[1]);
	result.setZ(tab[2]);

	return result;
}

Matrice34 Matrice34::Inverse()
{
	Matrice34 result;
	Matrice33 matrice33;
	Vector3D vector;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			matrice33.getValues(i*3+j) = this->values[i*4+j];
		}
	}
	vector.setX(this->values[3]);
	vector.setY(this->values[7]);
	vector.setZ(this->values[11]);

	matrice33 = matrice33.Inverse();
	vector = vector * -1;
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result.values[i * 4 + j] = matrice33.getValues(i * 3 + j);
		}
	}
	result.values[3] = vector.getX();
	result.values[7] = vector.getY();
	result.values[11] = vector.getZ();

	return result;
}

void Matrice34::SetOrientationAndPosition(const Quaternion& q, const Vector3D& pos)
{
	Vector3D vecteur = pos;
	values[0] = 1 - 2 * (q.getY() * q.getY() + q.getZ() * q.getZ());
	values[1] = 2 * (q.getX() * q.getY() + q.getW() * q.getZ());
	values[2] = 2 * (q.getX() * q.getZ() - q.getW() * q.getY());
	values[3] = vecteur.getX();

	values[4] = 2 * (q.getX() * q.getY() - q.getW() * q.getZ());
	values[5] = 1 - 2 * (q.getX() * q.getX() + q.getZ() * q.getZ());
	values[6] = 2 * (q.getY() * q.getZ() + q.getW() * q.getX());
	values[7] = vecteur.getY();

	values[8] = 2 * (q.getX() * q.getZ() + q.getW() * q.getY());
	values[9] = 2 * (q.getY() * q.getZ() - q.getW() * q.getX());
	values[10] = 1 - 2 * (q.getX() * q.getX() + q.getY() * q.getY());
	values[11] = vecteur.getZ();
}

Vector3D Matrice34::TransformPosition(const Vector3D& v)
{
	Vector3D result;
	// Appliquer la transformation de la position en utilisant la matrice
	result.setX(v.getX() * values[0] + v.getY() * values[1] + v.getZ() * values[2] + values[3]);
	result.setY(v.getX() * values[4] + v.getY() * values[5] + v.getZ() * values[6] + values[7]);
	result.setZ(v.getX() * values[8] + v.getY() * values[9] + v.getZ() * values[10] + values[11]);
	return result;
}

Vector3D Matrice34::TransformDirection(const Vector3D& v)
{
	Vector3D result;
	// Appliquer la transformation de la direction en utilisant la partie rotation de la matrice
	result.setX(v.getX() * values[0] + v.getY() * values[1] + v.getZ() * values[2]);
	result.setY(v.getX() * values[4] + v.getY() * values[5] + v.getZ() * values[6]);
	result.setZ(v.getX() * values[8] + v.getY() * values[9] + v.getZ() * values[10]);
	return result;
}
