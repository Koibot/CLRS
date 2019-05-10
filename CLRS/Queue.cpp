#include<iostream>

using namespace std;

#define QUEUE_SIZE 512

template<class Datatype>
class Queue {
private:
	Datatype* data;
	int front;
	int rear;
public:
	Queue();
	Queue(Queue& q);
	void Push(const Datatype& data);
	Datatype* Pop();
	bool Is_Empty() {};
	bool Is_Full();
};

template<class Datatype>
Queue<Datatype>::Queue():front(0), rear(0) {
	Datatype* q = new Datatype[QUEUE_SIZE];
	this->data = q;
}

template<class Datatype>
Queue<Datatype>::Queue(Queue& q):front(0), rear(0) {
	Datatype* data_new = new Datatype[QUEUE_SIZE];
	memcpy(data_new, q.data, sizeof(Datatype)*QUEUE_SIZE);
	this->data = data_new;
}

template<class Datatype>
void Queue<Datatype>::Push(const Datatype& d) {
	if (rear == QUEUE_SIZE) {
		if (front != 0) {
			rear = 0;
		}
		else {
			cout << "queue is full" << endl;
			return;
		}
	}
	this->data[rear] = d;
	rear++;
}

template<class Datatype>
Datatype* Queue<Datatype>::Pop() {
	Datatype* pop_data;
	if (front == rear) {
		cout << "no element in queue" << endl;
		pop_data = 0;
	}
	else {
		pop_data = &(this->data[front]);
		front++;
		
	}
	return pop_data;
}

void Queue_main() {
	Queue<int> q;
	q.Push(3);
	cout << *(q.Pop()) << endl;
	system("pause");
}