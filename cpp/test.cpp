#include <vector>
#include <iostream>
using namespace std;

int main()
{
	int	i;

	vector<int> v1 = {1, 2, 3};
	vector<int> v2 = {4, 5, 6};
	v1 += v2;
	i = -1;
	while (++i < v1.size())
		cout << v1[i] << "\n";
}
