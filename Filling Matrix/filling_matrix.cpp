#include<iostream>
#include<vector>
using namespace std;
class Matrix {
private:
	int _size;
	vector<vector<int>> _ele;
public:
	Matrix() = default;
	Matrix(int size, vector<vector<int>> ele) :_size(size), _ele(ele) {}
	void fill()
	{
		int count = 1;
		int row = 0;
		int line = 0;
		int block1 = _size;
		int block2 = 0;
		while (count <= _size * _size)
		{
			if (count == _size * _size)
			{
				if (_size % 2 == 0)
					_ele[_size / 2 - 1][_size / 2] = count;
				else
					_ele[_size / 2][_size / 2] = count;
				break;
			}
			for (; row != block1; ++row, count++)
			{
				if (_ele[row][line] == 0)
					_ele[row][line] = count;
			}
			row--;
			count--;
			for (; line != block1; ++line, count++)
			{
				if (_ele[row][line] == 0)
					_ele[row][line] = count;
			}
			line--;
			count--;
			for (; row >= block2; --row, count++)
			{

				if (_ele[row][line] == 0)
					_ele[row][line] = count;
			}
			row++;
			count--;
			for (; line > block2; --line, count++)
			{

				if (_ele[row][line] == 0)
					_ele[row][line] = count;
			}
			if (count == _size * _size)
			{
				if (_size % 2 == 0)
					_ele[_size / 2 - 1][_size / 2] = count;
				else
					_ele[_size / 2][_size / 2] = count;
				break;
			}
			line++;
			count--;
			block1--;
			block2++;
		}
		for (auto& i : this->_ele) {
			for (auto& j : i)
			{
				printf("%3d ", j);
			}
			cout << endl;
		}
		cout << endl << endl << endl;
	}
};
int main()
{
	int size = 0;
	vector<int> temp(size, 0);
	vector<vector<int>> temp1(size, temp);
	Matrix My_matrix(size, temp1);
	My_matrix.fill();
	return 0;
}