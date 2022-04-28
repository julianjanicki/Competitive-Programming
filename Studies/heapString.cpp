// Author: Julian Janicki 2022

#include <iostream>

using std::swap;
using std::string;
using std::cout;
using std::cin;
using std::noskipws;

class Vector
{
	int size;
	int capacity;
	string* arr;

public:
	Vector()
	{
		size = 0;
		capacity = 1;
		arr = new string[1];
	}

	void add(string value)
	{
		if (size == capacity)
		{
			string* temp = new string[capacity * 2];

			for (int i = 0; i < size; i++)
			{
				temp[i] = arr[i];
			}

			capacity *= 2;
			delete[] arr;
			arr = temp;
		}

		arr[size++] = value;
	}

	void remove()
	{
		size--;
	}

	int getSize()
	{
		return size;
	}

	string& operator[](int index)
	{
		return arr[index];
	}

	const string& operator[](int index) const
	{
		return arr[index];
	}

	~Vector()
	{
		delete[] arr;
	}
};

class PriorityQ
{
	Vector vec;
	bool r;

	bool cmp(bool r, string a, string b)
	{
		if (r == true)
		{
			a = a.substr(11);
			b = b.substr(11);
			int minSize = a.size();

			if (b.size() < minSize)
			{
				minSize = b.size();
			}

			for (int i = 0; i < minSize; i++)
			{
				if (a[i] < b[i])
				{
					return 1;
				}
				else if (b[i] < a[i])
				{
					return 0;
				}
			}

			if (a.size() <= b.size())
			{
				return 1;
			}

			return 0;
		}
		else
		{
			a = a.substr(0, 10);
			b = b.substr(0, 10);
			int yearA = atoi(a.substr(6).c_str());
			int yearB = atoi(b.substr(6).c_str());

			if (yearA < yearB)
			{
				return 1;
			}
			else if (yearA > yearB)
			{
				return 0;
			}

			int monthA = atoi(a.substr(3, 2).c_str());
			int monthB = atoi(b.substr(3, 2).c_str());
			if (monthA < monthB)
			{
				return 1;
			}
			else if (monthA > monthB)
			{
				return 0;
			}

			int dayA = atoi(a.substr(0, 2).c_str());
			int dayB = atoi(b.substr(0, 2).c_str());
			if (dayA <= dayB)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}

	int parent(int index)
	{
		return (index - 1) / 2;
	}

	int leftSon(int index)
	{
		return (index * 2) + 1;
	}

	int rightSon(int index)
	{
		return (index * 2) + 2;
	}

	void heapUp(int index)
	{
		if (index == 0)
		{
			return;
		}
		
		if (cmp(r, vec[index], vec[parent(index)]))
		{
			swap(vec[index], vec[parent(index)]);
			heapUp(parent(index));
		}
	}
	
	void heapDown(int index)
	{
		int min = index;

		if (leftSon(index) < vec.getSize() && cmp(r, vec[leftSon(index)], vec[min]))
		{
			min = leftSon(index);
		}

		if (leftSon(index) < vec.getSize() && rightSon(index) < vec.getSize())
		{
			if (vec[leftSon(index)] != vec[rightSon(index)])
			{
				if (cmp(r, vec[rightSon(index)], vec[min]))
				{
					min = rightSon(index);
				}
			}
		}
		

		if (min != index)
		{
			swap(vec[min], vec[index]);
			heapDown(min);
		}
	}

public:
	PriorityQ()
	{
		r = true;
	}

	void R()
	{
		r = !r;
		for (int i = vec.getSize() - 1; i >= 0; i--)
		{
			heapDown(i);
		}
	}

	void add(string val)
	{
		vec.add(val);
		heapUp(vec.getSize() - 1);
	}

	void remove()
	{
		cout << vec[0] << '\n';
		swap(vec[0], vec[vec.getSize() - 1]);
		vec.remove();
		heapDown(0);
	}
	
	void print()
	{
		for (int i = 0; i < vec.getSize(); i++)
		{
			cout << vec[i] << '\n';
		}
	}
};

int main()
{
	PriorityQ queue;
	string in;
	cin >> in;

	while (in != "q")
	{
		if (in == "+")
		{
			int num;
			cin >> num;
			
			while (num--)
			{
				string date, name, all;
				cin >> date >> name;
				all = date + ' ' + name;
				queue.add(all);
			}
		}
		else if (in == "-")
		{
			int num;
			cin >> num;

			while (num--)
			{
				queue.remove();
			}
		}
		else if (in == "p")
		{
			queue.print();
		}
		else if (in == "r")
		{
			queue.R();
		}

		cin >> in;
	}

	return 0;
}
