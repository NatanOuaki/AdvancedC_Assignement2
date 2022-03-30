#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Worker {
	unsigned int Id;
	char* name;
	unsigned long salary;
	char Year[7];
}Worker;

typedef struct WorkerList {
	Worker* data;
	struct WorkerList* next;
}WorkerList;

void PrintWorker(Worker* worker);
void printListWorkers(WorkerList* head);
Worker* CreateWorker();
WorkerList* addWorker(WorkerList* head, Worker* w);
int indexLoop(WorkerList* head, long unsigned Id);
int indexRecursive(WorkerList* head, long unsigned Id);
WorkerList* deleteWorstWorker(WorkerList* head);
void update_worker(WorkerList* head, float precent);
WorkerList* reverse(WorkerList* head);
void freeWorkers(WorkerList* head);

void main() {
	printf("Check the Create Worker and print functions:\n");
	Worker* w1 = CreateWorker();
	Worker* w2 = CreateWorker();
	Worker* w3 = CreateWorker();
	Worker* w4 = CreateWorker();
	PrintWorker(w1);
	PrintWorker(w2);
	PrintWorker(w3);
	PrintWorker(w4);
	printf("Check the add Worker function:\n");
	WorkerList* wL = NULL;
	wL = addWorker(wL, w1);
	wL = addWorker(wL, w2);
	wL = addWorker(wL, w3);
	wL = addWorker(wL, w4);
	printListWorkers(wL);
	printf("Check the indexLoop function:\n");
	printf("The result:%d\n", indexLoop(wL, 341070217));
	printf("Check the indexRecursive function:\n");
	printf("The result:%d\n", indexRecursive(wL, 341070175, 0));
	printf("Check the delete worst Worker function:\n");
	wL = deleteWorstWorker(wL);
	printListWorkers(wL);
	printf("Check the update Worker function:\n");
	update_worker(wL, 0.5);
	printListWorkers(wL);
	printf("Check the reverse function:\n");
	wL = reverse(wL);
	printListWorkers(wL);
	printf("Check the free Worker function:\n");
	freeWorkers(wL);
}
// Create Worker Function
Worker* CreateWorker() {
	Worker* ptr = (Worker*)malloc(sizeof(Worker));
	if (!ptr) { printf("allocation failed\n"); exit(0); };
	printf("Enter Id: ");
	scanf("%u", &(ptr->Id));
	ptr->name = (char*)malloc(20);
	if (!ptr->name) { printf("allocation failed\n"); exit(0); };
	printf("Enter name: ");
	scanf("%19s", ptr->name);
	ptr->name = realloc(ptr->name, strlen(ptr->name) + 1);
	printf("Enter salary: ");
	scanf("%ul", &ptr->salary);
	printf("Enter year: ");
	scanf("%6s", ptr->Year);
	printf("\n");
	return ptr;
}


// Print Worker Function
void PrintWorker(Worker* worker) {
	if (worker == NULL) {
		printf("error\n");
		return;
	}
	printf("Id:%d\nname:%s\nsalary:%lu\nYears:%s\n\n", worker->Id, worker->name, worker->salary, worker->Year);
}


// Add Worker Function
WorkerList* addWorker(WorkerList* head, Worker* w) {
	if (w == NULL) {//check if the worker is NULL
		printf("error");
		exit(1);
	}

	WorkerList* wL = (WorkerList*)malloc(sizeof(WorkerList));
	if (wL == NULL) { printf("allocation failed"); exit(1); };
	//pointer data's that we need from the worker to the new list
	wL->data = w;
	wL->next = NULL;

	if (head == NULL) {//If the list is empty
		return wL;
	}

	if (head->next == NULL) {//If in the list have only one object
		if (head->data->salary <= w->salary) {//if the first object is bigger then the new one
			wL->next = head;
			return wL;
		}
		else {//and the opposite
			head->next = wL;
			return head;
		}
	}
	WorkerList* temp = head;//pointer to the top of the list

	while (temp->next != NULL) {
		temp = temp->next;//return the temp to head of the list
	}
	if (head->data->salary > temp->data->salary) {//check if the list is big to small
		temp = head;
		if (temp->data->salary <= w->salary) {//if the salary of new worker is bigger than salary of the salary head
			wL->next = temp;
			return wL;
		}
		while (temp->next != NULL) {
			if (temp->next->data->salary <= w->salary) {//chack the location of the new worker
				wL->next = temp->next;
				temp->next = wL;
				return head;
			}
			else {//if we are in the end of the list
				temp->next = wL;
				return head;
			}
			temp = temp->next;
		}
		temp->next = w;//if the new has the smallest salary
		return head;
	}
	else {//if the list small to big
		temp = head;
		if (temp->data->salary >= w->salary) {//if the salary of new worker is bigger than salary of the salary head
			wL->next = temp;
			return wL;
		}

		while (temp->next != NULL) {
			if (temp->next->data->salary >= w->salary) {//chack the location of the new worker
				wL->next = temp->next;
				temp->next = wL;
				return head;
			}
			else {//if we are in the end of the list
				temp->next = wL;
				return head;
			}
			temp = temp->next;
		}
		temp->next = w;//if the new worker has the biggest salary
		return head;
	}

}

//Index Loop Function 
int indexLoop(WorkerList* head, long unsigned Id) {
	int count = 0;
	while (head != NULL) {//checking if the id is in the data
		count++;
		if (head->data->Id == Id) {
			return count;
		}
		head = head->next;
	}
	return -1;// if id is not in the list
}


//Index Recursive Function 
int indexRecursive(WorkerList* head, long unsigned Id, int index) {
	if (head == NULL) {														// if id is not in the list
		return -1;
	}
	if (head->data->Id == Id) {				//checking if the id is in the data
		return index + 1;					//the index is starting from 1
	}
	return indexRecursive(head->next, Id, index + 1);
}

// Delete Worst Function
WorkerList* deleteWorstWorker(WorkerList* head) {
	WorkerList* temp = head;
	if (head == NULL)						// if the list is empty we return Null
		return NULL;

	if (head->next == NULL) {				// if there is only one object in the list we free him
		free(head);
		return NULL;
	}

	if (head->data->salary > head->next->data->salary) {//if the list is sort in a big-small order.
		while (temp->next->next != NULL) {//checking if we reach the point we want to extract
			temp = temp->next;
		}
		free(temp->next->data);
		temp->next = NULL;
	}
	else {//here is the order is from small-big
		head = head->next;
		free(temp->data);
	}
	return head;
}

// Update Worker Function
void update_worker(WorkerList* head, float precent) {
	while (head != NULL) {
		head->data->salary += (head->data->salary) * precent;
		head = head->next;
	}
}

// Reverse function
WorkerList* reverse(WorkerList* head) {
	if (head == NULL)// if the list is empty 
		return NULL;

	if (head->next == NULL)// if there is only one object in the list
		return head;

	WorkerList* top = head;
	WorkerList* mid = head->next;
	if (head->next->next == NULL) {//if there is two object in the va_list
		mid->next = top;
		top->next = NULL;
		head = mid;
		return head;
	}
	//if there is 3 objects and above
	WorkerList* bootom = head->next->next;
	while (bootom != NULL)
	{
		mid->next = top;
		top = mid;
		mid = bootom;
		bootom = bootom->next;
	}
	mid->next = top;
	head->next = NULL;
	head = mid;
	return head;
}

// Free Worker Function
void freeWorkers(WorkerList* head) {
	if (head == NULL) {//if the list of workers is empty
		return;
	}

	if (head->next == NULL) {//if there is only one worker in the list.
		free(head->data);
		free(head);
	}

	WorkerList* temp = head->next;
	while (temp != NULL) {//a situation where we have two or more workers in the list.
		free(head->data);
		free(head);
		head = temp;
		temp = temp->next;
	}
	free(head->data);
	free(head);//setting free the last worker on the list.
}

// Print List Function
void printListWorkers(WorkerList* head) {
	while (head != NULL) {
		PrintWorker(head->data);
		head = head->next;
	}
}
